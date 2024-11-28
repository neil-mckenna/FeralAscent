#pragma once
#include "framework/Core.h"
#include <string>

namespace fa
{
    class Object
    {
    public:
        Object();  // Constructor
        virtual ~Object();  // Virtual destructor to allow proper cleanup in derived classes

        virtual void Destroy();  // Marks the object for destruction
        bool IsPendingDestroy() const { return m_isPendingDestroy; }  // Getter for destruction flag

    protected:
        bool m_isPendingDestroy;  // Flag to track if the object is pending destruction
    };
}
