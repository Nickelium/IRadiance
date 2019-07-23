#pragma once

#ifdef IRAD_PLATFORM_WINDOWS

//#include <vld.h>

int main(int argc, char** argv)
{
	IRAD_CORE_INFO("Booting Engine");
	IRadiance::Application* app = CreateApplication();
	app->Run();
	delete app;
	IRAD_CORE_INFO("Closing Engine");
	return 0;
}
#endif