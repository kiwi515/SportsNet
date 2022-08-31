#ifndef RP_AUDIO_SND_AUDIO_MGR_H
#define RP_AUDIO_SND_AUDIO_MGR_H
#include "types_RP.h"

class RPSndAudioMgr {
public:
    static RPSndAudioMgr* getInstance() { return sInstance; }

    void setSystemSeFadeInFrame(s16 frame);

private:
    static RPSndAudioMgr* sInstance;
};

#endif