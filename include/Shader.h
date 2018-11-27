/*
 * Shader.h
 *
 *  Created on: Nov 23, 2018
 *      Author: abslon
 */

#ifndef SHADER_H_
#define SHADER_H_
#include "TBSystem.h"
#include <fstream>
#include <sstream>

/*
 * Loads shader files from /res/shaders folder
 */

Dali::Shader LoadShaders(const char* vertexPath, const char* fragmentPath)
{

	std::string completeVertexPath = APP_RES_PATH + "shaders/" + vertexPath;
	std::string completeFragmentPath = APP_RES_PATH + "shaders/" + fragmentPath;
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(completeVertexPath.c_str());
		fShaderFile.open(completeFragmentPath.c_str());
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}

	catch (std::ifstream::failure e)
	{
		//dlog_print(DLOG_DEBUG, "TEST_BULLET", "failed to open shader file!");
	}

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	return Dali::Shader::New(vShaderCode, fShaderCode);
}

#endif /* SHADER_H_ */
