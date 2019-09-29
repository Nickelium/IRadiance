#pragma once

namespace IRadiance
{
	class Renderer;
	class CollisionHandler
	{
	public:
		CollisionHandler(Renderer* _renderer);
		HitRecord HitObjects(const Ray& _ray);
	private:
		Renderer* m_Renderer;
	};
}
