#include "pch.h"
#include "Utility.h"

#include <glm/gtx/string_cast.hpp>

std::string ReadFile(const std::string& _file)
{
	std::fstream stream(_file);
	IRAD_CORE_ASSERT(stream, "Invalid file : {0}", _file);
	return std::string ((std::istreambuf_iterator<char>(stream)),
		(std::istreambuf_iterator<char>()));
}

std::ostream& operator<<(std::ostream& _os, const glm::vec2& _vec)
{
	return _os << glm::to_string(_vec);
}

std::ostream& operator<<(std::ostream& _os, const glm::vec3& _vec)
{
	return _os << glm::to_string(_vec);
}

std::ostream& operator<<(std::ostream& _os, const glm::vec4& _vec)
{
	return _os << glm::to_string(_vec);
}

