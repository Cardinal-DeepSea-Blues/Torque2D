#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// Trigger Creation tool.
//-----------------------------------------------------------------------------
#ifndef _LEVELBUILDERTRIGGERTOOL_H_
#define _LEVELBUILDERTRIGGERTOOL_H_

#ifndef _T2DSCENEWINDOW_H_
#include "2d/gui/SceneWindow.h"
#endif

#ifndef _T2DTRIGGER_H_
#include "2d/sceneobject/Trigger.h"
#endif

#ifndef _LEVELBUILDERCREATETOOL_H_
#include "editor/levelBuilderCreateTool.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

//-----------------------------------------------------------------------------
// LevelBuilderTriggerTool
//-----------------------------------------------------------------------------
class LevelBuilderTriggerTool : public LevelBuilderCreateTool
{
   typedef LevelBuilderCreateTool Parent;

protected:
   virtual SceneObject* createObject();
   virtual void showObject();
  
public:
   LevelBuilderTriggerTool();
   ~LevelBuilderTriggerTool();

   // Declare our Console Object
   DECLARE_CONOBJECT(LevelBuilderTriggerTool);
};

#endif


#endif // TORQUE_TOOLS
