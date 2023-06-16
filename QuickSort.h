#pragma once
#include "Piirturi.h"

void Quicksort(int a[], const int alku, const int loppu, Piirturi& p, const int insertThreshold = 10);
int Partition(int a[], const int pivot, const int alku, const int loppu, Piirturi& p);
void IncrementL(int& left, Piirturi& p);
void DecrementR(int& right, Piirturi& p, const char symbol = 'R');
int MedianOf3(const int a, const int b, const int c, Piirturi& p);
