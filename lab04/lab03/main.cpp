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
#include "ClientManipulation.h"

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "wsock32.lib")


int main(int argc, char *argv[])
{
	std::string processName = std::string(argv[1]);
	
	CClientManipulation clientMan;
	clientMan.Run(processName);
		

	system("pause");
}