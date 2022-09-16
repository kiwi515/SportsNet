#include "SportsNetBaseScene.hpp"

#include "MenuBGModel.hpp"

#include <RPGraphics/RPGrpModelManager.h>
#include <RPGraphics/RPGrpModelResManager.h>
#include <RPGraphics/RPGrpRenderer.h>
#include <RPGraphics/RPGrpScreen.h>
#include <RPKernel/RPSysCursorDrawMgr.h>
#include <RPUtility/RPPrint.h>
#include <stdio.h>

namespace spnet {

SportsNetBaseScene::SportsNetBaseScene() {
    mMenuBGModel = new MenuBGModel();
    MATO_ASSERT(mMenuBGModel != NULL);
}

SportsNetBaseScene::~SportsNetBaseScene() { delete mMenuBGModel; }

void SportsNetBaseScene::OnConfigure() {}
void SportsNetBaseScene::OnLoadResource() {}
void SportsNetBaseScene::OnReset() {}
void SportsNetBaseScene::OnCalculate() {}
void SportsNetBaseScene::OnExit() {}
void SportsNetBaseScene::OnUserDraw() {}

void SportsNetBaseScene::Configure() {
    // Setup BG model scene
    RPGrpModelResManager::GetInstance()->CreateResourceList(256);
    RPGrpModelManager::GetInstance()->CreateModelScene(0, 0, 1, NULL, NULL);

    // Setup renderer view
    RPGrpScreen* screen = new RPGrpScreen();
    // For decomp reference: This is definitely an EGG inline
    if (screen->GetCanvasMode() != RPGrpScreen::CANVASMODE_0) {
        screen->SetFlag(0x1);
        screen->SetCanvasMode(RPGrpScreen::CANVASMODE_0);
    }
    RPGrpRenderer::GetInstance()->CreateView2D(1, screen);

    // Setup BG model
    mMenuBGModel->Configure(MenuBGModel::COLOR_BLUE);

    // Finalize view
    RPGrpRenderer::GetInstance()->CorrectView();

    OnConfigure();
}

void SportsNetBaseScene::LoadResource() {
    mMenuBGModel->LoadResource();

    OnLoadResource();
}

void SportsNetBaseScene::Reset() {
    // Setup cursor
    RPSysCursorDrawMgr::GetInstance()->startDpdCheck();
    RPSysCursorDrawMgr::GetInstance()->createActiveCursor();

    // Reset graphics
    mMenuBGModel->Reset();

    OnReset();
}

void SportsNetBaseScene::Calculate() {
    mMenuBGModel->Calculate();
    OnCalculate();
}

void SportsNetBaseScene::Exit() { OnExit(); }

void SportsNetBaseScene::UserDraw() { OnUserDraw(); }

/**
 * @brief Print formatted text to the screen
 *
 * @param x X position
 * @param y Y position
 * @param scale Text scale
 * @param color Text color
 * @param fmt Format string
 * @param ... Format arguments
 */
void SportsNetBaseScene::Printf(f32 x, f32 y, f32 scale, bool center,
                                mato::Color color, const char* fmt, ...) {

    if (RPGrpRenderer::GetDrawPass() != RPGrpRenderer::DRAWPASS_LYT ||
        RPGrpRenderer::D_804BF615 != 1) {
        return;
    }

    char msg_buf[0x800];
    va_list list;
    va_start(fmt, list);
    vsnprintf(msg_buf, sizeof(msg_buf), fmt, list);
    va_end(list);

    RPPrint(x, y, scale, msg_buf, color.argb(), center);
}

/**
 * @brief Print formatted text to the screen with a shadow
 *
 * @param x X position
 * @param y Y position
 * @param scale Text scale
 * @param textColor Text color
 * @param shadowColor Shadow color
 * @param fmt Format string
 * @param ... Format arguments
 */
void SportsNetBaseScene::PrintfShadow(f32 x, f32 y, f32 scale, bool center,
                                      mato::Color textColor,
                                      mato::Color shadowColor, const char* fmt,
                                      ...) {

    if (RPGrpRenderer::GetDrawPass() != RPGrpRenderer::DRAWPASS_LYT ||
        RPGrpRenderer::D_804BF615 != 1) {
        return;
    }

    char msg_buf[0x800];
    va_list list;
    va_start(fmt, list);
    vsnprintf(msg_buf, sizeof(msg_buf), fmt, list);
    va_end(list);

    // Shadow
    RPPrint(x + 2.0f, y + 2.0f, scale, msg_buf, shadowColor.argb(), center);
    // Text
    RPPrint(x, y, scale, msg_buf, textColor.argb(), center);
}

/**
 * @brief Print formatted text to the screen with an outline
 *
 * @param x X position
 * @param y Y position
 * @param scale Text scale
 * @param textColor Text color
 * @param shadowColor Shadow color
 * @param fmt Format string
 * @param ... Format arguments
 */
void SportsNetBaseScene::PrintfOutline(f32 x, f32 y, f32 scale, bool center,
                                       mato::Color textColor,
                                       mato::Color outlineColor,
                                       const char* fmt, ...) {

    if (RPGrpRenderer::GetDrawPass() != RPGrpRenderer::DRAWPASS_LYT ||
        RPGrpRenderer::D_804BF615 != 1) {
        return;
    }

    char msg_buf[0x800];
    va_list list;
    va_start(fmt, list);
    vsnprintf(msg_buf, sizeof(msg_buf), fmt, list);
    va_end(list);

    // Outline
    RPPrint(x - 2.0f, y, scale, msg_buf, outlineColor.argb(), center);
    RPPrint(x + 2.0f, y, scale, msg_buf, outlineColor.argb(), center);
    RPPrint(x, y - 2.0f, scale, msg_buf, outlineColor.argb(), center);
    RPPrint(x, y + 2.0f, scale, msg_buf, outlineColor.argb(), center);
    // Text
    RPPrint(x, y, scale, msg_buf, textColor.argb(), center);
}

} // namespace spnet