#include "Functions.h"


Size WindowSize(140, 35);
Settings AppSettings(7, 0, "2110877786");

void SetSceenSize(int Width, int Height) {
	CONSOLE_SCREEN_BUFFER_INFO Screen; //Declare the screen handler.
	system(("mode con: cols=" + to_string(Width) + " lines=" + to_string(Height)).c_str());
}

Size GetScreenSize() {
	Size ScreenSize;
	CONSOLE_SCREEN_BUFFER_INFO Screen; //Declare the screen handler.

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Screen); //Retrieve screen information to the screen handler.
	ScreenSize.X = double(Screen.srWindow.Right) - double(Screen.srWindow.Left) + 1.0; //Set the screen width.
	ScreenSize.Y = double(Screen.srWindow.Bottom) - double(Screen.srWindow.Top) + 1.0; //Set the screen height.

	return ScreenSize;
}

void SetScreenColor(int Forground, int Background) {
	cout << string("\x1b[3" + to_string(Forground) + "m\x1b[4" + to_string(Background) + "m").c_str();
}

void Delay(unsigned int Millis)
{
	clock_t goal = Millis + clock(); //Set the required resume point.
	while (goal > clock()); //Loop until resume point is achieved.
}

int Input() {
	int Char = _getch();
	if (Char == 0 || Char == 224) Char = 256 + _getch();
	return Char;
}

string InputField(string Label, string& Screen, string Default, bool Password, bool NumericOnly) {
	string Text = Default;
	while (true) {
		system("cls");
		cout << Screen;

		cout << (Label + ": ") << (Password ? MaskString(Text) : Text);

		int TCh = Input();
		if (TCh == Key_Backspace) {
			if (Text.length() > 0) Text = Text.substr(0, Text.length() - 1);
		}
		else if (TCh == Key_Enter && Text.length() > 0) {
			break;
		}
		else if (TCh == Key_ESC) {
			return to_string(-2);
		}
		else if (TCh != Key_Enter && TCh != Key_Tab && TCh != Key_ESC) {
			if (!NumericOnly) {
				Text += TCh;
			}
			else
			{
				switch (TCh)
				{
				case Key_0:
				case Key_1:
				case Key_2:
				case Key_3:
				case Key_4:
				case Key_5:
				case Key_6:
				case Key_7:
				case Key_8:
				case Key_9:
				case Key_Decimal:
					Text += TCh;
					break;
				}
			}
		}
	}
	
	return Text;
}

string ComboBox(string Label, string& Screen, vector<string> Items, string Default, bool ForceUseItems, bool Optional) {
	string Text = Default;
	int Sel = 0;

	while (true) {
		system("cls");
		cout << Screen;

		cout << (Label + ": " + Text);

		vector<string> Suggests;
		if (Text.length() > 0) {
			int TCount = 0;
			for (int i = 0; i < Items.size(); i++) {
				string TItem = Items[i];
				transform(TItem.begin(), TItem.end(), TItem.begin(), ::tolower);

				string TText = Text;
				transform(TText.begin(), TText.end(), TText.begin(), ::tolower);

				if (TItem.rfind(TText, 0) == 0) {
					Suggests.insert(Suggests.end(), Items[i]);
					cout << endl << ("     " + (TCount == Sel ? SelectedString(Items[i]) : Items[i]));
				}

				TCount++;
			}
		}

		int TCh = Input();
		if (TCh == Key_Down) {
			Sel++;
		}
		else if (TCh == Key_Up) {
			Sel--;
		}
		else if (TCh == Key_Tab && Suggests.size() > 0) {
			Text = Suggests[Sel];
			break;
		}
		else if (TCh == Key_Backspace) {
			if (Text.length() > 0) Text = Text.substr(0, Text.length() - 1);
			Sel = 0;
		}
		else if (TCh == Key_Enter) {
			if (Text.length() > 0) {
				if (!ForceUseItems || VectorContain(Text, Items)) break;
			}
			else if (Optional)
			{
				break;
			}
		}
		else if (TCh == Key_ESC) {
			return to_string(-2);
		}
		else if (TCh != Key_Enter && TCh != Key_Tab && TCh != Key_ESC) {
			Text += TCh;
			Sel = 0;
		}

		int SuggestsCount = (int(Suggests.size()) - 1);
		if (SuggestsCount < 0) SuggestsCount = 0;
		if (Sel > SuggestsCount) {
			Sel = SuggestsCount;
		}
		else if (Sel < 0) {
			Sel = 0;
		}
	}

	system("cls");
	cout << Screen;
	cout << (Label + ": " + Text);

	return Text;
}

int Choice(string Label, string& Screen, vector<int> Choices) {
	while (true) {
		system("cls");
		cout << Screen << Label;

		int TCh = Input();
		if (TCh == Key_ESC) {
			return -2;
		}
		else if (TCh != Key_Enter && TCh != Key_Tab && TCh != Key_ESC) {
			if (VectorContain(toupper(TCh), Choices) || VectorContain(tolower(TCh), Choices)) return TCh;
		}
	}
}

string AllignString(string String, int Allignment, int Offset) {
	int Allign_Offset = 0;
	if (Allignment == 0) Allign_Offset = int(((GetScreenSize().X - String.length()) / 2) + Offset);
	if (Allignment == 1) Allign_Offset = int((GetScreenSize().X - String.length()) + Offset);
	
	string Alligned = "";
	for (int i = 0; i < Allign_Offset; i++) Alligned += " ";
	Alligned += String;

	return Alligned;
}

vector<string> SplitString(string String, char Delimeter) {
	vector<string> Tokens;

	string TStr = "";
	for (int i = 0; i < String.length(); i++) {
		if (String[i] == Delimeter) {
			Tokens.insert(Tokens.end(), TStr);
			TStr = "";
		}
		else
		{
			TStr += String[i];
		}
	}

	Tokens.insert(Tokens.end(), TStr);

	return Tokens;
}

string CombineStrings(vector<string> Tokens, char Delimeter) {
	string String = "";

	for (int i = 0; i < Tokens.size(); i++) {
		if (String != "") String += Delimeter;
		String += Tokens[i];
	}

	return String;
}

string MaskString(string String, char Mask) {
	string Masked = "";
	for (int i = 0; i < String.length(); i++) Masked += Mask;
	return Masked;
}

string HashString(string String) {
	unsigned int Hashed = 5381;
	unsigned char* Str;

	Str = (unsigned char*)String.c_str();
	while (*Str != '\0') {
		Hashed = (Hashed << 5) + Hashed + *Str;
		++Str;
	}

	return to_string(Hashed);
}

string ColorString(string String, int Forecolor) {
	return ("\x1b[3" + to_string(Forecolor) + "m" + String + "\x1b[3" + to_string(AppSettings.Forecolor) + "m"); //Retured colored string.
}

string HighlightString(string String, int Backcolor) {
	return ("\x1b[4" + to_string(Backcolor) + "m" + String + "\x1b[4" + to_string(AppSettings.Backcolor) + "m"); //Retured colored string.
}

string SelectedString(string String, int Forecolor, int Backcolor) {
	return HighlightString(ColorString(String, Forecolor), Backcolor);
}

string MulString(string String, int Count) {
	string Result = "";
	for (int i = 0; i < Count; i++) {
		Result += String;
	}
	return Result;
}

void ReplaceAllString(string& String, string Find, string Replace)
{
	size_t pos = String.find(Find);
	while (pos != std::string::npos)
	{
		String.replace(pos, Find.size(), Replace);
		pos = String.find(Find, pos + Replace.size());
	}
}

int GetMiddle(int Length) {
	int Middle = Length;
	if (Length % 2 == 0) {
		Middle = ((int)(Length / 2));
	}
	else
	{
		Middle = ((int)(Length / 2)) + 1;
	}

	return Middle;
}