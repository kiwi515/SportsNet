#ifndef RP_KERNEL_LYT_RES_ACCESSOR_H
#define RP_KERNEL_LYT_RES_ACCESSOR_H
#include "types_RP.h"

#include <egg/types_egg.h>
#include <nw4r/lyt/lyt_arcResourceAccessor.h>

/**
 * @brief ArcResourceAccessor wrapper used for layouts,
 * with added support for resfont data
 * @wfuname
 */
class RPSysLytResAccessor {
public:
    class InternalAccessor : public nw4r::lyt::ArcResourceAccessor {
    public:
        InternalAccessor();

        //! @address 80198c78
        virtual ~InternalAccessor(); // at 0x8

        /**
         * @brief Get resource from the open archive
         * @details Font queries are redirected to the font manager
         * @param type Resource type (char literal)
         * @param name Resource name
         * @param[out] length Resource length
         * @address 80198c54
         */
        virtual void* GetResource(u32 type, const char* name,
                                  u32* length); // at 0xC
    };

public:
    RPSysLytResAccessor();

    /**
     * @brief Create a resource accessor from the specified heap
     * @param heap Parent heap
     * @address 80198bb8
     */
    static RPSysLytResAccessor* create(EGG::Heap* heap);

    /**
     * @brief Mount an archive
     * @param archive Archive binary
     * @param dir Directory to open
     * @return Success
     * @address 80198b6c
     */
    bool mountArchive(void* archive, const char* dir);

    /**
     * @brief Get resource from the open archive
     * @details Font queries are redirected to the font manager
     * @param type Resource type (char literal)
     * @param name Resource name
     * @param[out] length Resource length
     */
    void* getResource(u32 type, const char* name, u32* length) {
        return mInternalAccessor->GetResource(type, name, length);
    }

private:
    InternalAccessor* mInternalAccessor; // at 0x0
};

#endif