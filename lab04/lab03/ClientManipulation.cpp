#include "ClientManipulation.h"

#include "stdafx.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include "Control.h"

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "wsock32.lib")

CClientManipulation::CClientManipulation()
{
}


CClientManipulation::~CClientManipulation()
{
}

template <typename T>
std::string NumberToString(T number)
{
	std::ostringstream os;
	os << number;
	return os.str();

}

void CClientManipulation::Run(const std::string & processName)
{
	unsigned number = RandomRangeFloatInClient(0, 200);
	std::cout << " port " << number << std::endl;
	ConnectToServer(number, processName);
	if (ConnectToClient(number))
	{
		Sleep(1000);
		TransmitDataOnServer(m_iterations, GetPi(m_iterations), processName);
	}
}

int CClientManipulation::RandomRangeFloatInClient(int a, int b)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, int(b));
	return dist(gen);
}

void CClientManipulation::ConnectToServer(unsigned Nmax, std::string const &processName)
{

	std::vector<std::string> messages;
	CControlSocket helper;
	helper.CreateSocket();
	helper.TuneSocket(11111, "localhost");
	helper.SendMes(NumberToString(Nmax));

}

bool CClientManipulation::ConnectToClient(unsigned Nmax)
{
	std::vector<std::string> messages;

	CControlSocket helper;
	helper.CreateSocket();
	helper.TuneSocket(Nmax, INADDR_ANY);
	helper.WaitSend(messages, 1);
	m_iterations = atoi(messages[0].c_str());
	return true;
}

void CClientManipulation::TransmitDataOnServer(size_t Nmax, double Pi, std::string const &processName)
{
	std::string info = processName + ", " + NumberToString(Nmax) + ", Pi= " + NumberToString(Pi);

	CControlSocket helper;
	helper.CreateSocket();
	helper.TuneSocket(11111, "localhost");
	helper.SendMes(info);
}



double CClientManipulation::GetPi(size_t iterationsNumber)
{
	size_t Nmax = iterationsNumber;
	double Ncirc = 0;
	for (size_t i = 0; i < Nmax; ++i)
	{
		int x = RandomRangeFloatInClient(0.f, m_radius);
		int y = RandomRangeFloatInClient(0.f, m_radius);
		if (pow(x, 2) + pow(y, 2) <= pow(m_radius, 2))
		{
			++Ncirc;
		}
	}

	double Pi = (Ncirc / Nmax) * 4;

	std::cout << Nmax << ", " << Pi << std::endl;
	std::cout << "Pi = " << Pi << std::endl;
	return Pi;
}