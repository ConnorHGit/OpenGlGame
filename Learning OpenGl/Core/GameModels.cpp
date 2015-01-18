
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

	std::vector<VertexFormat> verticies;
	glm::vec3 ver1 = glm::vec3(-1.0f, 1.0f, 1.0f);
	glm::vec3 ver2 = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ver3 = glm::vec3(1.0f, -1.0f, 1.0f);
	glm::vec3 ver4 = glm::vec3(-1.0f, -1.0f, 1.0f);

	glm::vec3 ver5 = glm::vec3(-1.0f, 1.0f, -1.0f);
	glm::vec3 ver6 = glm::vec3(1.0f, 1.0f, -1.0f);
	glm::vec3 ver7 = glm::vec3(1.0f, -1.0f, -1.0f);
	glm::vec3 ver8 = glm::vec3(-1.0f, -1.0f, -1.0f);

	verticies.push_back(VertexFormat(ver1, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver2, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver3, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver4, glm::vec4(1, 0, 0, 1)));

	verticies.push_back(VertexFormat(ver2, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver6, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver7, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver3, glm::vec4(1, 0, 0, 1)));

	verticies.push_back(VertexFormat(ver5, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver6, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver7, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver8, glm::vec4(1, 0, 0, 1)));

	verticies.push_back(VertexFormat(ver1, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver5, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver8, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver4, glm::vec4(1, 0, 0, 1)));

	verticies.push_back(VertexFormat(ver1, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver2, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver6, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver5, glm::vec4(1, 0, 0, 1)));

	verticies.push_back(VertexFormat(ver4, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver3, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver8, glm::vec4(1, 0, 0, 1)));
	verticies.push_back(VertexFormat(ver6, glm::vec4(1, 0, 0, 1)));
	//For Commit
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * verticies.size(), &verticies[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)16);

	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
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