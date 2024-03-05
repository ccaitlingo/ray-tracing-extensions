#ifndef TRIANGLE_PLANE_H
#define TRIANGLE_PLANE_H

#include "hittable.h"
#include "vec3.h"

class triangle_plane : public hittable {
    public:
        triangle_plane(point3 _v0, point3 _v1, point3 _v2, shared_ptr<material> _material) : v0(_v0), v1(_v1), v2(_v2), mat(_material) {}

        vec3 vec0() const { return v0; }
        vec3 vec1() const { return v1; }
        vec3 vec2() const { return v2; }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            // Muller-Trumbore Algorithm
            // This is the version where either face can detect a ray intersection.

            double bary_u, bary_v;
            vec3 edge1;
            vec3 edge2;
            vec3 origin_minus_v0; // Ray origin minus vertex 0
            vec3 cross_dir_edge2; // Cross product of ray direction and edge2
            vec3 cross_originMinusV0_edge1; // Cross product of (ray origin minus vertex 0) and edge1
            double det; // Determinant
            double inv_det; // Inverse determinant
            double t;

            edge1 = v1 - v0;
            edge2 = v2 - v0;

            // Calculate the determinant (we'll need to divide by this later)
            cross_dir_edge2 = cross(r.direction(), edge2);
            det = dot(edge1, cross_dir_edge2);

            // If det = 0, then ray is parallel, so no intersection
            if (det > -0.001 && det < 0.001){
                return false;
            }
            inv_det = 1.0 / det;

            // Calculate u
            origin_minus_v0 = r.origin() - v0;
            bary_u = dot(origin_minus_v0, cross_dir_edge2) * inv_det;
            // Does the value of u show that the (possible intersection) point is in the triangle?
            if (bary_u < 0.0 || bary_u > 1){
                return false;
            }

            // Calculate v
            cross_originMinusV0_edge1 = cross(origin_minus_v0, edge1);
            bary_v = dot(r.direction(), cross_originMinusV0_edge1) * inv_det;
            // Does the value of v show that the (possible intersection) point is in the triangle?
            if (bary_v < 0.0 || bary_v + bary_u > 1.0){
                return 0;
            }

            // Calculate t!
            t = dot(edge2, cross_originMinusV0_edge1) * inv_det;
            if (!ray_t.surrounds(t)){ return false; }
            rec.t = t;
            rec.p = r.at(rec.t); // return p... use the ray and t to find this
            rec.set_face_normal(r, unit_vector(cross(edge1, edge2))); // we've already got this from our .obj file, but it's also quick to calculate
            rec.mat = mat;

            return true;
        }

    private:
        point3 v0;
        point3 v1;
        point3 v2;
        shared_ptr<material> mat;
};

#endif