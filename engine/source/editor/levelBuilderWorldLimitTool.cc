#ifndef TORQUE_PLAYER

//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//
// Level Object Creation tool.
//---------------------------------------------------------------------------------------------

#include "console/console.h"
#include "graphics/dgl.h"
#include "editor/levelBuilderWorldLimitTool.h"

// Implement Our Console Object
IMPLEMENT_CONOBJECT(LevelBuilderWorldLimitTool);

void LevelBuilderWorldLimitTool::updateSceneObject()
{
   // Do nothing if there is no valid scene object
   if(!mSceneObject || !mSceneWindow )
      return;
   
   const Vector2 min = mWorldLimitPosition - (mWorldLimitSize * 0.5);
   const Vector2 max = mWorldLimitPosition + (mWorldLimitSize * 0.5);

   /* This part is copied from former finishEdit() - Why aren't those modes allowed?
   // Set a default limit mode if necessary.
   SceneObject::eWorldLimit limit = mSceneObject->getWorldLimitMode();
   if ((limit == SceneObject::T2D_LIMIT_OFF) ||
       (limit == SceneObject::T2D_LIMIT_INVALID) ||
       (limit == SceneObject::T2D_LIMIT_NULL))
   {
      limit = SceneObject::T2D_LIMIT_BOUNCE;
   }
   */

   SceneObject::eWorldLimit limit = mSceneObject->getWorldLimitMode();
   if( limit == SceneObject::T2D_LIMIT_INVALID )
      limit = SceneObject::T2D_LIMIT_BOUNCE;

   mSceneObject->setWorldLimit(limit, min, max, mSceneObject->getWorldLimitCallback());

   if( mSceneWindow->getSceneEdit() )
      mSceneWindow->getSceneEdit()->onObjectSpatialChanged(mSceneObject);
}

LevelBuilderWorldLimitTool::LevelBuilderWorldLimitTool() : LevelBuilderBaseEditTool(),
                                                           mWorldLimitPosition(0.0f, 0.0f),
                                                           mWorldLimitSize(100.0f, 75.0f),
                                                           mCameraOutlineColor( 255, 255, 255, 200 ),
                                                           mCameraFillColor( 40, 40, 40, 150),
                                                           mSceneObject(NULL),
                                                           mSceneWindow(NULL),
                                                           mUndoFullAction(NULL),
                                                           mUndoAction(NULL),
                                                           mMouseDownAR(1.0f)
{
   // Set our tool name
   mToolName = StringTable->insert("World Limit Tool");
}

LevelBuilderWorldLimitTool::~LevelBuilderWorldLimitTool()
{
}

bool LevelBuilderWorldLimitTool::onAdd()
{
   if (!Parent::onAdd())
      return false;

   if (!mUndoManager.registerObject())
      return false;

   mUndoManager.setModDynamicFields(true);
   mUndoManager.setModStaticFields(true);

   return true;
}

void LevelBuilderWorldLimitTool::onRemove()
{
   mUndoManager.unregisterObject();

   Parent::onRemove();
}

bool LevelBuilderWorldLimitTool::onActivate(LevelBuilderSceneWindow* sceneWindow)
{
   if (!Parent::onActivate(sceneWindow))
      return false;

   mSceneWindow = sceneWindow;
   mSceneObject = NULL;

   return true;
}

void LevelBuilderWorldLimitTool::onDeactivate()
{
   finishEdit();

   mUndoFullAction = NULL;
   mUndoAction = NULL;

   mSceneObject = NULL;
   mSceneWindow = NULL;
   Parent::onDeactivate();
}

bool LevelBuilderWorldLimitTool::onAcquireObject(SceneObject* object)
{
   if(!isEditable(object) || !mSceneWindow)
      return false;

   if (!Parent::onAcquireObject(object))
      return false;

   if (!mSceneObject || (mSceneWindow->getToolOverride() == this))
   {
      finishEdit();
      editObject(object);
   }

   return true;
}

void LevelBuilderWorldLimitTool::onRelinquishObject(SceneObject* object)
{
   if(!mSceneWindow || !mSceneObject)
      return Parent::onRelinquishObject(object);

   if (object == mSceneObject)
   {
      finishEdit();

      if (mSceneWindow->getToolOverride() == this)
      {
         bool foundNewObject = false;
         // Since we're a tool override, we should try to edit any object we can.
         for (S32 i = 0; i < mSceneWindow->getSceneEdit()->getAcquiredObjectCount(); i++)
         {
            SceneObject* newObject = mSceneWindow->getSceneEdit()->getAcquiredObject(i);
            if ((newObject != mSceneObject) && isEditable(newObject))
            {
               foundNewObject = true;
               editObject(newObject);
               break;
            }
         }

         if (!foundNewObject)
         {
            // Grab the size and position of the camera from the scenegraph.
            Vector2 cameraPosition = Vector2(0.0f, 0.0f);
            Vector2 cameraSize = Vector2(100.0f, 75.0f);
            if (mSceneWindow->getSceneGraph())
            {
               const char* pos = mSceneWindow->getSceneGraph()->getDataField(StringTable->insert("cameraPosition"), NULL);
               if (SceneObject::getStringElementCount(pos) == 2)
                  cameraPosition = SceneObject::getStringElementVector(pos);
               
               const char* size = mSceneWindow->getSceneGraph()->getDataField(StringTable->insert("cameraSize"), NULL);
               if (SceneObject::getStringElementCount(size) == 2)
                  cameraSize = SceneObject::getStringElementVector(size);
            }

            // And update the camera.
            mSceneWindow->setTargetCameraZoom( 1.0f );
            mSceneWindow->setTargetCameraPosition(cameraPosition, cameraSize.x, cameraSize.y);
            mSceneWindow->startCameraMove( 0.5f );
            mSceneObject = NULL;
         }
      }
   }

   // Do parent cleanup
   Parent::onRelinquishObject(object);
}

void LevelBuilderWorldLimitTool::editObject(SceneObject* object)
{
   if (!mSceneWindow || !isEditable(object))
      return;

   mSceneObject = object;

   SceneObject::eWorldLimit mode = object->getWorldLimitMode();
   Vector2 min = object->getWorldLimitMin();
   Vector2 max = object->getWorldLimitMax();
   bool callback = object->getWorldLimitCallback();

   // Store entry values
   mWorldLimitMinBackup = min;
   mWorldLimitMinBackup = max;

   if (RectF(min.x, min.y, max.x - min.x, max.y - min.y).isValidRect())
   {
      mWorldLimitPosition = min + ((max - min) * 0.5);
      mWorldLimitSize = max - min;
   }
   else
   {
      // Set to default
      mSceneObject->setDefaultWorldLimit();
      editObject( mSceneObject );
      return;
   }

   mCameraArea = mSceneWindow->getCurrentCameraArea();
   mCameraZoom = mSceneWindow->getCurrentCameraZoom();

   mSceneWindow->setTargetCameraZoom(1.0f);
   mSceneWindow->setTargetCameraPosition(mWorldLimitPosition, mWorldLimitSize.x * 2.0f, mWorldLimitSize.y * 2.0f);
   mSceneWindow->startCameraMove( 0.5f );

   mUndoFullAction = new UndoFullWorldLimitAction(mSceneObject, "World Limit Change");
   mUndoFullAction->setStart(mode, min, max, callback);
}

ConsoleMethod(LevelBuilderWorldLimitTool, editObject, void, 3, 3, "Selects an object for editing.")
{
   SceneObject* obj = dynamic_cast<SceneObject*>(Sim::findObject(argv[2]));
   if (obj)
      object->editObject(obj);
   else
      Con::warnf("Invalid object past to LevelBuilderWorldLimitTool::editObject");
}

void LevelBuilderWorldLimitTool::cancelEdit()
{
   if (!mSceneObject || !mSceneWindow)
      return;

   // Restore world limit
   mSceneObject->setWorldLimitMin( mWorldLimitMinBackup );
   mSceneObject->setWorldLimitMax( mWorldLimitMaxBackup );

   // Reset the camera.
   mSceneWindow->setTargetCameraZoom( mCameraZoom );
   mSceneWindow->setTargetCameraArea( mCameraArea );
   mSceneWindow->startCameraMove( 0.5f );

   // Cancel the undo.
   if (mUndoFullAction)
   {
      delete mUndoFullAction;
      mUndoFullAction = NULL;
   }
   
   mUndoManager.clearAll();

   mSceneObject = NULL;
}

ConsoleMethod(LevelBuilderWorldLimitTool, cancelEdit, void, 2, 2, "Cancels editing of an object.")
{
   object->cancelEdit();
}

void LevelBuilderWorldLimitTool::finishEdit()
{
   if (!mSceneObject || !mSceneWindow)
      return;

   // Update the SceneObject
   updateSceneObject();

   // Reset the camera.
   mSceneWindow->setTargetCameraZoom( mCameraZoom );
   mSceneWindow->setTargetCameraArea( mCameraArea );
   mSceneWindow->startCameraMove( 0.5f );

   // Set the undo.
   if (mUndoFullAction)
   {
      mUndoFullAction->setFinish( mSceneObject->getWorldLimitMode(), 
                                  mSceneObject->getWorldLimitMin(), 
                                  mSceneObject->getWorldLimitMax(),
                                  mSceneObject->getWorldLimitCallback());

      if (mUndoFullAction->hasChanged())
         mUndoFullAction->addToManager(&mSceneWindow->getSceneEdit()->getUndoManager());
      else
         delete mUndoFullAction;

      mUndoFullAction = NULL;
   }
   
   mUndoManager.clearAll();

   mSceneObject = NULL;
}

ConsoleMethod(LevelBuilderWorldLimitTool, finishEdit, void, 2, 2, "Applies changes and ends editing of an object.")
{
   object->finishEdit();
}

bool LevelBuilderWorldLimitTool::onMouseDown( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus )
{
   if (sceneWindow != mSceneWindow)
      return Parent::onMouseDragged(sceneWindow, mouseStatus);

   // Acquire Object
   if (!mSceneObject)
   {
      if (mouseStatus.pickList.size() == 0)
         return Parent::onMouseDown(sceneWindow, mouseStatus);

      SceneObject* pObj = mouseStatus.pickList[0];

      if (mouseStatus.event.mouseClickCount >= 2)
         sceneWindow->getSceneEdit()->requestAcquisition(pObj);

      return true;
   }

   mMouseDownAR = mWorldLimitSize.x / mWorldLimitSize.y;

   Vector2 upperLeft = mWorldLimitPosition - (mWorldLimitSize * 0.5);
   Vector2 lowerRight = mWorldLimitPosition + (mWorldLimitSize * 0.5);

   mSizingState = getSizingState( sceneWindow, mouseStatus.event.mousePoint, RectF(upperLeft, mWorldLimitSize));

   mMoving = false;
   if (!mSizingState)
   {
      if ((mouseStatus.mousePoint2D.x > upperLeft.x) && (mouseStatus.mousePoint2D.x < lowerRight.x) &&
          (mouseStatus.mousePoint2D.y > upperLeft.y) && (mouseStatus.mousePoint2D.y < lowerRight.y))
      {
          mMoving = true;
          mOffset = mouseStatus.mousePoint2D - (upperLeft + ((lowerRight - upperLeft) * 0.5));
      }
   }

   if ((mouseStatus.event.mouseClickCount >= 2) && !mMoving && !mSizingState)
      finishEdit();

   mUndoAction = new UndoWorldLimitAction(this, "World Limit Change");
   mUndoAction->setStartBounds(mWorldLimitPosition, mWorldLimitSize);

   return true;
}

bool LevelBuilderWorldLimitTool::onMouseDragged( LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus &mouseStatus )
{
   if (!mSceneObject || (sceneWindow != mSceneWindow))
      return Parent::onMouseDragged(sceneWindow, mouseStatus);

   bool flipX, flipY;
   if (mSizingState)
      scale(sceneWindow->getSceneEdit(), mWorldLimitSize, mWorldLimitPosition, mouseStatus.mousePoint2D, mouseStatus.event.modifier & SI_CTRL,
            mouseStatus.event.modifier & SI_SHIFT, mMouseDownAR, mWorldLimitSize, mWorldLimitPosition, flipX, flipY);
   else if (mMoving)
      move(sceneWindow->getSceneEdit(), mWorldLimitSize, mouseStatus.mousePoint2D - mOffset, mWorldLimitPosition);

   updateSceneObject();

   return true;
}

bool LevelBuilderWorldLimitTool::onMouseUp(LevelBuilderSceneWindow* sceneWindow, const t2dEditMouseStatus& mouseStatus)
{
   if (!mSceneObject || (sceneWindow != mSceneWindow) || !mUndoAction )
      return Parent::onMouseUp(sceneWindow, mouseStatus);

   mUndoAction->setFinishBounds(mWorldLimitPosition, mWorldLimitSize);
   if (mUndoAction->hasChanged())
      mUndoAction->addToManager(&mUndoManager);
   else
      delete mUndoAction;

   mUndoAction = NULL;

   return false;
}

void LevelBuilderWorldLimitTool::onRenderGraph(LevelBuilderSceneWindow* sceneWindow)
{ 
   // Render Parent first
   Parent::onRenderGraph( sceneWindow );

   if (!mSceneObject || (sceneWindow != mSceneWindow))
      return;

   Vector2 upperLeft = mWorldLimitPosition - (mWorldLimitSize * 0.5);
   Vector2 lowerRight = mWorldLimitPosition + (mWorldLimitSize * 0.5);
   Vector2 windowUpperLeft, windowLowerRight;
   sceneWindow->sceneToWindowCoord(upperLeft, windowUpperLeft);
   sceneWindow->sceneToWindowCoord(lowerRight, windowLowerRight);

   Point2I offsetUpperLeft = sceneWindow->localToGlobalCoord(Point2I(S32(windowUpperLeft.x), S32(windowUpperLeft.y)));
   Point2I offsetLowerRight = sceneWindow->localToGlobalCoord(Point2I(S32(windowLowerRight.x), S32(windowLowerRight.y)));

   RectI cameraRect = RectI(offsetUpperLeft, offsetLowerRight - offsetUpperLeft);

   dglDrawRect( cameraRect, mCameraOutlineColor );
   dglDrawRectFill( cameraRect, mCameraFillColor );

   drawSizingNuts(sceneWindow, RectF(upperLeft, mWorldLimitSize));
}


#endif // TORQUE_TOOLS
