#include "SportsNetBaseScene.hpp"

#include "MenuBGModel.hpp"

#include <RPGraphics/RPGrpModelManager.h>
#include <RPGraphics/RPGrpModelResManager.h>
#include <RPGraphics/RPGrpRenderer.h>
#include <RPGraphics/RPGrpScreen.h>
#include <RPKernel/RPSysCursorDrawMgr.h>

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

} // namespace spnet