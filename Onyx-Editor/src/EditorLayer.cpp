#include "EditorLayer.h"

#include "../.../../glfw3/GLFW/glfw3.h"

#include <fstream>

using namespace Onyx;
WNDCLASSEX wc;
HWND hwnd;
MSG Msg;

RenderedPixelData* renderedFrame;
char* pbuffer = nullptr;

EditorSandbox::EditorSandbox()
	: Layer("Sandbox2DSecond")
{

}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
	{
		if (renderedFrame && renderedFrame->Data) {
			HDC dc = GetDC(hwnd);
			HBITMAP f;
			BITMAPINFO info;
			ZeroMemory(&info, sizeof(BITMAPINFO));
			info.bmiHeader.biBitCount = 32;
			info.bmiHeader.biWidth = 1280;
			info.bmiHeader.biHeight = 720;
			info.bmiHeader.biPlanes = 1;
			info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			info.bmiHeader.biSizeImage = renderedFrame->Size;
			info.bmiHeader.biCompression = BI_RGB;

			StretchDIBits(dc, 0, 0, 1280, 720, 0, 0, 1280, 720, pbuffer, &info, DIB_RGB_COLORS, SRCCOPY);
			ReleaseDC(hwnd, dc);
		}
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void EditorSandbox::OnAttach()
{


	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"myWindowClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"myWindowClass",
		L"Onyx Native Editor",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
		NULL, NULL, GetModuleHandle(NULL), NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}

	ShowWindow(hwnd, 10);


	RenderCommand::SetClearColour(glm::vec4(.2f, .2f, .2f, 1.0f));
	RenderCommand::Clear();

	Renderer3D::Init();

	m_Texture1 = Texture2D::Create("res/textures/mario2.png");
	m_Cube = Mesh::Create(PrimitiveMeshType::Cube);
	m_Cone = Mesh::Create(PrimitiveMeshType::Cone);
	m_FbxMeshTest = Mesh::Create("res/models/CubeTri.fbx");


	
	m_Cube->SetTintColor(glm::vec4(1.0, 0.2, 0.5, 1.0));
	m_Cone->SetTintColor(glm::vec4(0.2, 1.0, 0.5, 1.0));

	m_Scene = new Scene();
}

void EditorSandbox::OnDetach()
{
	delete m_Texture1;
}

void EditorSandbox::OnUpdate(Timestep timestep)
{
	
	//SCENE & RENDER
	m_Scene->OnUpdate(timestep);

	renderedFrame = &RenderCommand::GetRenderedFrameBuffer();
	pbuffer = renderedFrame->Data;

	UpdateWindow(hwnd);

	TranslateMessage(&Msg);
	DispatchMessage(&Msg);

	delete[] renderedFrame->Data;

}
