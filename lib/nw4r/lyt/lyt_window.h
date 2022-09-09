#ifndef NW4R_LYT_WINDOW_H
#define NW4R_LYT_WINDOW_H
#include "lyt_pane.h"
#include "types_nw4r.h"
#include "ut_Font.h"

namespace nw4r {
namespace lyt {

class Window : public Pane {
public:
    Window();
    virtual ~Window(); // at 0x8
};

} // namespace lyt
} // namespace nw4r

#endif