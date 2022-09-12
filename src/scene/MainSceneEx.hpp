#ifndef SPORTSNET_SCENE_MAIN_SCENE_EX_H
#define SPORTSNET_SCENE_MAIN_SCENE_EX_H
#include <RPSports/RPSportsMainScene.h>

namespace spnet {

/**
 * @brief Sports pack main scene extension for network select
 */

class MainSceneEx : public RPSportsMainScene {
public:
    void Dispatch();

private:
    // MainSceneEx should not be constructed
    MainSceneEx();
    MainSceneEx(const MainSceneEx&);
    ~MainSceneEx();
};

} // namespace spnet

#endif