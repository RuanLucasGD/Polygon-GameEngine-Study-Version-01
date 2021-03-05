#pragma once

#include <polygon/glm/glm.hpp>
#include <polygon/transform.h>

/*
* Base for custom materials that use another shaders
*/

class MaterialScripting {

private:

	int textureWidth;
	int textureHeigth;

	unsigned int shaderID;
	unsigned int textureID;

	void ShowShaderLog(unsigned int shader, unsigned int type, const char* msg);

public:

	// default uniform names 
	const char* textureIsNull = "material.textureIsNull";

	// object owner
	GameObject* gameObject;

	virtual void OnStart() {}
	virtual void OnUpdate() {}

	/*
	* Use filter in texture  (if texture exist)
	* @param use: enable of disabled
	*/
	void EnableMipmapping(bool use);

	/* Set shader used in mateial
	* @param vPath: vertex shader file path
	* @param fPath: fragment shader file path
	*/
	void SetShader(const char* vPath, const char* fPath);

	/*
	* Set texture of material
	* @param path: texture path
	* @param useAlfa: color type of texture, GL_RGB or GL_RGBA
	*/
	void SetTexture(const char* path, bool useAlfa = false);

	/*
	* Set bool uniform attribute
	* @param uniform: attribute name
	* @param v: value
	*/
	void SetBool(const char* uniform, bool v);

	/*
	* Set int uniform attribute
	* @param uniform: attribute name
	* @param v: value
	*/
	void SetInt(const char* uniform, int v);

	/*
	* Set float uniform attribute
	* @param uniform: attribute name
	* @param v: value
	*/
	void SetFloat(const char* uniform, float v);

	/*
	* Set vec3 uniform attribute
	* @param uniform: attribute name
	* @param v: value
	*/
	void SetVec3(const char* uniform, glm::vec3 v);

	/*
	* Set vec4 uniform attribute
	* @param uniform: attribute name
	* @param v: value
	*/
	void SetVec4(const char* uniform, glm::vec4 v);

	/*
	* Set mat4 uniform attribute
	* @param uniform: attribute name
	* @param v: value
	*/
	void SetMat4(const char* uniform, glm::mat4 v);

	/*
	* Send transformations data to shader
	*/
	void UpdateTransform();

	/*
	* Active shader, used before that set uniform attribute
	*/
	void Use();
};