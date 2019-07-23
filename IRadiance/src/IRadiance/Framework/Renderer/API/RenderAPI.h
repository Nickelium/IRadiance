#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
/**
 * Represent abstraction of OpenGL and D3D11
 */

/**
 * RenderAPI is a virtual (interface) to utilize runtime polymorphism between the different implementations
   But in the end these represent wrappers around raw implementation calls, which are actually static function calls.
   Therefore RenderCommand is called statically.
 */
namespace IRadiance
{
	class RenderAPI
	{
	public:
		enum class API
		{
			OPENGL = 0,
			D3D11,
			NONE
		};

		virtual void SetClearColor(const glm::vec4& _color) = 0;
		virtual void Clear() = 0;
		virtual void EnableDepth(bool _enable) = 0;
		virtual void EnableBlend(bool _enable) = 0;

		virtual void DrawIndexed(VertexArray* _vertexArray) = 0;
	
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}
