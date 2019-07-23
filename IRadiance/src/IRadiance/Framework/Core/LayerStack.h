#pragma once

#include <vector>

//Can't forward declare because is template parameter
#include "Layer.h"

namespace IRadiance
{
	class LayerStack
	{
	public:
		using Layers = std::vector<Layer*>;
		using LayerIt = Layers::iterator;
		using LayerCIt = Layers::const_iterator;
		
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* _layer);
		void PopLayer(Layer* _layer);
		void PushOverlay(Layer* _overlay);
		void PopOverlay(Layer* _overlay);

		inline LayerIt begin() { return m_Layers.begin(); }
		inline LayerIt end() { return m_Layers.end(); }
		inline LayerCIt begin() const { return m_Layers.cbegin(); }
		inline LayerCIt end() const { return m_Layers.cend(); }

	private:
		std::vector<Layer*> m_Layers;
		size_t m_LayerInsertIndex = 0;
	};
}
