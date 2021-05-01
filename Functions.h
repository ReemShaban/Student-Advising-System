#ifndef Functions_h
#define Functions_h

#include "Helper.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include <windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

////////Definitions
#define Black   0
#define Red     1
#define Green   2
#define Yellow  3
#define Blue    4
#define Magenta 5
#define Cyan    6
#define White   7

#define Allign_Left   -1
#define Allign_Center  0
#define Allign_Right   1

#define Key_Up        328
#define Key_Down      336
#define Key_Left      331
#define Key_Right     333
#define Key_Tab       9
#define Key_Enter     13
#define Key_Backspace 8
#define Key_ESC       27
#define Key_Decimal	  46

#define Key_0		  48
#define Key_1		  49
#define Key_2		  50
#define Key_3		  51
#define Key_4		  52
#define Key_5		  53
#define Key_6		  54
#define Key_7		  55
#define Key_8		  56
#define Key_9		  57

////////Declarations
extern Size WindowSize;
extern Settings AppSettings;

////////Prototypes
string AllignString(string String, int Allignment = 0, int Offset = 0);
vector<string> SplitString(string String, char Delimeter);
string CombineStrings(vector<string> Tokens, char Delimeter);
string MaskString(string String, char Mask = '*');
string HashString(string String);
string ColorString(string String, int Forecolor);
string HighlightString(string String, int Backcolor);
string SelectedString(string String, int Forecolor = AppSettings.Backcolor, int Backcolor = AppSettings.Forecolor);
string MulString(string String, int Count);
void ReplaceAllString(string& String, string Find, string Replace);
int GetMiddle(int Length);

void SetSceenSize(int Width, int Height);
Size GetScreenSize();
void SetScreenColor(int Forground, int Background);
void Delay(unsigned int Millis);
int Input();
string InputField(string Label, string& Screen, string Default = "", bool Password = false, bool NumericOnly = false);
string ComboBox(string Label, string& Screen, vector<string> Items, string Default = "", bool ForceUseItems = false, bool Optional = true);
int Choice(string Label, string& Screen, vector<int> Choices);

////////Definitions
template<class T> void VectorSwap(T* E1, T* E2) {
	T TEV = *E1;
	*E1 = *E2;
	*E2 = TEV;
}

template<class T> bool VectorContain(T Element, vector<T> Vector) {
	return find(Vector.begin(), Vector.end(), Element) != Vector.end();
}
#endif
