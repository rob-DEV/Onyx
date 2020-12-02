
#include <Onyx/Onyx.h>
#include <Onyx/Runtime/RuntimeApplication.h>

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
) {

	//printf("--------------------------------------------------- RUNTIME ---------------------------------------------------\n");
	Onyx::RuntimeApplication* appliation = new Onyx::RuntimeApplication();
	appliation->Run();
	delete appliation;

	return 0;
}
