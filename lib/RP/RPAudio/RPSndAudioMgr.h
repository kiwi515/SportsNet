#ifndef RP_AUDIO_SND_AUDIO_MANAGER_H
#define RP_AUDIO_SND_AUDIO_MANAGER_H
#include "types_nw4r.h"
#include "types_rp.h"

#include <nw4r/snd/snd_SoundHandle.h>
#include <nw4r/snd/snd_SoundHeap.h>

class RPSndAudioMgr {
public:
    static RPSndAudioMgr* getInstance() { return sInstance; }

    void setSystemSeFadeInFrame(s16 frame);

    bool startSound(u32 id) { return startSound(&mSndHandle, id); }
    bool startSound(const char* name) { return startSound(&mSndHandle, name); }

    bool attachArchive(const char* archiveName, bool bStaticPath,
                       nw4r::snd::SoundHeap* heap);
    bool startSound(nw4r::snd::SoundHandle* handle, u32 id);
    bool startSound(nw4r::snd::SoundHandle* handle, const char* name);

    void doSomethingAndCloseArchive();
    bool loadGroup(UNKWORD, UNKWORD, UNKWORD);
    void stopAllSound();

private:
    char UNK_0x0[0x928];
    nw4r::snd::SoundHandle mSndHandle; // at 0x928

    static RPSndAudioMgr* sInstance;
};

#endif