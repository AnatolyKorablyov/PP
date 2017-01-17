#pragma once

#include "stdafx.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <vector>
#include <string>
#include "Control.h"

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "wsock32.lib")


class CClientManipulation
{
public:
	CClientManipulation();
	~CClientManipulation();
	void Run(const std::string & processName);
	int RandomRangeFloatInClient(int a, int b);
	void ConnectToServer(unsigned Nmax, std::string const & processName);
	bool ConnectToClient(unsigned Nmax);
	void TransmitDataOnServer(size_t Nmax, double Pi, std::string const & processName);
	double GetPi(size_t iterationsNumber);

private:
	float m_radius = 10.f;
	int m_iterations = 0;
};

