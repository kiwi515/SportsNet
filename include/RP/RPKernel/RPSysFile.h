#ifndef RP_KERNEL_FILE_H
#define RP_KERNEL_FILE_H
#include "types_rp.h"

#include <egg/core/eggDisposer.h>
#include <nw4r/ut/ut_list.h>

/**
 * @brief Disc file loaded into RAM
 * @details Similar to EGG's DvdFile structure,
 * except this class expects the file's data to already have been loaded into
 * RAM.
 *
 * Paths are relative to the project root (i.e. `"Common/Kokeshi/common.carc"`)
 *
 * In theory this class could be used for all open files, but the resource
 * manager seems to only use it for archives post-decompression. Perhaps it
 * "simulates" the existence of data only in memory as a file?
 *
 * This class has an additional ut::Node so that the resource manager can keep
 * track of all open files. It removes itself from the resource manager's file
 * list (at 0x10) on destruction.
 *
 * @wfuname
 */
class RPSysFile : public EGG::Disposer {
public:
    /**
     * @address 80199678
     * @param path File path (relative to project root)
     * @param size File size
     * @param data Pointer to file data
     */
    RPSysFile(const char* path, int size, const void* data);

    //! @address 80199604
    virtual ~RPSysFile();

public:
    //! @brief Link node for resource manager
    nw4r::ut::Node mNode; // at 0x10
private:
    //! @brief File path
    char mPath[128]; // at 0x18
    //! @brief File size
    int mSize; // at 0x98
    //! @brief File data
    void* mData; // at 0x9C
};

#endif