#ifndef RP_SYSTEM_SCENE_CREATOR_H
#define RP_SYSTEM_SCENE_CREATOR_H
#include "types_rp.h"

#include <egg/core/eggSceneCreator.h>

/**
 * @brief Factory for all RP scenes
 * @details Not to be confused with the scene manager, the scene creator simply
 * creates/destroys scenes. The scene creator ensures that all scenes created
 * are intended for the current pack by referencing the scene attributes.
 * @wfuname
 */
class RPSysSceneCreator : public EGG::SceneCreator {
public:
    //! @brief RP Scene ID
    //! @wfuname
    enum ESceneID {
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

        SCENE_MAX
    };

    /**
     * @brief Sport ID
     */
    enum ESportID {
        SPORT_BASEBALL,
        SPORT_TENNIS,
        SPORT_GOLF,
        SPORT_BOXING,
        SPORT_BOWLING,

        SPORT_MAX
    };

    //! @brief Pack Project game ID
    enum EPackID {
        RP_SPORTS_PACK,
        RP_PARTY_PACK,
        RP_HEALTH_PACK,
        RP_MUSIC_PACK,
        RP_ALLPACK
    };

    /**
     * @brief Attributes to show the creator how to handle a given scene
     * @customname
     */
    struct SceneAttributes {
        //! @brief Scene ID
        s32 scene; // at 0x0
        //! @brief Pack ID
        s32 pack; // at 0x4
        //! @brief How to create the scene
        s32 createType; // at 0x8
        //! @brief Toggle "Now Loading" text (unused)
        s32 showLoadingText; // at 0xC
        //! @brief How to exit the scene
        s32 exitType; // at 0x10
        //! @brief Whether to use the RP common sound archive
        s32 useCommonSound; // at 0x14
        //! @brief Scene file directory
        const char* resDirName; // at 0x18
        //! @brief Proper name (unused lookup feature?)
        const char* sceneName; // at 0x1C
    };

public:
    //! @address 80184e10
    static RPSysSceneCreator* CreateInstance(EGG::Heap* heap);
    static RPSysSceneCreator* getInstance() { return sInstance; }

    s32 getLastSceneID() const { return mLastSceneID; }
    void setLastSceneID(s32 scene) { mLastSceneID = scene; }

    /**
     * @brief Fade out into a new scene, optionally reloading the current scene
     * @address 80184ba4
     * @return Success
     */
    bool changeSceneAfterFade(s32 sceneID, bool reenterCurrent);
    /**
     * @brief Change to the boot scene (performing a soft reset)
     * @address 80184b98
     */
    void changeSoftReset();

    /**
     * @brief Create a Sports Pack scene
     * @address 80184000
     */
    EGG::Scene* createSportsScene(s32 sceneID);

    //! @address 801845f4
    s32 getCreateType(s32 sceneID);
    //! @address 80184558
    s32 getExitType(s32 sceneID);
    //! @address 801844bc
    s32 getUseCommonSound(s32 sceneID);
    //! @address 80184758
    s32 getResDirName(s32 sceneID);
    //! @address 80184690
    s32 getSceneID(s32 sportID);
    //! @address 801846ec
    s32 getSportID(s32 sceneID);

    /**
     * @brief Create any Pack Project scene
     * @address 80184838
     */
    virtual EGG::Scene* create(s32 sceneID);

    /**
     * @brief Request engine shutdown
     * @address 80184804
     */
    virtual void destroy(s32);

private:
    RPSysSceneCreator(EGG::Heap* heap) : mParentHeap(heap), mLastSceneID(-1) {}
    //! @address 80183f68
    virtual ~RPSysSceneCreator() {}

private:
    //! @brief Heap in which this object was allocated
    EGG::Heap* mParentHeap; // at 0x4
    //! @brief Last created scene's ID
    s32 mLastSceneID; // at 0x8

    /**
     * @brief Configuration for all supported Pack Project scenes
     * @address 803820f8
     */
    static SceneAttributes sSceneAttributeTable[];

    /**
     * @brief Static instance
     * @address 804bf4f8
     */
    static RPSysSceneCreator* sInstance;
};

#endif