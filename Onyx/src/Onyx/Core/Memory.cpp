#include "onyxpch.h"
#include "Memory.h"

namespace Onyx {

}

void* operator new(size_t size)
{
	//printf("Allocating %d bytes\n", size);
	return malloc(size);
}
