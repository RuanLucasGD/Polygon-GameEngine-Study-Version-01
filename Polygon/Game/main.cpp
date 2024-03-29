#include <polygon/polygon.h>

#include <Level_0.h>

int main() {

	DefaultGameConfig* gameConfig = new DefaultGameConfig("Polygon Engine", 980, 840);
	DefaultLevelConfig* levelConfig = new DefaultLevelConfig("level 0", new Level_0());

	Core* game = new Core(gameConfig, levelConfig);
	game->Loop();
	game->~Core();

	return 0;
}