# opengl-overlay
 An overlay created in C++ OpenGL

An overlay which is written in OpenGL/GLFW and C++.

WARNING: the glfw used is the `a465c1c32e0754d3de56e01c59a0fef33202f04c` branch, this is due to the fact that we need to set the hint `GLFW_MOUSE_PASSTHROUGH` to true.

# Example Usage
```C++
#include "include/Overlay/Overlay.h"

int main()
{
	LPCWSTR windowName = L"Untitled - Notepad";
	Kostek::Overlay* overlay = new Kostek::Overlay();

	if (overlay->Create(windowName))
	{
		while (overlay->Run())
		{
			overlay->DrawEmptyRect(100, 100, 25, 25, 1, 0, 0);
			overlay->DrawRect(500, 500, 25, 25, 1, 1, 0);
			overlay->DrawCircle(200, 100, 50.f, 0, 1, 0);
			overlay->DrawEmptyCircle(300, 300, 100.f, 0, 0, 1);
			overlay->DrawPoint(500, 150, 15.f, 1, 0, 0);

			overlay->Handle();
		}
	}
	return 0;
}
```

# How to include
You need to include src/include folder in your project, then in your file just include include/Overlay/Overlay.h
