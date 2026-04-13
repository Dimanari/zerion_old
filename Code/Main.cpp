#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include "game.h"
HINSTANCE hinstance;
#define IDT_TIMER1 110
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS);
HFONT hfnt,bigfont;
Game game;
HWND hWND;
extern void initGame(Game);
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	WNDCLASSEX wcex;
	static TCHAR szWindowClass[] = _T("zerion");
	static TCHAR szTitle[] = _T("Zerion Test Version 0.1");
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
#ifdef _DEBUG
	AllocConsole();

	FILE* pCout;
    freopen_s(&pCout, "conout$", "w", stdout); //returns 0
	std::cout<<"-DeBUG Mode-"<<std::endl;
	std::cout<<"Works with std::cout"<<std::endl;
	printf("and also with Printf();\n");
#endif
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}
	hfnt = CreateFont(18,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
	bigfont = CreateFont(40,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
	/* The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	*********************************************/
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Zerion"),
			NULL);

		return 1;
	}
	hWND = hWnd;
	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);
	hinstance = hInstance;
	game.Init();
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#ifdef _DEBUG
	fclose(pCout);
#endif
	return (int) msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd,             // handle to main window 
				 IDT_TIMER1,            // timer identifier 
				 40,                 // 0.1-second interval 
				 (TIMERPROC) NULL);     // no timer callback 
		break;
	case WM_TIMER:
		 switch (wParam) 
		 { 
		 case IDT_TIMER1: 
			 KillTimer(hWnd, IDT_TIMER1);
			 game.Update();
			 InvalidateRect(hWnd, NULL, TRUE);
			 // process the 10-second timer ]
			 SetTimer(hWnd,             // handle to main window 
				 IDT_TIMER1,            // timer identifier 
				 40,                 // 0.1-second interval 
				 (TIMERPROC) NULL);     // no timer callback 
			 return NULL; 
		 }
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		Paint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_ERASEBKGND:
        return (LRESULT)1; // Say we handled it.
	case WM_KEYDOWN:
		game.move(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	case WM_QUIT:
		KillTimer(hWnd, IDT_TIMER1);
		game.~Game();
		break;
	default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
	}
	return NULL;
}

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
	RECT rc;
    HDC hdcMem;
    HBITMAP hbmMem, hbmOld;
    HBRUSH hbrBkGnd;
    HFONT hfntOld;
	hfntOld =CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
    //
    // Get the size of the client rectangle.
    //

    GetClientRect(hWnd, &rc);

    //
    // Create a compatible DC.
    //

    hdcMem = CreateCompatibleDC(lpPS->hdc);

    //
    // Create a bitmap big enough for our client rectangle.
    //

    hbmMem = CreateCompatibleBitmap(lpPS->hdc,
                                    rc.right-rc.left,
                                    rc.bottom-rc.top);

    //
    // Select the bitmap into the off-screen DC.
    //

    hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

    //
    // Erase the background.
    //

    hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    FillRect(hdcMem, &rc, hbrBkGnd);
    DeleteObject(hbrBkGnd);

    //
    // Select the font.
    //

    if (hfnt) {
		hfntOld = (HFONT)SelectObject(hdcMem, hfnt);
    }

    //
    // Render the image into the offscreen DC.
    /*
	LPCSTR szCaption = "Hello World";
	//Draw BG*/
    SetBkMode(hdcMem, TRANSPARENT);
	//Draw Screen Objects
	game.Paint(hdcMem);
	//Draw Text

	if (bigfont) {
		hfntOld = (HFONT)SelectObject(hdcMem, bigfont);
    }

	/*
    SetTextColor(hdcMem, GetSysColor(COLOR_WINDOWTEXT));
    DrawText(hdcMem,
             szCaption,
             -1,
             &rc,
             DT_CENTER);
	*/
    if (hfntOld) {
        SelectObject(hdcMem, hfntOld);
    }

    //
    // Blt the changes to the screen DC.
    //

    BitBlt(lpPS->hdc,
           rc.left, rc.top,
           rc.right-rc.left, rc.bottom-rc.top,
           hdcMem,
           0, 0,
           SRCCOPY);

    //
    // Done with off-screen bitmap and DC.
    //

    SelectObject(hdcMem, hbmOld);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);

}