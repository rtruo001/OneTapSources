#ifndef __MAINMENU_H_
#define __MAINMENU_H_

#include "scene.h"
#include "game.h"
#include "input.h"

class MainMenu : public Scene
{
private:

public:
	//Constructor
	MainMenu();
	
	//Destructor
	~MainMenu();

    // initialise the menu
    void Init();

    // Update the menu
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the menu
    void Render();

};
#endif