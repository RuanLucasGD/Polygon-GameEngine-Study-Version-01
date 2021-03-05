#pragma once

#include <vector>

#include <polygon/glm/glm.hpp>

#include <polygon/mesh.h>
#include <polygon/component.h>
#include <polygon/materialScripting.h>

/*
* Render 3D model on 3D space
*/

class MeshRenderer : public Component
{
private:

	// --- opengl buffers --- //

	unsigned int vao;
	unsigned int ebo;
	unsigned int vbo;

	MaterialScripting* material;

	Mesh* mesh;

public:

	void OnRender();

	/*
	* Use some 3D mesh existent
	* @param mesh: some mesh
	*/
	void SetMesh(Mesh* mesh);

	/*
	* Set object material
	* @param material: material with shader
	*/
	void SetMaterial(MaterialScripting* material);

	/*
	* Get object material
	*/
	MaterialScripting* GetMaterial();
};

