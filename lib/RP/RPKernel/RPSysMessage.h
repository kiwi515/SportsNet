#ifndef RP_KERNEL_MESSAGE_H
#define RP_KERNEL_MESSAGE_H
#include "types_RP.h"

#include <egg/util/eggMsgRes.h>

/**
 * @brief MsgRes wrapper with extra MsgInfo support
 * @details Has added support for the extra text features
 * seen in RP BMG files (scale, char space, etc.)
 * @wfuname
 */
class RPSysMessage : public EGG::MsgRes {
public:
    /**
     * @brief RP extension for MsgInfo
     * @details MsgInfoBlock stores the sizes of its entries,
     * allowing games to add extra features to their text.
     */
    struct RPMsgInfoBlockEntry : public EGG::MsgRes::MsgInfoBlockEntry {
        //! @brief Text scale
        u16 mScale; // at 0x8
        //! @brief Text kerning
        s8 mCharSpace; // at 0xA
    };

public:
    /**
     * @address 80190dec
     * @param bin Binary message file (BMG)
     */
    RPSysMessage(const void* bin, EGG::Heap* heap);

    //! @address 80190d94
    virtual ~RPSysMessage();

    /**
     * @brief Get message info by ID
     * @param groupId Message group ID
     * @param msgId Message ID
     * @address 80190d90
     */
    RPMsgInfoBlockEntry* GetMessage(u32 groupId, u32 msgId);

    /**
     * @brief Get message attribute by ID
     * @param groupId Message group ID
     * @param msgId Message ID
     * @address 80190d6c
     */
    u32 GetAttribute(u32 groupId, u32 msgId);

    /**
     * @brief Get message scale by ID
     * @param groupId Message group ID
     * @param msgId Message ID
     * @address 80190d48
     */
    u16 GetScale(u32 groupId, u32 msgId);

    /**
     * @brief Get message char space (kerning) by ID
     * @param groupId Message group ID
     * @param msgId Message ID
     * @address 80190d24
     */
    s8 GetCharSpace(u32 groupId, u32 msgId);
};

#endif