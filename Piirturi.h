#pragma once
//#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#undef max
#else
#include <climits>
#define TCHAR char
#endif

class Piirturi
{
public:
	const bool ShowCounts;
	const int bottomNegatives;
	const int width;
	const int height;
	const int size;
	const int CompDelay;
	const int CopyDelay;
	int PrevPivot{ -1 };
	int CompCount{ 0 };
	int WriteCount{ 0 };
	const char varsi;
	const char piste;
#ifdef _WIN32
	HANDLE hStdout;
#endif
private:
	TCHAR* data = nullptr;

public:
	Piirturi(const int Wid, const int Hei, const int bot, const int delay1,
		const int delay2, bool counts = true);
	Piirturi(const Piirturi&) = delete;
	Piirturi& operator=(const Piirturi&) = delete;
	~Piirturi();

	void Reset();
	void Redraw(bool clrScr = false) const;
	void PutText(const int x, int y, const char* text);
	void PutCounts();
	void PutHorLine(const int row, const char merkki, const int left = 0, int right = INT_MAX);
	void ResetRow(const int reference[], const int row, const int left = 0, int right = INT_MAX);
	void PutHorLineGently(const int row, const char merkki, const int left = 0, int right = INT_MAX);
	void PutVertLine(const int col, const char merkki, const int bottom = 0, int top = INT_MAX);
	TCHAR& at(const int col, int row);
	void Tolppa(int x, int y);
};
