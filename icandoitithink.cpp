#include <Windows.h>
// window message processor prototype
LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int iCmdShow) {
	// class name
	static TCHAR appName[] = L"Cookiezi";
	//window handle
	HWND hwnd;
	//message to work with
	MSG msg;
	//creates winow class
	WNDCLASS wndclass;

	//sets some style settings
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//function pointer to the window procedure
	wndclass.lpfnWndProc = WndProc;
	//next 2 are for extra internal storage in the class
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	//The hInstance is what Windows itself talks to
	wndclass.hInstance = hInstance;
	//loads an icon with a deprecated function
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//loads the cursor with a deprecated function
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//paints the background
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	// sets the name for the menu (there is none)
	wndclass.lpszMenuName = nullptr;
	// sets the name for the window class
	wndclass.lpszClassName = appName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			appName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindowExW(
		//sets some weird window style thing
		WS_EX_LEFT,
		// sets the class name to work with
		appName,
		// sets the name of the window
		L"Cookiezi",
		//creates a normal average overlapped window
		WS_OVERLAPPEDWINDOW,
		//sets default location and size
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// parent window if button
		nullptr,
		// sets the menu handle if there is one
		nullptr,
		//program instance handle
		hInstance,
		nullptr
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) { // gets messages from windows
		TranslateMessage(&msg); // keyboard translation
		DispatchMessage(&msg); // sends the message back to windows and gives it to the window procedure
	}
	return msg.wParam;
}

LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (uMsg) {
	case WM_CREATE: // called on startup
		PlaySound(TEXT("movie_1.wav"), nullptr , SND_FILENAME | SND_ASYNC);
		return 0;

	case WM_PAINT: // called whenever the client area is invalid
		hdc = BeginPaint(hwnd, &ps); // uses the paintstruct to begin painting
		GetClientRect(hwnd, &rect); // sets the rect to the four corners of the client area
		DrawText(hdc, L"Hello, Windows 98", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps); // ends the draw commands
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
