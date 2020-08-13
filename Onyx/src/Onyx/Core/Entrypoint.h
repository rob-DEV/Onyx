#ifndef _ONYX_ENTRYPOINT_H_
#define _ONYX_ENTRYPOINT_H_

#include "onyxpch.h"
#include "Core.h"
#include "Application.h"

#include <Windows.h>


extern Onyx::Application* CreateApplication();

int main(int argc, char** argv);

#endif // !_ONYX_ENTRYPOINT_H_