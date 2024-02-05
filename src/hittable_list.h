#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
    public:
        // vector<hittable> is like an array of hittables.
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        // Clear is a function of std::vector
        void clear() { objects.clear(); }

        void add(shared_ptr<hittable> object) {
            // Push_back is a function of std::vector
            objects.push_back(object);
        }

        shared_ptr<hittable> get(int index) {
            return objects[index];
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            // Question:
            // Why do some classes not need constructors, like hit_record?
            // Do they just ues the default constructor?
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            for (const auto& object : objects) {
                // -> is used to access the public members of a class
                // related to . like object.hit(), but specifically access the member
                // of a structure/union using a pointer
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif