#pragma once
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <map>
#include <math.h>
#include <gl/GL.h>

#include "../glfw/include/glfw3.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"

#include "../Profile/Profile.h"
//#include "../CofReader/CofReader.h"

namespace Kostek
{
	class CastHud
	{
	private:
		Profile m_Profile;
		bool menuEnabled = false;

		//OpenGL size variables
		int m_width = NULL, m_height = NULL, m_x = NULL, m_y = NULL;

		GLFWwindow* glfw_window = NULL;

		void MaximizeWindow();

		void DrawCrosshairs();

		void KeybindHandler();

		void DrawMenu();

		void Exit();
		bool SaveConfig();
		Profile LoadConfig();

	public:

		CastHud();

		bool Create();

		bool Run();

		void Handle();
	};
}
