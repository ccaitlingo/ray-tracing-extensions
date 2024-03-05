#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "hittable.h"
#include "material.h"
#include "sphere.h"
#include "triangle_plane.h"
#include "parser.h"

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
    auto material_emis_bright = make_shared<emissive>(color(1.0, 1.0, 0.0),color(1.0, 1.0, 1.0));

    // Spheres
    world.add(make_shared<sphere>(point3(0,    3.0, 1.0),   1.0, material_emis_bright));
    // world.add(make_shared<sphere>(point3(0, 1.5, 0), 0.5, material_right));
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground)); // xyz = (R/L)(U/D)(toward/away)
    // //world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    // world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    // world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    // world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_emis));
    // world.add(make_shared<sphere>(point3( 0.5,   -0.4, -0.7), 0.1, material_emis_blue));
    // world.add(make_shared<sphere>(point3(-0.25,  -0.4,  -0.6),   0.1, material_right));
    // world.add(make_shared<sphere>(point3( -0.6,   -0.45,  -0.8),   0.06, material_center));
    // Triangles
    // world.add(make_shared<triangle_plane>(point3(-0.25, 0.3, -0.6), point3(0.25, 0.3, -0.6), point3(0.0, 0.5, -0.6), material_emis_blue)); // center = (0.0, 0.5, -0.6)


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

    cam.vfov = 90;
    cam.lookfrom = point3(-2,2,1);
    cam.lookat = point3(0,0,-1);
    cam.vup = vec3(0,1,0);

    // Imported 3D model
    parser p;
    vector<shared_ptr<triangle_plane>> triangles;
    // Eventually: parse("src/scene_objs/uploads_files_725980_LightBlueGem.obj")
    triangles = p.parse("src/scene_objs/gem.txt", make_shared<metal>(color(0.8, 0.6, 0.2)), false); 
    for (int i = 0; i < triangles.size(); i++){
        world.add(triangles[i]);
    }

    cam.render(world);
}
