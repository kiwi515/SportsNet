#ifndef RP_SYSTEM_DVD_STATUS_H
#define RP_SYSTEM_DVD_STATUS_H
#include "types_rp.h"

#include <egg/core/eggColorFader.h>
#include <egg/core/eggHeap.h>

/**
 * @brief Current status/error of the DVD.
 * @details Similar to EGG's DvdStatus, but seems to be a re-implementation
 * (missing Disposer inheritance)
 * @wfuname
 */
class RPSysDvdStatus {
public:
    //! @brief Status of the last access to the DVD drive
    enum EDvdStatus {
        DVD_IDLE = -2,
        DVD_READING,
        DVD_DISC_REMOVED,
        DVD_CANNOT_READ,
        DVD_FATAL_ERROR
    };

public:
    //! @address 80188280
    static RPSysDvdStatus* CreateInstance(EGG::Heap* heap);
    static RPSysDvdStatus* getInstance() { return sInstance; }

    /**
     * @brief Draw status message (only if an error has occurred)
     * @address 80187fa4
     */
    void draw();

    /**
     * @brief Update status using DVD library
     * @address 8018818c
     */
    void update();

    /**
     * @brief Check if the DVD cannot be accessed
     * @address 80188260
     * @typo
     */
    bool isErrorOccured();

private:
    RPSysDvdStatus(EGG::Heap* heap)
        : mParentHeap(heap), mErrorStatus(DVD_IDLE) {
        mErrorMessage = new char[256];

        mErrorFader =
            new EGG::ColorFader(0.0f, 0.0f, 640.0f, 456.0f, nw4r::ut::Color(0),
                                EGG::ColorFader::STATUS_PREPARE_IN);

        // Maybe the status in the constructor is a defualt argument?
        mErrorFader->setStatus(EGG::ColorFader::STATUS_PREPARE_IN);
    }

    //! @address 80187f64
    virtual ~RPSysDvdStatus();

private:
    //! @brief Heap in which this object was allocated
    EGG::Heap* mParentHeap; // at 0x4
    //! @brief DVD status
    s32 mErrorStatus; // at 0x8
    //! @brief Error message to draw (constructed when needed)
    const char* mErrorMessage; // at 0xC
    //! @brief Fader to black out the screen when displaying an error message
    EGG::ColorFader* mErrorFader; // at 0x10

    /**
     * @brief Static instance
     * @address 804bf500
     */
    static RPSysDvdStatus* sInstance;
};

#endif