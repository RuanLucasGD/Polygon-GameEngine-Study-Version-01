#pragma once

#include <polygon/materialScripting.h>

class SampleMaterial : public MaterialScripting
{
public:

	float specular;

	void OnStart();
	void OnUpdate();
};

