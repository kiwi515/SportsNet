#ifndef NW4R_LYT_TEXT_BOX_H
#define NW4R_LYT_TEXT_BOX_H
#include "types_nw4r.h"
#include "ut_Font.h"
#include "lyt_pane.h"

namespace nw4r
{
    namespace lyt
    {
        class TextBox : public Pane
        {
        public:
            TextBox();
            virtual ~TextBox(); // at 0x8
        };
    }
}

#endif