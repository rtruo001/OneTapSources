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

#ifndef __SCENE_H_
#define __SCENE_H_

#include <list>
#include "Iw2DSceneGraph.h"
#include "IwTween.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
using namespace IwTween;

class SceneManager;

/****************************************Scene*******************************************************/

class Scene : public CNode
{
protected:
    unsigned int        m_NameHash;                     // Hash string representation of scene name
    bool                m_IsActive;                     // Active state
    bool                m_IsInputActive;                // Input active state
    SceneManager*       m_Manager;                      // Scene manager
    CTweenManager       m_Tweener;                      // Scene local tween manager

public:
    bool                IsActive() const                    { return m_IsActive; }
    void                SetActive(bool active)              { m_IsActive = active; }
    void                SetName(const char* name);
    unsigned int        GetNameHash() const                 { return m_NameHash; }
    void                SetManager(SceneManager* manager)   { m_Manager = manager; }
    void                SetInputActive(bool active)         { m_IsInputActive = active; }
    CTweenManager&      GetTweener()                        { return m_Tweener; }

public:
    Scene();
    virtual ~Scene();
    virtual void    Init();
    virtual void    Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    virtual void    Render();
};

/****************************************Scene Manager*************************************************/

class SceneManager
{
protected:
    Scene*              m_Current;              // Currently active scene
    Scene*              m_Next;                 // Next scene (scene that is being switched to)
    std::list<Scene*>   m_Scenes;               // Scenes list
public:
    Scene*  GetCurrent()                { return m_Current; }

public:
    SceneManager();
    ~SceneManager();

    void    Update(float deltaTime = 0.0f);
    void    Render();
    void    Add(Scene* scene);
    void    Remove(Scene* scene);
    Scene*  Find(const char* name);

    // Internal
    static void OnSwitchComplete(CTween* pTween);
    void    FinishSwitch();

    void SwitchTo(Scene* scene);
};

extern SceneManager* g_pSceneManager;


#endif  // __SCENE_H__


