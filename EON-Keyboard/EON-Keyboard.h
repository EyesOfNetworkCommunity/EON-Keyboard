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
#include "vKeyboardCode.h"
#include <string> 
using namespace std;

int Version = 1;
int Subversion = 0;

int Usage();
int KeyString(CString strToPress);
int MoveMouse(int x, int y);
int ClickMouse(int WantedButton, int NumberOfClick);

/* Number Function (AZERTY)*/
int Press_0(int milliSeconds);
int Press_1(int milliSeconds);
int Press_2(int milliSeconds);
int Press_3(int milliSeconds);
int Press_4(int milliSeconds);
int Press_5(int milliSeconds);
int Press_6(int milliSeconds);
int Press_7(int milliSeconds);
int Press_8(int milliSeconds);
int Press_9(int milliSeconds);

/* Letter functions */
int Press_A(int milliSeconds);
int Press_a(int milliSeconds);
int Press_B(int milliSeconds);
int Press_b(int milliSeconds);
int Press_C(int milliSeconds);
int Press_c(int milliSeconds);
int Press_D(int milliSeconds);
int Press_d(int milliSeconds);
int Press_E(int milliSeconds);
int Press_e(int milliSeconds);
int Press_F(int milliSeconds);
int Press_f(int milliSeconds);
int Press_G(int milliSeconds);
int Press_g(int milliSeconds);
int Press_H(int milliSeconds);
int Press_h(int milliSeconds);
int Press_I(int milliSeconds);
int Press_i(int milliSeconds);
int Press_J(int milliSeconds);
int Press_j(int milliSeconds);
int Press_K(int milliSeconds);
int Press_k(int milliSeconds);
int Press_L(int milliSeconds);
int Press_l(int milliSeconds);
int Press_M(int milliSeconds);
int Press_m(int milliSeconds);
int Press_N(int milliSeconds);
int Press_n(int milliSeconds);
int Press_O(int milliSeconds);
int Press_o(int milliSeconds);
int Press_P(int milliSeconds);
int Press_p(int milliSeconds);
int Press_Q(int milliSeconds);
int Press_q(int milliSeconds);
int Press_R(int milliSeconds);
int Press_r(int milliSeconds);
int Press_S(int milliSeconds);
int Press_s(int milliSeconds);
int Press_T(int milliSeconds);
int Press_t(int milliSeconds);
int Press_U(int milliSeconds);
int Press_u(int milliSeconds);
int Press_V(int milliSeconds);
int Press_v(int milliSeconds);
int Press_W(int milliSeconds);
int Press_w(int milliSeconds);
int Press_X(int milliSeconds);
int Press_x(int milliSeconds);
int Press_Y(int milliSeconds);
int Press_y(int milliSeconds);
int Press_Z(int milliSeconds);
int Press_z(int milliSeconds);

int Press_Space(int milliSeconds);
int Press_Comma(int milliSeconds);
int Press_SemiComma(int milliSeconds);
int Press_Dot(int milliSeconds);
int Press_DotWhat(int milliSeconds);
int Press_BackSlash(int milliSeconds);
int Press_SmallerThan(int milliSeconds);
int Press_GreaterThan(int milliSeconds);

/* Special Key */
int Press_Enter(int milliSeconds);
int Press_Tab(int milliSeconds);
int Press_Win(int milliSeconds);

/* Special Char */
int Press_Pound(int milliSeconds);
int Press_And(int milliSeconds);
int Press_Arobase(int milliSeconds);
int Press_Euro(int milliSeconds);

/* Math */
int Press_Add(int milliSeconds);
int Press_Substract(int milliSeconds);
int Press_Multiple(int milliSeconds);
int Press_Divide(int milliSeconds);