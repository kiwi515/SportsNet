#ifndef MATO_KERNEL_MAP_FILE_H
#define MATO_KERNEL_MAP_FILE_H
#include "matoLinkList.hpp"

namespace mato {

/**
 * @brief Kamek symbol map utility for debugging exceptions
 */
class MapFile {
public:
    enum LinkType {
        LINK_NONE,   //!< Map file not loaded
        LINK_STATIC, //!< Map file for static module
        LINK_DYNAMIC //!< Map file for dynamic module
    };

    /**
     * @brief Map file symbol structure
     */
    struct Symbol {
        static u32 GetNodeOffset() { return offsetof(Symbol, node); }

        //! @brief List node
        TLinkListNode node;
        //! @brief Symbol linkage
        LinkType type;
        //! @brief Symbol location
        union {
            void* addr;
            u32 offset;
        };
        //! @brief Symbol size
        u32 size;
        //! @brief Symbol name (owned by map binary)
        char* name;
    };

public:
    static MapFile& GetInstance() {
        static MapFile instance;
        return instance;
    }

    void LoadFromDVD(const char* path, LinkType type);
    void Close();
    const Symbol* QueryTextSymbol(const void* addr);

private:
    MapFile();
    virtual ~MapFile();

    void Unpack();

private:
    //! @brief Map file type
    LinkType mType;
    //! @brief Map file text
    char* mMapBinary;
    //! @brief Whether the map has been unpacked
    bool mIsUnpacked;
    //! @brief Map symbols
    TLinkList<Symbol> mSymbols;
};

} // namespace mato

#endif