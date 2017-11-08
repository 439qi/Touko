#include"main.h"
 int Swidth;
const int Sheight=600;
RECT window;
bool Over=false;
bool showcursor = false;
HWND hwnd;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* trap the WM_CLOSE (clicking X) message, and actually tell the window to close */
		case WM_CLOSE: {
			DestroyWindow(hwnd);
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);Over=true;
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	
	lua_State*
		lua = lua_open();
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_math(lua);
	luaopen_table(lua);
	luaL_dofile(lua, "date_init.lua");
 Swidth = Lua_GetInt(lua, "Swidth");
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG Msg; 


	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, "small.ico");
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL,  NULL);

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Transistor",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		Swidth, /* width */
		Sheight, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	HIMC g_hIMC = NULL;//g_hIMC 用于恢复时使用  
	g_hIMC = ImmAssociateContext(hwnd, NULL);//handle 为要禁用的窗口句柄  
	D3D_Init(hwnd); ShowCursor(showcursor); 
	while(!Over)
	{
		GetWindowRect(hwnd, &window);
		ClipCursor(&window);
		if(PeekMessage(&Msg, NULL, 0, 0,PM_REMOVE)) 
		{ 
		TranslateMessage(&Msg); 
		DispatchMessage(&Msg); 
		}
		
		Dinput_Update();
		All_Run();
		Draw();
		
	}
	D3D_End();
	return Msg.wParam;
}
