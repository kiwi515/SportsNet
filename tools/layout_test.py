# For use with layout test scene

import socket
from os import system, path

SEQ_RECV_FILE_SIZE = bytes([0, 0, 0, 3])
SEQ_RECV_FILE_CHUNK = bytes([0, 0, 0, 4])
SEQ_RECV_LYT_NAME = bytes([0, 0, 0, 5])

# Also change this in LytTestScene
FILE_CHUNK_SIZE = 1024

SOCK = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


def is_valid_addr_ipv4(ip):
    try:
        socket.inet_aton(ip)
    except Exception:
        return False
    return True


def is_valid_port_ipv4(port):
    try:
        port_int = int(port)
        return port_int >= 0 and port_int <= 65535
    except Exception:
        return False


def is_sock_connected():
    try:
        return SOCK.getpeername() != None
    except Exception:
        return False


def handle_command(cmd, args):
    cmd = cmd.casefold()
    args = [arg.casefold() for arg in args]

    # Disconnect from server
    if cmd == "close" or cmd == "disconnect":
        SOCK.close()
    # Connect to server
    elif cmd == "connect" and len(args) == 2:
        SOCK.close()
        if not is_valid_addr_ipv4(args[0]):
            print("Invalid IP.")
            return
        if not is_valid_port_ipv4(args[1]):
            print("Invalid port.")
            return
        SOCK.connect(args[0], int(args[1]))
    # Upload archive
    elif cmd == "send" and len(args) == 1:
        src = args[0].replace("\\", "/")

        if not src.endswith(".d"):
            print("Invalid arc folder (missing .d suffix)")
        elif not path.isdir(src):
            print("Arc folder does not point to a directory")

        # Trim .d extension
        dst = src[:len(src) - 2]

        # Repack assets
        system(
            f"wszst CREATE {src} --DEST {dst} --rm-dest")

        # Send archive file size
        SOCK.send(SEQ_RECV_FILE_SIZE)
        SOCK.send(path.getsize(dst).to_bytes(4, byteorder="big"))

        # Read file contents
        with open(dst, "rb") as f:
            arc = f.read()
        # Send chunks
        num_chunks = len(arc) // FILE_CHUNK_SIZE
        for i in range(num_chunks):
            start = i * FILE_CHUNK_SIZE
            end = (i + 1) * FILE_CHUNK_SIZE
            SOCK.send(SEQ_RECV_FILE_CHUNK)
            SOCK.send(arc[start:end])
        # Send extra data (if applicable)
        if len(arc) % FILE_CHUNK_SIZE != 0:
            last = num_chunks * FILE_CHUNK_SIZE
            assert len(arc) - last <= FILE_CHUNK_SIZE, "Last chunk too big?"
            SOCK.send(SEQ_RECV_FILE_CHUNK)
            SOCK.send(arc[last:])
    # Load layout
    elif cmd == "load" and len(args) == 1:
        SOCK.send(SEQ_RECV_LYT_NAME)
        SOCK.send(args[0].encode())
    else:
        print("Invalid command/arguments.")


def main():
    # Connect to server
    # while not is_sock_connected():
    #     # Input server IP
    #     ip = ""
    #     while not is_valid_addr_ipv4(ip):
    #         ip = input("Enter server IPv4:")

    #     # Input server port
    #     port = ""
    #     while not is_valid_port_ipv4(port):
    #         port = input("Enter server port:")
    #     port = int(port)

    #     SOCK.connect((ip, port))

    SOCK.connect(("192.168.0.187", 12345))

    if is_sock_connected():
        print("Connected to server.")

    # Accept commands
    while is_sock_connected():
        # Parse line from console
        line = input()
        tokens = line.split()

        if len(tokens) == 1:
            handle_command(tokens[0], "")
        elif len(tokens) > 1:
            handle_command(tokens[0], tokens[1:])


if __name__ == "__main__":
    main()
