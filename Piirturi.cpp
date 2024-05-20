#include <cassert>
#include <cstdio>
#include "Piirturi.h"


Piirturi::Piirturi(const int Wid,
                   const int Hei,
                   const int bot,
                   const int delay1,
                   const int delay2,
                   bool counts)
	:  ShowCounts{ counts },
	  bottomNegatives{ bot + (ShowCounts ? 2 : 0) },
	  width{ Wid + 1 },
	  height{ Hei + bottomNegatives + 1 },
	  size{ width * height },
	//   huti{ '\0' },
	  CompDelay{ delay1 },
	  CopyDelay{ delay2 },
	  varsi{ '|' },
	  piste{ '*' },
#ifdef _WIN32
	hStdout{ GetStdHandle(STD_OUTPUT_HANDLE) },
#endif
	data{ new TCHAR[size] }
{
	Reset();
};

Piirturi::~Piirturi()
{
	if ( data != nullptr )
	{
		delete[] data;
		data = nullptr;
	}
}

void Piirturi::Reset()
{
	for ( int i = 0; i < size - 1; ++i )
	{
		if ( i % width == width - 1 )
			data[i] = '\n';
		else
			data[i] = ' ';
	}
	data[size - 1] = '\0';
	PutHorLine(0, '-');
	CompCount = WriteCount = PrevPivot = 0;
}

void Piirturi::PutText(const int x, int y, const char* text)
{
	auto* cursor = &at(x, y);
	for ( int i = 0; text[i] != '\0' && *cursor != '\0';)
	{
		if ( text[i] == '\n' )
		{
			if ( --y < -bottomNegatives )
				return;
			
			cursor = &at(x, y);
			++i;
			continue;
		}
		
		if ( *cursor == '\n' )
		{
			if ( --y < -bottomNegatives )
				return;

			cursor = &at(0, y);
			continue;
		}
		
		*cursor++ = text[i++];
	}
}

void Piirturi::PutCounts()
{
	char s[50]{0};
#ifdef _WIN32
	sprintf_s(s, 50, "Comparisons: %d\nWrites:      %d", CompCount, WriteCount);
#else
	snprintf(s, 50, "Comparisons: %d\nWrites:      %d", CompCount, WriteCount);
#endif
	PutText(0, -3, s);
}

void Piirturi::PutHorLine(const int row, const char merkki, const int left, int right)
{
	if ( right > width - 2 )
		right = width - 2;

	for ( int i = left; i <= right; ++i )
		at(i, row) = merkki;

}

void Piirturi::ResetRow(const int reference[], const int row, const int left, int right)
{
	if ( right > width - 2 )
		right = width - 2;
	
	for ( int i = left; i <= right; ++i )
	{
		if ( reference[i] > row )
			at(i, row) = varsi;
		else if ( reference[i] < row )
			at(i, row) = ' ';
		else
			at(i, row) = piste;
	}
}

void Piirturi::PutHorLineGently(const int row, const char merkki, const int left, int right)
{
	if ( right > width - 2 )
		right = width - 2;
	
	for ( int i = left; i <= right; ++i )
	{
		auto& slot = at(i, row);
		if ( slot != piste )
			slot = merkki;
	}
}

void Piirturi::PutVertLine(const int col, const char merkki, const int bottom, int top)
{
	if ( top > height - bottomNegatives - 1 )
		top = height - bottomNegatives - 1;
	
	for ( int i = bottom; i <= top; ++i )
	{
		if ( i == PrevPivot )
			at(col, i) = '-';
		else
			at(col, i) = merkki;
	}
}

TCHAR& Piirturi::at(const int col, int row)
{
	row = height - row - 1 - bottomNegatives;

	assert(row >= 0);
	assert(row < height);
	assert(col >= 0);
	assert(col < width - 1);

	return data[row * width + col];
}

void Piirturi::Tolppa(int x, int y)
{
	at(x, y) = piste;
	PutVertLine(x, varsi, 1, y - 1);
	PutVertLine(x, ' ', y + 1);
}

void Piirturi::Redraw(bool clear) const
{
#ifdef _WIN32
	COORD coordScreen = { 0, 0 }; // home for the cursor 

	// Put the cursor at its home coordinates.
	SetConsoleCursorPosition(hStdout, coordScreen);

	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 
	if ( !GetConsoleScreenBufferInfo(hStdout, &csbi) )
		return;

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if ( clear )
	{
		// Fill the entire screen with blanks.
		if ( !FillConsoleOutputCharacter(hStdout, (TCHAR)' ',
			dwConSize, coordScreen, &cCharsWritten) )
			return;

		// // Get the current text attribute.
		// if ( !GetConsoleScreenBufferInfo(hStdout, &csbi) )
		// 	return;

		// // Set the buffer's attributes accordingly.
		// if ( !FillConsoleOutputAttribute(hStdout, csbi.wAttributes,
		// 	dwConSize, coordScreen, &cCharsWritten) )
		// 	return;
	}

	WriteConsole(hStdout, data, size, &cCharsWritten, NULL);
#else
	if ( clear )
		printf("\033c");
	printf("\x1b[H");
	printf("%s", data);
#endif
}
