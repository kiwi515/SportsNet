#ifndef RP_SPORTS_BASE_SCENE_H
#define RP_SPORTS_BASE_SCENE_H
#include "RPSysScene.h"
#include "RPSysSceneCreator.h"
#include "types_RP.h"

/**
 * @brief Base class for all Sports Pack scenes
 * @customname
 */
class RPSportsBaseScene : public RPSysScene {
public:
    RPSportsBaseScene() {}
    //! @address 80184460
    virtual ~RPSportsBaseScene() {}

    /**
     * @brief Initialize/setup the scene
     * @address 801ef1c8
     */
    virtual void Configure();
    /**
     * @brief Load any needed resources
     * @address 801ef184
     */
    virtual void LoadResource();
    /**
     * @brief Re-initialize the scene
     * @address 801ef140
     */
    virtual void Reset();
    /**
     * @brief Run scene logic
     * @address 801ef0fc
     */
    virtual void Calculate();
    /**
     * @brief Exit the scene
     * @address 801ef064
     */
    virtual void Exit();

    /**
     * @brief Configure callback
     * @address 801ef20c
     */
    virtual void OnConfigure();
    /**
     * @brief LoadResource callback
     * @address 801ef1c4
     */
    virtual void OnLoadResource();
    /**
     * @brief Reset callback
     * @address 801ef180
     */
    virtual void OnReset();
    /**
     * @brief Calculate callback
     * @address 801ef13c
     */
    virtual void OnCalculate();
    /**
     * @brief UserDraw callback
     * @address 801ef0f8
     */
    virtual void OnUserDraw();
    /**
     * @brief DebugDraw callback
     * @address 801ef0b4
     */
    virtual void OnDebugDraw();
    /**
     * @brief Exit callback
     * @address 801ef0a0
     */
    virtual void OnExit();

    /**
     * @brief Any drawing the object needs to do
     * @address 801ef0b8
     */
    virtual void UserDraw();
    /**
     * @brief Debug draw pass, nearly all objects stub this out
     * @address 801ef0a4
     */
    virtual void DebugDraw();

protected:
    //! @brief Current sequence (from sequence mgr)
    u32 mSequence; // at 0x44
    //! @brief Current training game (from sequence mgr)
    u32 mTrainingGame; // at 0x48

    //! @brief Blurs the scene
    BOOL mIsBlurred; // at 0x4C
    //! @brief Scene blur amount
    //! @details Interpolates from 0 to 1 by 0.05/frame
    f32 mBlurAmount; // at 0x50

    //! @brief Current sport ID
    u32 mSport; // at 0x54

    //! @brief Pause permission
    BOOL mCanPause; // at 0x58
    //! @brief Hide scene with fade color
    BOOL mIsHidden; // at 0x5C

    //! @brief Sports text (sports_message.bmg)
    RPSysMessage* mSportsMsg; // at 0x60
    //! @brief Common text (common_message.bmg)
    RPSysMessage* mCommonMsg; // at 0x64

    UNKTYPE* mSkillGraph; // at 0x68
    UNKTYPE* mScreenWipe; // at 0x6C
    UNKTYPE* PTR_0x70;
    UNKTYPE* PTR_0x74;
    UNKTYPE* PTR_0x78;
    UNKTYPE* mTutorialSkip; // at 0x7C
    UNKTYPE* PTR_0x80;
    RPSportsTrainingResult* mTrainingResultLyt; // at 0x84
    UNKTYPE* PTR_0x88;
    UNKTYPE* PTR_0x8C;
    UNKTYPE* PTR_0x90;
    UNKTYPE* PTR_0x94;
    UNKTYPE* PTR_0x98;
};

#endif