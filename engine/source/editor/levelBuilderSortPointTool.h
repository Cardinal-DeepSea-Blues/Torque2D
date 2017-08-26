#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// SceneObject Link Point Tool.
//-----------------------------------------------------------------------------
#ifndef _LevelBuilderSortPointTool_H_
#define _LevelBuilderSortPointTool_H_

#ifndef _T2DSCENEWINDOW_H_
#include "2d/gui/SceneWindow.h"
#endif

#ifndef _T2DSCENEOBJECT_H_
#include "2d/sceneobject/SceneObject.h"
#endif

#ifndef _LEVELBUILDERBASETOOL_H_
#include "editor/levelBuilderBaseTool.h"
#endif

#ifndef _LEVELBUILDERSCENEEDIT_H_
#include "editor/levelBuilderSceneEdit.h"
#endif

class UndoSortPointMoveAction;

//-----------------------------------------------------------------------------
// LevelBuilderSortPointTool
//-----------------------------------------------------------------------------
class LevelBuilderSortPointTool : public LevelBuilderBaseTool
{
   typedef LevelBuilderBaseTool Parent;

private:
   RectF mCameraArea;
   F32 mCameraZoom;
   F32 mRotation;

   UndoSortPointMoveAction* mUndoAction;
   bool mAddUndo;

protected:
   SceneObject* mSceneObject;
   LevelBuilderSceneWindow* mSceneWindow;

   bool isEditable(SceneObject* obj);
   Point2I getMountPointWorld(LevelBuilderSceneWindow* sceneWindow, const SceneObject *obj, Point2F oneToOnePoint) const;
   Point2F getMountPointObject(LevelBuilderSceneWindow* sceneWindow, const SceneObject *obj, const Point2I &worldPoint) const;

public:
   LevelBuilderSortPointTool();
   ~LevelBuilderSortPointTool();
   
   // Base Tool Overrides
   bool onActivate(LevelBuilderSceneWindow* sceneWindow);
   void onDeactivate();
   bool onAcquireObject(SceneObject* object);
   void onRelinquishObject(SceneObject* object);
   
   void onRenderGraph( LevelBuilderSceneWindow* sceneWindow );

   // Object Editing
   void editObject(SceneObject* object);
   // This cancels an edit, applying changes.
   void finishEdit();

   virtual bool onMouseMove( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus );
   virtual bool onMouseDown( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus );
   virtual bool onMouseUp( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus );
   virtual bool onMouseDragged( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus );

   DECLARE_CONOBJECT(LevelBuilderSortPointTool);
};

class UndoSortPointMoveAction : public UndoAction
{
private:
   LevelBuilderSceneEdit* mSceneEdit;
   SceneObject* mObject;
   
   Vector2 mStartPosition;
   Vector2 mEndPosition;

public:
   UndoSortPointMoveAction(LevelBuilderSceneEdit* sceneEdit, UTF8* actionName) : UndoAction(actionName) { mSceneEdit = sceneEdit; };

   void setStartPosition(SceneObject* object, Vector2 position) { mObject = object; mStartPosition = position; deleteNotify(object); };
   void setEndPosition(Vector2 position) { mEndPosition = position; };

   virtual void onDeleteNotify(SimObject* object)
   {
      if ((object == mObject) && mUndoManager)
         mUndoManager->removeAction(this);
   };

   bool isChanged()
   {
      if( mEndPosition == mStartPosition )
         return false;
      
      return true;
   }

   virtual void undo()
   {
      mObject->setSortPoint(mStartPosition);
      mSceneEdit->onObjectSpatialChanged(mObject);
   };
   virtual void redo()
   {
      mObject->setSortPoint(mEndPosition);
      mSceneEdit->onObjectSpatialChanged(mObject);
   };
};

#endif


#endif // TORQUE_TOOLS
