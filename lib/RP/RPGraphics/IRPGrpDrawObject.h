#ifndef RP_GRAPHICS_I_DRAW_OBJECT_H
#define RP_GRAPHICS_I_DRAW_OBJECT_H
#include "types_RP.h"

/**
 * @brief Linked-list interface for renderable objects.
 * @details The engine's renderer has a linked list of draw objects that it
 * iterates through when rendering.
 * @wfuname
 */
class IRPGrpDrawObject {
private:
    //! @brief Next draw object
    IRPGrpDrawObject* mNext; // at 0x0

public:
    IRPGrpDrawObject() : mNext(NULL) {}
    virtual ~IRPGrpDrawObject() {} // at 0x4

    //! @brief Any drawing the object needs to do
    virtual void UserDraw() {} // at 0x8
    //! @brief Debug draw pass, nearly all objects stub this out
    virtual void DebugDraw() {} // at 0xC
};

#endif