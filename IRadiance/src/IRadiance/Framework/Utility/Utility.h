#pragma once

//Read file into string
std::string ReadFile(const std::string& _file);

std::ostream& operator<<(std::ostream& _os, const glm::vec2& _vec);
std::ostream& operator<<(std::ostream& _os, const glm::vec3& _vec);
std::ostream& operator<<(std::ostream& _os, const glm::vec4& _vec);




