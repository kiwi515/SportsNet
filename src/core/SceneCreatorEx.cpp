#include "SceneCreatorEx.hpp"

#include "LobbyScene.hpp"

#include <RPAudio/RPSndAudioMgr.h>
#include <RPSystem/RPSysBootScene.h>
#include <RPSystem/RPSysNunchukScene.h>
#include <RPSystem/RPSysPlayerSelectScene.h>
#include <RPSystem/RPSysSceneCreator.h>
#include <RPSystem/RPSysSceneMgr.h>
#include <TRK/__mem.h>

namespace spnet {

/**
 * @brief Create scene
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreatorEx::Create(ESceneIDEx id) {
    RPSysScene* scene = NULL;

    // Check for SportsNet scene ID
    if (id > RP_SCENE_MAX) {
        scene = CreateSportsNetScene(id);
    } else {
        // Either system (all pack) or sports scene
        switch (GetPackID(id)) {
        case RP_SPORTS_PACK:
            scene = CreateSportsScene(id);
            break;
        case RP_ALLPACK:
            scene = CreateSystemScene(id);
            break;
        default:
            break;
        }
    }

    MATO_ASSERT_EX(scene != NULL, "Failed to create scene (id %d)", id);

    if (GetShowLoadingText(id)) {
        scene->setShowLoadingText();
    }

    if (GetExitType(id) == 4) {
        scene->disableFadeIn();
    }

    scene->setCreatorSceneID(getLastSceneID());
}
kmBranchMF(0x80184838, SceneCreatorEx, Create);

/**
 * @brief Create Pack Project scene
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreatorEx::CreateSystemScene(ESceneIDEx id) {
    switch (id) {
    case RP_BOOT_SCENE:
        return new RPSysBootScene();
    case RP_PLAYER_SELECT_SCENE:
        return new RPSysPlayerSelectScene();
    case RP_NUNCHAKU_SCENE:
        return new RPSysNunchukScene();
    default:
        return NULL;
    }
}

/**
 * @brief Create Sports Pack scene
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreatorEx::CreateSportsScene(ESceneIDEx id) {
    return reinterpret_cast<RPSysScene*>(
        RPSysSceneCreator::createSportsScene(id));
}

/**
 * @brief Create SportsNet scene
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreatorEx::CreateSportsNetScene(ESceneIDEx id) {
    switch (id) {
    case SPNET_LOBBY_SCENE:
        return new LobbyScene();
    default:
        return NULL;
    }
}

/**
 * @brief Fade out into new scene
 *
 * @param next Scene ID
 * @param reload Reload current scene
 * @returns Success
 */
bool SceneCreatorEx::ChangeSceneAfterFade(ESceneIDEx next, bool reload) {
    // Ensure all threads are idle
    if (!RPSysSceneMgr::getInstance()->isTaskFinished()) {
        return false;
    }

    const ESceneIDEx current = static_cast<ESceneIDEx>(
        RPSysSceneMgr::getInstance()->getCurrentSceneID());

    // Optionally reload current scene
    if (reload) {
        next = current;
    }

    // Send request to scene manager
    bool success =
        RPSysSceneMgr::getInstance()->changeNextSceneAfterFade(next, reload);

    // Fade in system SE if we are switching sound archives?
    if (GetUseCommonSound(next) != GetUseCommonSound(current)) {
        const s16 frame = RPSysSceneMgr::getInstance()->getFadeFrame();
        RPSndAudioMgr::getInstance()->setSystemSeFadeInFrame(frame);
    }

    // Update last scene for exiting
    if (GetExitType(next) != 4) {
        setLastSceneID(current);
    }

    return success;
}
kmBranchMF(0x80184ba4, SceneCreatorEx, ChangeSceneAfterFade);

/**
 * @brief Convert sport ID to scene ID
 *
 * @param sport Sport ID
 */
SceneCreatorEx::ESceneIDEx SceneCreatorEx::GetSceneID(ESportID sport) const {
    switch (sport) {
    case SPORT_BASEBALL:
        return RP_BSB_SCENE;
    case SPORT_TENNIS:
        return RP_TNS_SCENE;
    case SPORT_GOLF:
        return RP_GOL_SCENE;
    case SPORT_BOXING:
        return RP_BOX_SCENE;
    case SPORT_BOWLING:
        return RP_BOW_SCENE;
    default:
        return RP_SPORTS_MENU_SCENE;
    }
}
kmBranchMF(0x80184690, SceneCreatorEx, GetSceneID);

/**
 * @brief Convert scene ID to sport ID
 *
 * @param scene Scene ID
 */
SceneCreatorEx::ESportID SceneCreatorEx::GetSportID(ESceneIDEx scene) const {
    switch (scene) {
    case RP_BSB_SCENE:
        return SPORT_BASEBALL;
    case RP_TNS_SCENE:
        return SPORT_TENNIS;
    case RP_GOL_SCENE:
        return SPORT_GOLF;
    case RP_BOX_SCENE:
        return SPORT_BOXING;
    case RP_BOW_SCENE:
        return SPORT_BOWLING;
    default:
        return SPORT_BASEBALL;
    }
}
kmBranchMF(0x801846ec, SceneCreatorEx, GetSportID);

/**
 * @brief Get index into attributes table by scene id
 * @note Might seem redundant but the table is not guaranteed to be in order
 * @param id Scene ID
 */
s32 SceneCreatorEx::GetTableIndex(ESceneIDEx id) const {
    // Use -1 for current scene
    if (id < 0) {
        id = static_cast<ESceneIDEx>(
            RPSysSceneMgr::getInstance()->getCurrentSceneID());
    }

    for (int i = 0; i < SCENE_MAX; i++) {
        if (sSceneAttrTable[i].scene == id) {
            return i;
        }
    }

    MATO_ASSERT_EX(false, "Scene missing from table: %d", id);
    return -1;
}

/**
 * @brief Get pack ID from scene
 *
 * @param id Scene ID
 */
SceneCreatorEx::EPackID SceneCreatorEx::GetPackID(ESceneIDEx id) const {
    return static_cast<EPackID>(sSceneAttrTable[GetTableIndex(id)].pack);
}

/**
 * @brief Get create type from scene
 *
 * @param id Scene ID
 */
s32 SceneCreatorEx::GetCreateType(ESceneIDEx id) const {
    return sSceneAttrTable[GetTableIndex(id)].createType;
}
kmBranchMF(0x801845f4, SceneCreatorEx, GetCreateType);

/**
 * @brief Check if scene should show the loading screen text
 *
 * @param id Scene ID
 */
bool SceneCreatorEx::GetShowLoadingText(ESceneIDEx id) const {
    return sSceneAttrTable[GetTableIndex(id)].showLoadingText;
}

/**
 * @brief Get exit type from scene
 *
 * @param id Scene ID
 */
s32 SceneCreatorEx::GetExitType(ESceneIDEx id) const {
    return sSceneAttrTable[GetTableIndex(id)].exitType;
}
kmBranchMF(0x80184558, SceneCreatorEx, GetExitType);

/**
 * @brief Check if scene should use the RP common sound archive
 *
 * @param id Scene ID
 */
bool SceneCreatorEx::GetUseCommonSound(ESceneIDEx id) const {
    return sSceneAttrTable[GetTableIndex(id)].useCommonSound;
}
kmBranchMF(0x801844bc, SceneCreatorEx, GetUseCommonSound);

/**
 * @brief Get resource directory from scene
 *
 * @param id Scene ID
 */
const char* SceneCreatorEx::GetResDirName(ESceneIDEx id) const {
    return sSceneAttrTable[GetTableIndex(id)].resDirName;
}
kmBranchMF(0x80184758, SceneCreatorEx, GetResDirName);

/**
 * @brief Get scene name
 *
 * @param id Scene ID
 */
const char* SceneCreatorEx::GetSceneName(ESceneIDEx id) const {
    return sSceneAttrTable[GetTableIndex(id)].sceneName;
}

//! Scene attribute table
const SceneCreatorEx::SceneAttributes
    SceneCreatorEx::sSceneAttrTable[SceneCreatorEx::SCENE_MAX] = {
        // clang-format off
    // Scene                       pack          c    s    e    u       resDir                 name
    {RP_BOOT_SCENE,             RP_ALLPACK,     0, false, 1, true,  "RPCommon/",             "ロゴ"},
    {RP_PLAYER_SELECT_SCENE,    RP_ALLPACK,     0, false, 2, true,  "RPCommon/",             "プレイヤーセレクト"},
    {RP_NUNCHAKU_SCENE,         RP_ALLPACK,     1, false, 3, false, "RPCommon/",             "ヌンチャクチェック"},
    {RP_BSB_SCENE,              RP_SPORTS_PACK,  1, false, 0, false, "RPBsbScene/",           "野球"},
    {RP_BOW_SCENE,              RP_SPORTS_PACK,  1, false, 0, false, "RPBowScene/",           "ボウリング"},
    {RP_GOL_SCENE,              RP_SPORTS_PACK,  1, false, 0, false, "RPGolScene/",           "ゴルフ"},
    {RP_TNS_SCENE,              RP_SPORTS_PACK,  1, false, 0, false, "RPTnsScene/",           "テニス"},
    {RP_BOX_SCENE,              RP_SPORTS_PACK,  1, false, 0, false, "RPBoxScene/",           "ボクシング"},
    {RP_SPORTS_TITLE_SCENE,     RP_SPORTS_PACK,  0, false, 1, true,  "RPSportsTitle/",        "スポーツパック"},
    {RP_SPORTS_MENU_SCENE,      RP_SPORTS_PACK,  0, false, 2, true,  "RPSportsCommon/",       "スポーツメニューセレクト"},
    {RP_TRAIN_MENU_SCENE,       RP_SPORTS_PACK,  1, false, 3, true,  "RPSportsTrainingMenu/", "トレーニングメニュー"},
    {RP_PHYSICAL_MENU_SCENE,    RP_SPORTS_PACK,  1, false, 3, true,  "RPSportsPhysical/",     "体力測定メニュー"},
    {RP_PHYSICAL_PREVIEW_SCENE, RP_SPORTS_PACK,  1, false, 3, true,  "RPSportsPhysical/",     "体力測定説明"},
    {RP_PHYSICAL_RESULT_SCENE,  RP_SPORTS_PACK,  1, false, 3, true,  "RPSportsPhysical/",     "体力測定結果"},
    {RP_GOL_SELECT_SCENE,       RP_SPORTS_PACK,  1, false, 0, false, "RPGolScene/",           "ゴルフコースセレクト"},
    // SportsNet scenes
    {SPNET_LOBBY_SCENE,         RP_SPORTS_PACK,  1, false, 2, true,  "LobbyScene/",           "Lobby Scene"}
        // clang-format on
};

} // namespace spnet