/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: session.h - An application that will establish a connection to a comm port.
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
bool connect(HWND& hwnd, HANDLE& hComm, LPCSTR& lpszCommName);
