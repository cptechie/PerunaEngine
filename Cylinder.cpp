//
//  Cylinder.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/11/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#include "Cylinder.h"

Cylinder::Cylinder():cylinderRadius(.5), cylinderHeight(1), cylinderDetail(10){
//    for(int i=0; i<cylinderDetail; ++i){
//        for(int j=0; j<ringDetail; ++j){
//            cols.push_back(glm::vec4(.75, .25, .64, 1.0));
//        }
//    }
    init();
}

Cylinder::Cylinder(float cylinderRadius, float cylinderHeight, int cylinderDetail, const glm::vec4& col):
cylinderRadius(cylinderRadius), cylinderHeight(cylinderHeight), cylinderDetail(cylinderDetail) {
//    for(int i=0; i<cylinderDetail; ++i){
//        for(int j=0; j<ringDetail; ++j){
//            cols.push_back(col);
//        }
//    }
//    init();
}


// must include concrete implementations
// of abstract functions (pure virtuals)

// Y-axis rotaiton
/*
 z' = z*cos q - x*sin q
 x' = z*sin q + x*cos q
 y' = y
 */

// z-axis rotaiton
/*
 x' = x*cos q - y*sin q
 y' = x*sin q + y*cos q
 z' = z
 */


void Cylinder::calcVerts() {
    glm::vec3 temp;
    float theta = 0.0;
    for(int i=0; i<cylinderDetail; ++i){
        float phi = 0.0;
        // start with rot around y-axis
        temp.z = cos(theta)*ringRadius;
        temp.x = cylinderRadius + sin(theta)*ringRadius;
        temp.y = 0;
        for(int j=0; j<ringDetail; ++j){
            // now rotate around z-axis
            verts.push_back(glm::vec3( temp.x*cos(phi) - temp.y*sin(phi), temp.x*sin(phi) + temp.y*cos(phi), temp.z ));
            phi += M_PI*2/ringDetail;
            
            // 2 triangles making up each quad of cylinder
            /*
             a---c
             |  /|
             | / |
             |/  |
             b---d
             */
            int a = i*ringDetail+j;
            int b = i*ringDetail+j+1;
            int c = (i+1)*ringDetail+j;
            int d = (i+1)*ringDetail+j+1;
            
            // end cases
            int e = i *ringDetail;
            int f = (i+1)*ringDetail;
            int g = j+1;
            
            if (i<cylinderDetail-1){
                if (j<ringDetail-1){
                    inds.push_back(Elem(a, d, b));
                    inds.push_back(Elem(a, c, d));
                } else {
                    // close ring
                    inds.push_back(Elem(a, f, e));
                    inds.push_back(Elem(a, c, f));
                }
                // close cylinder
            } else {
                if (j<ringDetail-1){
                    inds.push_back(Elem(a, g, b));
                    inds.push_back(Elem(a, j, g));
                } else {
                    // close ring
                    inds.push_back(Elem(a, 0, e));
                    inds.push_back(Elem(a, j, 0));
                }
                
                
            }
        }
        theta += M_PI*2/cylinderDetail;
    }
}

void Cylinder::calcInds() {
    // handled in calcVerts
}

