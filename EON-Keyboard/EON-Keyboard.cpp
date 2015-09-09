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
#include "wtypes.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp EONKeyboard;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int TimeWait = 60;
	int nRetCode = 0;
	LPWSTR *szArglist;
	int nArgs;
	int iLoop;
	
	int iMouseData = 0;
	int iXMouseCursorPosition = 0;
	int iYMouseCursorPosition = 0;
	int iHorizontalResolution = 0;
	int iVerticalResolution = 0;

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
			//debug purpose.
			//for (int i = 0; i<nArgs; i++) printf("%d: %ws\n", i, szArglist[i]);

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

						// Initial Wait to allow this "strange" OS named Windows to deal whit his own event.... /Nocomment .....
						Sleep(300);

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
							iLoop += 2;
						}


						if (CString(szArglist[iLoop]).GetAt(1) == 'T') {
							TimeWait = _wtoi(CString(szArglist[iLoop + 1]));
							iLoop+=2;
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
						if (CString(szArglist[iLoop]).GetAt(1) == 'g') {

							GetWindowRect(hDesktop, &desktop);
							iHorizontalResolution = desktop.right;
							iVerticalResolution = desktop.bottom;

							POINT p;
							if (GetCursorPos(&p))
							{
								printf("%d,%d,%d,%d\n",iHorizontalResolution,iVerticalResolution,p.x,p.y);
							}
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
							if (CString(szArglist[iLoop + 1]).GetAt(0) == 'w') {
								iMouseData = _wtoi(CString(szArglist[iLoop + 2]));
								WheelMouse(0, iMouseData, TimeWait);
								exit(0);
							}
							if (CString(szArglist[iLoop + 1]).GetAt(0) == 'W') {
								iMouseData = _wtoi(CString(szArglist[iLoop + 2]));
								WheelMouse(1, iMouseData, TimeWait);
								exit(0);
							}
							printf("\n Unknow option of click.%ws\n", CString(szArglist[iLoop + 1]).GetAt(0));
							Usage();
						}

						if (CString(szArglist[iLoop]).GetAt(1) == 's') {
							//printf("\n -s engaged \n");
							KeyString(TimeWait, CString(szArglist[iLoop + 1]));
							exit(0);
						}

						if (CString(szArglist[iLoop]).GetAt(1) == 'S') {
							//printf("\n -S engaged \n");
							SpecialKeyString(TimeWait, CString(szArglist[iLoop + 1]));
							exit(0);
						}
						printf("\nUnknow option.\n");
						Usage();
					}
				}
				else
				{
					printf("\nUnknow option (seems too long).\n");
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
	printf(" -g: Get info about screensize and mouse x,y position.\n");
	printf("\n");
	printf(" -w X: Where X is the number of sec to wait before action (debug purpose only, not needed in production)\n");
	printf(" -T X: Where X is the number of Millisec to wait when pressing and release keys\n");
	printf(" -m xN yN: Move mouse cursor to xN yN\n");
	printf("\n");
	printf(" -c l: Click on Left button\n");
	printf(" -c L: Double click on Left Button\n");
	printf(" -c m: Click on Middle Button\n");
	printf(" -c r: Click on Right Button\n");
	printf(" -g: Get info about screensize and mouse x,y position.\n");
	printf("\n");
	printf(" -s \"Your String\": Str delimited by \"word to type.\"\n");
	printf(" -S \"{XXX}\": Type special key or char. Can be:\n");
	printf("\t\t- \"{TAB}\": For TAB key\n");
	printf("\t\t- \"{ENTER}\": For ENTER key\n");
	printf("\t\t- \"{WIN}\": For WIN key\n");
	printf("Exemple: EON-Keyboard_32.exe -w 4 -T 5 -s \"ceci est un test du clavier virtuel.\" \n");
	printf("Please note: EON Keyboard is low level drived.\n So your keyboard must be set as French (AZERTY) to see what you expect.\n");
	exit(1);
}

int KeyString(int TimeWait, CString strToPress)
{
	int iLoop = 0;
	int strLenght = strToPress.GetLength();

	for (iLoop = 0; iLoop < strLenght; iLoop++) {

		if (strToPress.GetAt(iLoop) == 'a') { Press_Letter('a',TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'b') { Press_Letter('b',TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'c') { Press_Letter('c', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'd') { Press_Letter('d', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'e') { Press_Letter('e', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'f') { Press_Letter('f', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'g') { Press_Letter('g', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'h') { Press_Letter('h', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'i') { Press_Letter('i', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'j') { Press_Letter('j', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'k') { Press_Letter('k', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'l') { Press_Letter('l', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'm') { Press_Letter('m', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'n') { Press_Letter('n', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'o') { Press_Letter('o', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'p') { Press_Letter('p', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'q') { Press_Letter('q', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'r') { Press_Letter('r', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 's') { Press_Letter('s', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 't') { Press_Letter('t', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'u') { Press_Letter('u', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'v') { Press_Letter('v', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'w') { Press_Letter('w', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'x') { Press_Letter('x', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'y') { Press_Letter('y', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'z') { Press_Letter('z', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == ' ') { Press_Letter(' ', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == ',') { Press_Letter(',',TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == ';') { Press_Letter(';', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == ':') { Press_Letter(':', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '!') { Press_Letter('!', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '*') { Press_Letter('*', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '&') { Press_Letter('&', TimeWait); continue; }
		
		if (strToPress.GetAt(iLoop) == '\'') { Press_Letter('\'', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '(') { Press_Letter('(', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '-') { Press_Letter('-', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '_') { Press_Letter('_', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == ')') { Press_Letter(')', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '=') { Press_Letter('=', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '<') { Press_Letter('<', TimeWait); continue; }

		if (strToPress.GetAt(iLoop) == '$') { Press_Letter('$',TimeWait); continue; }

		if (strToPress.GetAt(iLoop) == 'A') { Press_UpperLetter('A', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'B') { Press_UpperLetter('B', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'C') { Press_UpperLetter('C', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'D') { Press_UpperLetter('D', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'E') { Press_UpperLetter('E', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'F') { Press_UpperLetter('F', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'G') { Press_UpperLetter('G', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'H') { Press_UpperLetter('H', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'I') { Press_UpperLetter('I', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'J') { Press_UpperLetter('J', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'K') { Press_UpperLetter('K', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'L') { Press_UpperLetter('L', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'M') { Press_UpperLetter('M', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'N') { Press_UpperLetter('N', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'O') { Press_UpperLetter('O', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'P') { Press_UpperLetter('P', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'Q') { Press_UpperLetter('Q', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'R') { Press_UpperLetter('R', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'S') { Press_UpperLetter('S', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'T') { Press_UpperLetter('T', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'U') { Press_UpperLetter('U', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'V') { Press_UpperLetter('V', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'W') { Press_UpperLetter('W', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'X') { Press_UpperLetter('X', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'Y') { Press_UpperLetter('Y', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == 'Z') { Press_UpperLetter('Z', TimeWait); continue; }

		if (strToPress.GetAt(iLoop) == '0') { Press_UpperLetter('0', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '1') { Press_UpperLetter('1', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '2') { Press_UpperLetter('2', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '3') { Press_UpperLetter('3', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '4') { Press_UpperLetter('4', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '5') { Press_UpperLetter('5', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '6') { Press_UpperLetter('6', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '7') { Press_UpperLetter('7', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '8') { Press_UpperLetter('8', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '9') { Press_UpperLetter('9', TimeWait); continue; }

		if (strToPress.GetAt(iLoop) == '>') { Press_UpperLetter('>', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '?') { Press_UpperLetter('?', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '.') { Press_UpperLetter('.', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '/') { Press_UpperLetter('/', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '%') { Press_UpperLetter('%', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '+') { Press_UpperLetter('+', TimeWait); continue; }

		if (strToPress.GetAt(iLoop) == '#') { Press_ALTGRLetter('#', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '{') { Press_ALTGRLetter('{', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '[') { Press_ALTGRLetter('[', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '|') { Press_ALTGRLetter('|', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '\\') { Press_ALTGRLetter('\\', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '^') { Press_ALTGRLetter('^', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '@') { Press_ALTGRLetter('@', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == ']') { Press_ALTGRLetter(']', TimeWait); continue; }
		if (strToPress.GetAt(iLoop) == '}') { Press_ALTGRLetter('}', TimeWait); continue; }

		printf("Char not handled, sorry: %c\n", (LPCTSTR)strToPress.GetAt(iLoop));
	}

	return(0);
}
int SpecialKeyString(int TimeWait, CString strToPress)
{
	int iLoop = 0;
	int iDebug = 0;

	int iStringIndex = 0;
	int strLenght = strToPress.GetLength();
	//printf("String: %ws\n", strToPress.GetString());

	while ( iLoop < strLenght) {
	
		if (iDebug) printf("String(%d): %ws... iLoop(%d)\n", strLenght, strToPress.GetString(), iLoop);

		if ( strToPress.Find(_T("{DOUBLEQUOTE}"), iStringIndex) == 0) {
			if (iDebug) printf("In string %ws i found on index(%d) the ", strToPress.GetString(), (strToPress.Find(_T("{DOUBLEQUOTE}"), iStringIndex)));
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{DOUBLEQUOTE}") - 1));
			iLoop += (sizeof("{DOUBLEQUOTE}") - 1);
			Press_Letter('"', TimeWait);
			if (iDebug) printf("{DOUBLEQUOTE}.\n");
			continue;
		}

		if (strToPress.Find(_T("{F1}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F1}") - 1));
			iLoop += (sizeof("{F1}") - 1);
			if (iDebug) printf("F1\n");
			Press_F1(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F2}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F2}") - 1));
			iLoop += (sizeof("{F2}") - 1);
			if (iDebug) printf("F2\n");
			Press_F2(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F3}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F3}") - 1));
			iLoop += (sizeof("{F3}") - 1);
			if (iDebug) printf("F3\n");
			Press_F3(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F4}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F4}") - 1));
			iLoop += (sizeof("{F4}") - 1);
			if (iDebug) printf("F4\n");
			Press_F4(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F5}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F5}") - 1));
			iLoop += (sizeof("{F5}") - 1);
			if (iDebug) printf("F5\n");
			Press_F5(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F6}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F6}") - 1));
			iLoop += (sizeof("{F6}") - 1);
			if (iDebug) printf("F6\n");
			Press_F6(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F7}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F7}") - 1));
			iLoop += (sizeof("{F7}") - 1);
			if (iDebug) printf("F7\n");
			Press_F7(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F8}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F8}") - 1));
			iLoop += (sizeof("{F8}") - 1);
			if (iDebug) printf("F8\n");
			Press_F8(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F9}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F9}") - 1));
			iLoop += (sizeof("{F9}") - 1);
			if (iDebug) printf("F9\n");
			Press_F9(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F10}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F10}") - 1));
			iLoop += (sizeof("{F10}") - 1);
			if (iDebug) printf("F10\n");
			Press_F10(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F11}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F11}") - 1));
			iLoop += (sizeof("{F11}") - 1);
			if (iDebug) printf("F11\n");
			Press_F11(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{F12}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{F12}") - 1));
			iLoop += (sizeof("{F12}") - 1);
			if (iDebug) printf("F12\n");
			Press_F12(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{ALTF4}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{ALTF4}") - 1));
			iLoop += (sizeof("{ALTF4}") - 1);
			if (iDebug) printf("ALTF4\n");
			Press_AltF4(TimeWait);
			continue;
		}
		 
		if (strToPress.Find(_T("{TAB}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{TAB}") - 1));
			iLoop += (sizeof("{TAB}") - 1); 
			if (iDebug) printf("TAB\n");
			Press_Tab(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{WIN}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{WIN}") - 1));
			iLoop += (sizeof("{WIN}") - 1);
			if (iDebug) printf("WIN\n");
			Press_Win(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{ENTER}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{ENTER}") - 1));
			iLoop += (sizeof("{ENTER}") - 1);
			if (iDebug) printf("ENTER\n");
			Press_Enter(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{DOWN}"), iStringIndex) == 0) {
			if (iDebug) printf("In string %ws i found on index(%d) the ", strToPress.GetString(), (strToPress.Find(_T("{DOWN}"), iStringIndex)));
			strToPress = strToPress.Right(strToPress.GetLength() - ( sizeof("{DOWN}") - 1));
			iLoop += (sizeof("{DOWN}") -1);
			if (iDebug) printf("DOWN\n");
			Press_Down(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{UP}"), iStringIndex) == 0) {
			if (iDebug) printf("In string %ws i found on index(%d) the ", strToPress.GetString(), (strToPress.Find(_T("{UP}"), iStringIndex)));
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{UP}") - 1));
			iLoop += (sizeof("{UP}") - 1);
			if (iDebug) printf("UP\n");
			Press_Up(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{RIGHT}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{RIGHT}") - 1));
			iLoop += (sizeof("{RIGHT}") - 1);
			if (iDebug) printf("RIGHT\n");
			Press_Right(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{LEFT}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{LEFT}") - 1));
			iLoop += (sizeof("{LEFT}") - 1);
			if (iDebug) printf("LEFT\n");
			Press_Left(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{PAGEUP}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{PAGEUP}") - 1));
			iLoop += (sizeof("{PAGEUP}") - 1);
			if (iDebug) printf("PAGEUP\n");
			Press_PageUp(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{PAGEDOWN}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{PAGEDOWN}") - 1));
			iLoop += (sizeof("{PAGEDOWN}") - 1);
			if (iDebug) printf("PAGEDOWN\n");
			Press_PageDown(TimeWait);
			continue;
		}

		if (strToPress.Find(_T("{ECHAP}"), iStringIndex) == 0) {
			strToPress = strToPress.Right(strToPress.GetLength() - (sizeof("{ECHAP}") - 1));
			iLoop += (sizeof("{ECHAP}") - 1);
			if (iDebug) printf("ECHAP\n");
			Press_Echap(TimeWait);
			continue;
		}
		//printf ("Loop\n");
		if (iDebug) printf("\t\tiLoop(%d on %d)\n", iLoop, strLenght);
	}

	return(0);
}

int MoveMouse(int x, int y) {
	int response;
	// NOT WORKING.... Should consider adapatation of:
	/*
	    INPUT Input={0};
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)nx;
    Input.mi.dy = (LONG)ny;

    // set move cursor directly and left click
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

    SendInput(1,&Input,sizeof(INPUT));
	*/
	response = SetCursorPos(x, y);
	
	
	return response;
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
int WheelMouse(bool bDirection, int NumberWheel, int TimeWait) {

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
	

	if (bDirection == 0){
		// Wheel goes down :P
		ip.mi.dwFlags = MOUSEEVENTF_XDOWN;
	}
	if (bDirection == 1){
		// Wheel goes up
		ip.mi.dwFlags = MOUSEEVENTF_XUP;
	}
	
	ip.mi.mouseData = NumberWheel;
	SendInput(1, &ip, sizeof(ip));
				
	Sleep(TimeWait * 3);
	return 0;// Feel more human :)
}

int Press_Letter(WCHAR AskedLetter, int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	ip.type = INPUT_KEYBOARD;

	ip.ki.wScan = MapVirtualKeyEx(VkKeyScanEx(AskedLetter, HKLCurrentLayout) & 0xFF, MAPVK_VK_TO_VSC, HKLCurrentLayout);

	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = VkKeyScanEx(AskedLetter, HKLCurrentLayout);
	ip.ki.dwFlags = 0; 
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = VkKeyScanEx(AskedLetter, HKLCurrentLayout); 
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	return 0;
}
int Press_UpperLetter(WCHAR AskedLetter, int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);
	

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_SHIFT & 0xFF, MAPVK_VK_TO_VSC, 0); 
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	
	Sleep(milliSeconds * 2);

	ip.ki.wScan = MapVirtualKeyEx(VkKeyScanEx(AskedLetter, HKLCurrentLayout) & 0xFF, MAPVK_VK_TO_VSC, HKLCurrentLayout);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds);

	ip.ki.wVk = VkKeyScanEx(AskedLetter, HKLCurrentLayout); 
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds);

	ip.ki.wVk = VK_SHIFT; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_SHIFT & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds * 2);
	ip.ki.wVk = VK_SHIFT; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds *2);

	return 0;
}
int Press_ALTGRLetter(WCHAR AskedLetter, int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Control key
	ip.ki.wScan = MapVirtualKeyEx(VK_CONTROL & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	// Press Alt key
	ip.ki.wScan = MapVirtualKeyEx(VK_MENU & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wScan = MapVirtualKeyEx(VkKeyScanEx(AskedLetter, HKLCurrentLayout) & 0xFF, MAPVK_VK_TO_VSC, HKLCurrentLayout);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds);

	ip.ki.wVk = VkKeyScanEx(AskedLetter, HKLCurrentLayout);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds);

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_MENU; 
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds * 2);


	// WorkAround this stupid OS using RDP....
	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_MENU & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds * 3);
	ip.ki.wVk = VK_MENU; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds * 3);
	
	// Normal releasing.
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds * 2);

	// WorkAround this stupid OS using RDP....
	ip.ki.wScan = MapVirtualKeyEx(VK_CONTROL & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds * 3);
	ip.ki.wVk = VK_CONTROL; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds * 3);





	return 0;
}

int Press_F1(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F1 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F1; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F2(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F2 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F2; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F3(int milliSeconds) {

	INPUT ip;
	
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F3 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F3; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F4(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wScan = MapVirtualKeyEx(VK_F4 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F4; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F5(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F5 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F5; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F6(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F6 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F6; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F7(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F7 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F7; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F8(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F8 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F8; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F9(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F9 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F9; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F10(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F10 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F10; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F11(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F11 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F11; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_F12(int milliSeconds) {

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_F12 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F12; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}

int Press_AltF4(int milliSeconds) {
	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press ALT key
	ip.ki.wScan = MapVirtualKeyEx(VK_MENU & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; 
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wScan = MapVirtualKeyEx(VK_F4 & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; 
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_F4; 
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	
	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_MENU; // Left ALT
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(milliSeconds * 2);

	return 0;
}


int Press_Tab(int milliSeconds){

	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_TAB & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_TAB; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_Win(int milliSeconds) {
	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = 0;
	ip.ki.wVk = VK_LWIN;
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds);

	ip.ki.wVk = VK_LWIN;
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds);

	return 0;
}
int Press_Enter(int milliSeconds) {
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_RETURN & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_RETURN; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}
int Press_Echap(int milliSeconds) {
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = MapVirtualKeyEx(VK_ESCAPE & 0xFF, MAPVK_VK_TO_VSC, 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 2);

	ip.ki.wVk = VK_ESCAPE; // virtual-key code for the LShift key
	//ip.ki.wScan = MapVirtualKey(VK_SHIFT, 0);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	//WaitForInputIdle(GetCurrentProcess(), milliSeconds * 30); // Too smart for RDP session :(
	Sleep(milliSeconds * 2);

	return 0;
}

int Press_Down(int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = 0x50; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.wVk = VK_DOWN;
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	ip.ki.wVk = VK_DOWN;
	ip.ki.wScan = 0x50; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	return 0;
}
int Press_Up(int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = 0x48; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.wVk = VK_UP;
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	ip.ki.wVk = VK_UP;
	ip.ki.wScan = 0x48; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	return 0;

}
int Press_Right(int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = 0x4D; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.wVk = VK_RIGHT;
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	ip.ki.wVk = VK_RIGHT;
	ip.ki.wScan = 0x4D; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	return 0;
}
int Press_Left(int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = 0x4B; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.wVk = VK_LEFT;
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	ip.ki.wVk = VK_LEFT;
	ip.ki.wScan = 0x4B; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	return 0;
}

int Press_PageDown(int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = 0x51; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.wVk = VK_NEXT;
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	ip.ki.wVk = VK_NEXT;
	ip.ki.wScan = 0x51; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	return 0;
}
int Press_PageUp(int milliSeconds) {

	INPUT ip;
	HKL HKLCurrentLayout = GetKeyboardLayout(0);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press Shift key
	ip.ki.wScan = 0x49; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.wVk = VK_PRIOR;
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	ip.ki.wVk = VK_PRIOR;
	ip.ki.wScan = 0x49; // See: Hardware Key Code (NOT VK CODE!!!!)
	ip.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(milliSeconds * 3);

	return 0;
}
