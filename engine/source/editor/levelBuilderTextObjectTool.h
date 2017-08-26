#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// Scene Object Creation tool.
//-----------------------------------------------------------------------------
#ifndef _LEVELBUILDERTEXTOBJECTTOOL_H_
#define _LEVELBUILDERTEXTOBJECTTOOL_H_

#ifndef _T2DSCENEWINDOW_H_
#include "2d/gui/SceneWindow.h"
#endif

#ifndef _T2DSCENEOBJECT_H_
#include "2d/sceneobject/SceneObject.h"
#endif

#ifndef _LEVELBUILDERCREATETOOL_H_
#include "editor/levelBuilderCreateTool.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

#include "T2D/t2dTextObject.h"

//-----------------------------------------------------------------------------
// LevelBuilderTextObjectTool
//-----------------------------------------------------------------------------
class LevelBuilderTextObjectTool : public LevelBuilderCreateTool
{
   typedef LevelBuilderCreateTool Parent;

private:
   StringTableEntry mDefaultFont;
   S32 mDefaultSize;
   S32 mDefaultHeight;
   t2dTextObject::TextAlign mDefaultAlignment;
   bool mDefaultWordWrap;
   bool mDefaultClipText;
   bool mDefaultAutoSize;
   F32 mDefaultAspectRatio;
   F32 mDefaultLineSpacing;
   F32 mDefaultCharacterSpacing;
   StringBuffer mDefaultText;

protected:
   virtual SceneObject* createObject();
   virtual void showObject();
   virtual Vector2 getDefaultSize(LevelBuilderSceneWindow* sceneWindow);
  
public:
   LevelBuilderTextObjectTool();
   ~LevelBuilderTextObjectTool();

   virtual void onObjectCreated();

   void setFontDBName( const char* name);

   // Declare our Console Object
   DECLARE_CONOBJECT(LevelBuilderTextObjectTool);
};

#endif


#endif // TORQUE_TOOLS
