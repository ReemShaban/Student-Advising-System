#include "Helper.h"
#include "Functions.h"

Size::Size(double _X, double _Y) {
	X = _X;
	Y = _Y;
}

///////////////////////////////////////////////////////////////////////////////////////////

Settings::Settings(int _Forecolor, int _Backcolor, string _HashedPassword) {
	Forecolor = _Forecolor;
	Backcolor = _Backcolor;
	Password = _HashedPassword;
}

void Settings::Save(string _Filename) {
    vector<string>values;
   
    values.push_back(to_string(Forecolor));
    values.push_back(to_string(Backcolor));
    values.push_back(Password);

    string Settings = CombineStrings(values, '~');

    ofstream myfile;
    myfile.open(_Filename);
    myfile << Settings;
    myfile.close();
}

bool Settings::Load(string _Filename) {
    ifstream FilePointer;
    FilePointer.open(_Filename);
    if (FilePointer.fail()) return false;

    string data;
    getline(FilePointer, data);
    vector<string> SettingTokens = SplitString(data, '~');

    Forecolor = stoi(SettingTokens[0]);
    Backcolor = stoi(SettingTokens[1]);
    Password = SettingTokens[2];

    FilePointer.close();
    return true;
}