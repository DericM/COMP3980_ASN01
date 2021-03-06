/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: application.h - An application that will create a window with
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
#pragma warning (disable: 4096)

#define STRICT
#define WINDOW_WIDTH					600
#define WINDOW_HEIGHT					400
#define READ_TIMEOUT					500

#define IDM_TX							100
#define IDM_RX							101
#define IDM_Port						102
#define IDM_Speed						103
#define IDM_Word						104
#define IDM_ZETA						105
#define IDM_Save						106
#define IDM_THETA						107
#define IDM_HELP						108
#define IDM_COM1						109
#define IDM_COM2						110
#define IDM_COM3						111
#define IDM_COM4						112
#define IDM_COM5						113
#define IDM_COM6						114
#define IDM_9600						115
#define IDM_32000						116
#define IDM_110000						117



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
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
void printToScreen(char readBuffer[], DWORD dwRead, LPVOID hwnd);

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
bool createReadThread(HWND hwnd);

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
DWORD WINAPI readThread(LPVOID pData);
