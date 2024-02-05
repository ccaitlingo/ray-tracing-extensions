# ray-tracing-extensions
My implementation and extension of Peter Shirley's "Ray Tracing in One Weekend"

## Development Instructions
1. Open with VS Code Developer command prompt
2. Run Build Task (Ctrl + Shift + B)
3. Run (top right-hand corner)
4. src/main.exe > ppms/render_title.ppm
5. To view your rendered image, upload the .ppm to [PPM Viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html)

![ray_tracing_extensions_multiple_spheres](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/6e511f6c-fc7a-4223-88b9-3c75f490f385)

## My Extensions
Emission: Modification of ray_color method and creation of emissive material subclass to add material in the ray tracer that can emit light instead of just reflecting it.

![ray_tracing_extensions_before](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/1b9bd041-c6d7-4a82-a6b7-2f6a8067732f)
![ray_tracing_extensions_after](https://github.com/ccaitlingo/ray-tracing-extensions/assets/122246189/aa730adf-8df1-419f-8bbd-26530a3053ec)
