#ifndef RP_KERNEL_LAYOUT_H
#define RP_KERNEL_LAYOUT_H
#include "RPSysLytDynamicAnm.h"
#include "types_RP.h"

#include <egg/math/eggVector.h>
#include <nw4r/ut/ut_Color.h>
#include <nw4r/ut/ut_list.h>

/**
 * @brief NW4R layout wrapper with added features, such as support for
 * Mii icons and dynamic animation.
 * @wfuname
 */
class RPSysLayout {
public:
    /**
     * @brief Layout flags
     */
    enum EFlags { FLAG_VISIBLE = (1 << 0) };

public:
    /**
     * @brief Get CPU color
     * @address 801957c0
     */
    static const GXColor& getCpuColor();

    /**
     * @brief Get player color
     * @address 801957c8
     */
    static const GXColor& getPlayerColor(u32);

    /**
     * @brief Check if all dynamic animations have finished animating out
     * @address 801957dc
     */
    bool isFinishedDynAnmOut();

    /**
     * @brief Check if all dynamic animations have finished animating out
     * @address 80195844
     */
    bool isFinishedDynAnmIn();

    /**
     * @brief Flip all dynamic animations horizontally
     * @param reverse Whether to reverse horizontal direction
     * @address 801958ac
     */
    void reverseDynAnmHDirection(bool reverse);

    /**
     * @brief Start animating out all dynamic animations
     * @param frame Starting frame
     * @address 80195914
     */
    void startDynAnmOut(s16 frame);

    /**
     * @brief Start animating in all dynamic animations
     * @param frame Starting frame
     * @address 8019597c
     */
    void startDynAnmIn(s16 frame);

    /**
     * @brief Draw Kokeshi (Mii) icon
     * @param screen Screen to draw to
     * @param pane Pane to draw on
     * @param icon Mii icon
     * @param color Material color
     * @address 801959e4
     */
    static void drawKokeshiIcon(RPGrpScreen* screen, nw4r::lyt::Pane* pane,
                                RPSysKokeshiIcon* icon, nw4r::ut::Color color);

    /**
     * @brief Draw Kokeshi (Mii) icon
     * @details Uses default white material color
     * @param screen Screen to draw to
     * @param pane Pane to draw on
     * @param icon Mii icon
     * @address 80195ae4
     */
    static void drawKokeshiIcon(RPGrpScreen* screen, nw4r::lyt::Pane* pane,
                                RPSysKokeshiIcon* icon);

    /**
     * @brief Make pane become its parent's youngest child
     * @param child Child pane
     * @address 80195b28
     */
    static void becomeYoungestChild(nw4r::lyt::Pane* child);

    /**
     * @brief Check if a specified position is within a bounding box
     * @param bounding Layout bounding box
     * @param pos Position
     * @return true if pos inside bounding; always false if layout is hidden
     * @address 80195b74
     */
    bool isInsideBounding(RPSysLytBounding* bounding,
                          const nw4r::math::VEC2& pos);

    /**
     * @brief Copy font color from alternative textbox
     * @details Searches for a textbox with the active textbox's name, applying
     * the id as a suffix
     * @see RPSysLytTextBox::copyFontColor
     * @param textBox Layout text box
     * @param id Pane id
     * @return true if color was changed successfully
     * @address 80195bb8
     */
    bool changeFontColor(RPSysLytTextBox* textBox, u32 id);

    /**
     * @brief Draw layout
     * @address 80195dcc
     */
    void draw();

    /**
     * @brief Setup GX cull/clip mode for drawing
     * @address 80195df8
     */
    static void drawInit();

    /**
     * @brief Update animations
     * @note Marks layout as visible
     * @address 80195e34
     */
    void calc();

    /**
     * @brief Reset animations
     * @note Marks layout as hidden
     * @address 80195f70
     */
    void reset();

    /**
     * @brief Append dynamic animation to layout
     * @param anm Dynamic animation
     * @address 8019605c
     */
    void appendDynamicAnm(RPSysLytDynamicAnm* anm);

    /**
     * @brief Search for layout group by name
     * @param name Group name
     * @address 80196064
     */
    nw4r::lyt::Group* findGroup(const char* name);

    /**
     * @brief Search for layout bounding by name
     * @param name Bounding name
     * @address 80196070
     */
    RPSysLytBounding* findBounding(const char* name);

    /**
     * @brief Search for layout window by name
     * @param name Window name
     * @address 80196120
     */
    RPSysLytWindow* findWindow(const char* name);

    /**
     * @brief Search for layout picture by name
     * @param name Picture name
     * @address 801961d0
     */
    RPSysLytPicture* findPicture(const char* name);

    /**
     * @brief Search for layout textbox by name
     * @param name Textbox name
     * @address 80196280
     */
    RPSysLytTextBox* findTextBox(const char* name);

    /**
     * @brief Search for layout pane by name
     * @param name Pane name
     * @address 80196330
     */
    nw4r::lyt::Pane* findPane(const char* name);

    /**
     * @brief Dynamic cast self to bounding
     * @return NULL if dynamic cast fails, otherwise bounding
     * @address 8019634c
     */
    RPSysLytBounding* castToBounding();

    /**
     * @brief Dynamic cast self to picture
     * @return NULL if dynamic cast fails, otherwise picture
     * @address 801963d8
     */
    RPSysLytPicture* castToPicture();

    /**
     * @brief Unbind an animation from a pane
     * @param anm Animation object
     * @param pane Pane
     * @param recurse Whether to search recursively through children
     * @address 80196464
     */
    static void unbindAnmObjToPane(RPSysLytAnmObj* anm, nw4r::lyt::Pane* pane,
                                   bool recurse);

    /**
     * @brief Force an animation to be bound to a pane
     * @details TODO
     * @param anm Animation object
     * @param pane Pane
     * @param recurse TODO
     * @address 80196480
     */
    static void forceBindAnmObjToPane(RPSysLytAnmObj* anm,
                                      nw4r::lyt::Pane* pane, bool recurse);

    /**
     * @brief Bind an animation to a pane
     * @param anm Animation object
     * @param pane Pane
     * @param recurse TODO
     * @address 80196774
     */
    static void bindAnmObjToPane(RPSysLytAnmObj* anm, nw4r::lyt::Pane* pane,
                                 bool recurse);

    /**
     * @brief Bind an animation to a pane
     * @details Searches layout children for pane name
     * @param anm Animation object
     * @param paneName Pane name
     * @param recurse TODO
     * @address 80196790
     */
    void bindAnmObjToPane(RPSysLytAnmObj* anm, const char* paneName,
                          bool recurse);

    /**
     * @brief Unbind all animations from the layout
     * @address 80196804
     */
    void unbindAllAnmObj();

    /**
     * @brief Unbind an animation from the layout
     * @param anm Animation object
     * @address 80196818
     */
    void unbindAnmObj(RPSysLytAnmObj* anm);

    /**
     * @brief Bind an animation to the layout
     * @param anm Animation object
     * @address 80196830
     */
    void bindAnmObj(RPSysLytAnmObj* anm);

    /**
     * @brief Create a animation object
     * @param heap Heap
     * @param accessor Resource accessor
     * @param anmName Animation file name (BRLAN)
     * @address 80196848
     */
    RPSysLytAnmObj* createAnmObj(EGG::Heap* heap, RPSysLytResAccessor* accessor,
                                 const char* anmName);

    /**
     * @brief Create a layout
     * @param heap Heap
     * @param accessor Resource accessor
     * @param lytName Layout file name (BRLYT)
     * @address 80196a38
     */
    static RPSysLayout* create(EGG::Heap* heap, RPSysLytResAccessor* accessor,
                               const char* lytName);

    /**
     * @brief Allocate string buffer for all textboxes in pane
     * @param pane Pane
     * @address 80196c70
     */
    static void allocStringBuffer(nw4r::lyt::Pane* pane);

    /**
     * @brief Create dynamic animation objects for a pane
     * @param heap Heap
     * @param pane Pane containing dynamic animation info
     * @address 80197340
     */
    void createDynamicAnm(EGG::Heap* heap, nw4r::lyt::Pane* pane);

    /**
     * @brief Parse dynamic animation info from a pane
     * @param pane Pane containing dynamic animation info
     * @param[out] direction Animation direction
     * @param[out] length Animation length
     * @address 80197598
     */
    void parseDynamicAnmInfo(nw4r::lyt::Pane* pane,
                             RPSysLytDynamicAnm::EDirection* direction,
                             s16* length);

    /**
     * @brief Parse integer literal (anim length) from a string
     * @param info Dynamic animation info
     * @address 801976b8
     */
    static s16 parseDynamicAnmLength(const char* info);

    /**
     * @brief Initialize layout system
     * @details Initializes nw4r::lyt
     * @address 8019778c
     */
    static void initialize();

private:
    u16 mFlags; // at 0x0
    f32 FLOAT_0x4;
    f32 FLOAT_0x8;
    f32 FLOAT_0xC;
    f32 FLOAT_0x10;
    f32 FLOAT_0x14;
    f32 FLOAT_0x18;
    //! @brief Layout draw info
    nw4r::lyt::DrawInfo* mDrawInfo; // at 0x1C
    //! @brief Parent NW4R layout
    nw4r::lyt::Layout* mLayout; // at 0x20
    //! @brief List of basic animations
    nw4r::ut::List mAnmObjs; // at 0x24
    //! @brief List of dynamic animations
    nw4r::ut::List mDynamicAnms; // at 0x30

    /**
     * @brief CPU color for layouts
     * @address 804c15f0
     */
    static const GXColor scCpuColor;

    /**
     * @brief Player colors for layouts
     * @address 80382d60
     */
    static const GXColor scPlayerColors[4];
};

#endif