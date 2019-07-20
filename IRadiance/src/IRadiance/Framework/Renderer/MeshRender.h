#pragma once

namespace IRadiance
{
	class VertexArray;
	class Mesh;
	class Shader;

	class MeshRender
	{
	public:
		MeshRender(Mesh* _mesh, Shader* _shader);
		~MeshRender();

		void Bind();
		void UnBind();

		inline VertexArray* GetVertexArray() const { return m_VertexArray; }
		inline Mesh* GetMesh() const { return m_Mesh; }
		inline Shader* GetShader() const { return m_Shader; }

	private:
		void BuildVertexArray();

		VertexArray* m_VertexArray;

		Mesh* m_Mesh;
		Shader* m_Shader;
	};
}
