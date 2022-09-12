#ifndef NW4R_LYT_PICTURE_H
#define NW4R_LYT_PICTURE_H
#include "lyt_pane.h"
#include "types_nw4r.h"
#include "ut_Font.h"

namespace nw4r {
namespace lyt {

class Picture : public Pane {
public:
    Picture();
    virtual ~Picture(); // at 0x8
};

} // namespace lyt
} // namespace nw4r

#endif