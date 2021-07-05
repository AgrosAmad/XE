#include <iostream>
#include "localWindow.h"

using namespace std;

int main()
{
	string windowTitle = "Nuevo tutorial";
	int majorVersion = 4;
	int minorVersion = 4;
	LocalWindow window;
	if (!window.createOpenGLWindow(windowTitle, majorVersion, minorVersion, 1920, 1080))
	{
		printf("Failed to create window with OpenGL context %d.%d! Shutting down...\n", majorVersion, minorVersion);
		return 1;
	}

	window.runApp();

	return 0;
}