#ifndef _GAME_MODELS_H_
#define _GAME_MODELS_H_

#pragma once
#include <vector>
#include <map>
#include <GL/glew.h>
#include "VertexFormat.h"

namespace Models
{
	struct Model
	{
		unsigned int vao;
		std::vector<unsigned int> vbos;

		Model(){}
	};

	class GameModels
	{
	public:
		GameModels();
		~GameModels();
		void CreateTriangleModel(const std::string& gameModelName);
		void CreateCubeModel(const std::string& gameModelName);
		void DeleteModel(const std::string& gameModelName);
		unsigned int GetModel(const std::string& gameModelName);
	private:
		std::map<std::string, Model> GameModelList;
	};
}
#endif