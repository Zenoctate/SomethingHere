#include <windows.h>
#include <winbase.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <memoryapi.h>
#include <stdbool.h>

void ErrorExit() 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    if (FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL) == 0) {
        MessageBox(NULL, TEXT("FormatMessage failed"), TEXT("Error"), MB_OK);
        ExitProcess(dw);
    }

    MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    ExitProcess(dw); 
}

struct Pointer {
	void *startAddr;
	int numoffs;
	int offsets[];
};

// Found through cheating :P
struct Pointer playerPTR = {
	(int *)0x0054ad30,
	1,
	{0}
};

HANDLE hProcess = NULL;
HANDLE hSnapshot = NULL;

void* BaseAddr = NULL;
int playerStruct = 0;
DWORD pID = 0;

void AttachProcess() {
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	do {
		if(strcmp(pe32.szExeFile, "gta-vc.exe") == 0) {
			CloseHandle(hSnapshot);
			pID = pe32.th32ProcessID; 
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);

			// Locate Base Address
			HMODULE hMods[1024];
			DWORD cbNeeded;
			if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
				for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
					char szModName[MAX_PATH];
					if (GetModuleFileNameExA(hProcess, hMods[i], szModName, sizeof(szModName))) {
						if (strstr(szModName, "gta-vc.exe") != NULL) {
							BaseAddr = hMods[i];
						}
					}
				}
			}
			break;
		}
	} while (Process32Next(hSnapshot, &pe32));
}

void SetPTRs() {
	if(!ReadProcessMemory(hProcess, (LPCVOID)((int)BaseAddr + playerPTR.startAddr), &playerStruct, 4, NULL)) {
		ErrorExit();
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello to GTA_VC!");

	switch (message) {
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			// Here your application is laid out.
			TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
			// End application-specific layout section.

			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		// case WM_KEYDOWN:
			// if(wParam == 'a') {
			// 	MessageBox(NULL, "Wow", "cool", NULL);
			// }
			// wchar_t msg[32];
			// swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
			// MessageBox(hWnd, msg, "cool", NULL);
			// break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void handleStuff() {
	do {
		Sleep(100);
		AttachProcess();
	} while(hProcess == NULL);
	// MessageBox(NULL, (LPCSTR)"Found", (LPCSTR)"Yay!", MB_OK | MB_ICONINFORMATION);
	
	do {
		Sleep(100);
		SetPTRs();
	} while(playerStruct == 0);
	// MessageBox(NULL, (LPCSTR)"Set player!", (LPCSTR)"Yay!", MB_OK | MB_ICONINFORMATION);
}
	
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	handleStuff();

	static TCHAR szWindowClass[] = _T("ConfusingTimes");
	static TCHAR szTitle[] = _T("WHAT IS THAT??");

	WNDCLASSEX wcex;

	wcex.cbSize         = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Windows Desktop Guided Tour"), MB_OK);
		return 1;
	}


	// The parameters to CreateWindowEx explained:
	// WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, height)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 100, NULL, NULL, hInstance, NULL);
	if (!hWnd) {
		MessageBox(NULL, _T("Call to CreateWindowEx failed!"), _T("Windows Desktop Guided Tour"), MB_OK);
		return 1;
	}

	HWND hwndButton = CreateWindow( 
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"ATTACH",  // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		10,         // y position 
		100,        // Button width
		100,        // Button height
		m_hwnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (GetAsyncKeyState('A') < 0) {
			float wow = 0.0f;
			char wowowowo[32];
			// sprintf(wowowowo, "HP: %f", wow);
			// MessageBox(NULL, wowowowo, "HUH", MB_OK);
			if(!ReadProcessMemory(hProcess, (void *)(playerStruct + 0x354), &wow, 4, NULL)) {
				MessageBox(NULL, "Could not read!", "Failed", MB_OK);
			} else {
				wow += 200.0f;
				if(!WriteProcessMemory(hProcess, (void *)(playerStruct + 0x354), &wow, 4, NULL)) {
					MessageBox(NULL, "Could not write!", "Failed", MB_OK);
				}
			}
		}

	}

	CloseHandle(hProcess);
	CloseHandle(hSnapshot);
	return (int) msg.wParam;
}
