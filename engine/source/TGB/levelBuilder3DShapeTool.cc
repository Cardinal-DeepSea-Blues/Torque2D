#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// 3D Shape Creation tool.
//---------------------------------------------------------------------------------------------

#include "console/console.h"
#include "TGB/levelBuilder3DShapeTool.h"

// Implement Our Console Object
IMPLEMENT_CONOBJECT(LevelBuilder3DShapeTool);

LevelBuilder3DShapeTool::LevelBuilder3DShapeTool() : LevelBuilderCreateTool(),
                                                     mShapeName(NULL)
{
   // Set our tool name
   mToolName = StringTable->insert("3D Shape Tool");
}

LevelBuilder3DShapeTool::~LevelBuilder3DShapeTool()
{
}

t2dSceneObject* LevelBuilder3DShapeTool::createObject()
{
   t2dShape3D* shape3D = dynamic_cast<t2dShape3D*>(ConsoleObject::create("t2dShape3D"));

   if (shape3D)
      shape3D->setShape(mShapeName);

   return shape3D;
}

ConsoleMethod(LevelBuilder3DShapeTool, setShape, void, 3, 3, "(shapeName) Sets the shape for the created 3D shapes."
			  "@param shapeName The name of the desired shape."
			  "@return No return value.")
{
   if (Platform::isFile(argv[2]))
      object->setShapeName(argv[2]);
   else
      Con::warnf("LevelBuilder3DShapeTool::setShape - Invalid shape file: %s.", argv[2]);
}

#endif // TORQUE_TOOLS
