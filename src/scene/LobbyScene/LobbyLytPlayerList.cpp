#include "LobbyLytPlayerList.hpp"

#include "LobbyLytPlayerSlot.hpp"

#include <RPAudio/RPSndAudioMgr.h>
#include <RPGraphics/RPGrpRenderer.h>
#include <RPKernel/RPSysCursorDrawMgr.h>
#include <RPKernel/RPSysLayout.h>
#include <RPKernel/RPSysLytResAccessor.h>
#include <RPSports/RPSportsLytButton.h>
#include <RPSystem/RPSysResourceManager.h>

namespace spnet {

LobbyLytPlayerList::LobbyLytPlayerList()
    : mLayout(NULL), mSettingsBtn(NULL), mStartBtn(NULL) {
    for (int i = 0; i < scMaxPlayers; i++) {
        mSlots[i] = new LobbyLytPlayerSlot(i);
        MATO_ASSERT(mSlots[i] != NULL);
    }
}

LobbyLytPlayerList::~LobbyLytPlayerList() {
    delete mLayout;
    delete mSettingsBtn;
    delete mStartBtn;
    for (int i = 0; i < scMaxPlayers; i++) {
        delete mSlots[i];
    }
}

void LobbyLytPlayerList::LoadResource() {
    // Load layout resources
    RPSysLytResAccessor* accessor = RPSysLytResAccessor::create(NULL);
    void* resultArc = RPSysResourceManager::GetFileFromArchive(
        RPSysResourceManager::GetInstance()->GetStaticLocalArchive(),
        "trainingResult.arc", NULL);
    MATO_ASSERT(resultArc != NULL);
    accessor->mountArchive(resultArc, NULL);

    // Create layout
    mLayout = RPSysLayout::create(NULL, accessor, "trainingResult_01.brlyt");
    MATO_ASSERT(mLayout != NULL);

    // Create buttons
    RPSportsLytButton::Arg arg;
    // Common button data
    arg.STR_0x18 = NULL;
    arg.parent = mLayout;
    arg.accessor = accessor;
    arg.activeAnim = "trainingResult_01_activeButton_00.brlan";
    arg.pushAnim = "trainingResult_01_pushButton_00.brlan";

    // Button 0 - Room Settings
    arg.id = 0;
    arg.pane = "P_button_00";
    arg.bounding = "B_button_00";
    mSettingsBtn = new RPSportsLytButton(arg);
    MATO_ASSERT(mSettingsBtn != NULL);

    // Button 1 - Start Game
    arg.id = 1;
    arg.pane = "P_button_01";
    arg.bounding = "B_button_01";
    mStartBtn = new RPSportsLytButton(arg);
    MATO_ASSERT(mStartBtn != NULL);

    // Link buttons together
    mSettingsBtn->Link(RPSportsLytButton::LINK_RIGHT, mStartBtn);
    mStartBtn->Link(RPSportsLytButton::LINK_LEFT, mSettingsBtn);
    // Allow control to wrap horizontally
    mSettingsBtn->Link(RPSportsLytButton::LINK_LEFT, mStartBtn);
    mStartBtn->Link(RPSportsLytButton::LINK_RIGHT, mSettingsBtn);

    // Bind buttons to window
    Bind(mSettingsBtn);
    Bind(mStartBtn);

    // Load frame cursor resources
    LoadCursorResource(
        RPSysResourceManager::GetInstance()->GetStaticLocalArchive());

    // Create player slots
    for (int i = 0; i < scMaxPlayers; i++) {
        mSlots[i]->LoadResource();
    }
}

void LobbyLytPlayerList::Reset() {
    mLayout->reset();

    for (int i = 0; i < scMaxPlayers; i++) {
        mSlots[i]->Reset();
    }

    // Initialize buttons and cursor
    RPSportsLytCursorBase::Reset();
}

void LobbyLytPlayerList::Calculate() {
    mLayout->calc();

    for (int i = 0; i < scMaxPlayers; i++) {
        mSlots[i]->Calculate();
    }

    // Update buttons using cursor position
    const EGG::Vector2f& pos =
        RPSysCursorDrawMgr::GetInstance()->getActiveCursorPos();
    RPSportsLytCursorBase::Calculate(pos, true);
}

void LobbyLytPlayerList::UserDraw() {
    // Draw layouts with transparency and during the correct draw pass
    if (RPGrpRenderer::GetDrawPass() == RPGrpRenderer::DRAWPASS_LYT &&
        RPGrpRenderer::D_804BF615 == 1) {
        mLayout->draw();
        RPSportsLytCursorBase::UserDraw();
    }

    for (int i = 0; i < scMaxPlayers; i++) {
        mSlots[i]->UserDraw();
    }
}

/**
 * @brief Update player slot with info from netplay manager
 *
 * @param player Player slot ID
 */
void LobbyLytPlayerList::UpdatePlayer(u32 player) {
    mSlots[player]->UpdatePlayer();
}

} // namespace spnet