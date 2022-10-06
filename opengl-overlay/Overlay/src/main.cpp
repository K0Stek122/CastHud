#include "include/CastHud/CastHud.h"

#include "include/ImGui/imgui.h"
#include "include/ImGui/imgui_impl_glfw.h"
#include "include/ImGui/imgui_impl_opengl3.h"
//#include "include/ImGui/imgui_impl_opengl3_loader.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	Kostek::CastHud* p_castHud = new Kostek::CastHud();

	if (p_castHud->Create())
	{
		while (p_castHud->Run())
		{
			p_castHud->Handle();
		}
	}
	return 0;
}
