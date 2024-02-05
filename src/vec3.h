#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
    public:
        // e is just the name of our array
        double e[3];

        // CONSTRUCTORS
        // : is a shortcut for implementing the body of the constructor
        // Equivalent to doing e[0] = 0, e[1] = 1, etc.
        vec3() : e{0,0,0} {}
        // Another constructor!
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        // Constants
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // Defining operations
        // minus (-)
        // i.e. How do you subtract vectors?
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        // indexing ([])
        double operator[](int i) const { return e[i]; }
        // indexing ([])
        // The & declares this as a reference variable
        // Why have a repeat?
        // Ans: For when it is invoked on const or non-const objects
        double& operator[](int i) { return e[i]; }

        // add (+)
        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            // * = a pointer, allows you to refer directly to values in memory
            // (not referring to a copy).
            // The only difference btwn reference (&) and pointer (*) is that
            // a pointer can be null.
            return *this;
        }

        // multiply (*)
        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        // divide (/)
        vec3& operator/=(double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        // To avoid a zero scatter direction vector in lambertian materials
        bool near_zero() const {
            // Return true if the vector is close to zero in all dimensions
            auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility functions / Static Functions
// toString
inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// add (+) two given vectors
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// add (-) two given vectors
inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// multiply (*) to given vectors
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// multiply (*) a given vector by a constant
inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

// multiply (*) a given vector by a constant
inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

// divide (/) a given vector by a double
inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline vec3 random_in_unit_sphere() {
    // 1. Generate a random vector inside of the unit sphere
    while (true) { 
        // Make a random vector
        auto p = vec3::random(-1,1);
        // Ensure it's within the dotted unit SPHERE and not just
        // the unit square (see Fig 11 in book)
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_unit_vector() {
    // 2. Normalize the vector
    // Ensure it's a vector ON the unit sphere surface,
    // making it a unit vector
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3& normal){
    // 3. Invert the normalized vector if it falls onto the wrong
    // hemisphere
    vec3 on_unit_sphere = random_unit_vector();
    // We can do this by comparing the vector with the surface
    // normal
    if (dot(on_unit_sphere, normal) > 0.0) { // In the same hemisphere as the normal
        return on_unit_sphere; 
    } else {
        return -on_unit_sphere;
    }
}

vec3 reflect(const vec3& v, const vec3& n) {
    // Based on a vector diagram: Draw an incoming vector that
    // goes through a surface, and note that the vector that is
    // reflected can be drawn from a point 2b directly above
    // the original vector you drew.
    return v - 2*dot(v,n)*n;
}

#endif