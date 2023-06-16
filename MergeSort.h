#pragma once

#include <queue>
#include <stack>
#include "Piirturi.h"

void MergeSort(int arr[], const int left, const int right, Piirturi& prt, const int insertThreshold=10, int* aux = nullptr);

void Merge(int arr[], int aux[], const int, const int,
	const int, const int, Piirturi&);

void QMergeSort(int arr[], const int left, const int right, Piirturi& piir, const int insertThreshold = 10,
	int* aux = nullptr,
	std::queue<std::pair<int, int> >* splitQue = nullptr,
	std::stack<std::tuple<int, int, int> >* mergeStack = nullptr);
	