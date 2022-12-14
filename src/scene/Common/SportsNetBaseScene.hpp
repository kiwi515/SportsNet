#ifndef SPORTSNET_COMMON_BASE_SCENE_H
#define SPORTSNET_COMMON_BASE_SCENE_H

#include <RPSystem/RPSysScene.h>
#include <mato/core/matoColor.hpp>

namespace spnet {

class MenuBGModel;

/**
 * @brief Base scene containing BG model and menu layout/cursor
 */
class SportsNetBaseScene : public RPSysScene {
public:
    SportsNetBaseScene();
    virtual ~SportsNetBaseScene();

    //! User overrides
    virtual void OnConfigure();
    virtual void OnLoadResource();
    virtual void OnReset();
    virtual void OnCalculate();
    virtual void OnExit();
    virtual void OnUserDraw();

    static void Printf(f32 x, f32 y, f32 scale, bool center, mato::Color color,
                       const char* fmt, ...);
    static void PrintfShadow(f32 x, f32 y, f32 scale, bool center,
                             mato::Color textColor, mato::Color shadowColor,
                             const char* fmt, ...);
    static void PrintfOutline(f32 x, f32 y, f32 scale, bool center,
                              mato::Color textColor, mato::Color outlineColor,
                              const char* fmt, ...);

private:
    //! Base scene functionality
    virtual void Configure();
    virtual void LoadResource();
    virtual void Reset();
    virtual void Calculate();
    virtual void Exit();
    virtual void UserDraw();

private:
    MenuBGModel* mMenuBGModel;
};

} // namespace spnet

#endif