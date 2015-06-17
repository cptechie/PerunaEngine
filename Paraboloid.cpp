//
//  Cylinder.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/11/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#include "Cylinder.h"

Cylinder::Cylinder():cylinderRadius(.5), cylinderHeight(1), cylinderDetail(10){
    
    int vertices = cylinderDetail * 2 + 2;
    
    for(int i=0; i<vertices; ++i){
        cols.push_back(glm::vec4(.75, .25, .64, 1.0));
    }
    
    init();
}

Cylinder::Cylinder(float cylinderRadius, float cylinderHeight, int cylinderDetail, const glm::vec4& col):
cylinderRadius(cylinderRadius), cylinderHeight(cylinderHeight), cylinderDetail(cylinderDetail) {
    
    int vertices = cylinderDetail * 2 + 2;
    
    for(int i=0; i<vertices; ++i){
        cols.push_back(col);
    }
    
    init();
}


void Cylinder::calcVerts() {
    float theta = 0.0;
    
    verts.push_back(glm::vec3(0, 0, cylinderHeight/2));
    verts.push_back(glm::vec3(0, 0, -cylinderHeight/2));
    
    for(int i=0; i<cylinderDetail; ++i){

        verts.push_back(glm::vec3(cylinderRadius*cos(theta), cylinderRadius*sin(theta), cylinderHeight/2));
        verts.push_back(glm::vec3(cylinderRadius*cos(theta), cylinderRadius*sin(theta), -cylinderHeight/2));

        theta += M_PI*2/cylinderDetail;
    }
}

void Cylinder::calcInds() {

    for (int i = 0; i < cylinderDetail - 1; i++) {
        
        int a = i * 2 + 2;
        int b = a + 2;
        int c = i * 2 + 3;
        int d = c + 2;
        inds.push_back(Elem(0, a, b));
        inds.push_back(Elem(1, c, d));
        
        inds.push_back(Elem(c, d, b));
        inds.push_back(Elem(c, b, a));
    }

    int g = cylinderDetail * 2;
    int h = cylinderDetail * 2 + 1;

    inds.push_back(Elem(0, g, 2));
    inds.push_back(Elem(1, h, 3));
    
    inds.push_back(Elem(2, h, 3));
    inds.push_back(Elem(2, g, h));
}

