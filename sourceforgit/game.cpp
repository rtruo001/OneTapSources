#include "MainMenu.h"
#include "game.h"
#include <iostream>

using namespace std;

//Constructor
Game::Game()
{}

//Destructor
Game::~Game() {}

// initialise the menu
void Game::Init()
{
    Scene::Init();
///***********************************HELLO WORLD EXAMPLE*****************************************/
    s3eSurfaceClear(0, 0, 255);
 
	// Print a line of debug text to the screen at top left (0,0)
    // Starting the text with the ` (backtick) char followed by 'x' and a hex value
    // determines the colour of the text.
    s3eDebugPrint(120, 150, "`xffffffThe Game!", 0);
 
    // Flip the surface buffer to screen
    s3eSurfaceShow();

///***********************************************************************************************/
}

// Update the menu
void Game::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
        return;

    Scene::Update(deltaTime, alphaMul);
    
    // Detect screen tap
    if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
        // Switch to game scene
        g_pInput->Reset();
        cout << endl << endl << "TESTING GAME TO MENU" << endl << endl;
        MainMenu* menu = (MainMenu*)g_pSceneManager->Find("menu");
        Init();
        g_pSceneManager->SwitchTo(menu);
    }
}

// Render the menu
void Game::Render()
{
	Scene::Render();
}