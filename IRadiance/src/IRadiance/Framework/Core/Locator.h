#pragma once

namespace IRadiance
{
	using ServiceType = std::string;
	class Service
	{
	public:
		virtual ServiceType GetType() const = 0;
	};

	#define SERVICE_CLASS(type)\
		inline static ServiceType GetStaticType() { return #type; }\
		virtual ServiceType GetType() const override { return GetStaticType(); }

	class Locator 
	{
	public:
		static void Destroy();

		static void Set(Service* _service);

		template <typename TypeService>
		static TypeService* Get()
		{
			ServiceType type = TypeService::GetStaticType();
			if (s_Services.find(type) == s_Services.end())
				return nullptr;
			return dynamic_cast<TypeService*>(s_Services[type]);
		}
	private:
		using ServiceMap = std::unordered_map<ServiceType, Service*>;
		static ServiceMap s_Services;
	};
}
