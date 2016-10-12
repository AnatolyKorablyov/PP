#include "MultiThreadRank.h"
#include <thread>

void StartFill(CMultiThreadRank * mat, size_t num)
{
	mat->FillMatrix(num);
}

CMultiThreadRank::CMultiThreadRank()
{
}

CMultiThreadRank::CMultiThreadRank(unsigned n, unsigned threads)
{
	
	/*
	matrix.resize(4);
	matrix[0].push_back(2);
	matrix[0].push_back(1);
	matrix[0].push_back(-2);
	matrix[0].push_back(6);
	
	matrix[1].push_back(3);
	matrix[1].push_back(1);
	matrix[1].push_back(-1);
	matrix[1].push_back(-1);				 

	matrix[2].push_back(1);
	matrix[2].push_back(-1);
	matrix[2].push_back(2);
	matrix[2].push_back(-7);

	matrix[3].push_back(7);
	matrix[3].push_back(2);
	matrix[3].push_back(-4);
	matrix[3].push_back(11);
	  */
	
	numThreads = threads;

	matrix = CreateMatrix(n);
	matrixSize = n;
	PrintMatrix(matrix);
	line_used.resize(matrixSize);

	
	MultiThreads();
}


CMultiThreadRank::~CMultiThreadRank()
{
}

void CreateLine(std::vector<std::vector<float>> & matrix, unsigned n, size_t numLine)
{
	matrix[numLine].resize(n);
	for (int j = 0; j < n; ++j)
	{
		matrix[numLine][j] = rand() % 10;
	}
}

void CreateLinesRange(std::vector<std::vector<float>> & matrix, unsigned minRange, unsigned maxRange, unsigned n)
{
	for (unsigned i = minRange; i < maxRange; ++i)
	{
		CreateLine(matrix, n, i);
	}
}

std::vector<std::vector<float>> CMultiThreadRank::CreateMatrix(unsigned n)
{
	/*
	std::vector<std::thread> hThreads;
	hThreads.resize(numThreads);

	std::vector<std::vector<float>> matrix;
	matrix.resize(n);

	for (int i = 0; i <= numThreads - 1; ++i)
	{
		size_t minSize = n / numThreads * i;
		size_t maxSize;

		if (i == (numThreads - 1))
		{
			maxSize = n;
		}
		else
		{
			maxSize = minSize + n / numThreads;
		}

		hThreads[i] = std::thread(CreateLinesRange, matrix, minSize, maxSize, n);
	}

	for (auto &it : hThreads)
	{
		it.join();		
	}

	  */
	std::vector<std::vector<float>> matrix;
	matrix.resize(n);

	for (auto i = 0; i < n; ++i)
	{
		matrix[i].resize(n);
		for (int j = 0; j < n; ++j)
		{
			matrix[i][j] = rand() % 10;
		}
	}
	return matrix;
}

void CMultiThreadRank::PrintMatrix(const std::vector<std::vector<float>> & matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void CMultiThreadRank::FillMatrix(size_t num)
{
	auto threadNumber = num;
	
	size_t minSize = matrix.size() / numThreads * threadNumber;
	size_t maxSize;									

	if (threadNumber == (numThreads - 1))
	{ 
		maxSize = matrix.size();
	}								     
	else
	{
		maxSize = minSize + matrix.size() / numThreads;
	}
	
	for (auto i = minSize; i < maxSize; ++i)
	{
		int j;
		for (j = 0; j < matrixSize; ++j)
			if (!line_used[j] && abs(matrix[j][i]) > EPS)
				break;
		if (j == matrixSize)
			--rank;
		else
		{
			line_used[j] = true;
			for (int p = i + 1; p < matrixSize; ++p)
				matrix[j][p] /= matrix[j][i];
			for (int k = 0; k < matrixSize; ++k)
				if (k != j && abs(matrix[k][i]) > EPS)
					for (int p = i + 1; p < matrixSize; ++p)
						matrix[k][p] -= matrix[j][p] * matrix[k][i];
		}
	}
}


void CMultiThreadRank::MultiThreads()
{
	unsigned minSize = matrix.size();
	unsigned maxSize = matrix[0].size();
	if (minSize > matrix[0].size())
	{
		minSize = matrix[0].size();
		maxSize = matrix.size();
	}

	rank = minSize;

	std::vector<std::thread> hThreads;
	hThreads.resize(numThreads);

	std::cout << "Threads = " << numThreads << std::endl;
	for (size_t i = 0; i <= numThreads - 1; i++)
	{
		hThreads[i] = std::thread(StartFill, this, i);
	}
	for (auto &it : hThreads)
	{
		it.join();
	}
	std::cout << "rank: " << rank << std::endl;

	//WaitForMultipleObjects(numThreads, hThreads, TRUE, INFINITE);
}