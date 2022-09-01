#include "LobbyScene.hpp"

#include <RPAudio/RPSndAudioMgr.h>
#include <RPAudio/rp_Common_Sports.h>
#include <RPGraphics/RPGrpModelManager.h>
#include <RPGraphics/RPGrpModelResManager.h>
#include <RPGraphics/RPGrpRenderer.h>
#include <RPGraphics/RPGrpScreen.h>
#include <RPKernel/RPSysCursorDrawMgr.h>
#include <RPSports/RPSportsMenuBGModel.h>

namespace spnet {

LobbyScene::LobbyScene() : mMenuModel(NULL) {
    ;
    ;
}

LobbyScene::~LobbyScene() {
    ;
    ;
}

void LobbyScene::Configure() {
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
    mMenuModel = new RPSportsMenuBGModel(0, 0, 0);
    MATO_ASSERT(mMenuModel != NULL);

    // Finalize view
    RPGrpRenderer::GetInstance()->CorrectView();
}

void LobbyScene::LoadResource() { mMenuModel->LoadResource(NULL); }

void LobbyScene::Reset() {
    // Setup cursor
    RPSysCursorDrawMgr::GetInstance()->startDpdCheck();
    RPSysCursorDrawMgr::GetInstance()->createActiveCursor();

    // Reset graphics
    mMenuModel->Reset();

    // Play BGM
    RPSndAudioMgr::getInstance()->startSound(STRM_Training_Select);
}

void LobbyScene::Calculate() { mMenuModel->Calculate(); }

void LobbyScene::Exit() {
    ;
    ;
}

void LobbyScene::UserDraw() {
    ;
    ;
}

} // namespace spnet