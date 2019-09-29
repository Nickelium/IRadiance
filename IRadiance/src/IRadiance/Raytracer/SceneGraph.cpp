#include "pch.h"
#include "SceneGraph.h"

namespace IRadiance
{
	SceneGraph::SceneGraph() : m_AmbientLight(nullptr) {}
	SceneGraph::~SceneGraph()
	{
		for (const Object* object : m_Objects)
			delete object;
		for (const Light* light : m_Lights)
			delete light;
		//delete m_AmbientLight;
	}

	void SceneGraph::AddObject(const Object* _object)
	{
		m_Objects.push_back(_object);
	}

	void SceneGraph::AddLight(const Light* _light)
	{
		m_Lights.push_back(_light);
	}

	void SceneGraph::SetAmbientLight(const Light* _ambientLight)
	{
		if (m_AmbientLight) delete m_AmbientLight;
		m_AmbientLight = _ambientLight;
	}

	const std::vector<const Object*>& SceneGraph::GetObjects() const
	{
		return m_Objects;
	}

	const std::vector<const Light*>& SceneGraph::GetLights() const
	{
		return m_Lights;
	}

	const Light* SceneGraph::GetAmbientLight() const
	{
		return m_AmbientLight;
	}

}