#pragma once

namespace IRadiance
{
	class Mesh
	{
	public:
		Mesh();
		void SetPositions(std::vector<glm::vec3> _positions);
		void SetTexCoords(std::vector<glm::vec2> _texCoords);
		void SetNormals(std::vector<glm::vec3> _normals);
		void SetIndices(std::vector<uint32_t> _indices);

		inline const std::vector<glm::vec3>& GetPositions() const { return m_Positions; }
		inline const std::vector<glm::vec2>& GetTexCoords() const { return m_TexCoords; }
		inline const std::vector<glm::vec3>& GetNormals() const { return m_Normals; }
		inline const std::vector<uint32_t>& GetIndices() const { return m_Indices; }

		inline int GetNbVertices() const { return static_cast<int>(m_Positions.size()); }
		inline int GetNbIndices() const { return static_cast<int>(m_Indices.size()); }

	private:
		std::vector<glm::vec3> m_Positions;
		std::vector<glm::vec3> m_Normals;
		std::vector<glm::vec2> m_TexCoords;
		std::vector<uint32_t> m_Indices;

	};
}
