#include "LobbySlot.hpp"

#include "NetplayMgr.hpp"

#include <RPGraphics/RPGrpRenderer.h>
#include <RPKernel/RPSysLayout.h>
#include <RPKernel/RPSysLytPicture.h>
#include <RPKernel/RPSysLytResAccessor.h>
#include <RPKernel/RPSysLytTextBox.h>
#include <RPKernel/RPSysLytWindow.h>
#include <RPSystem/RPSysResourceManager.h>
#include <stdio.h>
#include <wstring.h>

namespace spnet {

LobbySlot::LobbySlot(u32 player) : mPlayer(player), mLayout(NULL) {
    MATO_ASSERT(mPlayer < scMaxPlayers);
}

LobbySlot::~LobbySlot() { delete mLayout; }

void LobbySlot::LoadResource() {
    // Load layout resources
    RPSysLytResAccessor* accessor = RPSysLytResAccessor::create(NULL);
    void* resultArc = RPSysResourceManager::GetFileFromArchive(
        RPSysResourceManager::GetInstance()->GetStaticLocalArchive(),
        "trainingResult.arc", NULL);
    MATO_ASSERT(resultArc != NULL);
    accessor->mountArchive(resultArc, NULL);

    // Create layout
    mLayout = RPSysLayout::create(NULL, accessor, "trainingResult_02.brlyt");
    MATO_ASSERT(mLayout != NULL);

    // Apply player color
    RPSysLytWindow* W_faceBg_00 = mLayout->findWindow("W_faceBg_00");
    RPSysLytPicture* P_pBg_00 = mLayout->findPicture("P_pBg_00");
    MATO_ASSERT(W_faceBg_00 != NULL);
    MATO_ASSERT(P_pBg_00 != NULL);
    W_faceBg_00->applyPlayerColor(mPlayer, true);
    P_pBg_00->applyPlayerColor(mPlayer);

    // Position pane
    nw4r::lyt::Pane* RootPane = mLayout->findPane("RootPane");
    MATO_ASSERT(RootPane != NULL);
    RootPane->SetTranslate(sSlotRootTrans[mPlayer]);

    // Clear unused textboxes
    static const char* textBoxNames[] = {"T_rank_00", "T_rank_01", "T_score_00",
                                         "T_scoreSub_00"};
    for (int i = 0; i < ARRAY_LENGTH(textBoxNames); i++) {
        RPSysLytTextBox* textBox = mLayout->findTextBox(textBoxNames[i]);
        MATO_ASSERT_EX(textBox != NULL, "Could not find textbox: %s",
                       textBoxNames[i]);
        textBox->setText(L"", 0);
    }

    // Hide unused pictures
    static const char* pictureNames[] = {"P_Line_00", "P_Line_01"};
    for (int i = 0; i < ARRAY_LENGTH(pictureNames); i++) {
        RPSysLytPicture* picture = mLayout->findPicture(pictureNames[i]);
        MATO_ASSERT_EX(picture != NULL, "Could not find picture: %s",
                       pictureNames[i]);
        // I know this looks bad, but SetVisible wasn't working
        picture->SetTranslate(nw4r::math::VEC2(10000.0f, 10000.0f));
    }
}

void LobbySlot::Reset() { mLayout->reset(); }

void LobbySlot::Calculate() {
    mLayout->calc();

    // TO-DO: Make this into a callback or something,
    // so it doesn't have to run every frame
    SetName(NetplayMgr::GetInstance().GetPlayerName(mPlayer));
}

void LobbySlot::UserDraw() {
    if (RPGrpRenderer::GetDrawPass() == RPGrpRenderer::DRAWPASS_LYT &&
        RPGrpRenderer::D_804BF615 == 1) {
        // Draw main window
        mLayout->draw();

        // Draw Mii head
        nw4r::lyt::Pane* N_faceNull_00 = mLayout->findPane("N_faceNull_00");
        MATO_ASSERT(N_faceNull_00 != NULL);
        RPSysKokeshiIcon* icon =
            NetplayMgr::GetInstance().GetKokeshiIcon(mPlayer);
        if (icon != NULL) {
            mLayout->drawKokeshiIcon(RPGrpRenderer::GetActiveScreen(),
                                     N_faceNull_00, icon);
        }
    }
}

/**
 * @brief Update player slot name
 *
 * @param name Widechar name string
 */
void LobbySlot::SetName(const wchar_t* name) {
    MATO_ASSERT(mLayout != NULL);

    // Player name text box
    RPSysLytTextBox* T_name_00 = mLayout->findTextBox("T_name_00");
    MATO_ASSERT(T_name_00 != NULL);

    // Name is limited to 10 characters
    if (wcslen(name) > scPlayerNameLength) {
        MATO_LOG_EX("[LobbySlot::SetName] Name too long for buffer: %s", name);

        wchar_t buf[scPlayerNameLength + 1];
        wcsncpy(buf, name, sizeof(buf));
        buf[scPlayerNameLength] = '\0';

        name = buf;
    }

    T_name_00->setText(name, 0);
}

const nw4r::math::VEC2 LobbySlot::sSlotRootTrans[LobbySlot::scMaxPlayers] = {
    nw4r::math::VEC2(12.0f, 117.0f), nw4r::math::VEC2(12.0f, 50.0f),
    nw4r::math::VEC2(12.0f, -17.0f), nw4r::math::VEC2(12.0f, -84.0f)};

} // namespace spnet