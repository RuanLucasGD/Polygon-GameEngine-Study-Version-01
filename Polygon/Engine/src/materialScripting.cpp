#define STB_IMAGE_IMPLEMENTATION

#include <polygon/materialScripting.h>

#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <polygon/stb_image.h>
#include <polygon/glad/glad.h>
#include <polygon/glm/gtc/type_ptr.hpp>

#include <polygon/sceneManager.h>

void MaterialScripting::SetShader(const char* vPath, const char* fPath) {

	// --- create and compile shaders --- //


	// --- open shaders files ---//
	std::ifstream vFile;
	std::ifstream fFile;

	vFile.open(vPath);
	fFile.open(fPath);

	std::stringstream vStream;
	std::stringstream fStream;

	vStream << vFile.rdbuf();
	fStream << fFile.rdbuf();

	vFile.close();
	fFile.close();

	std::string vCode = vStream.str();
	std::string fCode = fStream.str();

	const char* vShaderSource = vCode.c_str();
	const char* fShaderSource = fCode.c_str();

	// --- create shaders --- //

	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vShaderSource, nullptr);
	glShaderSource(fShader, 1, &fShaderSource, nullptr);

	glCompileShader(vShader);
	glCompileShader(fShader);

	ShowShaderLog(vShader, GL_COMPILE_STATUS, "vertex shader: ");
	ShowShaderLog(fShader, GL_COMPILE_STATUS, "fragment shader: ");

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vShader);
	glAttachShader(shaderID, fShader);

	glLinkProgram(shaderID);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	ShowShaderLog(shaderID, GL_LINK_STATUS, "link shader: ");
}

void MaterialScripting::SetInt(const char* uniform, int v) {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;

		return;
	}

	Use();

	int location = glGetUniformLocation(shaderID, uniform);
	glUniform1iv(location, 1, &v);
}

void MaterialScripting::SetBool(const char* uniform, bool v) {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;

		return;
	}

	Use();

	int location = glGetUniformLocation(shaderID, uniform);
	glUniform1i(location, v);
}

void MaterialScripting::SetFloat(const char* uniform, float v) {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;

		return;
	}

	Use();

	int loc = glGetUniformLocation(shaderID, uniform);
	glUniform1fv(loc, 1, &v);
}

void MaterialScripting::SetVec3(const char* uniform, glm::vec3 v) {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;

		return;
	}

	Use();

	int loc = glGetUniformLocation(shaderID, uniform);
	glUniform3fv(loc, 1, &v[0]);
}

void MaterialScripting::SetVec4(const char* uniform, glm::vec4 v) {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;

		return;
	}

	Use();

	int loc = glGetUniformLocation(shaderID, uniform);
	glUniform4fv(loc, 1, &v[0]);
}

void MaterialScripting::SetMat4(const char* uniform, glm::mat4 v) {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;

		return;
	}

	Use();

	int loc = glGetUniformLocation(shaderID, uniform);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(v));
}

void MaterialScripting::SetTexture(const char* path, bool useAlfa) {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;

		return;
	}

	// --- import and generate texture --- //

	stbi_set_flip_vertically_on_load(true);

	int channel; // used for flip image
	unsigned char* textureData = stbi_load(path, &textureWidth, &textureHeigth, &channel, 0);

	if (textureData) {

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		const int COLOR_TYPE = useAlfa ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, COLOR_TYPE, textureWidth, textureHeigth, 0, COLOR_TYPE, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		SetBool(textureIsNull, false);
	}
	else std::cout << "image not loaded " << path << std::endl;
}

void MaterialScripting::EnableMipmapping(bool use) {

	if (textureID == 0) {

		std::cout << "texture not created" << std::endl;
		return;
	}

	const int FILTER = use ? GL_LINEAR : GL_NEAREST;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FILTER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FILTER);
}

void MaterialScripting::UpdateTransform() {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;
		return;
	}

	Camera* camera = gameObject->GetSceneOwner()->GetCurrentCamera();

	SetMat4("transform", gameObject->transform->GetModel());
	SetMat4("viewProj", camera->GetViewProjection());
}

void MaterialScripting::ShowShaderLog(unsigned int shader, unsigned int type, const char* msg) {

	int success;
	glGetShaderiv(shader, type, &success);

	if (!success) {

		char error[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, error);
		std::cout << msg << error << std::endl;
	}
}

void MaterialScripting::Use() {

	if (shaderID == 0) {

		std::cout << "shader not created" << std::endl;

		return;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glUseProgram(shaderID);
}