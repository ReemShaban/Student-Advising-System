#include "Visuals.h"

///////////////////////////////////////////////////////////////////////////////////////////

Menu::Menu(string _Title, vector<string> _Options) {
	Title = _Title;
	Options = _Options;
	SelectedIndex = -1;
}

void Menu::AddItem(string _Item) {
	Options.insert(Options.end(), _Item);
}

void Menu::RemoveItem(int _Index) {
	Options.erase(Options.begin() + _Index);
}

int Menu::Show(bool _NewPage) {
	while (int(Options.size()) > 0)
	{
		if (SelectedIndex >= int(Options.size())) {
			SelectedIndex = int(Options.size()) - 1;
		}
		else if (SelectedIndex < 0) {
			SelectedIndex = 0;
		}

		if (_NewPage) {
			system("cls");
			ShowAppLogo();
		}
		
		cout << endl;
		cout << AllignString(("[" + Title + "]"), Allign_Center) << endl;
		cout << AllignString("Please select an option", Allign_Center) << endl;
		cout << AllignString("----------------------------------", Allign_Center) << endl;
		cout << endl;

		for (int i = 0; i < Options.size(); i++) {
			if (i == SelectedIndex) {
				cout << AllignString(SelectedString(Options[i]), Allign_Center, 10) << endl;
			}
			else
			{
				cout << AllignString(Options[i], Allign_Center) << endl;
			}
		}

		int Sel = Input();
		if (Sel == Key_Down) {
			SelectedIndex++;
		}
		else if (Sel == Key_Up) {
			SelectedIndex--;
		}
		else if (Sel == Key_Enter) {
			return SelectedIndex;
		}
		else if (Sel == Key_Backspace || Sel == Key_ESC) {
			return -2;
		}
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////

string ShowAppLogo() {
	int SCWidth = int(GetScreenSize().X);
	
	string Logo = "\n\n";
	for (int i = 0; i < SCWidth; i++) Logo += "=";
	Logo += "\n";

	Logo += (AllignString("  ______        _____                                          _       _  _                   ___    ___", Allign_Center, -1) + "\n");
	Logo += (AllignString(" |  ____|      |  __ \\                                        (_)     (_)| |                 / _ \\  / _ \\ ", Allign_Center, 0) + "\n");
	Logo += (AllignString(" | |__  ______ | |__) | _ __   ___   _ __   ___   __ _  _   _  _  ___  _ | |_   ___  ______ | (_) || (_) |", Allign_Center, 0) + "\n");
	Logo += (AllignString(" |  __||______||  ___/ | '__| / _ \\ | '__| / _ \\ / _` || | | || |/ __|| || __| / _ \\|______| \\__, | \\__, |", Allign_Center, 0) + "\n");
	Logo += (AllignString(" | |____       | |     | |   |  __/ | |   |  __/| (_| || |_| || |\\__ \\| || |_ |  __/           / /    / /", Allign_Center, 0) + "\n");
	Logo += (AllignString(" |______|      |_|     |_|    \\___| |_|    \\___| \\__, | \\__,_||_||___/|_| \\__| \\___|          /_/    /_/", Allign_Center, -1) + "\n");
	Logo += (AllignString("                                                    | |", Allign_Center, -25) + "\n");
	Logo += (AllignString("                                                    |_|", Allign_Center, -25) + "\n");

	for (int i = 0; i < SCWidth; i++) Logo += "=";
	Logo += "\n\n";

	cout << Logo;
	return Logo;
}

void ShowSplashScreen() {
	system("cls");
	cout << "Nile Universty Elite CS Team Production," << endl;
	cout << "A Fall 2019 CSCI207 Project." << endl;
	cout << endl << endl << endl << endl << endl;
	ShowAppLogo();
	cout << endl << AllignString("Initializing System ...", Allign_Center) << endl << endl << endl;
}

void ShowGoodBye() {
	system("cls");
	cout << endl;
	cout << endl;
	cout << endl << endl << endl << endl << endl;
	ShowAppLogo();
	cout << endl << AllignString("Created by Nile Universty Elite CS Team" , Allign_Center) << endl;
	Delay(1000);
	exit(0);
}

