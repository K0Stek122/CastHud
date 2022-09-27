#include "include/Overlay/Overlay.h"

#include "include/ImGui/imgui.h"
#include "include/ImGui/imgui_impl_glfw.h"
#include "include/ImGui/imgui_impl_opengl3.h"
//#include "include/ImGui/imgui_impl_opengl3_loader.h"

int main()
{
	Kostek::CastHud* overlay = new Kostek::CastHud();

	int xOffset = 0;
	int yOffset = 0;

	if (overlay->Create())
	{
		while (overlay->Run())
		{
			overlay->Handle();
		}
	}
	return 0;
}
