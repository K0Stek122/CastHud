#include "Overlay.h"

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %s\n", description);
}

Kostek::CastHud::CastHud()
{
}

bool Kostek::CastHud::Create()
{
	m_Profile = LoadConfig();
	MaximizeWindow();

	if (!glfwInit()) { return false; };

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

	this->glfw_window = glfwCreateWindow(m_width,
		m_height,
		"Kostek Overlay",
		NULL,
		NULL);

	if (!glfw_window) { return false; };

	glfwMakeContextCurrent(glfw_window);
	glfwSwapInterval(1);

	//IMGUI
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
	ImGui_ImplOpenGL3_Init();

	glfwDefaultWindowHints();

	glfwShowWindow(glfw_window);

	return true;
}

void Kostek::CastHud::KeybindHandler()
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{

		menuEnabled = !menuEnabled;
		if (menuEnabled)
			glfwSetWindowAttrib(glfw_window, GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE);
		else
			glfwSetWindowAttrib(glfw_window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
	}
}

void Kostek::CastHud::DrawMenu()
{

	ImGui::SetNextWindowSize(ImVec2(417, 269));
	ImGui::Begin("CastHud", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	ImGui::RadioButton("Style 1", &m_Profile.style, 0); ImGui::SameLine();
	ImGui::RadioButton("Style 2", &m_Profile.style, 1); ImGui::SameLine();
	ImGui::RadioButton("Style 3", &m_Profile.style, 2); ImGui::SameLine();
	ImGui::RadioButton("Style 4", &m_Profile.style, 3); ImGui::SameLine();
	ImGui::RadioButton("Style 5", &m_Profile.style, 4);

	ImGui::PushItemWidth(150.f);
	ImGui::ColorPicker3("",
		(float*)&m_Profile.color,
		ImGuiColorEditFlags_NoSidePreview |
		ImGuiColorEditFlags_NoSmallPreview);
	
	ImGui::SameLine();
	ImGui::SliderFloat("Scale", &m_Profile.scale, 1.f, 15.f, "%.1f");
	ImGui::SetCursorPos(ImVec2(166.5f, 75.f));
	ImGui::SliderFloat("Thickness", &m_Profile.thickness, 1.f, 15.f, "%.1f");
	ImGui::SetCursorPos(ImVec2(166.5f, 100.f));
	ImGui::SliderFloat("Gap", &m_Profile.gap, 0.f, 30.f, "%.1f");
	ImGui::SetCursorPos(ImVec2(166.5, 125.f));
	ImGui::InputInt("X Offset", &m_Profile.xOffset);
	ImGui::SetCursorPos(ImVec2(166.5, 150.f));
	ImGui::InputInt("Y Offset", &m_Profile.yOffset);

	ImGui::SetCursorPos(ImVec2(166.5f, 175.f));
	if (ImGui::Button("Exit"))
	{
		SaveConfig();
		Exit();
	}


	ImGui::End();
}

bool Kostek::CastHud::Run()
{
	KeybindHandler(); //All the keystates that need to hapen

	if (glfwWindowShouldClose(glfw_window)) { return false; };

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (menuEnabled)
		DrawMenu();

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_width, m_height, 0, 0, 1);
	glViewport(0, 0, m_width, m_height);

	DrawCrosshairs();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	return true;
}

void Kostek::CastHud::MaximizeWindow()
{
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	if (m_x != rect.left ||
		m_y != rect.top ||
		m_width != rect.right - rect.left ||
		m_height != rect.bottom - rect.top)
	{
		m_x = rect.left;
		m_y = rect.top;
		m_width = rect.right - rect.left;
		m_height = rect.bottom - rect.top;
		m_width -= 1;
		m_height -= 1;

		glfwSetWindowPos(glfw_window, m_x, m_y);
		glfwSetWindowSize(glfw_window, m_width, m_height);
	}
}

void Kostek::CastHud::Handle()
{
	glfwSwapBuffers(this->glfw_window);
	glfwPollEvents();
}

void Kostek::CastHud::DrawCrosshairs()
{
	auto draw = ImGui::GetForegroundDrawList();

	//Recoil Dot
	if (m_Profile.style == 0)
	{
		draw->AddCircle(
			ImVec2(m_width / 2 + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			m_Profile.scale,
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			0, m_Profile.thickness);
	}

	//Dot
	else if (m_Profile.style == 1)
	{
		draw->AddCircleFilled(ImVec2(m_width / 2 + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			m_Profile.scale,
			ImColor(m_Profile.color[0], m_Profile.color[1], m_Profile.color[2]));
	}

	//Chevron
	else if (m_Profile.style == 2)
	{
		draw->AddLine(ImVec2(m_width / 2 + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImVec2(m_width / 2 + (10 - m_Profile.scale) + m_Profile.xOffset,
				m_height / 2 + (10 - m_Profile.scale) + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);

		draw->AddLine(ImVec2(m_width / 2 + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImVec2(m_width / 2 - (10 - m_Profile.scale) + m_Profile.xOffset,
				m_height / 2 + (10 - m_Profile.scale) + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);
	}

	//2 Arrows
	else if (m_Profile.style == 3)
	{
		draw->AddLine(ImVec2(m_width / 2 + m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImVec2(m_width / 2 + m_Profile.scale + m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.scale + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);
		draw->AddLine(ImVec2(m_width / 2 + m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImVec2(m_width / 2 + m_Profile.scale + m_Profile.gap + m_Profile.xOffset, m_height / 2 - m_Profile.scale + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);

		draw->AddLine(ImVec2(m_width / 2 - m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImVec2(m_width / 2 - m_Profile.scale - m_Profile.gap + m_Profile.xOffset, m_height / 2 - m_Profile.scale + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);
		draw->AddLine(ImVec2(m_width / 2 - m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImVec2(m_width / 2 - m_Profile.scale - m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.scale + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);
	}

	//Crosshair
	else if (m_Profile.style == 4)
	{
		draw->AddLine(ImVec2(m_width / 2 + m_Profile.xOffset, m_height / 2 - m_Profile.gap + m_Profile.yOffset),
			ImVec2(m_width / 2 + m_Profile.xOffset, m_height / 2 - m_Profile.scale - m_Profile.gap + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);

		draw->AddLine(ImVec2(m_width / 2 + m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImVec2(m_width / 2 + m_Profile.scale + m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);

		draw->AddLine(ImVec2(m_width / 2 + m_Profile.xOffset, m_height / 2 + m_Profile.gap + m_Profile.yOffset),
			ImVec2(m_width / 2 + m_Profile.xOffset, m_height / 2 + m_Profile.scale + m_Profile.gap + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);

		draw->AddLine(ImVec2(m_width / 2 - m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImVec2(m_width / 2 - m_Profile.scale - m_Profile.gap + m_Profile.xOffset, m_height / 2 + m_Profile.yOffset),
			ImColor(m_Profile.color[0],
				m_Profile.color[1],
				m_Profile.color[2]),
			m_Profile.thickness);
	}
}

bool Kostek::CastHud::SaveConfig()
{	
	std::ofstream file("profile.cof");

	if (!file.is_open())
		return false;

	file << m_Profile.color[0] << ";"
		<< m_Profile.color[1] << ";"
		<< m_Profile.color[2] << ";"
		<< m_Profile.gap << ";"
		<< m_Profile.scale << ";"
		<< m_Profile.style << ";"
		<< m_Profile.thickness << ";"
		<< m_Profile.xOffset << ";"
		<< m_Profile.yOffset << ";";

	file.close();
}

Profile Kostek::CastHud::LoadConfig()
{
	Profile ret;
	std::ifstream file("profile.cof");
	if (!file.is_open())
		return ret;

	//This iterator magically reads all contents of the file into string "s"
	std::string s((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	std::cout << s << std::endl;

	std::vector<std::string> split;
	size_t pos = 0;
	std::string token;
	std::string delimiter = ";";
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		split.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	std::cout << s << std::endl;

	for (short int i = 0; i < split.size(); i++)
	{
		std::cout << split[i] << std::endl;
	}

	ret.color[0] = std::stof(split[0]);
	ret.color[1] = std::stof(split[1]);
	ret.color[2] = std::stof(split[2]);
	ret.gap = std::stoi(split[3]);
	ret.scale = std::stof(split[4]);
	ret.style = std::stoi(split[5]);
	ret.thickness = std::stof(split[6]);
	ret.xOffset = std::stoi(split[7]);
	ret.yOffset = std::stoi(split[8]);

	file.close();
	return ret;
}

void Kostek::CastHud::Exit()
{
	SaveConfig();
	exit(0);
}
