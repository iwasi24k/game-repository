//==============================================================================
// File        : Behaviour.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-08-29
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "Component.h"

namespace Framework {

    class Behaviour : public Component {
    private:
		bool m_Enabled = true;

    public:
        virtual bool IsEnabled() const { return m_Enabled; }
        virtual void SetEnabled(bool enabled) { m_Enabled = enabled; }
    };
}

#endif // BEHAVIOUR_H