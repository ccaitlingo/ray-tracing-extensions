#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "vec3.h"

#include <iostream>
#include <string.h>
#include <ctime>

class camera {
    public:
        // Image
        double aspect_ratio = 16.0 / 9.0; // Width / height
        int image_width = 400; // Rendered image width in pixel count
        int samples_per_pixel = 10; // Count of random samples for each pixel
        int max_depth = 10; // Maximum number of ray bounces into scene

        // Positionable Camera
        double vfov = 90; // Vertical view angle (field of view)
        point3 lookfrom = point3(0,0,-1); // Point camera is looking from
        point3 lookat = point3(0,0,0); // Point camera is looking at
        vec3 vup = vec3(0,1,0); // Camera-relative "up" direction

        // Render
        void render(const hittable& world) {
            initialize();

            // For naming the file with the date and time
            // std::time_t t = std::time(0);
            // std::tm* now = std::localtime(&t);

            // In eclipse, use
            // std::ofstream ofs("test.ppm");

            // In eclipse, replace "std::cout" with "ofs"
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            // For each pixel
            for (int j = 0; j < image_height; ++j) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; ++i) {
                    color pixel_color(0,0,0);
                    for (int sample = 0; sample < samples_per_pixel; ++sample) {
                        ray r = get_ray(i, j);
                        // The video changes the name pixel_color to light
                        // for clarity
                        // The video also has a multiplier used on ray_color (16:10)
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    // In eclipse, replace "std::cout" with "ofs"
                    write_color(std::cout, pixel_color, samples_per_pixel);
                }
            }

            std::clog << "\rDone.   \n";
        }
    
    private:
        int image_height; // Rendered image height
        point3 center; // Camera center
        point3 pixel00_loc; // Location of pixel 0, 0
        vec3 pixel_delta_u; // Offset to pixel to the right
        vec3 pixel_delta_v; // Offset to pixel below
        vec3 u, v, w; // Camera frame basis vectors

        void initialize() {
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            // Changed from: center = point3(0,0,0);
            center = lookfrom;

            // Determine viewport dimensions
            // Changed from: auto focal_length = 1.0;
            auto focal_length = (lookfrom - lookat).length();
            // For positionable camera, keep track of view angle
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2 * h * focal_length;
            auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    
            // Calculate the u,v,w unit basis vectors for the camera coordinate frame
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            // Calculate the vectors across the horizontal and down the vertical viewport edges
            auto viewport_u = viewport_width * u; // Vector across viewport horizontal edge
            auto viewport_v = viewport_height * -v; // Vector down viewport vertical edge

            // Calculate the horizontal and verticlal delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left = center 
                                    - (focal_length*w) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        ray get_ray(int i, int j) const {
            // Get a randomly sampled camera ray for the pixel at location i, j.

            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto pixel_sample = pixel_center + pixel_sample_square();
            
            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 pixel_sample_square() const {
            // Returns a random point in the square surrounding a pixel at the origin
            auto px = -0.5 + random_double();
            auto py = -0.5 + random_double();
            return (px * pixel_delta_u) + (py * pixel_delta_v);
        }

        color ray_color(const ray& r, int depth, const hittable& world) const {
            // Sphere
            hit_record rec;
            // If we've exceed the ray bounce limit, no more light is gathered
            if (depth <= 0){
                return color(0,0,0);
            }
            // Ignore hits very close to intersection point
            if (world.hit(r, interval(0.001, infinity), rec)) {

                // Color to get a material-based diffuse
                ray scattered;
                color attenuation;
                // Material.scatter() alters attenuation and scattered
                if (rec.mat->scatter(r, rec, attenuation, scattered))
                    return ((attenuation * ray_color(scattered, depth-1, world)) += rec.mat->getEmissionPower());
                return color(0,0,0);
            }

            // Sky graident (background)
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            // Formula for a "lerp," or linear interpolation, or blended value
            // 0,0,0 is white, and 5,7,10 is blue
            // return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
            // Turn off the sky. 0,0,0 is black
            return color(0.25,0.35,0.5);
        }
};

#endif
