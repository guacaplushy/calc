#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void center(HWND hwnd) {
	    RECT rc = {0};
	    GetWindowRect(hwnd, &rc);
	    int win_w = rc.right - rc.left;
    	    int win_h = rc.bottom - rc.top;
	    int screen_w = GetSystemMetrics(SM_CXSCREEN);
    	    int screen_h = GetSystemMetrics(SM_CYSCREEN);
	    SetWindowPos(hwnd, HWND_TOP, (screen_w - win_w)/2, 
        	(screen_h - win_h)/2, 0, 0, SWP_NOSIZE);
}
void bringToFront(HWND hwnd) {
	SwitchToThisWindow(hwnd, FALSE);
	SetForegroundWindow(hwnd); 
	SetActiveWindow(hwnd); 
}

#define ID_MULTI 1
#define ID_DIVIS 2
#define ID_ADD 3
#define ID_SUB 4
#define ID_FIRSTNUM 5
#define ID_SECONDNUM 6
#define ID_GO 7
#define ID_FIRSTTEXT 8
#define ID_SECONDTEXT 9
int oType, multi = 1, divis = 2, add = 3, sub = 4;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR lpCmdLine, int nCmdShow) {
    HWND Console = GetConsoleWindow();
    ShowWindow( Console, SW_MINIMIZE );
    ShowWindow( Console, SW_HIDE );
    MSG  msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"C Calculator";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"C Calculator",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  200, 170, 300, 225, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0)) {
    
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {
    static HWND hwndFirst;
    static HWND hwndSecond;
    static wchar_t *FirstNum = L"First number: ";
    static wchar_t *SecondNum1 = L"Second ";
    static wchar_t *SecondNum2 = L"number: ";
    HWND hwndGo;
    
    switch(msg) {

        case WM_CREATE:
	    center(hwnd);

            CreateWindowW(L"Button", L"Multiplication",
                WS_VISIBLE | WS_CHILD ,
                30, 25, 100, 25, hwnd, (HMENU) ID_MULTI, NULL, NULL);

            CreateWindowW(L"Button", L"Division",
                WS_VISIBLE | WS_CHILD ,
                160, 25, 80, 25, hwnd, (HMENU) ID_DIVIS, NULL, NULL);
	    CreateWindowW(L"Button", L"Addition",
                WS_VISIBLE | WS_CHILD ,
                30, 80, 100, 25, hwnd, (HMENU) ID_ADD, NULL, NULL);

            CreateWindowW(L"Button", L"Subtraction",
                WS_VISIBLE | WS_CHILD ,
                160, 80, 80, 25, hwnd, (HMENU) ID_SUB, NULL, NULL);

	    CreateWindowW(L"Static", FirstNum, 
    		WS_CHILD | WS_VISIBLE | SS_LEFT,
    		30, 110, 100, 20,
    		hwnd, (HMENU) ID_FIRSTTEXT, NULL, NULL);

	    CreateWindowW(L"Static", SecondNum1, 
    		WS_CHILD | WS_VISIBLE | SS_LEFT,
    		150, 110, 100, 20,
    		hwnd, (HMENU) ID_SECONDTEXT, NULL, NULL);

	    CreateWindowW(L"Static", SecondNum2, 
    		WS_CHILD | WS_VISIBLE | SS_LEFT,
    		202, 110, 100, 20,
    		hwnd, (HMENU) ID_SECONDTEXT, NULL, NULL);

	    hwndFirst = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                30, 130, 100, 20, hwnd, (HMENU) ID_FIRSTNUM,
                NULL, NULL);
	    
	    hwndSecond = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                150, 130, 100, 20, hwnd, (HMENU) ID_SECONDNUM,
                NULL, NULL);

            hwndGo = CreateWindowW(L"button", L"Calculate!",
                WS_VISIBLE | WS_CHILD, 80, 160, 100, 25,
                hwnd, (HMENU) ID_GO, NULL, NULL);
	    bringToFront(hwnd);
            break;

        case WM_COMMAND:
	    if (LOWORD(wParam) == ID_GO) {
                int lenFirst = GetWindowTextLengthW(hwndFirst) + 1;
                wchar_t textFirst[lenFirst-1];
                GetWindowTextW(hwndFirst, textFirst, lenFirst);
		unsigned long long first = _wtoi(textFirst);
		int lenSecond = GetWindowTextLengthW(hwndSecond) + 1;
                wchar_t textSecond[lenSecond-1];
                GetWindowTextW(hwndSecond, textSecond, lenSecond);
		unsigned long long second = _wtoi(textSecond);
		if (oType == multi) {
			unsigned long long result = first * second;
			wchar_t wRes[1024];
			swprintf_s(wRes, 1024, L"%lld times %lld is %lld", first, second, result);
			MessageBoxW(NULL, wRes, L"C Calculator", MB_ICONINFORMATION);
		} else if (oType == divis) {
			double result = (double)first / second;
			wchar_t wRes[1024];
			swprintf_s(wRes, 1024, L"%lld divided by %lld is %Lf", first, second, result);
			MessageBoxW(NULL, wRes, L"C Calculator", MB_ICONINFORMATION);
		} else if (oType == add) {
			unsigned long long result = first + second;
			wchar_t wRes[1024];
			swprintf_s(wRes, 1024, L"%lld plus %lld is %lld", first, second, result);
			MessageBoxW(NULL, wRes, L"C Calculator", MB_ICONINFORMATION);
		} else if (oType == sub) {
			unsigned long long result = first - second;
			wchar_t wRes[1024];
			swprintf_s(wRes, 1024, L"%lld minus %lld is %lld", first, second, result);
			MessageBoxW(NULL, wRes, L"C Calculator", MB_ICONINFORMATION);
		} else {
			MessageBoxW(NULL, L"You must click the operation type.", L"C Calculator", MB_ICONERROR);
		}
            }
            if (LOWORD(wParam) == ID_MULTI) {
            	oType = 1;
            }

            if (LOWORD(wParam) == ID_DIVIS) {
		oType = 2;
            }
	    if (LOWORD(wParam) == ID_ADD) {
            	oType = 3;
                
            }

            if (LOWORD(wParam) == ID_SUB) {
            	oType = 4;
            }

            break;

        case WM_DESTROY:

            PostQuitMessage(0);
            break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
