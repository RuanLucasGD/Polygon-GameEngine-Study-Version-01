#pragma once

#include <vector>

#include <polygon/glm/glm.hpp>

/*
* Draw debug lines
*/

class Gizmos
{
private:

	// 6 = glm::vec3 start line + glm::vec3 end line
	const int VERTICES_BUFFER_SIZE = 6 * sizeof(float);
	// 2 = vectors amount per line (position start and end)
	const int INDICES_BUFFER_SIZE = 2 * sizeof(int);

	// gizmo line
	struct Line {

		glm::vec3 start;
		glm::vec3 end;
		glm::vec3 color;
	};

	// --- gizmo shader ---

	const char* vShaderSource = R"glsl(

		#version 330 core

		uniform mat4 proj;

		layout (location = 0) in vec3 aPos;

		void main(){
			
			gl_Position = proj * vec4(aPos, 1.0);
		}

	)glsl";

	const char* fShaderSource = R"glsl(

		#version 330 core
		
		uniform vec3 color = vec3(1.0f);
		out vec4 frag;

		void main(){
			
			frag = vec4(color, 1);
		}

	)glsl";

	unsigned int shaderProgram;

	// earch line use one coordinate
	std::vector<Line*> lines;

	static Gizmos* instance;

	// show shader compiler / link errors 
	void ShowShaderLog(unsigned int shader, unsigned int type, const char* msg);

public:

	Gizmos();

	/*
	* Generate gizmos shaders
	*/
	void CreateGizmos();

	/*
	* draw line to 3D world
	*
	* @param start: start of line
	* @pararm end: end of line
	* @param color: color of line
	*/
	void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color = glm::vec3(1.0f));
	void OnRender();


	static Gizmos* GetInstance();
};

// is not possible initialize gizmos here 
// becase opengl is not initialized
static Gizmos* gizmos = Gizmos::GetInstance();