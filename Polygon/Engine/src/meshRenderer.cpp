

#include <polygon/meshRenderer.h>

#include <iostream>

#include <polygon/glad/glad.h>
#include <polygon/glm/gtc/type_ptr.hpp>
#include <polygon/glm/gtc/matrix_transform.hpp>

#include <polygon/mesh.h>
#include <polygon/scene.h>
#include <polygon/screen.h>
#include <polygon/gameObject.h>

void MeshRenderer::OnRender() {

	if (!gameObject->GetSceneOwner()->GetCurrentCamera()) return;
	Camera* camera = gameObject->GetSceneOwner()->GetCurrentCamera();

	// --- do all calculations of shader --- //
	material->OnUpdate();
	material->UpdateTransform();


	// --- render --- //
	glBindVertexArray(vao);

	// some 3D meshs not have index for use EBO
	//glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());	// render model
}

void MeshRenderer::SetMesh(Mesh* mesh) {

	if (!material) {

		std::cout << "material not created" << std::endl;
		return;
	}

	// --- generate 3D model --- //

	this->mesh = mesh;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	const size_t INDICES_BUFFER_SIZE = sizeof(int) * mesh->indices.size();
	const size_t VERTICES_BUFFER_SIZE = sizeof(float) * mesh->vertices.size();


	// --- send data to buffers --- //
	glBufferData(GL_ARRAY_BUFFER, VERTICES_BUFFER_SIZE, mesh->vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES_BUFFER_SIZE, mesh->indices.data(), GL_STATIC_DRAW);


	// --- send data to shader attributes --- //
	const int VERTEX_POSITION_ATTRIB = 0;
	const int VERTEX_NORMAL_ATTRIB = 1;
	const int TEXTURE_COORDENATE_ATTRIB = 2;

	// vertices + normal + texture coordenate = 8 
	const int SPACE_BETWEEN_ELEMENTS = 8 * sizeof(float);
	glVertexAttribPointer(VERTEX_POSITION_ATTRIB, 3, GL_FLOAT, GL_FALSE, SPACE_BETWEEN_ELEMENTS, (void*)0);
	glVertexAttribPointer(VERTEX_NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, SPACE_BETWEEN_ELEMENTS, (void*)(3 * sizeof(float)));
	glVertexAttribPointer(TEXTURE_COORDENATE_ATTRIB, 2, GL_FLOAT, GL_FALSE, SPACE_BETWEEN_ELEMENTS, (void*)(6 * sizeof(float)));


	// --- enable shader attributes --- //
	glEnableVertexAttribArray(VERTEX_POSITION_ATTRIB);
	glEnableVertexAttribArray(VERTEX_NORMAL_ATTRIB);
	glEnableVertexAttribArray(TEXTURE_COORDENATE_ATTRIB);


	// --- clean --- //
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void MeshRenderer::SetMaterial(MaterialScripting* material) {

	this->material = material;
	this->material->gameObject = this->gameObject;
	this->material->OnStart();
}

MaterialScripting* MeshRenderer::GetMaterial() {

	if (!material) {

		std::cout << "material not created" << std::endl;
		return nullptr;
	}

	return material;
}