#include "pch.h"
#include "Prefab.h"

#include "IRadiance/Framework/Renderer/Mesh.h"

namespace IRadiance
{
	Mesh* CreateCube()
	{
		Mesh* mesh = new Mesh;
		std::vector<glm::vec3> positions =
		{
			{ -0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, +0.5f, -0.5f },
			{ +0.5f, +0.5f, -0.5f },
			{ -0.5f, +0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },

			{ -0.5f, -0.5f, +0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ -0.5f, +0.5f, +0.5f },
			{ -0.5f, -0.5f, +0.5f },

			{ -0.5f, +0.5f, +0.5f },
			{ -0.5f, +0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f, +0.5f },
			{ -0.5f, +0.5f, +0.5f },

			{ +0.5f, +0.5f, +0.5f },
			{ +0.5f, +0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ +0.5f, +0.5f, +0.5f },

			{ -0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ -0.5f, -0.5f, +0.5f },
			{ -0.5f, -0.5f, -0.5f },

			{ -0.5f, +0.5f, -0.5f },
			{ +0.5f, +0.5f, -0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ -0.5f, +0.5f, +0.5f },
			{ -0.5f, +0.5f, -0.5f }
		};
		mesh->SetPositions(positions);	
		std::vector<uint32_t> indices =
		{
			0, 2, 1,
			3, 5, 4, 

			6, 7, 8,
			9, 10, 11,

			12, 13, 14,
			15, 16, 17,

			18, 20, 19,
			21, 23, 22,

			24, 25, 26,
			27, 28, 29,

			30, 32, 31,
			33, 35, 34
		};
		mesh->SetIndices(indices);

		return mesh;
	}

	Mesh* CreateTriangle()
	{
		Mesh* mesh = new Mesh;
		std::vector<glm::vec3> positions =
		{
			{-0.5f, -0.5f, 0.0f},
			{+0.5f, -0.5f, 0.0f},
			{+0.0f, +0.5f, 0.0f}
		};
		mesh->SetPositions(positions);
		std::vector<glm::vec3> normals = 
		{
			{0.0f, 0.0f, 1.0f}
		};
		mesh->SetNormals(normals);
		std::vector<unsigned int> indices =
		{
			0, 1, 2
		};
		mesh->SetIndices(indices);

		return mesh;
	}

	Mesh* CreateQuad()
	{
		Mesh* mesh = new Mesh;
		std::vector<glm::vec3> positions =
		{
			{-1.0f, -1.0f, 0.0f},
			{+1.0f, -1.0f, 0.0f},
			{+1.0f, +1.0f, 0.0f},
			{-1.0f, +1.0f, 0.0f}
		};
		mesh->SetPositions(positions);
		std::vector<glm::vec2> texCoords = 
		{
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f}
		};
		mesh->SetTexCoords(texCoords);

		std::vector<unsigned int> indices =
		{
			0, 1, 2,
			2, 3, 0
		};
		mesh->SetIndices(indices);

		return mesh;
	}
}