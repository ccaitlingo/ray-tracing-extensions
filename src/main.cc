#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "hittable.h"
#include "material.h"
#include "sphere.h"

#include <iostream>

int main() {
    // This got moved to camera.h!
    // Image
    // Calculate the image height, and ensure it's at least 1.

    // World
    hittable_list world;

    // Material
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));
    auto material_emis = make_shared<emissive>(color(1.0, 1.0, 0.0),color(.5, 0.3, 0.0));
    auto material_emis_blue = make_shared<emissive>(color(0.2, 0.2, 1.0),color(0.2, 0.8, 1.0));

    // Spheres
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    //world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_emis));
    world.add(make_shared<sphere>(point3( 0.5,   -0.4, -0.7), 0.1, material_emis_blue));
    world.add(make_shared<sphere>(point3(-0.25,  -0.4,  -0.6),   0.1, material_right));
    world.add(make_shared<sphere>(point3( -0.6,   -0.45,  -0.8),   0.06, material_center));

    // This was moved too!
    // Camera
    // Calculate the vectors across the horizontal and down the vertical viewport edges
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // Calculate the location of the upper left pixel.
    // And then...
    // Render

    // After we moved all that to camera, we now have:
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}
