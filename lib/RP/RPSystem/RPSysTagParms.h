#ifndef RP_SYSTEM_TAG_PARMS_H
#define RP_SYSTEM_TAG_PARMS_H
#include "types_RP.h"

#include <egg/core/eggStream.h>

/**
 * @brief Container for tag parameters
 * @details Base used for RP engine's GameConfig
 * @wfuname
 */
class RPSysTagParameters {
public:
    /**
     * @address 8018674c
     * @param name Container name
     */
    RPSysTagParameters(char* name);

private:
    //! @brief Name of parameter group
    const char* mName; // at 0x0
    //! @brief Children parameters
    RPSysTagParm* mChildren; // at 0x4
};

/**
 * @brief Base class for a tag parameter
 * @wfuname
 */
class RPSysTagParm {
public:
    /**
     * @address 80186840
     * @param parent Parent container
     * @param tag Parameter name
     */
    RPSysTagParm(RPSysTagParameters* parent, char* tag);

    /**
     * @brief Read parameter value
     * @address 80186748
     */
    virtual void read(EGG::Stream& stream);
    /**
     * @brief Write parameter value
     * @address 80186744
     */
    virtual void write(EGG::Stream& stream);
    /**
     * @brief Print parameter information? (stubbed)
     * @address 80186740
     */
    virtual void dump();

private:
    //! @brief Parameter tag
    char* mTag; // at 0x0
    //! @brief Next parameter in linked list
    RPSysTagParm* mNext; // at 0x4
};

/**
 * @brief Template for primitive typed tag parameters
 * @details Only the `int` template is used in OGWS
 * @tparam Parameter primitive type
 * @wfuname
 */
template <typename T> class RPSysPrimTagParm : public RPSysTagParm {
public:
    /**
     * @param parent Parent container
     * @param tag Parameter name
     */
    RPSysPrimTagParm(RPSysTagParameters* parent, char* tag)
        : RPSysTagParm(parent, tag) {}

    /**
     * @brief Read parameter value
     * @address 8018680c (\<int\> template)
     */
    virtual void read(EGG::Stream& stream);
    /**
     * @brief Read parameter value
     * @address 801867fc (\<int\> template)
     */
    virtual void write(EGG::Stream& stream);
    /**
     * @brief Print parameter information? (stubbed)
     * @address 801867f8 (\<int\> template)
     */
    virtual void dump();

private:
    //! @brief Parameter value
    T mValue; // at 0xC
};

/**
 * @brief Tag parameter class for string values
 * @wfuname
 */
class RPSysStringTagParm : public RPSysTagParm {
public:
    /**
     * @address 801867ac
     * @param parent Parent container
     * @param tag Parameter name
     */
    RPSysStringTagParm(RPSysTagParameters* parent, char* tag);

    /**
     * @brief Read parameter value
     * @address 80186770
     */
    virtual void read(EGG::Stream& stream);
    /**
     * @brief Write parameter value
     * @address 80186760
     */
    virtual void write(EGG::Stream& stream);
    /**
     * @brief Print parameter information? (stubbed)
     * @address 8018675c
     */
    virtual void dump();

private:
    //! @brief Parameter value
    const char* mValue; // at 0xC
};

#endif