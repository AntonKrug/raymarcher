#include <tuple>

#ifndef RAYMARCHER_SCENE_H
#define RAYMARCHER_SCENE_H

#include "../materialE.h"
#include "../vector.h"


template<class Derived>
class Scene {
public:

    inline static vector getCameraOrigin() {
        return Derived::cameraOrigin;
        return Derived::cameraOrigin;
    }

    inline static vector getCameraDirection() {
        return Derived::cameraDirection;
    }

    inline static vector getCameraRightPixel() {
        return Derived::cameraRightPixel;
    }

    inline static vector getCameraDownPixel() {
        return Derived::cameraDownPixel;
    }

    inline static vector getLightPosition() {
        return Derived::lightPosition;
    }

    static std::tuple<float,  materialE> signedDistance(vector point) {
        return Derived::signedDistance(point);
    }
};

#endif