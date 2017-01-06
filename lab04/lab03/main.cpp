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
#include "CorrectRandom.h"

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "wsock32.lib")




using namespace std;

namespace
{
	const float radius = 10.f;

	void ConnectToServer(unsigned Nmax, std::string const &processName)
	{
	
		std::vector<std::string> messages;
		CControl helper;
		helper.CreateSocket();
		helper.TuneSocket(11111, "localhost");	//192.168.0.4
		helper.SendMes(NumberToString(Nmax));
		//helper.TuneSocket(11111, INADDR_ANY);
		//helper.WaitSend(messages, 1);
	}

	bool ConnectToClient(unsigned Nmax)
	{
		std::vector<std::string> messages;

		CControl helper;
		helper.CreateSocket();
		helper.TuneSocket(Nmax, INADDR_ANY);	//192.168.0.4
		return helper.WaitSend(messages, 1);
	}

	void TransmitDataOnServer(size_t Nmax, double Pi, std::string const &processName)
	{
		std::string info = processName + ", " + NumberToString(Nmax) + ", " + NumberToString(Pi);

		CControl helper;
		helper.CreateSocket();
		helper.TuneSocket(11111, "localhost");	//192.168.0.4
		helper.SendMes(info);
	}



	double GetPi(size_t iterationsNumber)
	{
		size_t Nmax = iterationsNumber;
		double Ncirc = 0;
		for (size_t i = 0; i < Nmax; ++i)
		{
			double x = RandomRangeFloat(0.f, radius);
			double y = RandomRangeFloat(0.f, radius);
			if (pow(x, 2) + pow(y, 2) <= pow(radius, 2))
			{
				++Ncirc;
			}
		}

		double Pi = (Ncirc / Nmax) * 4;

		std::cout << Nmax << ", " << Pi << std::endl;
		std::cout << "Pi = " << Pi << std::endl;
		return Pi;
	}


}

int main(int argc, char *argv[])
{
	size_t iterationsNumber = atoi(argv[1]);
	std::string processName = std::string(argv[2]);
	
	unsigned number = RandomRangeFloat(0.f, 200);
	std::cout << " port " << number << std::endl;
	ConnectToServer(number, processName);
	if (ConnectToClient(number))
	{
		Sleep(1000);
		TransmitDataOnServer(iterationsNumber, GetPi(iterationsNumber), processName);
	}
		

	system("pause");
}