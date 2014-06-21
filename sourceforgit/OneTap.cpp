#include "s3e.h"
#include "IwDebug.h"
#include "MainMenu.h"
#include "scene.h"
#include "game.h"
#include "input.h"
#include <iostream>

using namespace std;

// FRAME_TIME is the amount of time that a single frame should last in seconds
#define FRAME_TIME  (30.0f / 1000.0f)

// Main entry point for the application
int main()
{
    g_pInput = new Input();

    g_pSceneManager = new SceneManager();

    //Initialise graphics system(s)
    MainMenu* menu = new MainMenu();
    menu->SetName("menu");
    menu->Init();
    g_pSceneManager->Add(menu);

    Game* game = new Game();
    game->SetName("game");
    g_pSceneManager->Add(game);

    g_pSceneManager->SwitchTo(menu);
    cout << endl << endl << "STARTING" << endl << endl;

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

        // Update input system
        g_pInput->Update();

        // Update scene manager
        g_pSceneManager->Update(FRAME_TIME);

        // Render scene manager
        g_pSceneManager->Render();

        // Your rendering/app code goes here.


        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    //Terminate modules being used
    delete g_pInput;
    delete g_pSceneManager;

    // Return
    return 0;
}

/**
* @class SceneManager
*
* @brief Manages a collection of scenes.
*
* The Scene Manager manages a collection of scenes. It also manages the update and rendering of those scenes and provides a mechanism to
* easily switch between them.
*
* Example usage:
* @code
*    // Create scene manager
*    g_pSceneManager = new SceneManager();
*
*    // Create a scene (Game is a class that is derived from Scene)
*    Game* game = new Game();
*    game->SetName("game");
*    g_pSceneManager->Add(game);
*
*    while (!s3eDeviceCheckQuitRequest())
*    {
*        // Update scene manager
*        g_pSceneManager->Update(FRAME_TIME);
*
*        // Render scene manager
*        g_pSceneManager->Render();
*    }
*
*    // Cleanup
*    delete g_pSceneManager;
* @endcode
*
* The scene manager uses teh concept of the "current scene" where only one scene can be active at any given time. To change from one
* scene tp another you use the SwitchTo() method.
*
*/
