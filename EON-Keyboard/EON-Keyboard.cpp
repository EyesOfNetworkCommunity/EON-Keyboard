// EON-Keyboard.cpp : Defines the entry point for the console application.
/*
Copyright (C) 2015 Michaël Aubertin

This package is free software; you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this software;
if not, write to :
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/
//

#include "stdafx.h"
#include "EON-Keyboard.h"
#include "vKeyboardCode.h"
#include "wtypes.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp EONKeyboard;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	LPWSTR *szArglist;
	int nArgs;
	int iLoop;
	int iXMouseCursorPosition = 0;
	int iYMouseCursorPosition = 0;
	int iHorizontalResolution = 0;
	int iVerticalResolution = 0;

	int TimeWait = 60;
	int SleepSec = 0;

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = -1;
		}
		else
		{
			szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
			//printf("\n\n nArgs:%d\n", nArgs);

			if ((NULL == szArglist ) || (nArgs == 1))
			{
				Usage();
			}
			else for (iLoop = 1; iLoop < nArgs; iLoop++) {
				/*printf("\nInto the loop.\n");
				printf("%d: %ws\n", iLoop, szArglist[iLoop]);			
				printf("Lenght Args: %d\n", CString(szArglist[iLoop]).GetLength());
				*/

				if (CString(szArglist[iLoop]).GetLength() < 3) {
					if (CString(szArglist[iLoop]).Find(_T("-")) == 0) {
						//printf("Detected at:%d\n", CString(szArglist[iLoop]).Find(_T("-")));
						if ( CString(szArglist[iLoop]).GetAt(1) == 'h') {
							// Do -h then exit
							Usage();
						}
						if (CString(szArglist[iLoop]).GetAt(1) == 'v') {
							// Do -h then exit
							printf("EON-Keyboard version %d.%d\n", Version, Subversion);
							exit(0);
						}

						if (CString(szArglist[iLoop]).GetAt(1) == 'w') {
							//printf("\n -w engaged \n");
							SleepSec = _wtoi(CString(szArglist[iLoop + 1]));
							Sleep(SleepSec * 1000);
							continue;
						}

						if (CString(szArglist[iLoop]).GetAt(1) == 'm') {
							//printf("\n -m engaged \n");
							// Do -m then exit
							iXMouseCursorPosition = _wtoi(CString(szArglist[iLoop + 1]));
							iYMouseCursorPosition = _wtoi(CString(szArglist[iLoop + 2]));

							GetWindowRect(hDesktop, &desktop);
							iHorizontalResolution = desktop.right;
							iVerticalResolution = desktop.bottom;

							if ((iHorizontalResolution < iXMouseCursorPosition) || (iVerticalResolution < iYMouseCursorPosition)) {
								printf("\nError: Mouse position (%d,%d) doesn't seems to be on this screen resolution (%d,%d).\n", iXMouseCursorPosition, iYMouseCursorPosition, iHorizontalResolution, iVerticalResolution);
								Usage();
							}

							MoveMouse(iXMouseCursorPosition, iYMouseCursorPosition);
							//printf("\nX:%d, Y:%d\n", iXMouseCursorPosition, iYMouseCursorPosition);
							exit(0);
						}
						if (CString(szArglist[iLoop]).GetAt(1) == 'c') {
							//printf("\n -c engaged \n");
							// Do -c then exit
							if (CString(szArglist[iLoop + 1]).GetAt(0) == 'l') {
								//printf("\n Simple left click \n");
								ClickMouse(1, 1); // Gauche
								exit(0);
							}
							if (CString(szArglist[iLoop + 1]).GetAt(0) == 'L') {
								//printf("\n Double left click \n");
								ClickMouse(1, 2); // Gauche
								exit(0);
							}
							if (CString(szArglist[iLoop + 1]).GetAt(0) == 'm') {
								//printf("\n Middle click \n");
								ClickMouse(4, 1); // Millieu
								exit(0);
							}
							if (CString(szArglist[iLoop + 1]).GetAt(0) == 'r') {
								//printf("\n Right click \n");
								ClickMouse(2, 1); // Droit
								exit(0);
							}
							printf("\n Unknow option of click.\n");
							Usage();
						}

						if (CString(szArglist[iLoop]).GetAt(1) == 's') {
							//printf("\n -s engaged \n");
							if (CString(szArglist[iLoop + 1]).GetAt(0) == '{') {
								//printf("\nSpecial Char wanted\n");
								if (CString(szArglist[iLoop + 1]).Find(_T("TAB")) == 1) { //Note 1 is position, not true 
									//printf("\nTAB Special key wanted\n");
									Press_Tab(TimeWait);
									break;
								}
								if (CString(szArglist[iLoop + 1]).Find(_T("ENTER")) == 1) { //Note 1 is position, not true 
									//printf("\nENTER Special key wanted\n");
									Press_Enter(TimeWait);
									break;
								}

								printf("\n Special ley not handled. Sorry.\n");
							} 
							else
							{
								KeyString(CString(szArglist[iLoop + 1]));
							}
							exit(0);
						}
						printf("\n \tUnknow option.\n");
						Usage();
					}
				}
				else
				{
					printf("\n Unknow option.\n");
					Usage();
				}



			}

			// Free memory allocated for CommandLineToArgvW arguments.
			LocalFree(szArglist);

			// Exit normally
			return 0;
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

int Usage(){
	printf("EON-Keyboard version %d.%d\n", Version, Subversion);
	printf("By EON Team. Maintainer: Michael Aubertin <michael.aubertin@gmail.com>\n");
	printf("Released under GPLV2. http://www.gnu.org/licenses/old-licenses/gpl-2.0.fr.html\n");
	printf("\n\nUsage:\n");
	printf(" -h: This help\n");
	printf(" -v: Version\n");
	printf(" -w X: Where X is the number of sec to wait before action (debug purpose only, not needed in production)\n");
	printf(" -m xN yN: Move mouse cursor to xN yN\n");
	printf("\n");
	printf(" -c l: Click on Left button\n");
	printf(" -c L: Double click on Left Button\n");
	printf(" -c m: Click on Middle Button\n");
	printf(" -c r: Click on Right Button\n");
	printf("\n");
	printf(" -s \"Your String\": Str delimited by \"word to type.\"\n");
	printf(" -s \"{XXX}\": Type special key or char. Can be:\n");
	printf("\t\t- \"{TAB}\": For TAB key\n");
	printf("\t\t- \"{ENTER}\": For ENTER key\n");
	printf("Please note: EON Keyboard is low level drived.\n So your keyboard must be set as French (AZERTY) to see what you expect.\n");
	exit(1);
}

int KeyString(CString strToPress)
{
	int iLoop = 0;
	int strLenght = strToPress.GetLength();
	int TimeWait = 60;

	for (iLoop = 0; iLoop < strLenght; iLoop++) {
		if (strToPress.GetAt(iLoop) == ' ') { Press_Space(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '0') { Press_0(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '1') { Press_1(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '2') { Press_2(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '3') { Press_3(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '4') { Press_4(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '5') { Press_5(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '6') { Press_6(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '7') { Press_7(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '8') { Press_8(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '9') { Press_9(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'a') { Press_a(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'b') { Press_b(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'c') { Press_c(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'd') { Press_d(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'e') { Press_e(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'f') { Press_f(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'g') { Press_g(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'h') { Press_h(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'i') { Press_i(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'j') { Press_j(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'k') { Press_k(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'l') { Press_l(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'm') { Press_m(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'n') { Press_n(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'o') { Press_o(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'p') { Press_p(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'q') { Press_q(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'r') { Press_r(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 's') { Press_s(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 't') { Press_t(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'u') { Press_u(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'v') { Press_v(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'w') { Press_w(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'x') { Press_x(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'y') { Press_y(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'z') { Press_z(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'A') { Press_A(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'B') { Press_B(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'C') { Press_C(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'D') { Press_D(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'E') { Press_E(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'F') { Press_F(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'G') { Press_G(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'H') { Press_H(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'I') { Press_I(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'J') { Press_J(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'K') { Press_K(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'L') { Press_L(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'M') { Press_M(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'N') { Press_N(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'O') { Press_O(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'P') { Press_P(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'Q') { Press_Q(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'R') { Press_R(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'S') { Press_S(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'T') { Press_T(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'U') { Press_U(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'V') { Press_V(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'W') { Press_W(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'X') { Press_X(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'Y') { Press_Y(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'Z') { Press_Z(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == ',') { Press_Comma(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == ';') { Press_SemiComma(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '?') { Press_DotWhat(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '.') { Press_Dot(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '<') { Press_SmallerThan(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '>') { Press_GreaterThan(TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '\\') { Press_BackSlash(TimeWait); continue; }

		printf("Char not handled, sorry: %c\n", (LPCTSTR)strToPress.GetAt(iLoop));
	}

	return(0);
}
int MoveMouse(int x, int y) {
	int response;
	response= SetCursorPos(x,y);
	return 0;
}
int ClickMouse( int WantedButton,int NumberOfClick) {
	
	int vKey_MouseLeftButton = 0x01;
	int vKey_MouseRightButton = 0x02;
	int vKey_MouseMiddleButton = 0x04;
	long ButtonToPress = 0;
	long ButtonToRelease = 0;

	POINT CurrentCursorPosition;
	HWND Handle;

	GetCursorPos(&CurrentCursorPosition);
	Handle = WindowFromPoint(CurrentCursorPosition); /* Avoid esoteric comportement of Mouse Event....*/
	SetFocus(Handle); /* Avoid esoteric comportement of Mouse Event....*/

	INPUT ip;
	
	ip.type = INPUT_MOUSE;
	ip.mi.time = 0;

	ip.mi.dx = CurrentCursorPosition.x;
	ip.mi.dy = CurrentCursorPosition.y;
	ip.mi.dwExtraInfo = 0;

	/* DEBUG PURPOSE ONLY
	CString x;
	CString y;
	x.Format(_T("%d"), CurrentCursorPosition.x);
	y.Format(_T("%d"), CurrentCursorPosition.y);
	MessageBox(NULL, (LPCTSTR)L"X:" + x + (LPCTSTR)L" Y:" + y , (LPCTSTR)L"Debug", MB_OK);
	*/
		
	if ((WantedButton == vKey_MouseLeftButton) || (WantedButton == vKey_MouseRightButton) || (WantedButton == vKey_MouseMiddleButton))
	{
		if (WantedButton == vKey_MouseLeftButton){
			ButtonToPress=MOUSEEVENTF_LEFTDOWN;
			ButtonToRelease=MOUSEEVENTF_LEFTUP;
			//MessageBox(NULL, (LPCTSTR)L"click gauche", (LPCTSTR)L"Debug", MB_OK);
		}
		if (WantedButton == vKey_MouseRightButton){
			ButtonToPress = MOUSEEVENTF_RIGHTDOWN;
			ButtonToRelease = MOUSEEVENTF_RIGHTUP;
			//MessageBox(NULL, (LPCTSTR)L"click droit", (LPCTSTR)L"Debug", MB_OK);
		}
		if (WantedButton == vKey_MouseMiddleButton){
			ButtonToPress = MOUSEEVENTF_MIDDLEDOWN;
			ButtonToRelease = MOUSEEVENTF_MIDDLEUP;
			//MessageBox(NULL, (LPCTSTR)L"click millieu", (LPCTSTR)L"Debug", MB_OK);
		}
		while (NumberOfClick) {
			ip.mi.dwFlags = ButtonToPress;
			SendInput(1, &ip, sizeof(INPUT));
			Sleep(10); // prevent event confusion
			ip.mi.dwFlags = ButtonToRelease;
			SendInput(1, &ip, sizeof(INPUT));
			Sleep(15); // prevent event confusion
			NumberOfClick--;
		}
	}
	Sleep(250); 
	return 0;// Feel more human :)
}

int Press_0(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_0; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_0; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_1(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_1; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_1; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_2(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_2; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_2; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_3(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_3; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_3; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_4(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_4; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_4; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_5(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_5; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_5; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_6(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_6; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_6; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_7(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_7; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_7; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_8(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_8; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_8; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_9(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_9; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_9; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}



int Press_a(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; 
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_a;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_a; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_b(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_b;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_b; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_c(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_c;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_c; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_d(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_d;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_d; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_e(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_e;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_e; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_f(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_f;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_f; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_g(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_g;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_g; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_h(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_h;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_h; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_i(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_i;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_i; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_j(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_j;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_j; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_k(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_k;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_k; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_l(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_l;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_l; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_m(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_m;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_m; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_n(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_n;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_n; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_o(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_o;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_o; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_p(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_p;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_p; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_q(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_q;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_q; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_r(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_r;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_r; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_s(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_s;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_s; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_t(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_t;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_t; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_u(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_u;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_u; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_v(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_v;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_v; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_w(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_w;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_w; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_x(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_x;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_x; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_y(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_y;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_y; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_z(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_z;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_z; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}


int Press_A(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "A" key
	ip.ki.wVk = vKey_a; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	// Release the "A" key
	ip.ki.wVk = vKey_a; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_B(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_b;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_b;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_C(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_c; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_c; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_D(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_d;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_d;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_E(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_e; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_e; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_F(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_f;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_f;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_G(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_g; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_g; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_H(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_h;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_h;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_I(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_i; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_i; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_J(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_j;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_j;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_K(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_k; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_k; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_L(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_l;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_l;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_M(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_m; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_m; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_N(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_n;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_n;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_O(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_o; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_o; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_P(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_p;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_p;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_Q(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_q; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_q; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_R(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_r;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_r;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_S(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_s; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_s; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_T(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_t;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_t;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_U(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_u;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_u;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_V(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_v; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_v; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_W(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_w;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_w;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_X(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_x; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_x; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_Y(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_y;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_y;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_Z(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_z; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_z; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}

int Press_Pound(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Alt; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Ctrl; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_3;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_3;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Ctrl; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Alt; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_And(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_1;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_1;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_Arobase(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Alt; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Ctrl; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_0;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_0;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Ctrl; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Alt; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_Euro(int milliSeconds){

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Alt; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Ctrl; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_e;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_e;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Ctrl; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Alt; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}

int Press_Add(int milliSeconds){

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Add;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Add;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_Substract(int milliSeconds) {
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Substract;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Substract;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_Divide(int milliSeconds) {
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Divide;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Divide;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_Multiple(int milliSeconds){
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Multiply;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Multiply;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}

int Press_Tab(int milliSeconds){
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Tab;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Tab;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_Win(int milliSeconds) {
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Win;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Win;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_Enter(int milliSeconds) {
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Enter;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Enter;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_Space(int milliSeconds) {
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Space;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Space;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_Comma(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Comma;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Comma; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_SemiComma(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_SemiComma;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_SemiComma; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}

int Press_Dot(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_SemiComma; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_SemiComma; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}
int Press_DotWhat(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Comma; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_Comma; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}

int Press_SmallerThan(int milliSeconds) {

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_SmallerThan;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_SmallerThan; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_GreaterThan(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wVk = vKey_Shift; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_SmallerThan; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_SmallerThan; // virtual-key code for the "a" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Shift; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}

int Press_BackSlash(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = vKey_Alt; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Ctrl; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_8;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = vKey_8;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Ctrl; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = vKey_Alt; // virtual-key code for the LShift key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	return 0;
}