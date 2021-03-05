#pragma once

#include <polygon/gizmos.h>

#include <polygon/glm/glm.hpp>

/*
* Draw grid in 3D scene using gizmos
*/

class EditorGrid
{
private:

	int size;
	int space;

public:

	/*
	* Generate 3D grid in the center world
	* @param size: size of grid
	* @param scpace: separation distance of lines
	*/
	EditorGrid(int size, int space);

	/*
	* Draw the grid
	*/
	void DrawEditorGrid();

	int GetSize();

	int GetSpace();
};

