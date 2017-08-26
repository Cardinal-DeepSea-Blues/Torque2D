#ifndef _T2D_DATABLOCKDROPDOWN_H_
#define _T2D_DATABLOCKDROPDOWN_H_
//-----------------------------------------------------------------------------
// Torque Game Engine 
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

#include "gui/guiPopUpCtrlEx.h"
#include "sim/simDatablock.h"
#include "T2D/t2dImageMapDatablock.h"
#include "2d/sceneobject/SceneObject.h"
#include "T2D/t2dAnimatedSprite.h"
#include "T2D/t2dStaticSprite.h"


class T2DDatablockDropDownCtrl : public GuiPopUpMenuCtrlEx
{
   typedef GuiPopUpMenuCtrlEx Parent;
   SimSet*           mDatablocks;
   StringTableEntry  mFilter;

   void populateList();
public:
   T2DDatablockDropDownCtrl();
   DECLARE_CONOBJECT( T2DDatablockDropDownCtrl );

   // Set our datablock type filter 
   // For example "t2dImageMapDatablock" would show all imagemaps, etc.
   void setFilter( StringTableEntry className );

   // Let's find out when our persistent fields are modified
   void onStaticModified( const char* slotName );

   static void initPersistFields();

   bool onAdd();
   bool onWake();
};

#endif