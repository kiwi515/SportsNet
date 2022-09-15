#ifndef SPORTSNET_LOBBY_SCENE_H
#define SPORTSNET_LOBBY_SCENE_H
#include "SportsNetBaseScene.hpp"
#include "types.h"

#include <RPSystem/RPSysScene.h>

namespace spnet {

class LobbyLytPlayerList;

/**
 * @brief Online multiplayer lobby scene
 */
class LobbyScene : public SportsNetBaseScene {
private:
    //! Scene states
    enum Sequence {
        SEQ_ASK_HOST,
        SEQ_JOIN_SERVER,
        SEQ_WAIT_LOBBY,
        SEQ_MAX,
    };

    typedef void (LobbyScene::*SequenceProc)();

public:
    LobbyScene();
    virtual ~LobbyScene();
    virtual void OnConfigure();
    virtual void OnLoadResource();
    virtual void OnReset();
    virtual void OnCalculate();
    virtual void OnExit();
    virtual void OnUserDraw();

    //! Player state callbacks
    static void OnPlayerConnect(void* arg, u32 player);
    static void OnPlayerDisconnect(void* arg, u32 player);

    //! Host/Client select sequence
    void CalcSeqAskHost();
    void DrawSeqAskHost();
    //! Join host server sequence
    void CalcSeqJoinServer();
    void DrawSeqJoinServer();
    //! Wait in lobby sequence
    void CalcSeqWaitLobby();
    void DrawSeqWaitLobby();

private:
    //! Scene state
    Sequence mSequence;

    //! Lobby text
    RPSysMessage* mLobbyMessage;

    //! Player list layout
    LobbyLytPlayerList* mPlayerListLyt;

    //! Sequence logic
    static const SequenceProc sSequenceCalcProc[SEQ_MAX];
    //! Sequence rendering
    static const SequenceProc sSequenceDrawProc[SEQ_MAX];
};

} // namespace spnet

#endif