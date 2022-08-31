#ifndef SPORTSNET_CORE_SCENE_CREATOR_EX_H
#define SPORTSNET_CORE_SCENE_CREATOR_EX_H
#include "types.h"

#include <RPSystem/RPSysScene.h>
#include <RPSystem/RPSysSceneCreator.h>

namespace spnet {

/**
 * @brief RP scene creator extension to support SportsNet scenes
 */
class SceneCreatorEx : public RPSysSceneCreator {
public:
    //! All game scenes
    enum ESceneIDEx {
        // RP scenes
        RP_BOOT_SCENE,
        RP_PLAYER_SELECT_SCENE,
        RP_NUNCHAKU_SCENE,
        RP_BSB_SCENE,
        RP_BOW_SCENE,
        RP_GOL_SCENE,
        RP_TNS_SCENE,
        RP_BOX_SCENE,
        RP_SPORTS_TITLE_SCENE,
        RP_SPORTS_MENU_SCENE,
        RP_TRAIN_MENU_SCENE,
        RP_PHYSICAL_MENU_SCENE,
        RP_PHYSICAL_PREVIEW_SCENE,
        RP_PHYSICAL_RESULT_SCENE,
        RP_GOL_SELECT_SCENE,

        // SportsNet scenes
        SPNET_LOBBY_SCENE,

        SCENE_MAX,

        RP_SCENE_MAX = RP_GOL_SELECT_SCENE + 1
    };

public:
    static SceneCreatorEx& GetInstance() {
        RPSysSceneCreator* base = RPSysSceneCreator::getInstance();
        MATO_ASSERT(base != NULL);
        return *reinterpret_cast<SceneCreatorEx*>(base);
    }

    RPSysScene* Create(ESceneIDEx id);
    RPSysScene* CreateSystemScene(ESceneIDEx id);
    RPSysScene* CreateSportsScene(ESceneIDEx id);
    RPSysScene* CreateSportsNetScene(ESceneIDEx id);
    bool ChangeSceneAfterFade(ESceneIDEx id, bool reload);

    EPackID GetPackID(ESceneIDEx id) const;
    s32 GetCreateType(ESceneIDEx id) const;
    bool GetShowLoadingText(ESceneIDEx id) const;
    s32 GetExitType(ESceneIDEx id) const;
    bool GetUseCommonSound(ESceneIDEx id) const;
    const char* GetResDirName(ESceneIDEx id) const;
    const char* GetSceneName(ESceneIDEx id) const;

private:
    // SceneCreatorEx should not be instantiated
    SceneCreatorEx();
    SceneCreatorEx(const SceneCreatorEx&);
    ~SceneCreatorEx();

    s32 GetTableIndex(ESceneIDEx id) const;

private:
    static const SceneAttributes sSceneAttrTable[SCENE_MAX];
};

} // namespace spnet

#endif