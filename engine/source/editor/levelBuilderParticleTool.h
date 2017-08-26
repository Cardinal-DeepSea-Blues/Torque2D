#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// Particle Effect Creation tool.
//-----------------------------------------------------------------------------
#ifndef _LEVELBUILDERPARTICLETOOL_H_
#define _LEVELBUILDERPARTICLETOOL_H_

#ifndef _T2DSCENEWINDOW_H_
#include "2d/gui/SceneWindow.h"
#endif

#include "2d/assets/ParticleAsset.h"
#ifndef _LEVELBUILDERCREATETOOL_H_
#include "editor/levelBuilderCreateTool.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

//-----------------------------------------------------------------------------
// LevelBuilderParticleTool
//-----------------------------------------------------------------------------
class LevelBuilderParticleTool : public LevelBuilderCreateTool
{
   typedef LevelBuilderCreateTool Parent;

private:
   StringTableEntry mEffectName;

protected:
   virtual SceneObject* createObject();
   virtual void showObject();
  
public:
   LevelBuilderParticleTool();
   ~LevelBuilderParticleTool();

   void setEffect(const char* name) { mEffectName = StringTable->insert(name); };

   // Declare our Console Object
   DECLARE_CONOBJECT(LevelBuilderParticleTool);
};

#endif


#endif // TORQUE_TOOLS
