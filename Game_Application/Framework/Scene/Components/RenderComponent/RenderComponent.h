//==============================================================================
// File        : RenderComponent.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Framework/Scene/Component.h"
#include "MathTransform.h"
#include <memory>

namespace Framework {

    class RenderComponent : public Component {
    public:
		virtual void SetShaderName(const std::wstring& name) = 0;
		virtual void LoadPixelShader(const std::wstring& psPath) = 0;
		virtual void LoadVertexShader(const std::wstring& vsPath) = 0; 
		virtual void LoadShader(const std::wstring& name, const std::wstring& vsPath, const std::wstring& psPath) = 0;

        virtual void SetTransform(const math::vector3f& position, const math::vector3f& scale, const math::vector3f& rotation) = 0;

		virtual void Draw() {}
		virtual void Draw(const math::matrix& view, const math::matrix& proj) {}
    };
}

#endif // RENDER_COMPONENT_H
