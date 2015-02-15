
#include "GameModels.h"
using namespace Models;

GameModels::GameModels(){

}

GameModels::~GameModels(){
	std::map<std::string, Model>::iterator it;
	for (it = GameModelList.begin(); it != GameModelList.end(); ++it){
		unsigned int* p = &it->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	GameModelList.clear();
}

void GameModels::CreateTriangleModel(const std::string& gameModelName){

	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> verticies;
	verticies.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0),
									 glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0),
									 glm::vec4(1,0,0,1)));
	verticies.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0),
		glm::vec4(1, 0, 0, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * verticies.size(), &verticies[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);

	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	GameModelList[gameModelName] = myModel;
}

void GameModels::CreateCubeModel(const std::string& gameModelName){

	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<glm::vec3> verticies;
	glm::vec3 ver1 = glm::vec3(-0.5f, 0.5f, 0.5f);
	glm::vec3 ver2 = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 ver3 = glm::vec3(0.5f, -0.5f, 0.5f);
	glm::vec3 ver4 = glm::vec3(-0.5f, -0.5f, 0.5f);

	glm::vec3 ver5 = glm::vec3(-0.5f, 0.5f, -0.5f);
	glm::vec3 ver6 = glm::vec3(0.5f, 0.5f, -0.5f);
	glm::vec3 ver7 = glm::vec3(0.5f, -0.5f, -0.5f);
	glm::vec3 ver8 = glm::vec3(-0.5f, -0.5f, -0.5f);


	float UV_DATA[] = {
		0,0,
		0.3333333333333333333333333,0,
		0.3333333333333333333333333,0.5,
		0,0.5,

		0.3333333333333333333333333, 0,
		0.6666666666666666666666666, 0,
		0.6666666666666666666666666, 0.5,
		0.3333333333333333333333333, 0.5,

		0.6666666666666666666666666, 0,
		1, 0,
		1, 0.5,
		0.6666666666666666666666666, 0.5,

		0, 0.5,
		0.3333333333333333333333333, 0.5,
		0.3333333333333333333333333, 1,
		0, 1,

		0.3333333333333333333333333, 0.5,
		0.6666666666666666666666666, 0.5,
		0.6666666666666666666666666, 1,
		0.3333333333333333333333333, 1,

		0.6666666666666666666666666, 0.5,
		1, 0.5,
		1, 1,
		0.6666666666666666666666666, 1,
	};
	//Front
	verticies.push_back(ver1);
	verticies.push_back(ver2);
	verticies.push_back(ver3);
	verticies.push_back(ver4);
	//Right
    verticies.push_back(ver2);
	verticies.push_back(ver6);
	verticies.push_back(ver7);
	verticies.push_back(ver3);
	//Back
	verticies.push_back(ver5);
	verticies.push_back(ver6);
	verticies.push_back(ver7);
	verticies.push_back(ver8);
	//Left
	verticies.push_back(ver1);
	verticies.push_back(ver5);
	verticies.push_back(ver8);
	verticies.push_back(ver4);
	//Top
	verticies.push_back(ver1);
	verticies.push_back(ver2);
	verticies.push_back(ver6);
	verticies.push_back(ver5);
	//Bottom
	verticies.push_back(ver4);
	verticies.push_back(ver3);
	verticies.push_back(ver7);
	verticies.push_back(ver8);

	
	//For Commit
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * verticies.size(), &verticies[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	
	unsigned int vbo2;
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 48, &UV_DATA[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	
	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	myModel.vbos.push_back(vbo2);
	GameModelList[gameModelName] = myModel;
}
void GameModels::CreateSquareModel(const std::string& gameModelName){
	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<glm::vec3> verticies;

	verticies.push_back(glm::vec3(-0.5f, 0.5f, 0.5));
	verticies.push_back(glm::vec3(0.5f, 0.5f, 0.5));
	verticies.push_back(glm::vec3(0.5f, -0.5f, 0.5));
	verticies.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));

	float UV_DATA[8] = {
		0,0,
		1,0,
		1,1,
		0,1
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * verticies.size(), &verticies[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0); 
	
	unsigned int vbo2;
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 8, &UV_DATA[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	myModel.vbos.push_back(vbo2);
	GameModelList[gameModelName] = myModel;
}
void GameModels::DeleteModel(const std::string& gameModelName){
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);
}

unsigned int GameModels::GetModel(const std::string& gameModelName){
	return GameModelList[gameModelName].vao;
}