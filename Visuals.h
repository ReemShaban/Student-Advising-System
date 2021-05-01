#ifndef Visuals_h
#define Visuals_h

#include "Functions.h"

///////////////////////////////////////////////////////////////////////////////////////////

class Menu {
public:
	string Title;
	vector<string> Options;
	int SelectedIndex;

	Menu(string _Title = "", vector<string> _Options = vector<string>());
	void AddItem(string _Item);
	void RemoveItem(int _Index);
	int Show(bool _NewPage = true);
};

///////////////////////////////////////////////////////////////////////////////////////////

string ShowAppLogo();
void ShowSplashScreen();
void ShowGoodBye();

#endif
