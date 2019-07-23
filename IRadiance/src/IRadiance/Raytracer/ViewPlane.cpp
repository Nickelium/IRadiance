#include "pch.h"
#include "ViewPlane.h"

namespace IRadiance
{
	ViewPlane::ViewPlane(int _hRes, int _vRes)
		: m_HorRes(_hRes), m_VertRes(_vRes), 
		m_PixelSize(1.0f), 
		m_Gamma(2.2f),
		m_InvGamma(1.0f / 2.2f)
	{
	}
}