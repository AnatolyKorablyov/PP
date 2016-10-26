#pragma once
#include "stdafx.h"
#include "RankGaussMethod.h"


class CMultiThreadRank : public CRankGaussMethod
{

public:
	CMultiThreadRank();
	CMultiThreadRank(unsigned threads);
	int GetRank(Matrix matr) override;
	void CalcRankWithRange(size_t numThread);
	~CMultiThreadRank();

private:
	Matrix m_matrix;
	std::vector<bool> m_line_used;
	size_t m_numThreads = 0;
	
	size_t m_matrixSize = 0;
	std::vector<int> m_threads;

};

