#include "SceneCreatorEx.hpp"

#include "LobbyScene.hpp"

#include <RPSystem/RPSysSceneCreator.h>
#include <TRK/__mem.h>

namespace spnet {

/**
 * @brief Create scene
 */
RPSysScene* SceneCreatorEx::Create(EScene id) {
    return reinterpret_cast<RPSysScene*>(
        RPSysSceneCreator::getInstance()->create(id));
}

/**
 * @brief Create SportsNet scene
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreatorEx::CreateImpl(EScene id) {
    switch (id) {
    case SPNET_LOBBY_SCENE:
        return new LobbyScene();
    default:
        return NULL;
    }
}
kmBranch(0x80184448, SceneCreatorEx::CreateImpl);

/**
 * @brief Get index into attributes table by scene id
 * @note Might seem redundant but the table is not guaranteed to be in order
 * @param id Scene ID
 */
s32 SceneCreatorEx::GetTableIndex(EScene id) {
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
SceneCreatorEx::EPack SceneCreatorEx::GetPackID(EScene id) {
    return (EPack)sSceneAttrTable[GetTableIndex(id)].pack;
}

/**
 * @brief Get create type from scene
 *
 * @param id Scene ID
 */
s32 SceneCreatorEx::GetCreateType(EScene id) {
    return sSceneAttrTable[GetTableIndex(id)].createType;
}

/**
 * @brief Check if scene should show the loading screen text
 *
 * @param id Scene ID
 */
bool SceneCreatorEx::GetShowLoadingText(EScene id) {
    return sSceneAttrTable[GetTableIndex(id)].showLoadingText;
}

/**
 * @brief Get exit type from scene
 *
 * @param id Scene ID
 */
s32 SceneCreatorEx::GetExitType(EScene id) {
    return sSceneAttrTable[GetTableIndex(id)].exitType;
}

/**
 * @brief Check if scene should use the RP common sound archive
 *
 * @param id Scene ID
 */
bool SceneCreatorEx::GetUseCommonSound(EScene id) {
    return sSceneAttrTable[GetTableIndex(id)].useCommonSound;
}

/**
 * @brief Get resource directory from scene
 *
 * @param id Scene ID
 */
const char* SceneCreatorEx::GetResDirName(EScene id) {
    return sSceneAttrTable[GetTableIndex(id)].resDirName;
}

/**
 * @brief Get scene name
 *
 * @param id Scene ID
 */
const char* SceneCreatorEx::GetSceneName(EScene id) {
    return sSceneAttrTable[GetTableIndex(id)].sceneName;
}

//! Scene attribute table
const SceneCreatorEx::SceneAttributes
    SceneCreatorEx::sSceneAttrTable[SceneCreatorEx::SCENE_MAX] = {
        // clang-format off
    // Scene                       pack          c    s    e    u       resDir                 name
    {RP_BOOT_SCENE,             RP_ALL_PACK,     0, FALSE, 1, TRUE,  "RPCommon/",             "ロゴ"},
    {RP_PLAYER_SELECT_SCENE,    RP_ALL_PACK,     0, FALSE, 2, TRUE,  "RPCommon/",             "プレイヤーセレクト"},
    {RP_NUNCHAKU_SCENE,         RP_ALL_PACK,     1, FALSE, 3, FALSE, "RPCommon/",             "ヌンチャクチェック"},
    {RP_BSB_SCENE,              RP_SPORTS_PACK,  1, FALSE, 0, FALSE, "RPBsbScene/",           "野球"},
    {RP_BOW_SCENE,              RP_SPORTS_PACK,  1, FALSE, 0, FALSE, "RPBowScene/",           "ボウリング"},
    {RP_GOL_SCENE,              RP_SPORTS_PACK,  1, FALSE, 0, FALSE, "RPGolScene/",           "ゴルフ"},
    {RP_TNS_SCENE,              RP_SPORTS_PACK,  1, FALSE, 0, FALSE, "RPTnsScene/",           "テニス"},
    {RP_BOX_SCENE,              RP_SPORTS_PACK,  1, FALSE, 0, FALSE, "RPBoxScene/",           "ボクシング"},
    {RP_SPORTS_TITLE_SCENE,     RP_SPORTS_PACK,  0, FALSE, 1, TRUE,  "RPSportsTitle/",        "スポーツパック"},
    {RP_SPORTS_MENU_SCENE,      RP_SPORTS_PACK,  0, FALSE, 2, TRUE,  "RPSportsCommon/",       "スポーツメニューセレクト"},
    {RP_TRAIN_MENU_SCENE,       RP_SPORTS_PACK,  1, FALSE, 3, TRUE,  "RPSportsTrainingMenu/", "トレーニングメニュー"},
    {RP_PHYSICAL_MENU_SCENE,    RP_SPORTS_PACK,  1, FALSE, 3, TRUE,  "RPSportsPhysical/",     "体力測定メニュー"},
    {RP_PHYSICAL_PREVIEW_SCENE, RP_SPORTS_PACK,  1, FALSE, 3, TRUE,  "RPSportsPhysical/",     "体力測定説明"},
    {RP_PHYSICAL_RESULT_SCENE,  RP_SPORTS_PACK,  1, FALSE, 3, TRUE,  "RPSportsPhysical/",     "体力測定結果"},
    {RP_GOL_SELECT_SCENE,       RP_SPORTS_PACK,  1, FALSE, 0, FALSE, "RPGolScene/",           "ゴルフコースセレクト"},
    // SportsNet scenes
    {SPNET_LOBBY_SCENE,         RP_SPORTS_PACK,  1, FALSE, 2, TRUE,  "LobbyScene/",           "Lobby Scene"}
        // clang-format on
};

} // namespace spnet