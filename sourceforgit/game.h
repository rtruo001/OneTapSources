#ifndef __GAME_H_
#define __GAME_H_

#include "scene.h"
#include "MainMenu.h"

class Game : public Scene
{
private:

public:
	//Constructor
	Game();
	
	//Destructor
	~Game();

    // initialize the menu
    void Init();

    // Update the menu
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the menu
    void Render();

};
#endif