#ifndef SPORTSNET_COMMON_MENU_BACK_BUTTON_H
#define SPORTSNET_COMMON_MENU_BACK_BUTTON_H
#include "types.h"

#include <RP/types_RP.h>

namespace spnet {

/**
 * @brief Back button
 */
class MenuBackButton {
public:
    MenuBackButton();
    virtual ~MenuBackButton();
    void LoadResource();
    void Reset();
    void Calculate();
    void UserDraw();

private:
    RPSysLayout* mLayout;
    RPSysLytAnmObj* mAnmOutFrame;
    RPSysLytAnmObj* mAnmInFrame;
    RPSysLytAnmObj* mAnmActiveBack;
    RPSysLytAnmObj* mAnmPushBack;
};

} // namespace spnet

#endif