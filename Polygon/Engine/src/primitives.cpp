#include <polygon/primitives.h>

Primitives* Primitives::instance;

Primitives* Primitives::GetInstance() {

	if (!instance) instance = new Primitives();

	return instance;
}