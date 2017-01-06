#pragma once

class CAppLauncher
{
public:
	CAppLauncher(char *argv[]);
	void Run();
	~CAppLauncher();
	void WaitConnected();
	void SendMessages(std::string number);
	void SendMessages(unsigned number);
	void SendMessages();
private:
	void WaitMessages();
	void SettingProcess(STARTUPINFO &si);
	
private:
	size_t m_procNumber;
	size_t m_itNumber;
	std::vector<STARTUPINFO> m_startUpInfos;
	std::vector<PROCESS_INFORMATION> m_processesInformation;
};