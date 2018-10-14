#include <windows.h>

enum { id_button1 = 1, id_button2 };

void OnCreate(HWND hw) {
	HWND hwnd1, hwnd2;
	hwnd1 = CreateWindow("BUTTON", "one", WS_CHILD | WS_VISIBLE | WS_BORDER,
		450, 200, 100, 30,
		hw, (HMENU)1, NULL, NULL);
	hwnd2 = CreateWindow("BUTTON", "two", WS_CHILD | WS_VISIBLE | WS_BORDER,
		450, 240, 100, 30,
		hw, (HMENU)2, NULL, NULL);

	ShowWindow(hwnd1, SW_SHOW);
	UpdateWindow(hw);
	ShowWindow(hwnd2, SW_SHOW);
	UpdateWindow(hw);
}

void OnCommand(HWND hw, int id) {
	char boxName1[] = "one";
	char boxName2[] = "two";
	LPCSTR box;
	id == id_button1 ? box = boxName1 : box = boxName2;
	MessageBox(hw, box, LPCSTR("NWP"), MB_ICONWARNING | MB_OK);
}

void OnDestroy() {
	PostQuitMessage(0);
}

LRESULT CALLBACK WndProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_CREATE:
			OnCreate(hw);
			return 0;
		case WM_COMMAND:
			OnCommand(hw, LOWORD(wp));
			return 0;
		case WM_DESTROY:
			OnDestroy();
			return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}


int RegisterMyClass(HINSTANCE hInstance, char* className)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof wc);

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0, 255, 255));  

	return RegisterClass(&wc);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	char clsName[] = "NWPClass";

	if(!RegisterMyClass(hInstance, clsName))
		return 0;

	HWND hwnd = CreateWindow(clsName, "NWP 1",  WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL); 

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	return msg.wParam;
}
