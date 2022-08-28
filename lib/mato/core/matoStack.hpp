#ifndef MATO_CORE_STACK_H
#define MATO_CORE_STACK_H
#include "matoAssert.h"
#include "matoLinkList.hpp"

namespace mato {

/**
 * @brief Generic stack
 * @tparam T Iterable type
 * @note Uses TLinkList under the hood, so the generic type still requires a
 * TLinkListNode and GetNodeOffset()
 */
template <typename T> class TStack {
public:
    TStack() {}
    virtual ~TStack() {}

    void Push(T* elem) {
        MATO_ASSERT(elem != NULL);
        mData.Append(elem);
    }

    T* Pop() {
        T* elem = mData.Back();
        mData.Remove(mData.End());
        return elem;
    }

    T* Peek() const { return mData.Back(); }

    u32 Size() const { return mData.Size(); }

    bool IsEmpty() const { return Size() == 0; }

private:
    TLinkList<T> mData;
};

} // namespace mato

#endif