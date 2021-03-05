#pragma once

#include <vector>

/*
* 3D model structure
*/
struct Mesh {

public:

	std::vector<float> vertices;
	std::vector<int> indices;
};