#include "MenuBGModel.hpp"
#include "SceneCreatorEx.hpp"

#include <RPSports/RPSportsMenuBGModel.h>
#include <RPSystem/RPSysResourceManager.h>

namespace spnet {

MenuBGModel::MenuBGModel() : mModel(NULL) {}

MenuBGModel::~MenuBGModel() { delete mModel; }

void MenuBGModel::Configure(EBGColor color) {
    MATO_ASSERT(color < COLOR_MAX);

    mModel = new RPSportsMenuBGModel(0, 0, color);
    MATO_ASSERT(mModel != NULL);
}

void MenuBGModel::LoadResource() {
    MATO_ASSERT(mModel != NULL);

    // Model data is in RPCommon/common.carc
    mModel->LoadResource(RPSysResourceManager::LoadGameCommonArchive(
        SceneCreatorEx::RP_BOOT_SCENE, NULL));
}

void MenuBGModel::Reset() {
    MATO_ASSERT(mModel != NULL);

    mModel->Reset();
}

void MenuBGModel::Calculate() {
    MATO_ASSERT(mModel != NULL);

    mModel->Calculate();
}

} // namespace spnet