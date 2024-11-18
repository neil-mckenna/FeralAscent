#include "framework/Object.h"
#include "framework/Core.h"

namespace fa
{
	Object::Object() : m_isPendingDestroy{false}
	{


	}

	void Object::Destroy()
	{
		m_isPendingDestroy = true;
	}


	Object::~Object()
	{
		LOG("Object destroyed");
	}

}


