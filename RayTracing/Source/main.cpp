#include "Source/Basis/Scene.h"
#include <time.h>

using namespace Vectormath::Aos;

int main()
{
	int nx = 2048;
	int ny = 2048;
	int sample = 1000;
	srand((unsigned int)time(NULL));
	std::unique_ptr<Scene> scene(std::make_unique<Scene>(nx, ny, sample));
	scene->Render();

	return 0;
}