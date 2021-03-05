#include <polygon/gizmos.h>

#include <vector>
#include <iostream>

#include <polygon/glad/glad.h>
#include <polygon/glm/gtc/type_ptr.hpp>

#include <polygon/sceneManager.h>

Gizmos* Gizmos::instance;

Gizmos::Gizmos() {

	shaderProgram = 0;
}

void Gizmos::CreateGizmos() {

	// --- create and compile shaders --- //

	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vShaderSource, nullptr);
	glShaderSource(fShader, 1, &fShaderSource, nullptr);

	glCompileShader(vShader);
	glCompileShader(fShader);

	ShowShaderLog(vShader, GL_COMPILE_STATUS, "gizmos: vertex shader: ");
	ShowShaderLog(fShader, GL_COMPILE_STATUS, "gizmos: fragment shader: ");

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);

	glLinkProgram(shaderProgram);

	ShowShaderLog(shaderProgram, GL_LINK_STATUS, "gizmos: link shader: ");

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void Gizmos::DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {

	//This method has a critical memory problem, part of the data is not deleted 
	//from memory when the line is destroyed.Drawn many lines increasing memory usage

	// When this command is done, a new drawing order is added to the list of lines
	// On "OnRender" method is created and drawn all lines os list

	Line* line = new Line();

	line->start = start;
	line->end = end;
	line->color = color;

	lines.push_back(line);
}

void Gizmos::OnRender() {

	glm::mat4 proj = sceneManager->GetCurrenScene()->GetCurrentCamera()->GetViewProjection();
	int projUniformLocation = glGetUniformLocation(shaderProgram, "proj");

	for (auto& c : lines) {

		float points[] = {

			c->start.x,
			c->start.y,
			c->start.z,

			c->end.x,
			c->end.y,
			c->end.z,
		};

		// --- creating line --- //
		unsigned int vao;
		unsigned int vbo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, VERTICES_BUFFER_SIZE, points, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		// --- drawing line --- //
		glUseProgram(shaderProgram);
		int loc = glGetUniformLocation(shaderProgram, "color");
		glUniform3f(loc, c->color.x, c->color.y, c->color.z);

		glUniformMatrix4fv(projUniformLocation, 1, GL_FALSE, glm::value_ptr(proj));
		glDrawArrays(GL_LINES, 0, 2);

		// --- clean line --- //
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	lines.clear();
}

Gizmos* Gizmos::GetInstance() {

	if (!instance) instance = new Gizmos();

	return instance;
}

void Gizmos::ShowShaderLog(unsigned int shader, unsigned int type, const char* msg) {

	int success;
	glGetShaderiv(shader, type, &success);

	if (!success) {

		char error[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, error);
		std::cout << msg << error << std::endl;
	}
}
