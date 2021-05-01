#ifndef Helper_h
#define Helper_h

#include <string>

using namespace std;

class Size {
public:
	double X;
	double Y;

	Size(double _X = 0, double _Y = 0);
};

///////////////////////////////////////////////////////////////////////////////////////////

class Settings {
public:
	int Forecolor;
	int Backcolor;
	string Password;

	Settings(int _Forecolor = 7, int _Backcolor = 0, string _HashedPassword = "");
	void Save(string _Filename = "Settings");
	bool Load(string _Filename = "Settings");
};

#endif
