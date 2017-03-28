#pragma once
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>       // for memset
#define BYTESPERPIXEL 4
extern int SCREENWIDTH;
extern int SCREENHEIGHT;

//BOOL SaveToFile(HBITMAP hBitmap, LPCTSTR lpszFileName);
extern bool operator < (const COORD A, const COORD B);


struct RGBA
{
	char r;
	char g;
	char b;
	char a;
};
class ScreenShot
{
public:
	//Methods
	ScreenShot();
	
	~ScreenShot();

	std::vector<COORD> FindBMP(LPCTSTR testBMP);
	//allocates and returns a byte array of a subBMP

	RGBA getPixel(int x, int y);
	void GetDesktopResolution(int& horizontal, int& vertical);
	BOOL SaveToFile(HBITMAP hBitmap, LPCTSTR lpszFileName);
	BYTE* LoadBMP(int* width, int* height, long* size, LPCTSTR bmpfile);
	bool SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile);
	HBITMAP getSubBMP(int ulx, int uly, int brx, int bry);
	void TestBMPCopy2(LPCTSTR input, LPCTSTR output);
	void TestBMPCopy(LPCTSTR input, LPCTSTR output);
	BYTE * hbitmapToBytes(HBITMAP input);
	BYTE* ConvertRGBToBMPBuffer(BYTE* Buffer, int width, int height, long* newsize);
	BYTE* ConvertBMPToRGBBuffer(BYTE* Buffer, int width, int height);
	bool LoadBMPIntoDC(HDC hDC, LPCTSTR bmpfile);
private:
	//Methods
	BYTE * getBytes(int ulx, int uly, int brx, int bry);
	
	HBITMAP bitmapFromBytes(BYTE arr[], int width, int height);
	//Guts
	HDC desktophandle;
	HDC memHDC;
	HBITMAP Teemo;
	//LPVOID lpvBITBUF;
	BYTE* bmpBuffer;
};