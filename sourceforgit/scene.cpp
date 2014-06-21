/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#include "scene.h"
#include "IwGx.h"
//#include "input.h"
//#include "main.h"

SceneManager* g_pSceneManager = 0;

/***********************************************************************************************************************
************************************************************************************************************************
***************************************************** Scene class ******************************************************
************************************************************************************************************************
************************************************************************************************************************/

Scene::Scene() 
:m_NameHash(0), m_IsActive(true), m_IsInputActive(false)
{
}

Scene::~Scene()
{
}

void Scene::SetName(const char* name)
{
    m_NameHash = IwHashString(name);
}

/**************************************function Init*********************************************
* Summary - Initialize scene
*************************************************************************************************/
void Scene::Init()
{
}

/**************************************function Update*******************************************
* Summary - Updates this scene
*
* @param deltaTime   Number of seconds that has passed since Update() was last called.
* @param alphaMul    The alpha value being passed down to this node. Default value is 1.
*************************************************************************************************/
void Scene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;

    m_Tweener.Update(deltaTime);

    CNode::Update(deltaTime, alphaMul);
}

/**************************************function Render*******************************************
* Summary - Render the scene
*************************************************************************************************/
void Scene::Render()
{
    CNode::Render();
}

/***********************************************************************************************************************
************************************************************************************************************************
************************************************ SceneManager class ****************************************************
************************************************************************************************************************
************************************************************************************************************************/

//Constructor
SceneManager::SceneManager() : m_Current(0), m_Next(0)
{
}

//Destructor
SceneManager::~SceneManager()
{
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
        delete *it;
}

/**************************************function Add**********************************************
* Summary - Add a scene to the manager
*
* @param scene - the scene to add if non-null
*************************************************************************************************/
void SceneManager::Add(Scene* scene)
{
    m_Scenes.push_back(scene);
    scene->SetManager(this);
}

/**************************************function Remove*******************************************
* Summary - Remove a scene from the manager
*
* @param scene - remove the scene if non-null
*************************************************************************************************/
void SceneManager::Remove(Scene* scene)
{
    m_Scenes.remove(scene);
}

/**************************************function Find*********************************************
* Summary - Returns the searched scene
*
* @param name - the name of the scene
* @return - scene, but null if it fails
*************************************************************************************************/
Scene* SceneManager::Find(const char* name)
{
    unsigned int name_hash = IwHashString(name);
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
    {
        if ((*it)->GetNameHash() == name_hash)
            return *it;
    }

    return 0;
}

/**************************************function Update*******************************************
* Summary - Updates this scene
*
* @param deltaTime   Number of seconds that has passed since Update() was last called.
*************************************************************************************************/
void SceneManager::Update(float deltaTime)
{
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
        (*it)->Update(deltaTime);
}


/**************************************function Render*******************************************
* Summary - Renders all of the scene in manager
*************************************************************************************************/
void SceneManager::Render()
{
    for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
        (*it)->Render();
}

void SceneManager::OnSwitchComplete(CTween* pTween)
{
    g_pSceneManager->FinishSwitch();
}

void SceneManager::FinishSwitch()
{
    m_Next->SetInputActive(true);
    m_Next->SetActive(true);
    m_Current->Update(0);           // Update one last time to ensure that last tweened values get set because on the next frame the scene will be inactive
    m_Current->SetActive(false);
    m_Current = m_Next;
    m_Next = 0;
}

/*********************************function SwitchTo*******************************************
* Sumarry: Switch to a new scene.
*
* @param scene - The new scene to switch to.
*********************************************************************************************/
void SceneManager::SwitchTo(Scene* scene)
{
    m_Next = scene;
    if (m_Current == 0)
    {
         // Activate and make visible the new scene
        m_Current = m_Next;
        m_Current->SetActive(true);
        m_Current->m_IsVisible = true;
        m_Current->SetInputActive(true);
        m_Next = 0;
    }
    else
    {
		// Activate and make visible the new scene
		m_Next->SetActive(true);
		m_Next->SetInputActive(true);
		m_Next->SetActive(true);
		m_Next->m_IsVisible = true;

		// Deactivate and hide the old scene
		m_Current->SetInputActive(false);
		m_Current->SetActive(false);
		m_Current->m_IsVisible = false;
		m_Current = m_Next;
		m_Next = 0;
    }
}
