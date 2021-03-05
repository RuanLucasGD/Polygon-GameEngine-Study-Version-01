#pragma once

/*
* Specifies initial settings of game
*/

class DefaultGameConfig
{
private:

	int width;
	int heigth;

	const char* name;

public:

	DefaultGameConfig(const char* name, int width, int heigth);

	/*
	* Get game name
	*/
	const char* GetName();

	/*
	* Get resolution width
	*/
	int GetResolutionWidth();

	/*
	* Get resolution height
	*/
	int GetResolutionHeight();
};

