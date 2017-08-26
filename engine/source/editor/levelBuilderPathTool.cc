#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// Path Creation tool.
//---------------------------------------------------------------------------------------------

#include "console/console.h"
#include "editor/levelBuilderPathTool.h"

// Implement Our Console Object
IMPLEMENT_CONOBJECT(LevelBuilderPathTool);

LevelBuilderPathTool::LevelBuilderPathTool() : LevelBuilderCreateTool()
{
   // Set our tool name
   mToolName = StringTable->insert("Path Tool");
}

LevelBuilderPathTool::~LevelBuilderPathTool()
{
}

SceneObject* LevelBuilderPathTool::createObject()
{
   t2dPath* path = dynamic_cast<t2dPath*>(ConsoleObject::create("t2dPath"));

   return path;
}

void LevelBuilderPathTool::showObject()
{
   mCreatedObject->setDebugOn(BIT(1));
   mCreatedObject->setVisible(true);
}

Vector2 LevelBuilderPathTool::getDefaultSize( LevelBuilderSceneWindow *window )
{
   return Vector2(10.0f, 10.0f);
}


#endif // TORQUE_TOOLS
