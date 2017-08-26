#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// SceneObject Link Point Tool.
//-----------------------------------------------------------------------------
#ifndef _LEVELBUILDERLINKPOINTTOOL_H_
#define _LEVELBUILDERLINKPOINTTOOL_H_

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

//-----------------------------------------------------------------------------
// LevelBuilderLinkPointTool
//-----------------------------------------------------------------------------
class LevelBuilderLinkPointTool : public LevelBuilderBaseTool
{
   typedef LevelBuilderBaseTool Parent;

private:
   RectF mCameraArea;
   F32 mCameraZoom;
   F32 mRotation;
   F32 mMountRotation;
   F32 mAutoMountRotation;

   S32 mDraggingMountNode;

   UndoAction* mUndoAction;
   bool mAddUndo;

protected:
   SceneObject* mSceneObject;
   LevelBuilderSceneWindow* mSceneWindow;

   S32 findMountNode( Point2I hitPoint );
   bool isEditable(SceneObject* obj);
   Point2I getMountPointWorld(LevelBuilderSceneWindow* sceneWindow, const SceneObject *obj, Point2F oneToOnePoint) const;
   Point2F getMountPointObject(LevelBuilderSceneWindow* sceneWindow, const SceneObject *obj, const Point2I &worldPoint) const;

public:
   LevelBuilderLinkPointTool();
   ~LevelBuilderLinkPointTool();
   
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
   virtual bool onRightMouseUp( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus );

   DECLARE_CONOBJECT(LevelBuilderLinkPointTool);
};

class UndoLinkPointAddAction : public UndoAction
{
private:
   LevelBuilderSceneEdit* mSceneEdit;
   SceneObject* mObject;
   U32 mNode;
   Vector2 mPosition;

public:
   UndoLinkPointAddAction(LevelBuilderSceneEdit* sceneEdit, UTF8* actionName) : UndoAction(actionName) { mSceneEdit = sceneEdit; };

   void setNode(SceneObject* object, U32 node, Vector2 position) { mObject = object; mNode = node; mPosition = position; deleteNotify(object); };

   virtual void onDeleteNotify(SimObject* object)
   {
      if ((object == mObject) && mUndoManager)
         mUndoManager->removeAction(this);
   };

   virtual void undo()
   {
      mObject->removeLinkPoint(mNode);
      mSceneEdit->onObjectChanged(mObject);
   };
   virtual void redo()
   {
      U32 node = mObject->addLinkPoint(mPosition);
      SceneObject::tMountNode* mountNode = mObject->getMountNode(node);
      mountNode->mMountID = mNode;
      mSceneEdit->onObjectChanged(mObject);
   };
};

class UndoLinkPointRemoveAction : public UndoAction
{
private:
   LevelBuilderSceneEdit* mSceneEdit;
   SceneObject* mObject;
   U32 mNode;
   Vector2 mPosition;

public:
   UndoLinkPointRemoveAction(LevelBuilderSceneEdit* sceneEdit, UTF8* actionName) : UndoAction(actionName) { mSceneEdit = sceneEdit; };

   void setNode(SceneObject* object, U32 node, Vector2 position) { mObject = object; mNode = node; mPosition = position; deleteNotify(object); };

   virtual void onDeleteNotify(SimObject* object)
   {
      if ((object == mObject) && mUndoManager)
         mUndoManager->removeAction(this);
   };

   virtual void redo()
   {
      mObject->removeLinkPoint(mNode);
      mSceneEdit->onObjectChanged(mObject);
   };
   virtual void undo()
   {
      U32 node = mObject->addLinkPoint(mPosition);
      SceneObject::tMountNode* mountNode = mObject->getMountNode(node);
      mountNode->mMountID = mNode;
      mSceneEdit->onObjectChanged(mObject);
   };
};

class UndoLinkPointMoveAction : public UndoAction
{
private:
   LevelBuilderSceneEdit* mSceneEdit;
   SceneObject* mObject;
   
   U32 mNode;
   Vector2 mStartPosition;
   Vector2 mEndPosition;

public:
   UndoLinkPointMoveAction(LevelBuilderSceneEdit* sceneEdit, UTF8* actionName) : UndoAction(actionName) { mSceneEdit = sceneEdit; };

   void setStartPosition(SceneObject* object, U32 node, Vector2 position) { mObject = object; mNode = node; mStartPosition = position; deleteNotify(object); };
   void setEndPosition(Vector2 position) { mEndPosition = position; };

   virtual void onDeleteNotify(SimObject* object)
   {
      if ((object == mObject) && mUndoManager)
         mUndoManager->removeAction(this);
   };

   virtual void undo()
   {
      mObject->setLinkPoint(mNode, mStartPosition);
      mSceneEdit->onObjectChanged(mObject);
   };
   virtual void redo()
   {
      mObject->setLinkPoint(mNode, mEndPosition);
      mSceneEdit->onObjectChanged(mObject);
   };
};

#endif


#endif // TORQUE_TOOLS
