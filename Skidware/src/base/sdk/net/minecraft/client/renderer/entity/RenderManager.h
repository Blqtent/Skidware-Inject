#pragma once

#include "../../../../../Object.h"
#include "../../../../../../util/math/geometry.h"

class CRenderManager :public Object
{
	//CRenderManager();

	//jclass getClass();
	//jobject getInstance();
public:
	using Object::Object;
	Vector3 RenderPos();
	Vector3 ViewerPos();
};

