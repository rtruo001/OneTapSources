#include "MainMenu.h"
#include "game.h"
#include <iostream>

using namespace std;

//Constructor
MainMenu::MainMenu()
{}

//Destructor
MainMenu::~MainMenu() {}

// initialise the menu
void MainMenu::Init()
{
///***********************************HELLO WORLD EXAMPLE*****************************************/
    s3eSurfaceClear(0, 0, 255);
 
	// Print a line of debug text to the screen at top left (0,0)
    // Starting the text with the ` (backtick) char followed by 'x' and a hex value
    // determines the colour of the text.
    s3eDebugPrint(120, 150, "`xffffffHello, World!", 0);
 
    // Flip the surface buffer to screen
    s3eSurfaceShow();

///***********************************************************************************************/
}

// Update the menu
void MainMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
        return;

    Scene::Update(deltaTime, alphaMul);

    // Detect screen tap
    if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
        // Switch to game scene
        g_pInput->Reset();
        cout << endl << endl << "TESTING MENU TO GAME" << endl << endl;
        Game* game = (Game*)g_pSceneManager->Find("game");
        Init();
        g_pSceneManager->SwitchTo(game);
    }
}

// Render the menu
void MainMenu::Render()
{
	Scene::Render();
}