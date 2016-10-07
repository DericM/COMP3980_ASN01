/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: physical.cpp - An application that will read and write to and from an established comm 
-- port connection.
--
-- PROGRAM: Comm Shell
--
-- FUNCTIONS:
-- bool writeToPort(char * lpBuf, DWORD dwToWrite, HANDLE& hComm)
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
-- An application that will read and write to and from an established comm 
-- port connection.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once
#include <windows.h>
#include "physical.h"


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: writeToPort
--
-- DATE: October 05, 2016
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Deric Mccadden
--
-- PROGRAMMER: eric Mccadden
--
-- INTERFACE: bool writeToPort(char * lpBuf, DWORD dwToWrite, HANDLE& hComm);
--
-- RETURNS: bool.
--
-- NOTES:
-- THis function sends text over a comm connection.
----------------------------------------------------------------------------------------------------------------------*/
bool writeToPort(char * lpBuf,
	DWORD dwToWrite,
	HANDLE& hComm)
{
	OVERLAPPED osWrite = { 0 };
	DWORD dwWritten;
	bool fRes;

	// Create this writes OVERLAPPED structure hEvent.
	osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osWrite.hEvent == NULL)
		// Error creating overlapped event handle.
		return FALSE;

	// Issue write.
	if (!WriteFile(hComm, lpBuf, dwToWrite, &dwWritten, &osWrite)) {
		if (GetLastError() != ERROR_IO_PENDING) {
			// WriteFile failed, but it isn't delayed. Report error and abort.
			fRes = FALSE;
		}
		else {
			// Write is pending.
			if (!GetOverlappedResult(hComm, &osWrite, &dwWritten, TRUE))
				fRes = FALSE;
			else
				// Write operation completed successfully.
				fRes = TRUE;
		}
	}
	else {
		// WriteFile completed immediately.
		fRes = TRUE;
	}

	CloseHandle(osWrite.hEvent);
	return fRes;
}








