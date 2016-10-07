/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: application.cpp - An application that will create a window with
-- modifiable settings allowing us to connect to a comm port and send and receive 
-- text.
--
-- PROGRAM: Comm Shell
--
-- FUNCTIONS:
-- void daemonize (void)
-- int initialize_inotify_watch (int fd, char pathname[MAXPATHLEN])
-- int ProcessFiles (char pathname[MAXPATHLEN])
-- unsigned int GetProcessID (char *process)
--
--
-- DATE: October 05, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Deric Mccadden
--
-- PROGRAMMER: Deric Mccadden
--
-- NOTES:
-- An application that will create a window with
-- modifiable settings allowing us to connect to a comm port and send and receive
-- text.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once




#include <windows.h>
#include <stdio.h>
#include "application.h"
#include "session.h"
#include "physical.h"


HANDLE hComm;
HANDLE hReadThread;
LPCSTR	lpszCommName = "";
char str[80] = "";





/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: WinMain
--
-- DATE: October 05, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Deric Mccadden
--
-- PROGRAMMER: Deric Mccadden
--
-- INTERFACE: int WINAPI WinMain(HINSTANCE hInst,
--								 HINSTANCE hprevInstance,
--								 LPSTR lspszCmdParam,
--								 int nCmdShow)
--
-- RETURNS: int.
--
-- NOTES:
-- This function builds the windows and menu.
----------------------------------------------------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hprevInstance,
	LPSTR lspszCmdParam,
	int nCmdShow)
{
	char name[] = "Comm Shell";
	MSG Msg;
	HWND hwnd;
	WNDCLASSEX Wcl;


	Wcl.cbSize = sizeof(WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style

	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = name;

	Wcl.lpszMenuName = "MYMENU"; // The menu Class
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0;

	if (!RegisterClassEx(&Wcl))
		return 0;

	hwnd = CreateWindow(
		name,
		name,
		WS_OVERLAPPEDWINDOW,
		10,
		10,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInst,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	CloseHandle(hComm);

	return Msg.wParam;
}





/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: WndProc
--
-- DATE: October 05, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Deric Mccadden
--
-- PROGRAMMER: Deric Mccadden
--
-- INTERFACE: LRESULT CALLBACK WndProc(HWND hwnd,
--									   UINT Message,
--									   WPARAM wParam,
--									   LPARAM lParam)
--
-- RETURNS: int.
--
-- NOTES:
-- This function handles menu interaction.
----------------------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hwnd,
	UINT Message,
	WPARAM wParam,
	LPARAM lParam)
{
	int response;
	HDC hdc;
	PAINTSTRUCT paintstruct;

	switch (Message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_COM1:
			lpszCommName = "COM1";
			break;
		case IDM_COM2:
			lpszCommName = "COM2";
			break;
		case IDM_COM3:
			lpszCommName = "COM3";
			break;
		case IDM_COM4:
			lpszCommName = "COM4";
			break;
		case IDM_COM5:
			lpszCommName = "COM5";
			break;
		case IDM_COM6:
			lpszCommName = "COM6";
			break;
		}
		//terminate previous thread.
		TerminateThread(hReadThread, INFINITE);
		CloseHandle(hComm);
		//CloseHandle(hReadThread);
		if (!connect(hwnd, hComm, lpszCommName)) {
			MessageBox(NULL, "Error opening COM port:", lpszCommName, MB_OK);
		}
		else {
			createReadThread(hwnd);
		}
		break;

	case WM_CHAR: // Process keystroke
		hdc = GetDC(hwnd);			 // get device context
		sprintf_s(str, "%c", (char)wParam);
		writeToPort(str, 1, hComm);
		OutputDebugStringA("Sending: ");
		OutputDebugStringA(str);
		OutputDebugStringA("\n");
		break;

	case WM_PAINT: // Process a repaint message
		hdc = BeginPaint(hwnd, &paintstruct); // Acquire DC
		TextOut(hdc, 0, 0, str, strlen(str)); // output character
		EndPaint(hwnd, &paintstruct); // Release DC
		break;

	case WM_DESTROY: // Terminate program
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}





/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: printToScreen
--
-- DATE: October 05, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Deric Mccadden
--
-- PROGRAMMER: Deric Mccadden
--
-- INTERFACE: void printToScreen(char readBuffer[], DWORD dwRead, LPVOID hwnd)
--
-- RETURNS: void.
--
-- NOTES:
-- This prints characters to the window for display to the user.
----------------------------------------------------------------------------------------------------------------------*/

void printToScreen(char readBuffer[], DWORD dwRead, LPVOID hwnd) {
	HDC hdc;
	RECT rect;
	TEXTMETRIC tm;
	SIZE size;

	static unsigned x = 0;
	static unsigned y = 0;

	hdc = GetDC((HWND)hwnd);

	sprintf_s(str, "%c", readBuffer[0]); // Convert char to string
	GetTextMetrics(hdc, &tm);

	TextOut(hdc, x, y, str, strlen(str));
	GetTextExtentPoint32(hdc, str, strlen(str), &size);

	x += size.cx;
	if (x >= WINDOW_WIDTH - 20) {
		x = 0;
		y = y + tm.tmHeight + tm.tmExternalLeading;
	}
	
	OutputDebugStringA("received: ");
	OutputDebugStringA(str);
	OutputDebugStringA("\n");
	ReleaseDC((HWND)hwnd, hdc);
	readBuffer = '\0';
}




/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: createReadThread
--
-- DATE: October 05, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Deric Mccadden
--
-- PROGRAMMER: Deric Mccadden
--
-- INTERFACE: bool createReadThread(HWND hwnd)
--
-- RETURNS: bool.
--
-- NOTES:
-- This function creates a new thread for reading.
----------------------------------------------------------------------------------------------------------------------*/
bool createReadThread(HWND hwnd) {

	//make new thread for reading
	hReadThread = CreateThread(
		NULL,
		0,
		readThread,
		(LPVOID)hwnd,
		0,
		NULL
	);

	return TRUE;
}





/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: readThread
--
-- DATE: October 05, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Deric Mccadden
--
-- PROGRAMMER: Deric Mccadden
--
-- INTERFACE: DWORD WINAPI readThread(LPVOID pData)
--
-- RETURNS: DWORD.
--
-- NOTES:
-- This prints characters to the window for display to the user.
----------------------------------------------------------------------------------------------------------------------*/
DWORD WINAPI readThread(LPVOID pData) {
	DWORD dwRead;
	DWORD dwRes;
	BOOL fWaitingOnRead = FALSE;
	OVERLAPPED osReader = { 0 };
	char readBuffer[1] = { 0 };

	osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (osReader.hEvent == NULL) {
		OutputDebugStringA("Error: osReader null\n");
		return FALSE;
	}

	while (1) {
		if (!fWaitingOnRead) {
			if (!ReadFile(hComm,
				readBuffer,
				sizeof(readBuffer),
				&dwRead,
				&osReader))
			{
				if (GetLastError() != ERROR_IO_PENDING) {     // read not delayed?
					OutputDebugStringA("Error in communications1\n");// Error in communications; report it.
				}
				else {
					fWaitingOnRead = TRUE;
				}
			}
			else {
				// read completed immediately
				printToScreen(readBuffer, dwRead, pData);
			}
		}
		if (fWaitingOnRead) {
			dwRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);
			switch (dwRes)
			{
			case WAIT_OBJECT_0:
				if (!GetOverlappedResult(hComm, &osReader, &dwRead, FALSE))
					OutputDebugStringA("Error in communications2\n");// Error in communications; report it.
				else {
					// Read completed successfully.
					printToScreen(readBuffer, dwRead, pData);
				}
				//  Reset flag so that another opertion can be issued.
				fWaitingOnRead = FALSE;
				break;

			case WAIT_TIMEOUT:
				OutputDebugStringA("WAIT_TIMEOUT\n");
				break;

			default:
				OutputDebugStringA("DEFAULT\n");
				break;
			}
		}
	}
}
