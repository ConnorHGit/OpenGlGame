#pragma once
#include "Main.h"
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
#include "Character.h"
Models::GameModels* gameModels;

using namespace Core;

GLuint program;

glm::vec3 CameraPosition;
glm::vec3 CameraRotation;


glm::mat4 ViewMatrix;
glm::mat4 ModelMatrix;
glm::mat4 ProjectionMatrix;

glm::vec3 MousePosition;

std::vector<Body*> cubes;

bool KeyDown[127];

bool stop;

float delta;

Character player;

MAIN::std::map <char*,GLuint> textures;

void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
glm::mat4 GetRotationMatrix(glm::vec3 rotation);
glm::vec3 DirectionVector(void);
void MouseMoved(int x, int y);
void repaint(int value);
glm::vec3 CameraForward(glm::mat4 &rotationMat);
glm::vec3 CameraRight(glm::mat4 &rotationMat);
glm::vec3 CameraUp(glm::mat4 &rotationMat);
float clamp(float min, float val, float max);
void update(double delta);
int getSign(float val);
float reduceAbs(float val,float decrease);
glm::vec3 printVec(glm::vec3 print,char* mes);
	void renderScene(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.25882352941176470588235294117647, 0.38431372549019607843137254901961 , 1.0, 1.0);//clear sky blue
		if (!KeyDown['r']){
			CameraRotation += glm::vec3(-MousePosition.x / 1000, -MousePosition.y / 1000, 0);
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2);
		}
		ViewMatrix = GetRotationMatrix(CameraRotation) * glm::translate(glm::mat4(1.0f), (player.pos + glm::vec3(0,player.size.y,0)) * glm::vec3(-1, -1, -1));
		glm::mat4 ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;

		//use the created program
		glUseProgram(program);

		glBindVertexArray(gameModels->GetModel("cube1"));
		for (int i = 0; i < cubes.size(); i++){
			cubes[i]->draw(ProjectionViewMatrix, program);
		}

		glutSwapBuffers();
	}

	void MousePressed(int button, int state, int x, int y){
		if (state == GLUT_LEFT_BUTTON){
			
		}
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
		ProjectionMatrix = glm::perspective<float>(1.084719755f, 4.0f / 3.0f, 0.1f, 10000.f);
		CameraPosition = glm::vec3(0, 0, -10.0f);
		CameraRotation = glm::vec3(0.01f, 0.01f, 0.01f);
		Body ground = Body(2, 0, 1, 100, 50, 100,"Floor");
		ground.setMass(0);
		cubes.push_back(&ground);
		player = Character(30, 5 , 30, 1, 1, 1,"Brick");
		player.acceleration = glm::vec3(0, -0.03, 0);
		cubes.push_back(&player);
		Body b = Body(30, 200,30, 1, 1, 1,"Grass");
		//b.setMass(0);
		b.acceleration = glm::vec3(0, -0.03, 0);
		cubes.push_back(&b);
	//	c.setMass(0);
	//	c.acceleration = glm::vec3(0, -0.03, 0);
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(1024, 768);
		glutCreateWindow("Open GL Game");
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

		glewInit();

		Init();

		LoadTexture("Brick", "Assets/Brick.png");
		LoadTexture("Grass", "Assets/Grass.png");
		LoadTexture("Floor", "Assets/Floor.png");
		// register callbacks
		glutCloseFunc(closeCallback);
		glutKeyboardFunc(keyPressed);
		glutKeyboardUpFunc(keyUp);
		glutPassiveMotionFunc(MouseMoved);
		glutMotionFunc(MouseMoved);
		glutMouseFunc(MousePressed);
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
			MAIN::delta = delta;
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
				std::cout << "FPS:" << i << std::endl;
				i = 0;
				std::cout << "Thing" << GetTickCount() - start << std::endl;
			}

			//END FPS Stuff
			renderScene();
			glutMainLoopEvent();

		
			std::this_thread::sleep_for(std::chrono::milliseconds((int)fmax(8 - (signed)(GetTickCount() - start), 0)));
		}

		delete gameModels;
		glDeleteProgram(program);

		return 0;


	}

	void update(double delta){
		if (KeyDown['w']) player.pos += (CameraForward(ViewMatrix) * glm::vec3(0.6f) * glm::vec3(-1, 0, -1));

		if (KeyDown['s']) player.pos -= (CameraForward(ViewMatrix) * glm::vec3(0.6f) * glm::vec3(-1, 0, -1));

		if (KeyDown['a']) player.pos += (CameraRight(ViewMatrix) * glm::vec3(0.6f) * glm::vec3(-1, 0, -1));

		if (KeyDown['d']) player.pos -= (CameraRight(ViewMatrix) * glm::vec3(0.6f) * glm::vec3(-1, 0, -1));
		player.velocity.x = reduceAbs(player.velocity.x, 0.2);
		player.velocity.y = reduceAbs(player.velocity.y, 0.2);
		player.velocity.z = reduceAbs(player.velocity.z, 0.2);
		for (int i = 0; i < cubes.size(); i++){
			cubes[i]->update(delta);
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
		MousePosition = glm::vec3(y - glutGet(GLUT_WINDOW_WIDTH) / 2, x - glutGet(GLUT_WINDOW_WIDTH) / 2, 0);
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
	float clamp(float min, float val, float max){
		if (val < min)return min;
		if (val > max)return max;
		return val;
	}
	int getSign(float val){
		if (val < 0)return -1;
		if (val > 0)return 1;
		return 1;
	}
	float reduceAbs(float val, float decrease){
		float newAbs = abs(val) - decrease;
		if (newAbs < 0)return 0;
		return newAbs * getSign(val);
	}
	glm::vec3 printVec(glm::vec3 print, char* mes){
		std::cout << "X:" << print.x << "    Y:" << print.y << "     Z:" << print.z << "Ext:" << mes << std::endl;
		return print;
	}
	void MAIN::LoadTexture(char* textname, char* imgpath){ 
		unsigned char* imgData;
		unsigned int w, h;
		unsigned err = lodepng_decode24_file(&imgData, &w, &h, imgpath);
		if (err) std::cout << "decoder error " << err << ": " << lodepng_error_text(err) << std::endl;

		GLuint textID;
		glGenTextures(1, &textID);
		glBindTexture(GL_TEXTURE_2D, textID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
		glUniform1i(glGetUniformLocation(program, "textSamp"), 0);
		textures.insert(std::pair<char*, GLuint>(textname, textID));
	}