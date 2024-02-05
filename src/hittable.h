#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "rtweekend.h"

class material;

class hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
        bool front_face;
        // When a ray hits a surface, mat (the material pointer) will be
        // set to point at the material pointer that the surface was 
        // originally given.
        shared_ptr<material> mat;

        vec3 getNormal(){
            return normal;
        }

        void set_face_normal(const ray& r, const vec3& outward_normal) {
            // Sets the hit record normal vecotr.
            // NOTE: the parameter 'outward_normal' is assumed to have unit length.
            
            // If in opposite directions...
            front_face = dot(r.direction(), outward_normal) < 0;
            // Ray is coming in, Normal will be outward
            normal = front_face ? outward_normal : -outward_normal;
            // If same directions... Ray is coming out, Normal will be inward
        }
};

class hittable {
    public:
        // The ~ is the deconstructor, or what is called when an
        // object is destroyed.  It destroys the object instance 
        // and frees up memory.
        virtual ~hittable() = default;

        // const means the code will not modify the data of the object
        // = 0 means that the function is "pure virtual" and MUST be
        // overridden by a subcalss
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

        // Note: We changed double ray_min and double ray_max to be one
        // parameter, interval ray_t, above.
};

#endif