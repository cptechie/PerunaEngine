//
//  Paraboloid.h
//  GLFW_Demo
//
//  Created by Ira on 6/11/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#ifndef __GLFW_Demo__Paraboloid__
#define __GLFW_Demo__Paraboloid__

#include <stdio.h>
#include "Geom.h"

class Paraboloid: public Geom {
    
public:
    Paraboloid();
    Paraboloid(float paraboloidRadius, float paraboloidHeight, int paraboloidVerticalDetail, int paraboloidRingDetail, float paraboloidCurvature, const glm::vec4& col = glm::vec4(.76, .56, .456, 1.0));
    // must ocreated concrete implementations
    // of abstract functions (pure virtuals)
    void calcVerts();
    void calcInds();
    
    // properties
    float paraboloidRadius, paraboloidHeight, paraboloidCurvature;
    int paraboloidVerticalDetail, paraboloidRingDetail;
    
};


#endif /* defined(__GLFW_Demo__Paraboloid__) */