#pragma once
#include "Core\Shader_Loader.h"
#include "Core\GameModels.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<glm\glm.hpp>
#include<glm\gtc\type_ptr.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include"glm\gtx\projection.hpp"
#include<math.h>

Models::GameModels* gameModels;

using namespace Core;

GLuint program;

glm::vec3 CameraPosition;
glm::vec3 CameraRotation;


glm::mat4 ViewMatrix;
glm::mat4 ModelMatrix;
glm::mat4 ProjectionMatrix;

glm::vec3 MousePosition;

bool KeyDown[127];

void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void repaint(int value);
glm::mat4 GetRotationMatrix(glm::vec3 rotation);
glm::vec3 DirectionVector(void);
void MouseMoved(int x, int y);

glm::vec3 CameraForward(glm::mat4 &rotationMat);
glm::vec3 CameraRight(glm::mat4 &rotationMat);
glm::vec3 CameraUp(glm::mat4 &rotationMat);

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

	//draw 3 vertices as triangles
	/*
	glBindVertexArray(gameModels->GetModel("triangle1"));

	ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
	glm::mat4 MVP = ProjectionViewMatrix * ModelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, false, &MVP[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	*/
	glBindVertexArray(gameModels->GetModel("cube1"));
	ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f));
	glm::mat4 MVP = ProjectionViewMatrix * ModelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, false, &MVP[0][0]);
	glDrawArrays(GL_QUADS, 0, 24);

	glutSwapBuffers(); 

	//Camera Movement
	if (KeyDown['w']) CameraPosition +=  CameraForward(ViewMatrix) * glm::vec3(0.1f);

	if (KeyDown['s']) CameraPosition -= CameraForward(ViewMatrix) * glm::vec3(0.1f);

	if (KeyDown['a']) CameraPosition += CameraRight(ViewMatrix) * glm::vec3(0.1f);

	if (KeyDown['d']) CameraPosition -= CameraRight(ViewMatrix) * glm::vec3(0.1f);
	//td::cout << CameraRotation.x << " " << CameraRotation.y << " " << std::endl;
	//Causes window to be redrawn in 16 milliseconds
	glutTimerFunc(16, repaint, 0);
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
	ProjectionMatrix = glm::perspective<float>(1.084719755f, 4.0f / 3.0f, 0.1f, 100.f);
	CameraPosition = glm::vec3(0.0f, 0.0f, -10.f);
	CameraRotation = glm::vec3(0.01f, 0.01f, 0.01f);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Open GL Game");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glewInit();

	Init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(MouseMoved);

	glutSetCursor(GLUT_CURSOR_NONE);

	glutMainLoop();

	delete gameModels;
	glDeleteProgram(program);
	return 0;

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