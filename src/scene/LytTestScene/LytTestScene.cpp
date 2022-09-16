#include "LytTestScene.hpp"

#include <EGG/core/eggHeap.h>
#include <RPAudio/RPSndAudioMgr.h>
#include <RPGraphics/RPGrpRenderer.h>
#include <RPKernel/RPSysLayout.h>
#include <RPKernel/RPSysLytResAccessor.h>

namespace spnet {

LytTestScene::LytTestScene()
    : mState(STATE_NO_PEER),
      mSocket(Socket::SOCK_STREAM),
      mIP(0xFF000001),
      mPort(12345),
      mClient(NULL),
      mArcBuffer(NULL),
      mArcSize(0),
      mArcBytesRead(0),
      mLayout(NULL) {
    mSocket.SetBlocking(false);
}

LytTestScene::~LytTestScene() {
    mSocket.Disconnect();
    delete mClient;
    mClient = NULL;
    delete mLayout;
    mLayout = NULL;
}

void LytTestScene::OnConfigure() {
    // Start server
    MATO_ASSERT(mSocket.Bind(mPort));
    MATO_ASSERT(mSocket.Listen());
    mIP = mSocket.GetHostIP();

    // Print server info to console
    const u8* oct = reinterpret_cast<const u8*>(&mIP);
    MATO_LOG_EX("Listening on %d.%d.%d.%d, port %d", oct[0], oct[1], oct[2],
                oct[3], mPort);
}

void LytTestScene::OnLoadResource() {}

void LytTestScene::OnReset() { RPSndAudioMgr::getInstance()->stopAllSoud(); }

void LytTestScene::OnCalculate() {
    s32 read;

    switch (mState) {
    // Accept incoming connection
    case STATE_NO_PEER:
        MATO_ASSERT(mClient == NULL);
        mClient = mSocket.Accept();
        if (mClient != NULL) {
            mClient->SetBlocking(false);
            mState = STATE_CHECK_CMD;
        }
        break;
    // See what client is trying to do (check command)
    case STATE_CHECK_CMD:
        MATO_ASSERT(mClient != NULL);

        u32 cmd;
        read = mClient->Recieve(&cmd, sizeof(cmd));

        // Handle errors
        if (read < 0) {
            if (read != -Socket::EAGAIN) {
                MATO_LOG_EX("Error while receiving command: %s",
                            Socket::GetErrorString(read));
                mState = STATE_CMD_CLOSE;
            }
        } else if (read == 0) {
            mState = STATE_CMD_CLOSE;
        } else if (read != sizeof(cmd)) {
            MATO_LOG_EX("Invalid command packet size: %d", read);
            mState = STATE_CMD_CLOSE;
        }
        // Successful read
        else {
            switch (cmd) {
            // Close client connection
            case CMD_CLOSE:
                mState = STATE_CMD_CLOSE;
                break;
            case CMD_RECV_FILE_SIZE:
                mState = STATE_CMD_RECV_FILE_SIZE;
                break;
            case CMD_RECV_FILE_CHUNK:
                mState = STATE_CMD_RECV_FILE_CHUNK;
                break;
            case CMD_RECV_LYT_NAME:
                mState = STATE_CMD_RECV_LYT_NAME;
            default:
                MATO_LOG_EX("Invalid command: %d", cmd);
            }
        }
        break;
    // Disconnect from client
    case STATE_CMD_CLOSE:
        mClient->Disconnect();
        mClient = NULL;
        mState = STATE_NO_PEER;
        // Delete current archive
        delete mLayout;
        mLayout = NULL;
        delete[] mArcBuffer;
        mArcBuffer = NULL;
        mArcSize = 0;
        mArcBytesRead = 0;
        break;
    // Client is sending the archive size
    case STATE_CMD_RECV_FILE_SIZE:
        u32 size;
        read = mClient->Recieve(&size, sizeof(size));
        // Handle errors
        if (read < 0) {
            if (read != -Socket::EAGAIN) {
                MATO_LOG_EX("Error while receiving file size: %s",
                            Socket::GetErrorString(read));
                mState = STATE_CMD_CLOSE;
            }
        } else if (read == 0) {
            mState = STATE_CMD_CLOSE;
        } else if (read != sizeof(size)) {
            MATO_LOG_EX("Invalid file size packet size: %d", read);
            mState = STATE_CMD_CLOSE;
        }
        // Successful read
        else {
            // Delete current archive
            delete mLayout;
            mLayout = NULL;
            mArcSize = 0;
            delete[] mArcBuffer;
            mArcBuffer = NULL;
            mArcBytesRead = 0;

            mArcSize = size;
            MATO_WARN_EX(mArcSize > 1000000,
                         "Archive size is over 1MB. (%.2f MB)",
                         mArcSize / 1000000.0f);
            MATO_LOG_EX("Allocating arc buffer (%d bytes)", mArcSize);
            // Allocate from sCurrentHeap
            mArcBuffer = static_cast<u8*>(EGG::Heap::alloc(mArcSize, 32, NULL));
            MATO_ASSERT(mArcBuffer != NULL);
        }
        mState = STATE_CHECK_CMD;
        break;
    // Client is sending an chunk of the archive (<= scChunkSize)
    case STATE_CMD_RECV_FILE_CHUNK:
        // There must be contents missing
        MATO_ASSERT(mArcBytesRead < mArcSize);

        // Attempt to receive chunk
        read = mClient->Recieve(mArcBuffer + mArcBytesRead, scChunkSize);

        // Handle error
        if (read < 0) {
            if (read != -Socket::EAGAIN) {
                MATO_LOG_EX("Error while receiving file chunk: %s",
                            Socket::GetErrorString(read));
                mState = STATE_CMD_CLOSE;
            }
        } else if (read == 0) {
            mState = STATE_CMD_CLOSE;
        }
        // Successful read
        else {
            mArcBytesRead += read;
        }

        mState = STATE_CHECK_CMD;
        break;
    case STATE_CMD_RECV_LYT_NAME:
        MATO_ASSERT_EX(mArcBytesRead == mArcSize, "Transfer incomplete");

        // Read layout name
        char lytName[128] = {};
        read = mClient->Recieve(lytName, sizeof(lytName));

        // Handle error
        if (read < 0) {
            if (read != -Socket::EAGAIN) {
                MATO_LOG_EX("Error while receiving file chunk: %s",
                            Socket::GetErrorString(read));
                mState = STATE_CMD_CLOSE;
            }
        } else if (read == 0) {
            mState = STATE_CMD_CLOSE;
        }
        // Successful read
        else {
            // Delete old layout
            delete mLayout;
            mLayout = NULL;

            // Mount archive
            RPSysLytResAccessor* accessor = RPSysLytResAccessor::create(NULL);
            accessor->mountArchive(mArcBuffer, NULL);
            mLayout = RPSysLayout::create(NULL, accessor, lytName);
            MATO_ASSERT(mLayout != NULL);
            delete accessor;
        }
        break;
    }

    if (mLayout != NULL) {
        mLayout->calc();
    }
}

void LytTestScene::OnExit() {}

void LytTestScene::OnUserDraw() {
    const u8* oct = reinterpret_cast<const u8*>(&mIP);

    switch (mState) {
    // Show server IP/port
    case STATE_NO_PEER:
        MATO_ASSERT(mClient == NULL);
        PrintfOutline(0.0f, 80.0f, 2.0f, true, mato::scColorWhite,
                      mato::scColorBlack, "Layout Test");

        PrintfOutline(0.0f, 0.0f, 2.0f, true, mato::scColorWhite,
                      mato::scColorBlack, "Listening on %d.%d.%d.%d, port %d",
                      oct[0], oct[1], oct[2], oct[3], mPort);
        break;
    default:
        // Print archive transmission process
        if (mLayout == NULL) {
            if (mArcBytesRead != 0) {
                PrintfOutline(0.0f, 0.0f, 2.0f, true, mato::scColorWhite,
                              mato::scColorBlack,
                              "Waiting for archive... (%.2f KB/%.2f KB)",
                              mArcBytesRead / 1024.0f, mArcSize / 1024.0f);
            } else {
                PrintfOutline(0.0f, 0.0f, 2.0f, true, mato::scColorWhite,
                              mato::scColorBlack, "Waiting for archive...");
            }
        }
        break;
    }

    if (mLayout != NULL) {
        if (RPGrpRenderer::GetDrawPass() == RPGrpRenderer::DRAWPASS_LYT &&
            RPGrpRenderer::D_804BF615 == 1) {
            mLayout->draw();
        }
    }
}

} // namespace spnet