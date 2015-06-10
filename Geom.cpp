//
//  Geom.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/3/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#include "Geom.h"


Geom::Geom(){
}


void Geom::init() {
	calcVerts();
	calcInds();
    calcFaces();
    calcVertexNorms();
	calcPrimitives();
	createBuffers();
	
}

void Geom::createBuffers(){
	
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoID); // Create VAO
	glBindVertexArray(vaoID); // Bind VAO (making it active)
	//2. Create and bind VBO
	// a. Vertex attributes
	glGenBuffers(1, &vboID); // Create VBO ID
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind vertex attributes VBO
	int vertsDataSize = sizeof (float)* static_cast<int>(interleavedPrims.size());
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW); // allocate space
	//std::cout << " vertsDataSize = " << vertsDataSize << std::endl;
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data

	// b. Indices  uses ELEMENT_ARRAY_BUFFER
	glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind indices VBO
	int indsDataSize = static_cast<int>(indPrims.size()) * sizeof (GL_UNSIGNED_INT);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &indPrims[0]); // upload the data

	for (int i = 0; i < 3; i++) {
		glEnableVertexAttribArray(i);
	}
	// STRIDE is 10: pos(3) + vertex norm(3) + col(4)
	// (x, y, z, nx, ny, nz, r, g, b, a)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(0)); // pos
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(12)); // vertex norms
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(24)); // col

	// Disable VAO
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

void Geom::calcFaces() {
    for(int i=0; i<inds.size(); ++i){
        faces.push_back( Face(&verts.at(inds.at(i).e0), &verts.at(inds.at(i).e1), &verts.at(inds.at(i).e2)) );
    }                                                
}
void Geom::calcVertexNorms() {
    for(int i=0; i<verts.size(); ++i){
        glm::vec3 temp;
        for(int j=0; j<faces.size(); ++j){
            if (&verts.at(i) == faces.at(j).v0 || &verts.at(i) == faces.at(j).v1 || &verts.at(i) == faces.at(j).v2){
                temp += faces.at(j).normal();
            }
        }
        vertNorms.push_back(glm::normalize(temp));
    }
}

void Geom::calcPrimitives(){
	if (interleavedPrims.size()>0) interleavedPrims.clear();
	if (indPrims.size() > 0) indPrims.clear();
	//std::cout << " verts size = " << verts.size() << std::endl;
	for (int i = 0; i < verts.size(); i++) {
		// fill interleaved primitive arrays
		
        // position
        interleavedPrims.push_back(verts.at(i).x);
		interleavedPrims.push_back(verts.at(i).y);
		interleavedPrims.push_back(verts.at(i).z);
        
        // vertex normals
        interleavedPrims.push_back(vertNorms.at(i).x);
        interleavedPrims.push_back(vertNorms.at(i).y);
        interleavedPrims.push_back(vertNorms.at(i).z);

		// colors
        interleavedPrims.push_back(cols.at(i).x); // r
		interleavedPrims.push_back(cols.at(i).y); // g
		interleavedPrims.push_back(cols.at(i).z); // b
		interleavedPrims.push_back(cols.at(i).w); // a

		// explode inds arrays to primitives
		for (int i = 0, j = 0; i < inds.size(); i++) {
			indPrims.push_back(inds.at(i).e0);
			indPrims.push_back(inds.at(i).e1);
			indPrims.push_back(inds.at(i).e2);
		}
	}
}

void Geom::display(renderMode mode) {
	
	switch (mode) {
	case SURFACE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case WIREFRAME:
		glLineWidth(1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case POINT:
		glPointSize(5.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	default:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}

	glBindVertexArray(vaoID);
	glDrawElements(GL_TRIANGLES, static_cast<int>(inds.size()) * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glBindVertexArray(0);
}





