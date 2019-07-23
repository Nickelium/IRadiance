#include "pch.h"
#include "Locator.h"

namespace IRadiance
{
	Locator::ServiceMap Locator::s_Services;

	void Locator::Destroy()
	{
		for (auto pair : s_Services)
			delete pair.second;
	}

	void Locator::Set(Service* _service)
	{
		IRADASSERT(s_Services.find(_service->GetType()) == s_Services.end(), "Service already exist");
		s_Services[_service->GetType()] = _service;
	}
}

