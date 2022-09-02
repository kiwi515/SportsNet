#ifndef MATO_KERNEL_COLOR_H
#define MATO_KERNEL_COLOR_H
#include "types.h"

namespace mato {

class Color {
public:
    Color(u8 r, u8 g, u8 b, u8 a) : mRed(r), mGreen(g), mBlue(b), mAlpha(a) {}
    Color(u32 color) {
        mRed = (color >> 24) & 0xFF;
        mGreen = (color >> 16) & 0xFF;
        mBlue = (color >> 8) & 0xFF;
        mAlpha = (color >> 0) & 0xFF;
    }
    Color() : mRed(255), mGreen(255), mBlue(255), mAlpha(255) {}

    const u8& operator[](int i) const { return (&mRed)[i]; }
    u8& operator[](int i) { return (&mRed)[i]; }

    operator u32() const { return rgba(); }

    const u8& r() const { return mRed; }
    u8& r() { return mRed; }

    const u8& g() const { return mGreen; }
    u8& g() { return mGreen; }

    const u8& b() const { return mBlue; }
    u8& b() { return mBlue; }

    const u8& a() const { return mAlpha; }
    u8& a() { return mAlpha; }

    u32 rgba() const { return mRed << 24 | mGreen << 16 | mBlue << 8 | mAlpha; }
    u32 argb() const { return mAlpha << 24 | mRed << 16 | mBlue << 8 | mGreen; }

private:
    u8 mRed;
    u8 mGreen;
    u8 mBlue;
    u8 mAlpha;
};

static const Color scColorBlack(0, 0, 0, 255);
static const Color scColorWhite(255, 255, 255, 255);
static const Color scColorRed(255, 0, 0, 255);
static const Color scColorGreen(0, 255, 0, 255);
static const Color scColorBlue(0, 0, 255, 255);

} // namespace mato

#endif