#pragma once
#include "Core\Shader_Loader.h"
#include "Core\GameModels.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<thread>
#include<ctime>
#include<glm\glm.hpp>
#include<glm\gtc\type_ptr.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include"glm\gtx\projection.hpp"
#include<math.h>
#include"Physics/Body.h"
#include "windows.h"
#include "Physics\CollisionDetection.h"
#include "LodePNG\lodepng.h"
Models::GameModels* gameModels;

using namespace Core;

GLuint program;

glm::vec3 CameraPosition;
glm::vec3 CameraRotation;


glm::mat4 ViewMatrix;
glm::mat4 ModelMatrix;
glm::mat4 ProjectionMatrix;

glm::vec3 MousePosition;

std::vector<Body> cubes;

bool KeyDown[127];

bool stop;

void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
glm::mat4 GetRotationMatrix(glm::vec3 rotation);
glm::vec3 DirectionVector(void);
void MouseMoved(int x, int y);
void repaint(int value);
glm::vec3 CameraForward(glm::mat4 &rotationMat);
glm::vec3 CameraRight(glm::mat4 &rotationMat);
glm::vec3 CameraUp(glm::mat4 &rotationMat);
void update(double delta);
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);//clear red
	if (!KeyDown['r']){
		CameraRotation += glm::vec3(-MousePosition.x / 1000, -MousePosition.y / 1000, 0);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2);
	}
	ViewMatrix = GetRotationMatrix(CameraRotation) * glm::translate(glm::mat4(1.0f), CameraPosition);

	glm::mat4 ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;
	
	//use the created program
	glUseProgram(program);

	glBindVertexArray(gameModels->GetModel("cube1"));
	for (int i = 0; i < cubes.size(); i++){
		cubes[i].draw(ProjectionViewMatrix, program);
	}
	glutSwapBuffers(); 
}



void repaint(int value){
	glutPostRedisplay();
}
void closeCallback(){
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}
void Init(){

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	gameModels = new Models::GameModels();
	//gameModels->CreateTriangleModel("triangle1");
	gameModels->CreateCubeModel("cube1");
	//load and compile shaders
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv) {
	ProjectionMatrix = glm::perspective<float>(1.084719755f, 4.0f / 3.0f, 0.1f, 1000.f);

	CameraPosition = glm::vec3(0,0,-10.0f);
	CameraRotation = glm::vec3(0.01f, 0.01f, 0.01f);
	cubes.push_back(Body(1, -1, 1, 1, 1, 1));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Open GL Game");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glewInit();

	Init();

	unsigned char* imgData;
	unsigned int w, h;
	unsigned err = lodepng_decode24_file(&imgData,&w,&h,"Assets/Test.png");
	if (err) std::cout << "decoder error " << err << ": " << lodepng_error_text(err) << std::endl;
	GLuint textID;
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(program, "textSamp"), 0);
	// register callbacks
	glutCloseFunc(closeCallback);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(MouseMoved);

	glutSetCursor(GLUT_CURSOR_NONE);
	
	
	double timeStep = 1000 / 60;
	double accum = 0;
	long start = GetTickCount();
	long end;
	int i, j;
	i = j = 0;
	while (!stop){
		end = GetTickCount();
		unsigned short delta = end - start;
		accum += delta;
		start = GetTickCount();

		while (accum > timeStep){
			update(timeStep);
			accum -= timeStep;
		}

		//FPS Stuff
		j += delta;
		i++;
		if (j > 1000){
			j = 0;
			std::cout <<"FPS:" << i << std::endl;
			i = 0;
			std::cout << "Thing" << delta << std::endl;
		}
		//END FPS Stuff
		renderScene();
		glutMainLoopEvent();

		std::this_thread::sleep_for(std::chrono::milliseconds((int)fmax(8 - (signed)(GetTickCount() - start),0)));
	}

	delete gameModels;
	glDeleteProgram(program);

	return 0;
	

}

void update(double delta){
	if (KeyDown['w']) CameraPosition += CameraForward(ViewMatrix) * glm::vec3(0.1f);

	if (KeyDown['s']) CameraPosition -= CameraForward(ViewMatrix) * glm::vec3(0.1f);

	if (KeyDown['a']) CameraPosition += CameraRight(ViewMatrix) * glm::vec3(0.1f);

	if (KeyDown['d']) CameraPosition -= CameraRight(ViewMatrix) * glm::vec3(0.1f);
	for (int i = 0; i < cubes.size(); i++){
		cubes[i].update(delta);
	}
	CollisionDetection::Broadphase(&cubes);
}

void keyPressed(unsigned char key, int x, int y){
	KeyDown[key] = true;
}
void keyUp(unsigned char key, int x, int y){
	KeyDown[key] = false;
}
glm::mat4 GetRotationMatrix(glm::vec3 rotation){
	float cosX = cos(rotation.x);
	float sinX = sin(rotation.x);

	float cosY = cos(rotation.y);
	float sinY = sin(rotation.y);

	float cosZ = cos(rotation.z);
	float sinZ = sin(rotation.z);

	float rotXData[16] = {
		1, 0, 0, 0,
		0, cosX, -sinX, 0,
		0, sinX, cosX, 0,
		0, 0, 0, 1
	};

	float rotYData[16] = {
		cosY, 0, sinY, 0,
		0, 1, 0, 0,
		-sinY, 0, cosY, 0,
		0, 0, 0, 1
	};

	float rotZData[16] = {
		cosZ, -sinZ, 0, 0,
		sinZ, cosZ, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return glm::make_mat4(rotXData) * glm::make_mat4(rotYData) * glm::make_mat4(rotZData);
}
void MouseMoved(int x, int y){
	MousePosition = glm::vec3(y - glutGet(GLUT_WINDOW_WIDTH) / 2, x - glutGet(GLUT_WINDOW_WIDTH) / 2,0);
}
glm::vec3 CameraForward(glm::mat4 &rotationMat){
	float* data = glm::value_ptr(rotationMat);
	return glm::vec3(data[2], data[6], data[10]);
}
glm::vec3 CameraRight(glm::mat4 &rotationMat){
	float* data = glm::value_ptr(rotationMat);
	return glm::vec3(data[0], data[4], data[8]);
}
glm::vec3 CameraUp(glm::mat4 &rotationMat){
	float* data = glm::value_ptr(rotationMat);
	return glm::vec3(data[1], data[5], data[9]);
}
