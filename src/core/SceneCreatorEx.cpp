#include "SceneCreatorEx.hpp"

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
        // TO-DO
        return NULL;
    default:
        return NULL;
    }
}
kmBranch(0x80184448, SceneCreatorEx::CreateSportsNetScene);

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