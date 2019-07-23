#include "pch.h"
#include "LayerStack.h"

namespace IRadiance
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* _layer)
	{
		m_Layers.emplace(m_Layers.cbegin() + m_LayerInsertIndex, _layer);
		++m_LayerInsertIndex;
		_layer->OnAttach();
		//m_LayerInsert = m_Layers.insert(m_LayerInsert, _layer);
	}

	void LayerStack::PopLayer(Layer* _layer)
	{
		auto res = std::find(m_Layers.cbegin(), m_Layers.cbegin() + m_LayerInsertIndex, _layer);
		if (res == m_Layers.cend())
			return;
		m_Layers.erase(res);
		--m_LayerInsertIndex;

		_layer->OnDetach();
	}

	void LayerStack::PushOverlay(Layer* _overlay)
	{
		//m_Layers.push_back(_overlay);
		m_Layers.emplace_back(_overlay);
		_overlay->OnAttach();
	}

	void LayerStack::PopOverlay(Layer* _overlay)
	{
		auto res = std::find(m_Layers.cbegin() + m_LayerInsertIndex, m_Layers.cend(), _overlay);
		if (res == m_Layers.cend())
			return;
		m_Layers.erase(res);

		_overlay->OnDetach();
	}
}