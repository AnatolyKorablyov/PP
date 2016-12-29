#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <chrono>

#include "../lab03/Control.h"
#include "../lab03/CorrectRandom.h"
#include "AppLauncher.h"


CAppLauncher::CAppLauncher(char * argv[])
	: m_itNumber(atoi(argv[2]))
	, m_procNumber(atoi(argv[1]))
{
}

void CAppLauncher::Run()
{
	int failedProc = 0;
	for (size_t i = 0; i != m_procNumber; ++i)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		std::string commandLine = "lab03.exe " + NumberToString(m_itNumber) + " " + NumberToString(i + 1);

		commandLine += " socket";

		SettingProcess(si);

		if (!CreateProcess(NULL, (LPSTR)commandLine.data(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			++failedProc;
			std::cout << "Could't create a process. Program will continue to work without it" << std::endl;
			continue;
		}


		m_startUpInfos.push_back(si);
		m_processesInformation.push_back(pi);
	}
	m_procNumber -= failedProc;

	WaitMessages();
}

void CAppLauncher::SettingProcess(STARTUPINFO &si)
{
	si.dwFlags = STARTF_USESIZE | STARTF_USESHOWWINDOW;
	si.dwXSize = 500;
	si.dwYSize = 300;
	si.wShowWindow = SW_SHOW;
}

CAppLauncher::~CAppLauncher()
{
	for (size_t i = 0; i != m_procNumber; ++i)
	{
		CloseHandle(m_processesInformation[i].hProcess);
		CloseHandle(m_processesInformation[i].hThread);
	}
}

void CAppLauncher::WaitMessages()
{
	auto start = std::chrono::system_clock::now();
	std::vector<std::string> messages;

	CControl helper;
	helper.CreateSocket();
	helper.TuneSocket(11111, INADDR_ANY);		//192.168.0.4
	helper.WaitSend(messages, m_procNumber);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Time : " << diff.count() << std::endl;
	for (auto const &mes : messages)
	{
		std::cout << mes << std::endl;
	}
	system("pause");

}
