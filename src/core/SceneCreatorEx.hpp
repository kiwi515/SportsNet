#ifndef SPORTSNET_CORE_SCENE_CREATOR_EX_H
#define SPORTSNET_CORE_SCENE_CREATOR_EX_H
#include "types.h"

#include <RP/types_RP.h>

namespace spnet {

/**
 * @brief RP scene creator extension to support SportsNet scenes
 */
class SceneCreatorEx {
public:
    //! All game scenes
    enum EScene {
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

    //! Pack Project titles
    enum EPack {
        RP_SPORTS_PACK, //!< Wii Sports
        RP_PARTY_PACK,  //!< Wii Play
        RP_HEALTH_PACK, //!< Wii Fit
        RP_MUSIC_PACK,  //!< Wii Music
        RP_ALL_PACK     //!< Pack Project
    };

    //! Specific scene attributes
    struct SceneAttributes {
        //! @brief Scene ID
        s32 scene;
        //! @brief Pack ID
        s32 pack;
        //! @brief How to create the scene
        s32 createType;
        //! @brief Toggle "Now Loading" text (unused)
        s32 showLoadingText;
        //! @brief How to exit the scene
        s32 exitType;
        //! @brief Whether to use the RP common sound archive
        s32 useCommonSound;
        //! @brief Scene file directory
        const char* resDirName;
        //! @brief Proper name (unused lookup feature?)
        const char* sceneName;
    };

public:
    static RPSysScene* Create(EScene);
    static RPSysScene* CreateImpl(EScene);

    // TO-DO: Getters for each attribute field
    // Replace inlined calls of RP functions with branches to ex functions

private:
    static const SceneAttributes sSceneAttrTable[SCENE_MAX];
};

} // namespace spnet

#endif