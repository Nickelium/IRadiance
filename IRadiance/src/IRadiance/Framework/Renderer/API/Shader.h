#pragma once

#include "pch.h"

namespace IRadiance
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		//TODO some magic virtual + template ? although trivially combining is not allowed in C++
		virtual void SetUniformFloat(const std::string& _name, float _val) = 0;
		virtual void SetUniformFloats(const std::string& _name, const std::vector<float>& _val) = 0;
		virtual void SetUniformInt(const std::string& _namee, int _value) = 0;
		virtual void SetUniformInts(const std::string& _name, const std::vector<int>& _val) = 0;
		virtual void SetUniformFloat2(const std::string& _name, const glm::vec2& _val) = 0;
		virtual void SetUniformFloat3(const std::string& _name, const glm::vec3& _val) = 0;
		virtual void SetUniformFloat4(const std::string& _name, const glm::vec4& _val) = 0;
		virtual void SetUniformMat(const std::string& _name, const glm::mat4& _val) = 0;
	};
}