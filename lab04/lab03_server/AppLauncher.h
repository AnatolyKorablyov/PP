#pragma once

class CAppLauncher
{
public:
	CAppLauncher(size_t m_procNum, size_t m_itNum);
	void Run();
	~CAppLauncher();
	void WaitConnected();
	void SendMessages(std::string number, const std::string & iterations);
private:
	void WaitMessages();
	void SettingProcess(STARTUPINFO &si);
	
private:
	size_t m_procNumber;
	size_t m_itNumber;
	std::vector<STARTUPINFO> m_startUpInfos;
	std::vector<PROCESS_INFORMATION> m_processesInformation;
};