#pragma once
#include <string.h>
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <time.h>
#define WIN32_LEAN_AND_MEAN
//#define _WIN32_WINNT 0x0500
#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 1080

//defining a struct, that will hold more information about a point
struct Point {

	/// the position in x, y, and z
	float x, y, z;

	/// ctor : default values for any new point
	Point() : x(0), y(0), z(0) {}

	/// ctor : idk what this is
	Point(const float a, const float b, const float c)
		:x(a), y(b), z(c) {}

	/// copy ctor : copy constructor
	Point(const Point& p) : x(p.x), y(p.y), z(p.z) {}
};

using namespace std;

class Utils
{

public:

	//constructor
	Utils();
	
	//destructor
	~Utils();

	//fill the vector with all points
	void fillVec(int pos, int speed, int lod, vector<COORD> ret);

	//setting up the mouse input buffer with required flags
	void MouseSetup(INPUT *buffer);

	//my attempt to make an vector unique, by removing all duplicates
	void makeUnique();


	//void MouseMoveAbsolute(INPUT *buffer, int x, int y);


	void MouseMoveAbsolute(INPUT *buffer, int speed, int lvOfLOD);

	//simulate a mouse click at the current mouse pos
	void MouseClick(INPUT *buffer);

	//move the mouse from your current position to the pos passed into ret
	//pos = 0
	//speed is how long the loop will wait before moving the mouse
	//lod is how many points will be in the array (kepe below 10)
	void moveMouse(int pos, int speed, int lod, vector<COORD> ret);

	/*
	*pass in a point by reference and it will populate that var
	*with the point the cursor is currently at
	*/
	void curPos(POINT &p);

	//possiby hide the cursor? accepts a true or false weather to show or hide it?
	void showHideCursor(bool tf);

	//enumurate through all of the windows. 
	void getAllWindows();


	//static vector <string> testVec;
	void findIt(string serchVal);

	//method to move the mouse to a specific x, y cords
	void MouseMove(int x, int y);

	//print everything in the s vector
	void print();

	//a point dont know what this is for
	POINT p;

	//increase the number of points in an array
	void IncreaseLod();

	/// a dynamic array of all points in the curve
	vector<Point> Points;


private:

	//WINAPI call for running enumerate windows
	static BOOL CALLBACK MyEnumWindowsProc(HWND hwnd, LPARAM lParam);

	//custom vac of pairs of strings then HWND.
	//this will be all windows names and HWND.
	static vector<pair<string, HWND>> s;

	//vector<pair<char, char>> vp;

};

