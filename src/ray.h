#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        // Empty constructor
        ray() {}

        // Arguments constructor
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        // Getter methods
        point3 origin() const { return orig; }
        vec3 direction() const { return dir; }

        // P(t), or at(t)
        point3 at(double t) const {
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif