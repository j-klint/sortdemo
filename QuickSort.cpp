#include <cstdlib>
#include <utility>
#include <time.h>
#include "sleep.h"
#include "QuickSort.h"
#include "InsertSort.h"

void Quicksort(int a[], const int alku, const int loppu, Piirturi& p, const int insertThreshold)
{
	int len{ loppu - alku + 1 };
	if (len <= 1) { return; }
	if (p.PrevPivot > 0) { p.ResetRow(a, p.PrevPivot); }

	if (len <=  insertThreshold)
	{
		p.PrevPivot = -1;
		InsertSort(a, alku, loppu, p);
		return;
	}

	int pivot;
	srand(static_cast<unsigned>(time(nullptr)));
	pivot = MedianOf3(a[alku + rand() % len], a[alku + rand() % len], a[alku + rand() % len], p);

	p.PrevPivot = pivot;
	p.PutHorLineGently(pivot, '-');
#ifdef TEKSTIT
	p.PutCounts();
#endif //TEKSTIT

	int index = Partition(a, pivot, alku, loppu, p);

	Quicksort(a, alku, index - 1, p, insertThreshold);
	Quicksort(a, index, loppu, p, insertThreshold);
}

int Partition(int a[], const int pivot, const int alku, const int loppu, Piirturi& p)
{
	int left{ alku }, right{ loppu };
	p.PutHorLine(0, '-');
	p.PutHorLine(0, '+', alku, loppu);
	p.PutHorLine(-1, ' ');
	p.PutHorLine(-2, ' ');
	p.at(left, -1) = '^';
	p.at(left, -2) = 'L';
	p.at(right, -1) = '^';
	p.at(right, -2) = 'R';
	p.Redraw();

	while (left < right && alku < right && left < loppu)
	{
		while (a[left] < pivot)
		{
			Sleep(p.CompDelay);
			IncrementL(left, p);
			if (p.ShowCounts)
			{
				++p.CompCount;
				p.PutCounts();
			}
			p.Redraw();
		}
		while (a[right] > pivot)
		{
			Sleep(p.CompDelay);
			DecrementR(right, p);
			if (p.ShowCounts)
			{
				++p.CompCount;
				p.PutCounts();
			}
			p.Redraw();
		}

		if (left < right)
		{
			Sleep(p.CompDelay);
			if (p.ShowCounts)
			{
				p.CompCount++;
				p.PutCounts();
			}
			if (true && a[left] > a[right])
			{
				std::swap(a[left], a[right]);
				p.Tolppa(left, a[left]);
				p.Tolppa(right, a[right]);
				if (p.ShowCounts)
				{
					p.WriteCount += 3;
					p.PutCounts();
				}
				Sleep(p.CopyDelay*3);
			}
			if (a[left] == pivot) { IncrementL(left, p); }
			if (a[right] == pivot && left + 1 < right) { DecrementR(right, p); }

			p.Redraw();
		}
	}

	if (left <= alku) { return alku + 1; }
	else if (left > loppu) { return loppu; }
	else { return left; }
}

void IncrementL(int& left, Piirturi& p)
{
	p.at(left, -1) = ' ';
	p.at(left, -2) = ' ';
	++left;
	if (left >= p.width - 1) { return; }
	p.at(left, -1) = '^';
	p.at(left, -2) = 'L';
}

void DecrementR(int& right, Piirturi& p, const char symbol)
{
	p.at(right, -1) = ' ';
	p.at(right, -2) = ' ';
	--right;
	if (right < 0) { return; }
	p.at(right, -1) = '^';
	p.at(right, -2) = symbol;
}

int MedianOf3(const int a, const int b, const int c, Piirturi& p)
{
	Sleep(p.CompDelay * 2);
	if (p.ShowCounts)
	{
		p.CompCount += 2;
		p.PutCounts();
	}
	if ((a > b) != (a > c))
	{
		return a;
	}
	else
	{
		Sleep(p.CompDelay * 2);
		if (p.ShowCounts)
		{
			p.CompCount += 2;
			p.PutCounts();
		}
		if ((b > a) != (b > c))
		{
			return b;
		}
		else return c;
	}
}
