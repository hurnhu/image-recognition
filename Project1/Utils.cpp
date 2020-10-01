#include "Utils.h"

using namespace std;


vector<pair<string, HWND>> Utils::s;

/*
constructor: sets the current cursor pos to var p
*/
Utils::Utils()
{
	curPos(p);
	//	testVec.reserve(5);
}

//distructor: does nothing atm
Utils::~Utils()
{

}


/*
* fill the vector
*/
void Utils::fillVec(int pos, int speed, int lod, vector<COORD> ret)
{
	//create a varible seconds to make a random seed basied on current time
	time_t seconds = 0;


	srand((unsigned int)seconds);


	if (ret.size() > 0)
	{



		int rx = 0, ry = 0;
		//int ry = (rand() % 500 + 1);
		POINT p;
		INPUT buffer;

		if (pos == 0)
		{
			for (auto const& value : ret) {

				//get current time stamp and store it in seconds
				time(&seconds);

				/*
				Convert seconds to a unsigned
				integer. and use seconds as a seed for random
				*/
				srand((unsigned int)seconds);

				//populate random x
				 rx = (rand() % 500 + 1);

				 //populate random y
				 ry = (rand() % 500 + 1);

				 //get current cursor pos
				curPos(p);

				//add the current mouse pos as the very first point in the array
				Points.push_back(Point(p.x, p.y, 0));

				//need to explain this better have no idea what this is doing
				//it is adding points for some reason
				if (value.Y < p.y)
				{
					Points.push_back(Point(value.X - rx, value.Y - ry, 0));
					Points.push_back(Point(0, 0, 0));

				}
				else
				{
					Points.push_back(Point(0, 0, 0));

					Points.push_back(Point(value.X + rx, value.Y + ry, 0));
				}

				Points.push_back(Point(value.X, value.Y, 1));
				MouseMoveAbsolute(&buffer, speed, lod);
				Points.clear();
			}
		}
		else
		{
			//have no idea what the point of this is further testing required!
			curPos(p);
			Points.push_back(Point(p.x, p.y, 0));

			if (ret.at(pos).Y < p.y)
			{
				Points.push_back(Point(ret.at(pos).X - rx, ret.at(pos).Y - ry, 0));

			}
			else
			{

				Points.push_back(Point(ret.at(pos).X + rx, ret.at(pos).Y + ry, 0));
			}

			Points.push_back(Point(ret.at(pos).X, ret.at(pos).Y, 1));
			MouseMoveAbsolute(&buffer, speed, lod);
			Points.clear();
		}
	}
}


//setting up the a mouse for use
void Utils::MouseSetup(INPUT *buffer)
{
	//all these flags are required for setting up the mouse
	buffer->type = INPUT_MOUSE;
	buffer->mi.dx = (0 * (0xFFFF / SCREEN_WIDTH));
	buffer->mi.dy = (0 * (0xFFFF / SCREEN_HEIGHT));
	buffer->mi.mouseData = 0;
	buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	buffer->mi.time = 0;
	buffer->mi.dwExtraInfo = 0;
}


//make the vector unique!
void Utils::makeUnique()
{
	//print the size of the array
	cout << Points.size() << endl;
	
	//loop through the array
	for (size_t i = 0; i < Points.size(); i++)
	{

		//check to see if we are at the end of the array
		if (i + 1 < Points.size())
		{

			//if we are not at the end of the array.
			//check if if point x and point y in pos i and i + 1 are the same
			//if they are delete the second point
			if (Points.at(i).x == Points.at(i + 1).x && Points.at(i).y == Points.at(i + 1).y)
			{
				//delete the second dup point
				Points.erase(Points.begin() + i +1, Points.begin() + i+1);
			}

		}

	}

}


//function for moving the mouse
void Utils::MouseMoveAbsolute(INPUT *buffer, int speed, int lvOfLOD)
{

	//print the size of the array
	cout << "  " << Points.size() << endl;

	//wait for user input, this does nothing accept for letting the user see the size of the vec
	getchar();

	//loop through and increas the LOD accoring to what the user wants
	for (size_t i = 0; i < lvOfLOD; i++)
	{

		IncreaseLod();
	
	}


	makeUnique();
	cout << "  " << Points.size() << endl;
	getchar();

	//loop through the vec and move the mose to each new point
	for (size_t i = 0; i < Points.size(); i++)
	{

		//sleep for user defined time to slow down the mouse
		Sleep(speed);

		//move the mouse for each point in the vec
		MouseMove(Points.at(i).x, Points.at(i).y);


	//	cout << Points.at(i).z << " " << Points.at(i).x << " " << Points.at(i).y << " " << endl;
	//	if (Points.at(i).z == 1)
	//	{
	//		Sleep(700);
	//	}
	}

}


//move the mouse to a specific x y cords
void Utils::MouseMove(int x, int y)
{
	//get curr screen size X
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;

	//get curr screen size Y
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;

	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);

	//create an blank input and set it up and move the mouse to the points specified
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	::SendInput(1, &Input, sizeof(INPUT));
}

//simulate a mouse click at the current mouse pos
void Utils::MouseClick(INPUT *buffer)
{
	//press down
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, buffer, sizeof(INPUT));

	//wait
	Sleep(10);

	//release
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, buffer, sizeof(INPUT));
}

//move the mouse, takes some of the needless things away
void Utils::moveMouse(int pos, int speed, int lod, vector<COORD> ret)
{
	INPUT buffer;
	MouseSetup(&buffer);
//	fillVec(pos, ret);
	MouseMoveAbsolute(&buffer, speed, lod);
}

//get cur mouse pos
void Utils::curPos(POINT &p)
{

	GetCursorPos(&p);

}

void Utils::showHideCursor(bool tf)
{
	if (tf == true)
	{
		cout << "Tt" << endl;
		ShowCursor(FALSE);//hides the cursor
	}
	else {

		ShowCursor(TRUE);//shows it again
	}
}


void Utils::getAllWindows()
{
	int i = 0;

	::printf("Starting EnumWindows()\n");
	::EnumWindows(&MyEnumWindowsProc, reinterpret_cast<LPARAM>(&i));
	::printf("EnumWindows() ended\n");
}


BOOL CALLBACK Utils::MyEnumWindowsProc(HWND hwnd, LPARAM lparam)
{
	int& i = *(reinterpret_cast<int*>(lparam));
	++i;
	char title[256];
	::GetWindowText(hwnd, title, sizeof(title));
	::printf("Window #%d (%x): %s\n", i, hwnd, title);
	string test = title;
	s.push_back(make_pair(test, hwnd));
	return TRUE;
}

void Utils::print()
{
	sort(s.begin(), s.end(), [](const std::pair<string, HWND> &left, const std::pair<string, HWND> &right) {
		return left.first < right.first;
	});

	for (auto i = s.begin(); i != s.end(); ++i)
		cout << get<0>(*i) << ' ' << get<1>(*i) << endl;

}

void Utils::IncreaseLod()
{
	std::vector<Point> NewPoints;

	// keep the first point
	NewPoints.push_back(Points[0]);
	for (unsigned int i = 0; i < (Points.size() - 1); ++i) {

		// get 2 original points
		const Point& p0 = Points[i];
		const Point& p1 = Points[i + 1];
		Point Q;
		Point R;

		// average the 2 original points to create 2 new points. For each
		// CV, another 2 verts are created.
		Q.x = 0.75f*p0.x + 0.25f*p1.x;
		Q.y = 0.75f*p0.y + 0.25f*p1.y;

		R.x = 0.25f*p0.x + 0.75f*p1.x;
		R.y = 0.25f*p0.y + 0.75f*p1.y;
		Q.x = round(Q.x);
		Q.y = round(Q.y);

		R.x = round(R.x);
		R.y = round(R.y);
		NewPoints.push_back(Q);
		NewPoints.push_back(R);
	}
	// keep the last point

	NewPoints.push_back(Points[Points.size() - 1]);

	// update the points array
	Points = NewPoints;
}

void Utils::findIt(string serchVal)
{


	cout << serchVal << endl;
	getchar();
	int t = s.size();
	cout << t << endl;
	getchar();
	for (size_t i = 0; i < t; i++)
	{
		if (s.at(i).first.find(serchVal) != std::string::npos)
		{
			cout << "found it:  " << s.at(i).first << " " << s.at(i).second << endl;
			getchar();
		}
	}
}
