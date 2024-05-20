#include <limits>
#include <iostream>
#include <cstdio>
#include <memory>
#include "sleep.h"
#include "Piirturi.h"
#include "Randomizer.h"
#include "QuickSort.h"
#include "InsertSort.h"
#include "MergeSort.h"

int ParseNumber(const char* arg)
{
	int result{ -1 };
	if ( '0' <= arg[0] && arg[0] <= '9' )
	{
		try { result = std::atoi(arg); }
		catch ( ... ) { }
	}
	return result;
}

int main(int argc, char** argv)
{
	try
	{	
		int lukuja = 100;
		int maxValue{ 24 };
		const int bottomMargin{ 2 };
		int CompDelay = 3;

		int *arguments[]{ nullptr, &CompDelay, &lukuja, &maxValue };
		for ( int i = 1; i < argc; ++i )
			if ( int temp = ParseNumber(argv[i]); temp >= 0 )
				*arguments[i] = temp;

		int writeDelay = CompDelay*1;
		const int insertSortThreshold{ 8 };

		Piirturi p{ lukuja, maxValue, bottomMargin, CompDelay, writeDelay, true };
		Randomizer dist(lukuja, maxValue);

		int* arr{ new int[lukuja] };
		std::unique_ptr<int[]> arrptr{ arr };
		bool firstRound{ 1 };

		while (1)
		{
			int bonus{ 0 };
			int arpa = 1 + rand() % 41;

			if (arpa <= 2) { dist.sawTeeth(arr, 2); }			// 2
			else if (arpa <= 4) { dist.sawTeeth(arr, -3); }		// 2
			else if (arpa <= 6) { dist.staircase(arr, 8); }		// 2
			else if (arpa <= 16) { dist.straight(arr); }		// 10
			else if (arpa <= 24) { dist.rnd(arr); }				// 8
			else if (arpa <= 25) { dist.rot1(arr); }			// 1
			else if (arpa <= 26) { dist.rotMinus1(arr); }		// 1
			else if (arpa <= 27) { dist.circle(arr, rand() % 2); }// 1
			else if (arpa <= 29) { dist.sinusoid(arr, 1.0L); }	// 1
			else if (arpa <= 29) { dist.sinusoid(arr, -0.8L); }	// 1
			else if (arpa <= 32) { dist.qube(arr); }			// 3
			else if (arpa <= 35) { dist.sqrt(arr); }			// 3
			else if (arpa <= 39) {
				dist.almost(arr, 3 + rand()%9);
				bonus = 3;
			}													// 4
			else { dist.gaussian(arr, 0.16L); }					// 2
			

			for (int i = 0; i < lukuja; i++)
			{
				p.Tolppa(i, arr[i]);
			}
			p.Redraw(true);

			if (firstRound)
			{
				printf("\rThis is how tall the text will be. Press Return to begin.");
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				for (int i = 0; i < lukuja; i++) { p.Tolppa(i, arr[i]); }
				firstRound = false;
				p.Redraw(true);
			}
			Sleep(1000);

			arpa = 1 + rand() % (10+bonus);
			if (arpa <= 5) { Quicksort(arr, 0, lukuja - 1, p, insertSortThreshold * (rand() % 2)); }
			else if ( arpa <= 8 ) { MergeSort(arr, 0, lukuja - 1, p, (insertSortThreshold + 4) * (rand() % 2)); }
			else if ( arpa <= 9 ) { QMergeSort(arr, 0, lukuja - 1, p, (insertSortThreshold + 4) * (rand() % 2)); }
			else { InsertSort(arr, 0, lukuja - 1, p); }
			
			//Quicksort(arr, 0, lukuja - 1, p, insertSortThreshold);
			//QMergeSort(arr, 0, lukuja - 1, p, 0);
			//MergeSort(arr, 0, lukuja - 1, p, insertSortThreshold + 4);
			//InsertSort(arr, 0, lukuja - 1, p);

			p.Reset();
			Sleep(1000);
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "\nYeggog: " << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "\nYeggog: Tuntematon virhe" << std::endl;
	}
}
