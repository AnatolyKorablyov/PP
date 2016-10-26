#include "OneThreadRank.h"



COneThreadRank::COneThreadRank()
{
	m_rank = 0;
}


COneThreadRank::~COneThreadRank()
{
}

int COneThreadRank::GetRank(Matrix matr)
{
	m_rank = matr.size();
	std::vector<bool> line_used(m_rank);
	for (int i = 0; i < matr.size(); ++i)
	{
		int j;
		for (j = 0; j < 4; ++j)
			if (!line_used[j] && abs(matr[j][i]) > EPS)
				break;
		if (j == 4)
			--m_rank;
		else
		{
			line_used[j] = true;
			for (int p = i + 1; p< 4; ++p)
				matr[j][p] /= matr[j][i];
			for (int k = 0; k< 4; ++k)
				if (k != j && abs(matr[k][i]) > EPS)
					for (int p = i + 1; p< 4; ++p)
						matr[k][p] -= matr[j][p] * matr[k][i];
		}
	}
	return m_rank;
}
