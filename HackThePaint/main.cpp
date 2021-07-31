#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
using namespace std;
//hack pt SPAINT 

HANDLE handleProc;
DWORD procID;

bool attachProcces(const char* procName) {
	//find the procName given
	PROCESSENTRY32 procEntry32;
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	auto hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while (Process32Next(hProcSnap, &procEntry32)){
		std::cout << procEntry32.szExeFile << "\n";
		if (!strcmp(procName, procEntry32.szExeFile)) {
			cout << "we found the procces " << procName << " with PID" << procEntry32.th32ProcessID << "\n";
			handleProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
			procID = procEntry32.th32ProcessID;
			CloseHandle(hProcSnap);
			return true;
		}
	}

	return false;
}


int main() {
	attachProcces("SPAINT.exe");
	int a = 100;
	DWORD address = 0x0113CE04;
	WriteProcessMemory(handleProc, (PVOID)address , &a, sizeof(int), 0);
	return 0;
}