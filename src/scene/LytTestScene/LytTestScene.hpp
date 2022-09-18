#ifndef SPORTSNET_LYT_TEST_SCENE_H
#define SPORTSNET_LYT_TEST_SCENE_H
#include "Socket.hpp"
#include "SportsNetBaseScene.hpp"
#include "types.h"

namespace spnet {

class LytTestScene : public SportsNetBaseScene {
private:
    //! Client commands
    enum NetCommand {
        CMD_RECV_FILE_SIZE,
        CMD_RECV_FILE_CHUNK,
        CMD_RECV_LYT_NAME
    };

    //! Scene states
    enum Sequence {
        SEQ_NO_PEER,
        SEQ_RECV_SEQ,
        SEQ_CLOSE,
        SEQ_RECV_FILE_SIZE,
        SEQ_RECV_FILE_CHUNK,
        SEQ_RECV_LYT_NAME,
        SEQ_MAX
    };

    typedef void (LytTestScene::*SequenceProc)();

public:
    LytTestScene();
    virtual ~LytTestScene();
    virtual void OnConfigure();
    virtual void OnLoadResource();
    virtual void OnReset();
    virtual void OnCalculate();
    virtual void OnExit();
    virtual void OnUserDraw();

    void CalcSeqNoPeer();
    void CalcSeqRecvSeq();
    void CalcSeqClose();
    void CalcSeqRecvFileSize();
    void CalcSeqRecvFileChunk();
    void CalcSeqRecvLytName();

    void FreeArchive();
    void FreeLayout();

private:
    //! Scene state
    Sequence mSequence;

    //! Server socket
    Socket mSocket;
    //! Server IP
    u32 mIP;
    //! Server port
    u16 mPort;
    //! Socket with client
    Socket* mClient;

    //! Current archive file
    u8* mArcBuffer;
    //! Current archive filesize
    u32 mArcSize;
    //! Bytes read so far of archive
    u32 mArcBytesRead;

    //! Active layout
    RPSysLayout* mLayout;
    //! Layout accessor
    RPSysLytResAccessor* mAccessor;

    //! Data chunk size
    static const s32 scChunkSize = 1024;

    //! Sequence logic
    static const SequenceProc sSequenceCalcProc[SEQ_MAX];
};

} // namespace spnet

#endif