#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// Level Object Creation tool.
//-----------------------------------------------------------------------------
#ifndef _LEVELBUILDERWORLDLIMITTOOL_H_
#define _LEVELBUILDERWORLDLIMITTOOL_H_

#ifndef _LEVELBUILDERBASEEDITTOOL_H_
#include "editor/levelBuilderBaseEditTool.h"
#endif
#ifndef _T2DSCENEOBJECT_H_
#include "2d/sceneobject/SceneObject.h"
#endif
#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

class UndoFullWorldLimitAction;
class UndoWorldLimitAction;

//-----------------------------------------------------------------------------
// LevelBuilderWorldLimitTool
//-----------------------------------------------------------------------------
class LevelBuilderWorldLimitTool : public LevelBuilderBaseEditTool
{
   typedef LevelBuilderBaseEditTool Parent;
private:
   UndoFullWorldLimitAction* mUndoFullAction;
   UndoWorldLimitAction* mUndoAction;

   F32 mMouseDownAR;

protected:
   bool mMoving;

   LevelBuilderSceneWindow* mSceneWindow;
   SceneObject* mSceneObject;

   Vector2 mWorldLimitPosition;
   Vector2 mWorldLimitSize;
   Vector2 mOffset;

   Vector2 mWorldLimitMinBackup;
   Vector2 mWorldLimitMaxBackup;

   ColorI mCameraOutlineColor;
   ColorI mCameraFillColor;

   RectF mCameraArea;
   F32 mCameraZoom;

   bool isEditable(SceneObject* object) { return true; };

   void updateSceneObject();

public:
   LevelBuilderWorldLimitTool();
   ~LevelBuilderWorldLimitTool();
   
   virtual bool onAdd();
   virtual void onRemove();
   
   virtual bool hasUndoManager() { return true; };

	virtual bool onMouseDown( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus );
	virtual bool onMouseDragged( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus );
   virtual bool onMouseUp( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus );

   // Base Tool Overrides
   virtual bool onActivate(LevelBuilderSceneWindow* sceneWindow);
   virtual void onDeactivate();
   virtual bool onAcquireObject(SceneObject* object);
   virtual void onRelinquishObject(SceneObject* object);

   // Object Editing
   void editObject(SceneObject* object);
   // This cancels an edit, not applying any changes.
   void cancelEdit();
   // This cancels an edit, applying changes.
   void finishEdit();

   virtual bool undo() { mUndoManager.undo(); return true; };
   virtual bool redo() { mUndoManager.redo(); return true; };

   void setWorldLimitPosition(Vector2 pos) { mWorldLimitPosition = pos; };
   void setWorldLimitSize(Vector2 size) { mWorldLimitSize = size; };

   void onRenderGraph( LevelBuilderSceneWindow* sceneWindow );

   // Declare our Console Object
   DECLARE_CONOBJECT(LevelBuilderWorldLimitTool);
};

// This undoes the entire world limit change.
class UndoFullWorldLimitAction : public UndoAction
{
   typedef UndoAction Parent;

private:
   SceneObject::eWorldLimit mStartMode;
   Vector2 mStartMin;
   Vector2 mStartMax;
   bool mStartCallback;
   
   SceneObject::eWorldLimit mEndMode;
   Vector2 mEndMin;
   Vector2 mEndMax;
   bool mEndCallback;

   SceneObject* mSceneObject;

public:
   UndoFullWorldLimitAction(SceneObject* sceneObject, UTF8* actionName) : UndoAction(actionName) { mSceneObject = sceneObject; deleteNotify(sceneObject); };

   void setStart(SceneObject::eWorldLimit mode, Vector2 min, Vector2 max, bool callback)
   {
      mStartMode = mode;
      mStartMin = min;
      mStartMax = max;
      mStartCallback = callback;
   };

   void setFinish(SceneObject::eWorldLimit mode, Vector2 min, Vector2 max, bool callback)
   {
      mEndMode = mode;
      mEndMin = min;
      mEndMax = max;
      mEndCallback = callback;
   };

   bool hasChanged()
   {
      if ((mStartMode != mEndMode) ||
          (mStartMin != mEndMin) ||
          (mStartMax != mEndMax) ||
          (mStartCallback != mEndCallback))
      {
         return true;
      }
      return false;
   };

   virtual void onDeleteNotify(SimObject* object)
   {
      if ((object == mSceneObject) && mUndoManager)
         mUndoManager->removeAction(this);
   };

   virtual void undo()
   {
      mSceneObject->setWorldLimit(mStartMode, mStartMin, mStartMax, mStartCallback);
   };

   virtual void redo()
   {
      mSceneObject->setWorldLimit(mEndMode, mEndMin, mEndMax, mEndCallback);
   };
};

// This undoes each incremental change by the world limit tool.
class UndoWorldLimitAction : public UndoAction
{
   typedef UndoAction Parent;

private:
   LevelBuilderWorldLimitTool* mWorldLimitTool;
   
   Vector2 mStartPosition;
   Vector2 mStartSize;
   Vector2 mFinishPosition;
   Vector2 mFinishSize;

public:
   UndoWorldLimitAction(LevelBuilderWorldLimitTool* tool, UTF8* actionName) : UndoAction(actionName) { mWorldLimitTool = tool; };

   bool hasChanged() { return !((mStartPosition == mFinishPosition) && (mStartSize == mFinishSize)); };

   void setStartBounds(Vector2 pos, Vector2 size) { mStartPosition = pos; mStartSize = size; };
   void setFinishBounds(Vector2 pos, Vector2 size) { mFinishPosition = pos; mFinishSize = size; };

   virtual void undo() { mWorldLimitTool->setWorldLimitPosition(mStartPosition); mWorldLimitTool->setWorldLimitSize(mStartSize); };
   virtual void redo() { mWorldLimitTool->setWorldLimitPosition(mFinishPosition); mWorldLimitTool->setWorldLimitSize(mFinishSize); };
};

#endif


#endif // TORQUE_TOOLS
