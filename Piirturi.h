#pragma once
#include <iostream>
#include <Windows.h>
#undef max

class Piirturi
{
public:
	const bool ShowCounts;
	const int bottomNegatives;
	const int width;
	const int height;
	const int size;
	char huti;
	const char varsi;
	const char piste;
	const int CompDelay;
	const int CopyDelay;
	int PrevPivot{ -1 };
	int CompCount{ 0 };
	int WriteCount{ 0 };
	HANDLE hStdout;
private:
	char* data = nullptr;
	// LPWSTR data;
	// TCHAR* data;

public:
	Piirturi(const int Wid, const int Hei, const int bot, const int delay1,
		const int delay2, bool counts = true);
	Piirturi(const Piirturi&) = delete;
	Piirturi& operator=(const Piirturi&) = delete;
	~Piirturi();

	void Reset();
	void Redraw() const;
	void PutText(const int x, int y, const char* text);
	void PutCounts();
	void PutHorLine(const int row, const char merkki, const int left = 0, int right = INT_MAX);
	void ResetRow(const int reference[], const int row, const int left = 0, int right = INT_MAX);
	void PutHorLineGently(const int row, const char merkki, const int left = 0, int right = INT_MAX);
	void PutVertLine(const int col, const char merkki, const int bottom = 0, int top = INT_MAX);
	char& at(const int col, int row);
	void Tolppa(int x, int y);
	void cls(bool forReal = false) const;
};
