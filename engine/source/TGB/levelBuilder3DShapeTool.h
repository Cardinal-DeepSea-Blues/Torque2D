#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// 3D Shape Creation tool.
//-----------------------------------------------------------------------------
#ifndef _LEVELBUILDER3DSHAPETOOL_H_
#define _LEVELBUILDER3DSHAPETOOL_H_

#ifndef _T2DSCENEWINDOW_H_
#include "T2D/t2dSceneWindow.h"
#endif

#ifndef _T2DSHAPE3D_H_
#include "T2D/t2dShape3D.h"
#endif

#ifndef _LEVELBUILDERCREATETOOL_H_
#include "TGB/levelBuilderCreateTool.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

//-----------------------------------------------------------------------------
// LevelBuilder3DShapeTool
//-----------------------------------------------------------------------------
class LevelBuilder3DShapeTool : public LevelBuilderCreateTool
{
   typedef LevelBuilderCreateTool Parent;

private:
   StringTableEntry mShapeName;

protected:
   virtual t2dSceneObject* createObject();
  
public:
   LevelBuilder3DShapeTool();
   ~LevelBuilder3DShapeTool();

   void setShapeName(const char* name) { mShapeName = StringTable->insert(name); };

   // Declare our Console Object
   DECLARE_CONOBJECT(LevelBuilder3DShapeTool);
};

#endif

#endif // TORQUE_TOOLS
