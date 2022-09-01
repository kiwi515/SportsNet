#ifndef SPORTSNET_COMMON_BG_MODEL_H
#define SPORTSNET_COMMON_BG_MODEL_H
#include "types.h"

#include <RP/types_RP.h>

namespace spnet {

/**
 * @brief Background/globe model
 */
class MenuBGModel {
public:
    enum EBGColor { COLOR_BLUE, COLOR_GREEN, COLOR_PURPLE, COLOR_MAX };

public:
    MenuBGModel();
    virtual ~MenuBGModel();

    void Configure(EBGColor color);
    void LoadResource();
    void Reset();
    void Calculate();

private:
    RPSportsMenuBGModel* mModel;
};

} // namespace spnet

#endif