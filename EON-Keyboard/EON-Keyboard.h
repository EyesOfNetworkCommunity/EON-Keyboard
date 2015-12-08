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

#pragma once

#include "resource.h"
#include <string> 
using namespace std;

int Version = 1;
int Subversion = 0;

int Usage();
int KeyString(int TimeWait, CString strToPress);
int SpecialKeyString(int TimeWait, CString strToPress);

int MoveMouse(int x, int y);
int ClickMouse(int WantedButton, int NumberOfClick);
int WheelMouse(bool bDirection, int NumberWheel, int TimeWait);



/* Letter functions */
int Press_Letter(WCHAR letter, int milliSeconds);
int Press_UpperLetter(WCHAR letter, int milliSeconds);
int Press_ALTGRLetter(WCHAR AskedLetter, int milliSeconds);

/* Special Key */
int Press_Echap(int milliSeconds);
int Press_Enter(int milliSeconds);
int Press_Tab(int milliSeconds);
int Press_Win(int milliSeconds);
int Press_F1(int milliSeconds);
int Press_F2(int milliSeconds);
int Press_F3(int milliSeconds);
int Press_F4(int milliSeconds);
int Press_F5(int milliSeconds);
int Press_F6(int milliSeconds);
int Press_F7(int milliSeconds);
int Press_F8(int milliSeconds);
int Press_F9(int milliSeconds);
int Press_F10(int milliSeconds);
int Press_F11(int milliSeconds);
int Press_F12(int milliSeconds);

int Press_AltF4(int milliSeconds);
int Press_Ctrl_a(int milliSeconds);
int Press_Ctrl_c(int milliSeconds);
int Press_Ctrl_v(int milliSeconds);
int Press_Ctrl_x(int milliSeconds);
int Press_Ctrl_F5(int milliSeconds);


/* Direction keys */
int Press_Down(int milliSeconds);
int Press_Up(int milliSeconds);
int Press_Right(int milliSeconds);
int Press_Left(int milliSeconds);

int Press_PageDown(int milliSeconds);
int Press_PageUp(int milliSeconds);

/* Special Char */