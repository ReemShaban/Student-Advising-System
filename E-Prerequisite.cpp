#include "Pages.h"

////////////////////////////////////////////////////////////////////////////// Section-1

bool Initialize();

////////////////////////////////////////////////////////////////////////////// Section-2

int main() {
	if (Initialize()) {
		Menu MainMenu("Main Menu");
		MainMenu.AddItem("Queries");
		MainMenu.AddItem("Courses Managment");
		MainMenu.AddItem("Students Managment");
		MainMenu.AddItem("Settings");
		MainMenu.AddItem("About Us");
		MainMenu.AddItem("Exit System");

		while (true)
		{
			switch (MainMenu.Show())
			{
			case 0:
				ShowQueries();
				break;

			case 1:
				ShowCoursesManagment();
				break;

			case 2:
				ShowStudentsManagment();
				break;

			case 3:
				ShowSettings();
				break;

			case 4:
				ShowAboutUs();
				break;

			case 5:
				ShowGoodBye();
				break;

			default:
				continue;
			}
		}
	}
	else
	{
		cout << endl << ColorString(">> An error occured while initializing the system.", Red) << endl;
		system("pause");
	}

	return 0;
}

bool Initialize() {
	SetSceenSize(int(WindowSize.X), int(WindowSize.Y));
	system("title E-Prerequisite-99 System V1.0");
	SetScreenColor(AppSettings.Forecolor, AppSettings.Backcolor);
	bool Init = true;

	ShowSplashScreen();

	if (AppSettings.Load()) {
		SetScreenColor(AppSettings.Forecolor, AppSettings.Backcolor);

		if (AppCoursesTree->Load() && AppStudentsList->Load()) {
		Re_Password:
			string Password = "";
			while (true)
			{
				ShowSplashScreen();

				cout << "> Please enter your password to continue: " << MaskString(Password);
				int TCh = Input();
				if (TCh == Key_Backspace) {
					if (Password.length() > 0) Password = Password.substr(0, Password.length() - 1);
				}
				else if (TCh == Key_Enter && Password.length() > 0) {
					break;
				}
				else {
					if (TCh != Key_Enter && TCh != Key_Tab && TCh != Key_ESC) {
						Password += TCh;
					}
				}
			}

			if (HashString(Password) == AppSettings.Password) {
				return true;
			}
			else
			{
				cout << endl << ColorString(">> Incorrect password, please check you input and try again.", Red) << endl;
				system("timeout 5");
				goto Re_Password;
			}
		}
	}

	return false;
}