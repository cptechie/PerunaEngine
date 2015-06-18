//
//  Paraboloid.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/11/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#include "Paraboloid.h"

Paraboloid::Paraboloid():paraboloidRadius(.5), paraboloidHeight(1), paraboloidVerticalDetail(10), paraboloidRingDetail(10), paraboloidCurvature(5){
    
    int vertices = paraboloidVerticalDetail * paraboloidRingDetail + 2;
    
    for(int i=0; i<vertices; ++i){
        cols.push_back(glm::vec4(.75, .25, .64, 1.0));
    }
    
    init();
}

Paraboloid::Paraboloid(float paraboloidRadius, float paraboloidHeight, int paraboloidVerticalDetail, int paraboloidRingDetail, float paraboloidCurvature, const glm::vec4& col):
paraboloidRadius(paraboloidRadius), paraboloidHeight(paraboloidHeight), paraboloidVerticalDetail(paraboloidVerticalDetail), paraboloidRingDetail(paraboloidRingDetail) {
    
    int vertices = paraboloidVerticalDetail * paraboloidRingDetail + 2;
    
    for(int i=0; i<vertices; ++i){
        cols.push_back(glm::vec4(.75, .25, .64, 1.0));
    }
    
    init();
}


void Paraboloid::calcVerts() {
    
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    
    verts.push_back(glm::vec3(x, y, z));
    verts.push_back(glm::vec3(x, paraboloidHeight, z));
    
    
    for(int i=0; i<paraboloidHeight; ++i){
        
        y += paraboloidHeight/paraboloidVerticalDetail;
        
        float radius = sqrt(y);
        
        float theta = 0;
        
        for(int j = 0; j < paraboloidRingDetail; j++){
            
            x = radius*cos(theta);
            z = radius*sin(theta);
            
            verts.push_back(glm::vec3(x, y, z));
            
            int a = i*paraboloidRingDetail+j;
            int b = i*paraboloidRingDetail+j+1;
            int c = (i+1)*paraboloidRingDetail+j;
            int d = (i+1)*paraboloidRingDetail+j+1;
            
//            // end cases
//            int e = i *paraboloidRingDetail;
//            int f = (i+1)*paraboloidRingDetail;
//            int g = j+1;
            
            if (i<paraboloidVerticalDetail-1){
                if (j<paraboloidVerticalDetail-1){
                    inds.push_back(Elem(a, d, b));
                    inds.push_back(Elem(a, c, d));
                }
//                else {
//                    // close ring
//                    inds.push_back(Elem(a, f, e));
//                    inds.push_back(Elem(a, c, f));
//                }
//                // close toroid
            }
//            else {
//                if (j<paraboloidVerticalDetail-1){
//                    inds.push_back(Elem(a, g, b));
//                    inds.push_back(Elem(a, j, g));
//                } else {
//                    // close ring
//                    inds.push_back(Elem(a, 0, e));
//                    inds.push_back(Elem(a, j, 0));
//                }
//                
//                
//            }

            
            
            theta += M_PI*2/paraboloidRingDetail;
        }
    }
}

void Paraboloid::calcInds() {

}

