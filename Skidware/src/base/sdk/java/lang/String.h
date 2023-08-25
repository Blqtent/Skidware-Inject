#pragma once

#include "../../Object.h"


class String : public Object
{
public:
	using Object::Object;
	String(std::string text);
	std::string ToString();
};

