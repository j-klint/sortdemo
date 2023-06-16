#include <cassert>
#include "InsertSort.h"
#include "MergeSort.h"


void MergeSort(int arr[], const int left, const int right, Piirturi& piir, const int insertThreshold, int* aux)
{
	if (left >= right) { return; }

	if (right-left+1 <= insertThreshold)
	{
		InsertSort(arr, left, right, piir);
		return;
	}

	bool created{ aux == nullptr };
	if (created) { aux = new int[right - left + 1]; }

	int mid = (left + right) / 2;

	MergeSort(arr, left, mid, piir, insertThreshold, aux);
	MergeSort(arr, mid + 1, right, piir, insertThreshold, aux);

	Merge(arr, aux, left, mid, mid + 1, right, piir);

	if (created)
	{
		delete[] aux;
		aux = nullptr;
	}
}

void Merge(int arr[], int aux[], const int firstBegin, const int firstEnd,
		const int secondBegin, const int secondEnd, Piirturi& p)
{
	assert(firstEnd + 1 == secondBegin);
	int left{ firstBegin }, right{ secondBegin }, cursor{ firstBegin };

	p.PutHorLine(0, '-');
	p.PutHorLine(0, '+', firstBegin, secondEnd);

	while (left <= firstEnd && right <= secondEnd)
	{
		p.PutHorLine(-1, ' ', firstBegin, secondEnd);
		p.PutHorLine(-2, ' ', firstBegin, secondEnd);
		p.at(left, -1) = '^';
		p.at(left, -2) = '1';
		p.at(right, -1) = '^';
		p.at(right, -2) = '2';
		
		if (p.ShowCounts)
		{
			++p.CompCount;
			++p.WriteCount;
			p.PutCounts();
		}
		Sleep(p.CompDelay + p.CopyDelay);
		p.Redraw();

		aux[cursor++] = arr[left] <= arr[right] ? arr[left++] : arr[right++];
	}

	int index = left <= firstEnd ? left : right;

	while (cursor <= secondEnd)
	{
		p.PutHorLine(-1, ' ', firstBegin, secondEnd);
		p.PutHorLine(-2, ' ', firstBegin, secondEnd);
		p.at(index, -1) = '^';
		p.at(index, -2) = index < secondBegin ? '1' : '2';
		if (p.ShowCounts)
		{
			++p.WriteCount;
			p.PutCounts();
		}
		Sleep(p.CopyDelay);
		p.Redraw();

		aux[cursor++] = arr[index++];
	}

	for (index = firstBegin; index <= secondEnd; index++)
	{
		p.PutHorLine(-1, ' ', firstBegin, secondEnd);
		p.PutHorLine(-2, ' ', firstBegin, secondEnd);
		p.at(index, -1) = '^';
		p.at(index, -2) = 'M';

		arr[index] = aux[index];
		p.Tolppa(index, arr[index]);
		if (p.ShowCounts)
		{
			++p.WriteCount;
			p.PutCounts();
		}
		Sleep(p.CopyDelay);
		p.Redraw();
	}

	p.PutHorLine(-1, ' ', firstBegin, secondEnd);
	p.PutHorLine(-2, ' ', firstBegin, secondEnd);
}



void QMergeSort(int arr[], const int left, const int right, Piirturi& piir, const int insertThreshold, int* aux, std::queue<std::pair<int, int> >* splitQue, std::stack<std::tuple<int, int, int> >* mergeStack)
{
	if (left >= right) { return; }
	if (right - left + 1 <= insertThreshold)
	{
		InsertSort(arr, left, right, piir);
		return;
	}

	bool created{ aux == nullptr };
	if (created)
	{
		aux = new int[right - left + 1];
		splitQue = new std::queue<std::pair<int, int> >;
		mergeStack = new std::stack<std::tuple<int, int, int> >;
	}

	int mid = (left + right) / 2;

	//splitQue->push({ mid + 1, right });
	//splitQue->push({ left, mid });
	//mergeStack->push({ left, mid, right });
	splitQue->emplace(std::pair{ mid + 1, right });
	splitQue->emplace(std::pair{ left, mid });
	mergeStack->emplace(std::tuple{ left, mid, right });

	if (created)
	{
		while (!splitQue->empty())
		{
			const auto [one, two] = splitQue->front();
			splitQue->pop();
			QMergeSort(arr, one, two, piir, insertThreshold, aux, splitQue, mergeStack);
		}

		while (!mergeStack->empty())
		{
			const auto [one, m, two] = mergeStack->top();
			mergeStack->pop();
			Merge(arr, aux, one, m, m + 1, two, piir);
		}

		delete[] aux;
		aux = nullptr;
		delete splitQue;
		splitQue = nullptr;
		delete mergeStack;
		mergeStack = nullptr;
	}
}
