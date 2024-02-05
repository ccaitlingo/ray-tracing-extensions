#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "ray.h"

class hit_record;

class material {
    // The material should do two things:
    // 1. Produce a scattered ray (or say it absorbed the incident ray)
    // 2. If scattered, say how much the ray should be attenuated
    public:
        virtual ~material() = default;

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;

        //***
        virtual color getEmissionPower(){
            return emission_power;
        }
    private:
        color emission_power;
    //***
};

class lambertian : public material {
    // A lambertian material tells the ray to always scatter, instead of
    // occasionally fully absorbing it
    // The ray will also attenuate (lose energy)
    public:
        lambertian(const color& a) : albedo(a) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
            auto scatter_direction = rec.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    private: 
        color albedo;
};

class metal : public material {
    // Scatters with direction
    public:
        metal(const color& a) : albedo(a) {}
        
        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }

    private:
        color albedo;
};

class emissive : public material {
    public:
        emissive(const color& a, const color& e) : albedo(a), emission_power(e) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
            // Optional: bias the direction of the light
            // You have to get world normal from the sphere that is the ground (or any other
            // vector that you want to bias scattering towards)
            // auto scatter_direction = unit_vector(bias_normal + random_in_unit_sphere());
            
            auto scatter_direction = random_in_unit_sphere();
            // Scattered now holds the next direction the ray has bounced in
            scattered = ray(rec.p, scatter_direction);
            // Attenuation represents the color of the material. Three different color channels
            // will be multiplied to the ray_color, always reducing or "attenuating" the contribution 
            // of the ray to the final pixel color

            // In the video, attenuation is called contribution
            attenuation = albedo;
            return true;
        }

        color getEmissionPower(){
            return emission_power;
        }

    private:
        color albedo;
        color emission_power;
        //vec3 bias_normal;
};

#endif