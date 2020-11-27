
#include <Onyx/Onyx.h>
#include <Onyx/Runtime/RuntimeApplication.h>

int main(int argc, char** argv) {

	printf("--------------------------------------------------- RUNTIME ---------------------------------------------------\n");
	Onyx::RuntimeApplication* appliation = new Onyx::RuntimeApplication();
	appliation->Run();
	delete appliation;

	return 0;
}
