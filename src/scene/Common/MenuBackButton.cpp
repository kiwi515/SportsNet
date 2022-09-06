#include "MenuBackButton.hpp"

#include "SceneCreatorEx.hpp"

#include <RP/common_message.h>
#include <RPAudio/RPSndAudioMgr.h>
#include <RPGraphics/RPGrpRenderer.h>
#include <RPKernel/RPSysCursorDrawMgr.h>
#include <RPKernel/RPSysLayout.h>
#include <RPKernel/RPSysLytResAccessor.h>
#include <RPKernel/RPSysLytTextBox.h>
#include <RPKernel/RPSysMessage.h>
#include <RPSystem/RPSysResourceManager.h>
#include <egg/core/eggController.h>

namespace spnet {

MenuBackButton::MenuBackButton()
    : mLayout(NULL),
      mAnmOutFrame(NULL),
      mAnmInFrame(NULL),
      mAnmActiveBack(NULL),
      mAnmPushBack(NULL) {}

MenuBackButton::~MenuBackButton() {
    delete mLayout;
    delete mAnmOutFrame;
    delete mAnmInFrame;
    delete mAnmActiveBack;
    delete mAnmPushBack;
}

void MenuBackButton::LoadResource() {
    // Load layout resources
    EGG::Archive* localArc = RPSysResourceManager::LoadGameLocalArchive(
        SceneCreatorEx::RP_BOOT_SCENE, NULL);
    void* backCommonArc = RPSysResourceManager::GetFileFromArchive(
        localArc, "backCommon.arc", NULL);

    // Create layout
    RPSysLytResAccessor* accessor = RPSysLytResAccessor::create(NULL);
    accessor->mountArchive(backCommonArc, NULL);
    mLayout = RPSysLayout::create(NULL, accessor, "backCommon_00.brlyt");
    MATO_ASSERT(mLayout != NULL);

    // Create animations
    mAnmOutFrame = mLayout->createAnmObj(NULL, accessor,
                                         "backCommon_00_outFrame_00.brlan");
    mAnmInFrame =
        mLayout->createAnmObj(NULL, accessor, "backCommon_00_inFrame_00.brlan");
    mAnmActiveBack = mLayout->createAnmObj(NULL, accessor,
                                           "backCommon_00_activeBack_00.brlan");
    mAnmPushBack = mLayout->createAnmObj(NULL, accessor,
                                         "backCommon_00_pushBack_00.brlan");
    MATO_ASSERT(mAnmOutFrame != NULL);
    MATO_ASSERT(mAnmInFrame != NULL);
    MATO_ASSERT(mAnmActiveBack != NULL);
    MATO_ASSERT(mAnmPushBack != NULL);

    // Set layout text
    void* commonBmg =
        RPSysResourceManager::GetMessageResource("common_message.bmg");
    RPSysMessage* commonMsg = new RPSysMessage(commonBmg, NULL);
    mLayout->findTextBox("T_caption_01")
        ->setMessage(commonMsg, MESSAGE_ID_ARGS(MSG_G0001C2_M00), 0);

    delete commonMsg;
}

void MenuBackButton::Reset() {
    // Unbind animations, then animate in
    mLayout->reset();
    mLayout->unbindAllAnmObj();
    mLayout->bindAnmObjToPane(mAnmInFrame, "N_frameDown_00", true);
}

void MenuBackButton::Calculate() {
    mLayout->calc();

    // Check active player for back button input
    const s32 player = RPSysCursorDrawMgr::GetInstance()->getActivePlayer();
    EGG::CoreController* cont =
        EGG::CoreControllerMgr::getInstance()->getNthController(player);
    if (cont->STATUS_0x14.trig & EGG::cCORE_FSSTICK_B) {
        // Play sound effect and exit scene
        RPSndAudioMgr::getInstance()->startSound(
            "RP_COMMON_SE_KEY_BACK_01_CTSP");
        mLayout->bindAnmObjToPane(mAnmPushBack, "N_frameDown_00", true);
    }
}

void MenuBackButton::UserDraw() {
    if (RPGrpRenderer::GetDrawPass() == RPGrpRenderer::DRAWPASS_LYT &&
        RPGrpRenderer::D_804BF615 == 1) {
        mLayout->draw();
    }
}

} // namespace spnet