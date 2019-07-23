#pragma once

#include "IRadiance/Framework/Core/Layer.h"

namespace IRadiance
{
	class MeshRender;
	class Texture2D;

	class BaseLayer : public Layer
	{
		MeshRender* m_QuadRender;
	protected: 
		Texture2D* m_Texture;

	public:
		BaseLayer(Application* _application);
		virtual ~BaseLayer();

		virtual void Render() override;
	};
}
