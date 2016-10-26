#include "MultiThreadRank.h"


#include <thread>

void StartCalcRank(CMultiThreadRank * mat, size_t num)
{
	mat->CalcRankWithRange(num);
}

CMultiThreadRank::CMultiThreadRank()
{
}

CMultiThreadRank::CMultiThreadRank(unsigned threads)
{							 
	m_numThreads = threads;
}

int CMultiThreadRank::GetRank(Matrix matr)
{
	m_matrix = matr;
	m_matrixSize = m_matrix.size();
	m_line_used.resize(m_matrixSize);

	unsigned minSize = m_matrixSize;
	unsigned maxSize = m_matrix[0].size();
	if (minSize > m_matrix[0].size())
	{
		minSize = m_matrix[0].size();
		maxSize = m_matrix.size();
	}

	m_rank = minSize;

	std::vector<std::thread> hThreads;
	hThreads.resize(m_numThreads);

	for (size_t i = 0; i <= m_numThreads - 1; i++)
	{
		hThreads[i] = std::thread(StartCalcRank, this, i);
	}
	for (auto &it : hThreads)
	{
		it.join();
	}
	
	return m_rank;
}

void CMultiThreadRank::CalcRankWithRange(size_t numThread)
{
	size_t minSize = m_matrix.size() / m_numThreads * numThread;
	size_t maxSize;

	if (numThread == (m_numThreads - 1))
	{
		maxSize = m_matrix.size();
	}
	else
	{
		maxSize = minSize + m_matrix.size() / m_numThreads;
	}

	for (auto i = minSize; i < maxSize; ++i)
	{
		size_t j;
		for (j = 0; j < m_matrixSize; ++j)
			if (!m_line_used[j] && abs(m_matrix[j][i]) > EPS)
				break;
		if (j == m_matrixSize)
			--m_rank;
		else
		{
			m_line_used[j] = true;
			for (auto p = i + 1; p < m_matrixSize; ++p)
				m_matrix[j][p] /= m_matrix[j][i];
			for (size_t k = 0; k < m_matrixSize; ++k)
				if (k != j && abs(m_matrix[k][i]) > EPS)
					for (unsigned p = i + 1; p < m_matrixSize; ++p)
						m_matrix[k][p] -= m_matrix[j][p] * m_matrix[k][i];
		}
	}
}

CMultiThreadRank::~CMultiThreadRank()
{
}