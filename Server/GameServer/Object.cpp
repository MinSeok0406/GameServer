#include "pch.h"
#include "Object.h"

Object::Object()
{
	objectInfo = new Protocol::ObjectInfo();
	posInfo = new Protocol::PosInfo(); // (¡Ú)

	objectInfo->set_allocated_pos_info(posInfo); // (¡Ú)
}

Object::~Object()
{
	delete objectInfo;
}
