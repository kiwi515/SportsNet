#include "LytTestScene.hpp"

#include <EGG/core/eggHeap.h>
#include <RPAudio/RPSndAudioMgr.h>
#include <RPGraphics/RPGrpRenderer.h>
#include <RPKernel/RPSysLayout.h>
#include <RPKernel/RPSysLytResAccessor.h>
#include <TRK/__mem.h>

namespace spnet {

LytTestScene::LytTestScene()
    : mSequence(SEQ_NO_PEER),
      mSocket(Socket::SOCK_STREAM),
      mIP(0xFF000001),
      mPort(12345),
      mClient(NULL),
      mArcBuffer(NULL),
      mArcSize(0),
      mArcBytesRead(0),
      mLayout(NULL),
      mAccessor(NULL) {
    // Socket is non-blocking to avoid game halt
    mSocket.SetBlocking(false);
}

LytTestScene::~LytTestScene() {
    // Disconnect from client
    mSocket.Disconnect();
    delete mClient;
    mClient = NULL;
    // Free memory
    FreeArchive();
    FreeLayout();
}

void LytTestScene::OnConfigure() {
    // Create accessor
    mAccessor = RPSysLytResAccessor::create(NULL);
    MATO_ASSERT(mAccessor != NULL);

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
    // Run sequence logic
    MATO_ASSERT(mSequence < SEQ_MAX);
    (this->*sSequenceCalcProc[mSequence])();

    // Always update layout if it exists
    if (mLayout != NULL) {
        mLayout->calc();
    }
}

void LytTestScene::OnExit() {}

void LytTestScene::OnUserDraw() {
    const u8* oct = reinterpret_cast<const u8*>(&mIP);

    switch (mSequence) {
    // Show server IP/port
    case SEQ_NO_PEER:
        MATO_ASSERT_EX(mClient == NULL, "Client cannot be null: Sequence %d",
                       mSequence);
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

    // Always draw layout if it exists
    if (mLayout != NULL) {
        if (RPGrpRenderer::GetDrawPass() == RPGrpRenderer::DRAWPASS_LYT &&
            RPGrpRenderer::D_804BF615 == 1) {
            mLayout->draw();
        }
    }
}

/**
 * @brief Wait for client
 */
void LytTestScene::CalcSeqNoPeer() {
    MATO_ASSERT(mClient == NULL);

    // Accept incoming connection
    mClient = mSocket.Accept();
    if (mClient != NULL) {
        mClient->SetBlocking(false);
        // Check for tasks
        mSequence = SEQ_RECV_SEQ;
        MATO_LOG("Peer accepted, waiting for task");
    }
}

/**
 * @brief Receive sequence from client
 */
void LytTestScene::CalcSeqRecvSeq() {
    MATO_ASSERT(mClient != NULL);

    u32 seq;
    const s32 read = mClient->Recieve(&seq, sizeof(seq));

    // Handle errors
    if (read < 0) {
        if (read != -Socket::EAGAIN) {
            MATO_LOG_EX("Error while receiving command: %s",
                        Socket::GetErrorString(read));
            mSequence = SEQ_CLOSE;
        }
    }
    // 0 bytes read (probably disconnected client?)
    else if (read == 0) {
        mSequence = SEQ_CLOSE;
    }
    // This isn't a valid packet
    else if (read != sizeof(seq)) {
        MATO_LOG_EX("Invalid command packet size: %d", read);
        mSequence = SEQ_CLOSE;
    }
    // Successful read, but invalid sequence
    else if (seq > SEQ_MAX) {
        MATO_LOG_EX("Invalid seq: %d", seq);
        mSequence = SEQ_CLOSE;
    }
    // Valid sequence
    else {
        mSequence = static_cast<Sequence>(seq);
    }
}

/**
 * @brief Close connection
 */
void LytTestScene::CalcSeqClose() {
    MATO_ASSERT(mClient != NULL);

    // Disconnect client
    delete mClient;
    mClient = NULL;
    mSequence = SEQ_NO_PEER;

    // Free memory
    FreeArchive();
    FreeLayout();
}

/**
 * @brief Receive file size from client
 */
void LytTestScene::CalcSeqRecvFileSize() {
    MATO_ASSERT(mClient != NULL);

    u32 size;
    const s32 read = mClient->Recieve(&size, sizeof(size));

    // Handle errors
    if (read < 0) {
        if (read != -Socket::EAGAIN) {
            MATO_LOG_EX("Error while receiving file size: %s",
                        Socket::GetErrorString(read));
            mSequence = SEQ_CLOSE;
        }
    }
    // 0 bytes read (probably disconnected client?)
    else if (read == 0) {
        mSequence = SEQ_CLOSE;
    }
    // This isn't a valid packet
    else if (read != sizeof(size)) {
        MATO_LOG_EX("Invalid file size packet size: %d", read);
        mSequence = SEQ_CLOSE;
    }
    // Successful read
    else {
        // Delete current archive
        FreeArchive();

        // Set new archive size
        mArcSize = size;
        MATO_WARN_EX(mArcSize > 1000000, "Archive size is over 1MB. (%.2f MB)",
                     mArcSize / 1000000.0f);

        // Allocate archive buffer (from sCurrentHeap)
        MATO_LOG_EX("Allocating arc buffer (%d bytes)", mArcSize);
        mArcBuffer = static_cast<u8*>(EGG::Heap::alloc(mArcSize, 32, NULL));

        // Archive is too big
        if (mArcBuffer == NULL) {
            MATO_LOG_EX("Failed to allocate arc buffer (%d bytes)", mArcSize);
            mSequence = SEQ_CLOSE;
            return;
        }
    }

    // Check for tasks
    mSequence = SEQ_RECV_SEQ;
}

/**
 * @brief Receive a chunk of the archive (<= scChunkSize)
 */
void LytTestScene::CalcSeqRecvFileChunk() {
    MATO_ASSERT(mClient != NULL);

    // There must be contents missing
    MATO_ASSERT(mArcBytesRead < mArcSize);

    // Attempt to receive chunk
    const s32 read = mClient->Recieve(mArcBuffer + mArcBytesRead, scChunkSize);
    MATO_ASSERT_EX(read <= scChunkSize, "WHY?????");

    // Handle error
    if (read < 0) {
        if (read != -Socket::EAGAIN) {
            MATO_LOG_EX("Error while receiving file chunk: %s",
                        Socket::GetErrorString(read));
            mSequence = SEQ_CLOSE;
        }
    }
    // 0 bytes read (probably disconnected client?)
    else if (read == 0) {
        mSequence = SEQ_CLOSE;
    }
    // Successful read
    else {
        mArcBytesRead += read;
    }

    mSequence = SEQ_RECV_SEQ;
}

/**
 * @brief Load layout specified by client
 */
void LytTestScene::CalcSeqRecvLytName() {
    MATO_ASSERT(mClient != NULL);
    MATO_ASSERT(mArcBytesRead <= mArcSize);

    // Incomplete transfer
    if (mArcBytesRead != mArcSize) {
        MATO_LOG("Transfer incomplete, cannot load layout");
        mSequence = SEQ_CLOSE;
        return;
    }

    // Read layout name
    char lytName[255];
    memset(lytName, 0, sizeof(lytName));
    const s32 read = mClient->Recieve(lytName, sizeof(lytName));

    // Handle errors
    if (read < 0) {
        if (read != -Socket::EAGAIN) {
            MATO_LOG_EX("Error while receiving command: %s",
                        Socket::GetErrorString(read));
            mSequence = SEQ_CLOSE;
        }
    }
    // 0 bytes read (probably disconnected client?)
    else if (read == 0) {
        mSequence = SEQ_CLOSE;
    }
    // Successful read
    else {
        // Delete old layout + accessor
        FreeLayout();

        // Mount archive
        mAccessor = RPSysLytResAccessor::create(NULL);
        MATO_ASSERT(mAccessor != NULL);
        mAccessor->mountArchive(mArcBuffer, NULL);

        // Attempt to load layout
        mLayout = RPSysLayout::create(NULL, mAccessor, lytName);
        if (mLayout == NULL) {
            MATO_LOG_EX("Could not load layout %s", lytName);
        }

        // Wait for further tasks
        mSequence = SEQ_RECV_SEQ;
    }
}

/**
 * @brief Free archive data
 */
void LytTestScene::FreeArchive() {
    mArcSize = 0;
    mArcBytesRead = 0;
    delete[] mArcBuffer;
    mArcBuffer = NULL;
}

/**
 * @brief Free layout and accessor
 */
void LytTestScene::FreeLayout() {
    delete mLayout;
    mLayout = NULL;
    delete mAccessor;
    mAccessor = NULL;
}

//! Sequence logic
const LytTestScene::SequenceProc
    LytTestScene::sSequenceCalcProc[LytTestScene::SEQ_MAX] = {
        // clang-format off
        &LytTestScene::CalcSeqNoPeer,
        &LytTestScene::CalcSeqRecvSeq,
        &LytTestScene::CalcSeqClose,
        &LytTestScene::CalcSeqRecvFileSize,
        &LytTestScene::CalcSeqRecvFileChunk,
        &LytTestScene::CalcSeqRecvLytName
        // clang-format on
};

} // namespace spnet