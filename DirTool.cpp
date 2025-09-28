#pragma execution_character_set("utf-8")
#include "DirTool.h"
#include <iostream>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <ctime>
#include <windows.h>

using namespace std;

void DirTool::makeDir(const char* path)
{
	std::string strLogPath = path;
	if (_access(strLogPath.c_str(), 0) == -1)
	{
		int nTemp = _mkdir(strLogPath.c_str());
	}
}

void DirTool::removeDirContent(const char* path, bool bIsRemoveChild, bool bIsRemoveEmptyChild)
{
	std::string strPath = path;
	if (_access(strPath.c_str(), 0) == -1)
	{
		return;
	}

	std::string strSearch = strPath + "\\*.*";
	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(strSearch.c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		const char* name = findData.cFileName;
		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;

		std::string fullPath = strPath + "\\" + name;
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (bIsRemoveChild)
			{
				removeDirContent(fullPath.c_str()); // 递归删除子目录内容
			}
			
			if (bIsRemoveEmptyChild)
			{
				_rmdir(fullPath.c_str());

			}
		}
		else
		{
			DeleteFileA(fullPath.c_str());      // 删除文件
		}
	} while (FindNextFileA(hFind, &findData));

	FindClose(hFind);
}