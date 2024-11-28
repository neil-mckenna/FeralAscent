#include "framework/Object.h"
#include "framework/Core.h"

namespace fa
{
    Object::Object() : m_isPendingDestroy{ false }
    {
        // Initialization can be done here if needed
    }

    void Object::Destroy()
    {
        m_isPendingDestroy = true;
        LOG("Object marked for destruction");
    }

    Object::~Object()
    {
        LOG("Object destroyed");
    }
}
