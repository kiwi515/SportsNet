#ifndef RP_SPORTS_PLAYER_DATA_H
#define RP_SPORTS_PLAYER_DATA_H
#include "types_rp.h"

#include <types_egg.h>

/**
 * @brief Wii Sports save file player list entry
 *
 * NOTE: Not a packed structure, this is an abstraction of the binary format
 *
 * (Custom name, derived from some Wii Fit U symbols)
 */
class RPSportsPlayerData {
public:
    /**
     * @brief For mFlags
     */
    enum EPlayerFlag { FLAG_ON_PLAYER_LIST = (1 << 1) };

    /**
     * @brief Used to index arrays in the sport data.
     *
     * With regards to the Iwata Asks interview, this enum likely represents
     * the order in which the sports were added to the game.
     */
    enum ESportID {
        SPORT_BASEBALL,
        SPORT_TENNIS,
        SPORT_GOLF,
        SPORT_BOWLING,
        SPORT_BOXING,

        SPORT_MAX
    };

    /**
     * @brief Training mode medals
     * For setTrainingMedal
     */
    enum ETrainingMedal {
        MEDAL_NONE,
        MEDAL_BRONZE,
        MEDAL_SILVER,
        MEDAL_GOLD,
        MEDAL_PLATINUM,
    };

    /**
     * @brief Golf difficulties
     * For indexing the best score array
     */
    enum EGolDifficulty {
        DIFF_NINEHOLE,
        DIFF_BEGINNER,
        DIFF_INTERMEDIATE,
        DIFF_EXPERT,

        DIFF_MAX
    };

    /**
     * @brief Used to index fitness data by statistics.
     */
    enum EStatID {
        STAT_STAMINA,
        STAT_SPEED,
        STAT_BALANCE,

        STAT_MAX
    };

public:
    RPSportsPlayerData(); // 8018ad34

    //! For serialization (From WFU)
    void write(EGG::RamStream* stream) const; // 8018ad70
    void read(EGG::RamStream* stream);        // 8018b0e4

    //! Player list debut time
    void setDebutTime(RPTime32 time); // 8018b44c
    RPTime32 getDebutTime() const;    // 8018b454

    //! Mii unique ID
    void setUniqueID(const u8* id);    // 8018b45c
    void getUniqueID(u8* idOut) const; // 8018b4a0

    //! Player list flag
    void setOnPlayerList(bool onList); // 8018b4e4
    bool isOnPlayerList() const;       // 8018b50c

    //! Last test start date
    void setLastFitTestStartDate(RPTime16 date); // 8018b518
    RPTime16 getLastFitTestStartDate() const;    // 8018b520

    // TO-DO: SHORTS_0x2D0/SHORTS_0x386 getters/setters

    //! Last test end date
    void setLastFitTestEndDate(RPTime16 date); // 8018b568
    RPTime16 getLastFitTestEndDate() const;    // 8018b570

    //! TO-DO: SHORTS_0x2B0/SHORTS_0x2AC getters/setters

    //! Fitness stats (Stamina, Speed, Balance)
    void setFitnessStatValue(u16 value, u32 stat); // 8018b5c0
    u16 getFitnessStatValue(u32 stat) const;       // 8018b5d0

    //! Total count of completed fitness tests
    void setTotalFitnessTests(int num); // 8018b5e0
    u16 getTotalFitnessTests() const;   // 8018b5e8

    //! Date of first completed fitness test
    void setFirstFitTestEndDate(RPTime16 date);           // 8018b5f0
    RPTime16 getFirstFitTestEndDate(RPTime16 date) const; // 8018b5f8

    //! Boxing training records
    void setBoxTrainingRecord(u32 game, u16 record); // 8018b600
    u16 getBoxTrainingRecord(u32 game) const;        // 8018b610

    //! Golf training records
    void setGolTrainingRecord(u32 game, u16 record); // 8018b600
    u16 getGolTrainingRecord(u32 game) const;        // 8018b610

    //! Golf hole-in-one count (for Wii Message Board)
    void setGolNumHoleInOnes(u8 num); // 8018b640
    u8 getGolNumHoleInOnes() const;   // 8018b648

    //! Golf high scores
    void setBowHighScore(s8 score, u32 difficulty); // 8018b650
    u16 getBowHighScore(u32 difficulty) const;      // 8018b65c

    //! Bowling training records
    void setBowTrainingRecord(u32 game, u16 record); // 8018b66c
    u16 getBowTrainingRecord(u32 game) const;        // 8018b67c

    //! Bowling perfect game count (for Wii Message Board)
    void setBowNumPerfectGames(u8 num); // 8018b68c
    u8 getBowNumPerfectGames() const;   // 8018b694

    //! Standard Bowling high score
    void setBowHighScore(u16 score); // 8018b69c
    u16 getBowHighScore() const;     // 8018b6a4

    //! Tennis training records
    void setTnsTrainingRecord(u16 record, u32 game); // 8018b6ec
    u16 getTnsTrainingRecord(u32 game) const;        // 8018b6f8

    // TO-DO: FLOAT_0x278/FLOAT_0x274 getter/setter

    // TO-DO: Unlockable(?) flag getter/setter

    // TO-DO: Flag 0x4 getter/setter

    //! Training mode medals
    void setTrainingMedal(u8 medal, u32 sport, u32 game); // 8018b788
    u8 getTrainingMedal(u32 sport, u32 game) const;       // 8018b7a0

    //! Training mode play counts
    void setTrainingPlayCount(u16 count, u32 sport, u32 game); // 8018b7b8
    u16 getTrainingPlayCount(u32 sport, u32 game) const;       // 8018b7d0

    //! General sport play counts
    void setPlayCount(u16 count, u32 sport); // 8018b7e8
    u16 getPlayCount(u32 sport) const;       // 8018b7f8

    //! Training mode first play dates
    void setTrainingFirstPlayDate(RPTime16 date, u32 sport,
                                  u32 game);                      // 8018b808
    RPTime16 getTrainingFirstPlayDate(u32 sport, u32 game) const; // 8018b820

    //! Standard first play dates
    void setStandardFirstPlayDate(RPTime16 date, u32 sport); // 8018b838
    RPTime16 getStandardFirstPlayDate(u32 sport) const;      // 8018b848

    //! Skill level graphs
    void setSkillGraphNode(u16 delta, u32 sport, u32 n); // 8018b858
    u16 getSkillGraphNode(u32 sport, u32 n) const;       // 8018b858

    //! Skill levels
    void setSkillLevel(f32 skill, u32 sport); // 8018b888
    f32 getSkillLevel(u32 sport) const;       // 8018b898

    // TO-DO: BYTE_0x10 getters/setters

    //! Reset all data (From WFU)
    void reset(); // 8018b994

private:
    static const u32 TRAINING_MAX = 3;
    static const u32 GRAPH_LENGTH = 49;

    /**
     * General player data
     */
    //! Player list entry flags
    u32 mFlags; // at 0x0
    //! Mii unique ID
    u8 mUniqueID[8]; // at 0x4
    //! @brief Time player was added to the player list
    //! (referred to as their debut on the message board)
    RPTime32 mDebutTime; // at 0xC
    //! Another set of flags
    u8 BYTE_0x10;
    //! Player skill levels
    f32 mSkillLevels[SPORT_MAX]; // at 0x14
    //! @brief Nodes on the Skill Level graph.
    //! Nodes are stored from most recent,
    //! and represent vertical displacement from the previous node.
    //! Rightmost node is displacement from top of graph
    s16 mSkillGraphs[SPORT_MAX][GRAPH_LENGTH]; // at 0x28
    //! First time playing the standard gamemode of any sport
    RPTime16 mStandardFirstPlayDates[SPORT_MAX]; // at 0x212
    //! First time playing the training games of any sport
    RPTime16 mTrainingFirstPlayDates[SPORT_MAX][TRAINING_MAX]; // at 0x21C
    //! @brief Sport-specific counter
    //! Most sports' count matches played, but golf's counts holes played
    u16 mPlayCounts[SPORT_MAX]; // at 0x23A
    //! Play count of all training games
    u16 mTrainingPlayCounts[SPORT_MAX][TRAINING_MAX]; // at 0x244
    //! Medals in all training games
    u8 mTrainingMedals[SPORT_MAX][TRAINING_MAX]; // at 0x262

    /**
     * Tennis player data
     */
    u16 SHORT_0x272;
    f32 FLOAT_0x274;
    f32 FLOAT_0x278;
    //! Tennis training high scores
    u8 mTnsTrainingRecords[TRAINING_MAX]; // at 0x27C

    /**
     * Baseball player data
     */
    //! @brief Hitting Home Runs best runs
    //! Highest home run count
    u8 mBsbHomerunBestRuns; // at 0x27F
    //! @brief Hitting Home Runs high score
    //! Best total run distance
    u16 mBsbHomerunBestDistance; // at 0x280
    //! Swing Control high score
    u8 mBsbUchiwakeHighScore; // at 0x282
    //! Batting Practice high score
    u8 mBsbRenzokuHighScore; // at 0x283

    /**
     * Bowling player data
     */
    u16 SHORT_0x284;
    //! Best score in standard Bowling
    u16 mBowHighScore; // at 0x286
    //! Perfect game counter (for message board)
    u8 mBowNumPerfectGames; // at 0x288
    //! Bowling training high scores
    u16 mBowTrainingRecords[TRAINING_MAX]; // at 0x28A

    /**
     * Golf player data
     */
    //! High scores on each course
    s8 mGolHighScores[DIFF_MAX]; // at 0x290
    //! For message board
    u8 mGolNumHoleInOnes;                  // at 0x294
    u16 mGolTrainingRecords[TRAINING_MAX]; // at 0x296

    /**
     * Boxing player data
     */
    //! Boxing training high scores
    u16 mBoxTrainingRecords[TRAINING_MAX]; // at 0x29C

    /**
     * Wii Fitness player data
     */
    //! Date of first completed test
    RPTime16 mFirstFitTestEndDate; // at 0x2A2
    //! Only counts completed tests
    u16 mTotalFitnessTests; // at 0x2A4
    //! Fitness stat rating (triangle graphic)
    u16 mFitnessStatRating[STAT_MAX]; // at 0x2A6
    //! Something coupled with the stat rating
    u8 BYTES_0x2AC[STAT_MAX];
    //! [SPORT_MAX][STAT_MAX]?
    u16 SHORTS_0x2B0[5][3];
    //! Date last test was completed
    RPTime16 mLastFitTestEndDate; // at 0x2CE
    //! Age/date for last 90 days?
    u16 SHORTS_0x2D0[91];
    RPTime16 SHORTS_0x386[91];
    //! Date last test was started (to stop early exits)
    RPTime16 mLastFitTestStartDate; // at 0x43C
    u16 SHORTS_0x43E[15];
};

#endif