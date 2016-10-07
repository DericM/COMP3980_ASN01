/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: session.cpp - An application that will establish a connection to a comm port.
--
-- PROGRAM: Comm Shell
--
-- FUNCTIONS:
-- connect(HWND& hwnd, HANDLE& hComm, LPCSTR& lpszCommName) 
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
-- An application that will establish a connection to a comm port.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once
#include <windows.h>
#include "session.h"



/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: connect
--
-- DATE: October 05, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Deric Mccadden
--
-- PROGRAMMER: Deric Mccadden
--
-- INTERFACE: bool connect(HWND& hwnd, HANDLE& hComm, LPCSTR& lpszCommName);
--
-- RETURNS: bool.
--
-- NOTES:
-- This function establishes a connection to an open comm port.
----------------------------------------------------------------------------------------------------------------------*/
bool connect(HWND& hwnd, HANDLE& hComm, LPCSTR& lpszCommName) {
	COMMCONFIG cc;

	//CloseHandle(hComm);
	//hComm = 0;

	//set comm settings
	cc.dwSize = sizeof(COMMCONFIG);
	cc.wVersion = 0x100;
	GetCommConfig(hComm, &cc, &cc.dwSize);
	if (!CommConfigDialog(lpszCommName, hwnd, &cc))
		return FALSE;

	//open comm port
	hComm = CreateFile(
		lpszCommName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL
	);

	//check for failure
	if (hComm == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	return TRUE;
}


