#ifndef EGG_MATH_VECTOR_H
#define EGG_MATH_VECTOR_H
#include "eggMath.h"
#include "math_types.h"
#include "types_egg.h"

namespace EGG {
struct Vector2f {
    Vector2f() {}
    Vector2f(f32 _x, f32 _y) : x(_x), y(_y) {}
    ~Vector2f();

    f32 x, y;

    static Vector2f zero;
    static Vector2f ex;
    static Vector2f ey;
};

struct Vector3f : nw4r::math::VEC3 {
    Vector3f() {}
    Vector3f(f32 _x, f32 _y, f32 _z) : VEC3(_x, _y, _z) {}
    ~Vector3f() {}

    f32 dot(const Vector3f& rhs) const {
        return mCoords.x * rhs.mCoords.x + mCoords.y * rhs.mCoords.y +
               mCoords.z * rhs.mCoords.z;
    }

    f32 length() const { return Math<f32>::sqrt(squaredLength()); }

    f32 squaredLength() const {
        return mCoords.x * mCoords.x + mCoords.y * mCoords.y +
               mCoords.z * mCoords.z;
    }

    Vector3f operator-() const {
        return Vector3f(-mCoords.x, -mCoords.y, -mCoords.z);
    }

    f32& operator()(int i) { return (&mCoords.x)[i]; }

    f32 normalise();

    // TO-DO: Resolve weak instance (eggDrawHelper i think?)
    Vector3f cross(const Vector3f& right) const;

    static Vector3f zero;
    static Vector3f ex;
    static Vector3f ey;
    static Vector3f ez;
};
} // namespace EGG

#endif