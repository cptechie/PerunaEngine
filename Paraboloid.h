//
//  Cylinder.h
//  GLFW_Demo
//
//  Created by Ira on 6/11/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#ifndef __GLFW_Demo__Cylinder__
#define __GLFW_Demo__Cylinder__

#include <stdio.h>
#include "Geom.h"

class Cylinder: public Geom {
    
public:
    Cylinder();
    Cylinder(float cylinderRadius, float cylinderHeight, int cylinderDetail, const glm::vec4& col = glm::vec4(.76, .56, .456, 1.0));
    // must ocreated concrete implementations
    // of abstract functions (pure virtuals)
    void calcVerts();
    void calcInds();
    
    // properties
    float cylinderRadius, cylinderHeight;
    int cylinderDetail;
    
};


#endif /* defined(__GLFW_Demo__Cylinder__) */