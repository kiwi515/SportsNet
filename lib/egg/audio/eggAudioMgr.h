#ifndef EGG_AUDIO_AUDIOMGR_H
#define EGG_AUDIO_AUDIOMGR_H
#include "eggAudioArcPlayerMgr.h"
#include "eggAudioHeapMgr.h"
#include "types_egg.h"

namespace EGG {
class IAudioMgr {
public:
    class Arg {};

    virtual UNKTYPE initialize(Arg*) {}
    virtual UNKTYPE calc() = 0;
};

class SimpleAudioMgr : public IAudioMgr, public SoundHeapMgr, public ArcPlayer {
    virtual ~SimpleAudioMgr(); // at 0x80
};
} // namespace EGG

#endif