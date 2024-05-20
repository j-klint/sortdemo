#include "sleep.h"
#include "InsertSort.h"

void InsertSort(int arr[], const int left, const int right, Piirturi& piirt)
{
	if (right <= left) { return; }

	piirt.PutHorLine(0, '-');
	piirt.PutHorLine(0, '+', left, right);
	piirt.PutHorLine(-2, ' ');

	for (int k = left+1; k <= right; ++k)
	{
		piirt.PutHorLine(-1, ' ');
		//piirt.at(k-1, -1) = '<';
		piirt.at(k, -1) = 'I';
		if (piirt.ShowCounts)
		{
			++piirt.CompCount;
			piirt.PutCounts();
		}
		Sleep(piirt.CompDelay);
		piirt.Redraw();

		if (arr[k] >= arr[k - 1])
		{
			continue;
		}

		int i{ k }, insertee{ arr[i] };

		while (i > left && insertee < arr[i - 1])
		{
			arr[i] = arr[i - 1];
			piirt.Tolppa(i, arr[i]);
			if (i <= k)
			{
				piirt.at(i-1, -1) = '^';
				if ( auto& m = piirt.at(i, -1); m == '^' ) { m = '-'; }
			}
			if (piirt.ShowCounts)
			{
				++piirt.WriteCount;
				++piirt.CompCount;
				piirt.PutCounts();
			}
			Sleep(piirt.CompDelay + piirt.CopyDelay);
			piirt.Redraw();
			--i;
		}

		arr[i] = insertee;
		piirt.Tolppa(i, arr[i]);
		if (piirt.ShowCounts) { piirt.PutCounts(); }
		Sleep(piirt.CopyDelay);
		piirt.Redraw();
	}
}
