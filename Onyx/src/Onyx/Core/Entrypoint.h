#ifndef _ONYX_ENTRYPOINT_H_
#define _ONYX_ENTRYPOINT_H_

#include "onyxpch.h"
#include "Core.h"
#include "Application.h"

#include <Windows.h>


extern Onyx::Application* CreateApplication();

int main(int argc, char** argv) {

	printf("--------------------------------------------------- Onyx Game Engine ---------------------------------------------------\n");

	Onyx::Application* onyxApplication = CreateApplication();

	onyxApplication->Run();
	delete onyxApplication;

	return 0;
}


#endif // !_ONYX_ENTRYPOINT_H_