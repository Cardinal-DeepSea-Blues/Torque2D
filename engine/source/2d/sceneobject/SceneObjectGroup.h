//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _SCENE_OBJECT_GROUP_H_
#define _SCENE_OBJECT_GROUP_H_

#include "2d/sceneobject/SceneObjectSet.h"

#ifndef _FIND_ITERATOR_H_
#include "collection/findIterator.h"
#endif

#ifndef _SIMDICTIONARY_H_
#include "sim/simDictionary.h"
#endif

#ifndef _SIM_OBJECT_H_
#include "sim/simObject.h"
#endif

#ifndef _TAML_CHILDREN_H_
#include "persistence/taml/tamlChildren.h"
#endif

//-----------------------------------------------------------------------------

class SceneObject;

//-----------------------------------------------------------------------------

class SceneObjectGroup : public SceneObjectSet
{
   typedef SceneObjectSet Parent;

public:
	SceneObjectGroup()
    {
        VECTOR_SET_ASSOCIATION(mObjectList);
    }

    ~SceneObjectGroup()
    {
    }
	virtual void addObject(SceneObject*) override;
    
};

#endif // _SCENE_OBJECT_SET_H_
