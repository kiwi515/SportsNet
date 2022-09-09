#ifndef RP_KERNEL_LYT_TEXT_BOX_H
#define RP_KERNEL_LYT_TEXT_BOX_H
#include "types_RP.h"

#include <nw4r/lyt/lyt_textBox.h>

/**
 * @brief NW4R layout textbox extension
 */
class RPSysLytTextBox : public nw4r::lyt::TextBox {
public:
    /**
     * @brief Copy font color from another textbox
     * @param other Textbox to copy from
     * @address 80198ce8
     */
    void copyFontColor(const RPSysLytTextBox& other);

    /**
     * @brief Set text horizontal scale
     * @param scale New scale
     * @address 80198e24
     */
    void setScaleX(f32 scale);

    /**
     * @brief Set custom text, and set attributes from a BMG message
     * @param msg Message file
     * @param group Message group ID (for attributes)
     * @param msgId Message ID (for attributes)
     * @param text New text
     * @address 80198e24
     */
    void setMessage(RPSysMessage* msg, u32 groupId, u32 msgId,
                    const wchar_t* text);

    /**
     * @brief Set text to formatted string from BMG
     * @param msg Message file
     * @param groupId Message group ID
     * @param msgId Message ID
     * @param argc Number of format arguments
     * @param argv Format arguments
     * @address 80198fd0
     */
    void setMessage(RPSysMessage* msg, u32 groupId, u32 msgId, int argc,
                    __va_list_struct* argv);

    /**
     * @brief Set text to formatted string from BMG
     * @param msg Message file
     * @param groupId Message group ID
     * @param msgId Message ID
     * @param argc Number of format arguments
     * @param ... Format arguments
     * @address 80199148
     */
    void setMessage(RPSysMessage* msg, u32 groupId, u32 msgId, int argc, ...);

    /**
     * @brief Set text to formatted string
     * @param fmt Format string
     * @param argc Number of format arguments
     * @param ... Format arguments
     * @address 8019931c
     */
    void setText(const wchar_t* fmt, int argc, ...);
};

#endif