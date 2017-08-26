#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// Path Creation tool.
//-----------------------------------------------------------------------------
#ifndef _LEVELBUILDERPATHTOOL_H_
#define _LEVELBUILDERPATHTOOL_H_

#ifndef _T2DSCENEWINDOW_H_
#include "2d/gui/SceneWindow.h"
#endif

#include "2d/sceneobject/Path.h"

#ifndef _LEVELBUILDERCREATETOOL_H_
#include "editor/levelBuilderCreateTool.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

//-----------------------------------------------------------------------------
// LevelBuilderPathTool
//-----------------------------------------------------------------------------
class LevelBuilderPathTool : public LevelBuilderCreateTool
{
   typedef LevelBuilderCreateTool Parent;

protected:
   virtual SceneObject* createObject();
   virtual void showObject();
   virtual Vector2 getDefaultSize( LevelBuilderSceneWindow *window );
  
public:
   LevelBuilderPathTool();
   ~LevelBuilderPathTool();

   // Declare our Console Object
   DECLARE_CONOBJECT(LevelBuilderPathTool);
};

#endif


#endif // TORQUE_TOOLS
