#ifndef SPORTSNET_LYT_TEST_SCENE_H
#define SPORTSNET_LYT_TEST_SCENE_H
#include "Socket.hpp"
#include "SportsNetBaseScene.hpp"
#include "types.h"

namespace spnet {

class LytTestScene : public SportsNetBaseScene {
private:
    enum NetCommand {
        CMD_CLOSE = -1,
        CMD_RECV_FILE_SIZE,
        CMD_RECV_FILE_CHUNK,
        CMD_RECV_LYT_NAME
    };

    enum State {
        STATE_NO_PEER,
        STATE_CHECK_CMD,
        STATE_CMD_CLOSE,
        STATE_CMD_RECV_FILE_SIZE,
        STATE_CMD_RECV_FILE_CHUNK,
        STATE_CMD_RECV_LYT_NAME
    };

public:
    LytTestScene();
    virtual ~LytTestScene();
    virtual void OnConfigure();
    virtual void OnLoadResource();
    virtual void OnReset();
    virtual void OnCalculate();
    virtual void OnExit();
    virtual void OnUserDraw();

private:
    //! Scene state
    State mState;

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

    //! Data chunk size
    static const s32 scChunkSize = 1024;
};

} // namespace spnet

#endif