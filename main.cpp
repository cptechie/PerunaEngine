//
//  main.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/2/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#if defined (_WIN32) || defined(_WIN64)
#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#if defined(__APPLE__)
//#include <OpenGL/glu.h>
#include "GLFW/glfw3.h"
#endif

#include "Shader.h"
#include "Cube.h"

// for matrices
#include "glm/gtc/type_ptr.hpp" // matrix copying
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

float width = 640, height = 480;
Cube* cube;

// shader
//Shader* s;

// MATRICES
// model, view, modelView, projection, modelViewProjection
glm::mat4 M, V, MV, P, MVP;
// translate, rotate, scale
glm::mat4 T, R, S;

// UNIFORMS for MATRICES
GLuint M_U, V_U, MV_U, P_U, MVP_U;
GLuint T_U, R_U, S_U;

float viewAngle = 75.0f;
float aspect;

// function prototypes
void initUniforms(Shader* s);
void translate(glm::vec3 v);
void rotate(float ang, glm::vec3 axes);
void scale(glm::vec3 sclFactor);
void concat();

// use GL3 context (OpenGL 3.2-4.1) // required for osx only, I think
#define GLFW_INCLUDE_GLCOREARB

int main(void)
{
    
#if defined (_WIN32) || defined(_WIN64)
    glewExperimental = GL_TRUE;
#endif
    
    
	if (!glfwInit()){
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

	glEnable(GL_DEPTH_TEST);

	
	Shader* s = new Shader("/Users/33993405/Desktop/computer_graphics_class/GLFW_Demo/GLFW_Demo/simpleShader01.vert", "/Users/33993405/Desktop/computer_graphics_class/GLFW_Demo/GLFW_Demo/simpleShader01.frag");

	glm::vec4 cols[] = {
		glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0),
		glm::vec4(0.0, 0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 0.5, 0.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
	};
    for(int i=0; i<8; ++i){
        cols[i] = glm::vec4(.3, .3, .3, 1.0);
    }
	cube = new Cube(cols);

	// initialize view matrices
	glViewport(0, 0, 640, 480);

	// START standard transformation matrices: ModelView / Projection / Normal
	M = glm::mat4(1.0f); // set to identity
	V = glm::lookAt(glm::vec3(0.0, 0.0, 10.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	MV = V * M;

	// projection matrix and MVP Matrix
	// perspective
	viewAngle = 75.0f;
	aspect = float(width) / float(height);
	//// ortho
	////trace("width = ", width);
	////trace("height =", height);
	//left = -width / 2;
	//right = width / 2;
	//bottom = -height / 2;
	//top = height / 2;

	//nearDist = .1f;
	//farDist = 1500.0f;

	P = glm::perspective(viewAngle, aspect, .1f, 2000.0f);
	MVP = P * MV;
	// END Model / View / Projection data

	// tranformation matricies
	T = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);
	s->bind();

	initUniforms(s);


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// float ratio;
       // int width, height;
       // glfwGetFramebufferSize(window, &width, &height);
       // ratio = width / (float) height;
//        std::cout << "width = " << width << std::endl;
//        std::cout << "height = " << height << std::endl;
        glViewport(0, 0, width, height);
		

		// reset to identity each frame
		M = glm::mat4(1.0f);
		MV = V * M;
		MVP = P * MV;

		glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
		glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);

		rotate(glfwGetTime(), glm::vec3(.75, 1, .5));
        cube->display(Cube::SURFACE);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void initUniforms(Shader* s){
   // std::cout << "s->shader_id = " << s->shader_id << std::endl;
	// set variable name of uniforms in shader
	M_U = glGetUniformLocation(s->shader_id, "modelMatrix");
	MV_U = glGetUniformLocation(s->shader_id, "modelViewMatrix");
	MVP_U = glGetUniformLocation(s->shader_id, "modelViewProjectionMatrix");
}

// TRNAFORMAION Functions
void translate(glm::vec3 v) {
	M = glm::translate(M, v);
	concat();
}

void rotate(float ang, glm::vec3 axes) {
	M = glm::rotate(M, ang, axes);
	concat();
}

void scale(glm::vec3 sclFactor) {
	M = glm::scale(M, sclFactor);
	concat();
}

// rebuild transformed MVP matrix and update shader uniforms
void concat(){
	MV = V * M;
	MVP = P * MV;
	glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
}

