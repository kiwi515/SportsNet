#ifndef RP_KERNEL_WIDE_TEXT_WRITER_H
#define RP_KERNEL_WIDE_TEXT_WRITER_H
#include "types_RP.h"

/**
 * @brief RP engine screen wide text (wchar_t) writer
 * @details This likely follows RPSysTextWriter in its inheritance
 * from NW4R structures, but this is not known for sure.
 * Only one function is in Wii Sports, and very few are in Wii Fit U.
 * @wfuname
 */
class RPSysWideTextWriter {
public:
    /**
     * @brief Initialize format buffer
     * @address 80198968
     */
    static void Initialize();

private:
    /**
     * @brief Static format buffer
     * @details Name from NW4R's text writer, because they share sizes
     * @address 804bf558
     */
    static wchar_t* mFormatBuffer;
};

#endif