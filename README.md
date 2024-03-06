# ray-tracing-extensions
My implementation and extension of Peter Shirley's "Ray Tracing in One Weekend"

## Development Instructions
1. Open with VS Code Developer command prompt
2. Run Build Task (Ctrl + Shift + B)
3. No need to run
4. src/main.exe > ppms/render_title.ppm
5. To view your rendered image, upload the .ppm to [PPM Viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html)

![ray_tracing_extensions_multiple_spheres](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/6e511f6c-fc7a-4223-88b9-3c75f490f385)

## My Extensions
Emission: Modification of ray_color method and creation of emissive material subclass to add material in the ray tracer that can emit light instead of just reflecting it.

![ray_tracing_extensions_before](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/1b9bd041-c6d7-4a82-a6b7-2f6a8067732f)
![ray_tracing_extensions_after](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/aa730adf-8df1-419f-8bbd-26530a3053ec)

Object Imports: Creation of triangle_plane class (Möller–Trumbore ray triangle intersection to implement "hit" method). Creation of parser class to read imported .obj or .blend files (after they are converted to .txt), which parse the vertices and faces, extracting information to make the triangles, and adds the triangle mesh to the world.

![gem](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/8e6208cf-eeb4-44b9-9878-2b3b8f216166)
![heart](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/90bca1d5-8c62-40db-b4d2-0d512391f275)
![gem_pos_1](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/ae471b67-de75-4c44-9e71-964af48af483)
![heart_pos_1](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/74edcef8-1ed7-4355-94f8-1f43be88225a)
