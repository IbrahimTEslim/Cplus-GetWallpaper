#include <iostream>
#include <Windows.h>

using namespace std;

LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
{
	strValue = strDefaultValue;
	WCHAR szBuffer[512];
	DWORD dwBufferSize = sizeof(szBuffer);
	ULONG nError;
	nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
	if (ERROR_SUCCESS == nError)
	{
		strValue = szBuffer;
	}
	return nError;
}
void main()
{
	wstring wstr_Path;
	HKEY hkey;

	RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_READ, &hkey);

	WCHAR PathBuffer[MAX_PATH];
	DWORD dwBufferSize = sizeof(PathBuffer);
	ULONG nError;

	nError = RegQueryValueExW(hkey, L"WallPaper", 0, NULL, (LPBYTE)PathBuffer, &dwBufferSize);
	if (nError != ERROR_SUCCESS)
		cout << endl << "Error!!\nError Number: " << GetLastError();

	wstr_Path = PathBuffer;
	cout << endl << "Image Path: ";
	wcout << wstr_Path;

	bool b = 1;

	if (CopyFile(wstr_Path.c_str(), L"Background.jpg", b) != 0)
		cout << endl << endl << "Copied Successfully to this app directory by name \"Background.jpg\"";

	else {
		cout << endl << endl << "Error While Coping it to this exe directory !!";
		cout << endl << "\nPress Enter if You Want to Overwrite if there is file with the same name: ";
		cin.get();
		b = 0;
		if (CopyFile(wstr_Path.c_str(), L"Background.jpg", b) != 0)
			cout << endl << endl << "Copied Successfully to this app directory by name \"Background.jpg\"";
		else
			cout << endl << endl << "Error While Coping it to this exe directory !!";
	}
	cin.get();
}