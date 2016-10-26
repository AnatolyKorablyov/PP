// lab0_matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "OneThreadRank.h"
#include "MultiThreadRank.h"
#include "Matrix.h"

using namespace std;

bool CheckStrToNumber(const std::string & numberStr)
{
	int number = atoi(numberStr.c_str());
	std::stringstream ss;
	ss << number;
	return (numberStr == ss.str());
}

int main(int argc, char * argv[])
{
	if (argc == 3)
	{
		if (CheckStrToNumber(argv[1]) && CheckStrToNumber(argv[2]))
		{
			size_t time = clock();
			CMatrix matr;
			matr.CreateMatrix(std::atoi(argv[1]));

			if (std::atoi(argv[2]) == 1)
			{
				COneThreadRank startGauss;
				startGauss.GetRank(matr.GetMatrix());
			}
			else
			{
				CMultiThreadRank startGauss(std::atoi(argv[2]));
				startGauss.GetRank(matr.GetMatrix());
			}
			CMultiThreadRank startMatrix(std::atoi(argv[2]));
			size_t finishTime = clock();
			double processTime = (finishTime - time) / 1000.0;
			std::cout << "Time: " << processTime << std::endl;
		}
		else
		{
			std::cout << "Недопустимые параметры, введены не числа. Example: lab.exe 3 2" << std::endl;
		}

	}
	else
	{
		std::cout << "Недопустимые параметры, некорректно введены аргументы. Example: lab.exe 3 2, где 3 - размер матрицы, 2 - кол-во потоков!!!" << std::endl;
	}

    return 0;
}

