/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: physical.h - An application that will read and write to and from an established comm
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
bool writeToPort(char * lpBuf, DWORD dwToWrite, HANDLE& hComm);
