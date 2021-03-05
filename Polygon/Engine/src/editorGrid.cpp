#include <polygon/editorGrid.h>

EditorGrid::EditorGrid(int size, int space) {

	this->size = size;
	this->space = space;
}

void EditorGrid::DrawEditorGrid() {

	// convert grid size em radius
	int xSize = size / 2;
	int zSize = size / 2;

	// draw horizonal lines
	for (int x = -xSize; x <= xSize; x += space) {

		glm::vec3 start = glm::vec3(x, 0, -zSize);
		glm::vec3 end = glm::vec3(x, 0, zSize);

		gizmos->DrawLine(start, end);
	}

	// draw longitudinal lines
	for (int z = -zSize; z <= zSize; z += space) {

		glm::vec3 start = glm::vec3(-xSize, 0, z);
		glm::vec3 end = glm::vec3(xSize, 0, z);

		gizmos->DrawLine(start, end);
	}
}

int EditorGrid::GetSize() { return size; }

int EditorGrid::GetSpace() { return space; }