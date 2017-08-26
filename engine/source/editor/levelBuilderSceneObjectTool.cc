#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// Scene Object Creation tool.
//---------------------------------------------------------------------------------------------

#include "console/console.h"
#include "editor/levelBuilderSceneObjectTool.h"

// Implement Our Console Object
IMPLEMENT_CONOBJECT(LevelBuilderSceneObjectTool);

LevelBuilderSceneObjectTool::LevelBuilderSceneObjectTool() : LevelBuilderCreateTool()
{
   // Set our tool name
   mToolName = StringTable->insert("Scene Object Tool");
}

LevelBuilderSceneObjectTool::~LevelBuilderSceneObjectTool()
{
}

SceneObject* LevelBuilderSceneObjectTool::createObject()
{
   SceneObject* staticSprite = dynamic_cast<SceneObject*>(ConsoleObject::create("SceneObject"));

   return staticSprite;
}

void LevelBuilderSceneObjectTool::showObject()
{
   mCreatedObject->setDebugOn(BIT(1));
   mCreatedObject->setVisible(true);
}


#endif // TORQUE_TOOLS
