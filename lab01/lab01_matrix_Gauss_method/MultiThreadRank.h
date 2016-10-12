#pragma once
#include "stdafx.h"

const double EPS = 1E-9;

class CMultiThreadRank
{
public:
	CMultiThreadRank();
	CMultiThreadRank(unsigned n, unsigned threads);
	~CMultiThreadRank();
	std::vector<std::vector<float>> CreateMatrix(unsigned n);
	//std::vector<std::vector<float>> CreateMatrix(unsigned n, size_t threads);
	void PrintMatrix(const std::vector<std::vector<float>>& matrix);
	void FillMatrix(size_t num);
	void MultiThreads();
private:
	std::vector<std::vector<float>> matrix;
	std::vector<bool> line_used;
	//int numThread;
	size_t numThreads = 0;
	int rank;
	size_t matrixSize = 0;
	std::vector<int> threads;
};

