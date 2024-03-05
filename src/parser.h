#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "vec3.h"
#include "material.h"
#include "triangle_plane.h"

using std::string;
using std::endl;
using std::vector;

class parser {
    public:
        // Parse method
        vector<shared_ptr<triangle_plane>> parse(string filename, shared_ptr<material> material, bool print_logs){
            
            vector<vec3> vertices;
            vector<int> vidx;
            vector<shared_ptr<triangle_plane>> triangles;

            // Vars needed for parsing
            std::ifstream objfile;
            string objstring;
            string tempstring;
            
            
            objfile.open(filename);
            if(objfile.is_open()){
                string line = "";
                // Parse
                while (getline(objfile, line)){

                    string v;
                    double v0, v1, v2;
                    tempstring = "";

                    std::stringstream inputstring(line);

                    // Break up the line to get each vec3() input
                    getline(inputstring, tempstring, ' ');
                    v = tempstring.c_str();
                    // Vectors
                    if (v == "v"){
                        getline(inputstring, tempstring, ' ');
                        v0 = atof(tempstring.c_str());
                        getline(inputstring, tempstring, ' ');
                        v1 = atof(tempstring.c_str());
                        getline(inputstring, tempstring, ' ');
                        v2 = atof(tempstring.c_str());
                        vertices.push_back(vec3(v0,v1,v2));
                    }
                    // Faces
                    if (v == "f"){
                        getline(inputstring, tempstring, '/');
                        vidx.push_back(atoi(tempstring.c_str()));
                        getline(inputstring, tempstring, ' ');
                        getline(inputstring, tempstring, '/');
                        vidx.push_back(atoi(tempstring.c_str()));
                        getline(inputstring, tempstring, ' ');
                        getline(inputstring, tempstring, '/');
                        vidx.push_back(atoi(tempstring.c_str()));
                        auto mtrl = determine_material(material);
                        triangles.push_back((make_shared<triangle_plane>(vertices[vidx[0]-1], vertices[vidx[1]-1], vertices[vidx[2]-1], mtrl)));
                        vidx.clear();
                    }

                    line = "";
                }
            }
            else{
                std::cout << "error opening file";
            }
            objfile.close();

            // Optional print
            if (print_logs){
                for (int i = 0; i < vertices.size(); i++){
                    std::cout << std::to_string(i+1) << ". vec3(" << vertices[i].x() << "," << vertices[i].y() << "," << vertices[i].z() << ")" << endl;
                }
                std::cout << "size: " << std::to_string(triangles.size()) << endl;
                for (int i = 0; i < triangles.size(); i++){
                    std::cout << std::to_string(i+1) << ". triangle_plane(";
                    std::cout << triangles[i]->vec0().x() << "," << triangles[i]->vec0().y() << "," << triangles[i]->vec0().z() << ",";
                    std::cout << triangles[i]->vec1().x() << "," << triangles[i]->vec1().y() << "," << triangles[i]->vec1().z() << ",";
                    std::cout << triangles[i]->vec2().x() << "," << triangles[i]->vec2().y() << "," << triangles[i]->vec2().z();
                    std::cout << ")" << endl;
                }
            }
            return triangles;
        }

    private:
        shared_ptr<material> determine_material(shared_ptr<material> material){
            // Determining the material is abstracted away in case I want to add more options later,
            // such as using multiple materials in one object
            return material;

            // Example of alternating between two materials in a gem
            // auto metal_material = make_shared<emissive>(color(0.2, 0.2, 1.0),color(0.1, 0.1, 0.1));
            // auto metal_material_2 = make_shared<emissive>(color(0.2, 0.2, 1.0),color(0.2, 0.8, 1.0));
            // int random = rand() % 100;
            // auto mtrl = (random > 50) ? metal_material : metal_material_2;
        }
};

#endif