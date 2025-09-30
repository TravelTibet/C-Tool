#pragma execution_character_set("utf-8")
#include "DirTool.h"
#include <io.h>
#include <direct.h>
#include <time.h>
#include <ctime>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>		//包含getline()
#include <cmath>

using namespace std;

void DirTool::makeDir(const char* path)
{
	std::string strLogPath = path;
	if (_access(strLogPath.c_str(), 0) == -1)
	{
		int nTemp = _mkdir(strLogPath.c_str());
	}
}

void DirTool::removeDirContent(const char* path, bool bIsRemoveRoot, bool bIsRemoveChild, bool bIsRemoveEmptyChild)
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
				removeDirContent(fullPath.c_str(), bIsRemoveChild, bIsRemoveEmptyChild, true);
				// 递归删除子目录内容，注意递归时 root 参数要传 true，才能删子目录本身
			}

			if (bIsRemoveEmptyChild)
			{
				_rmdir(fullPath.c_str()); // 删除空目录
			}
		}
		else
		{
			DeleteFileA(fullPath.c_str()); // 删除文件
		}
	} while (FindNextFileA(hFind, &findData));

	FindClose(hFind);

	if (bIsRemoveRoot)
	{
		_rmdir(strPath.c_str()); // 最后删除传入的根目录
	}
}


bool DirTool::getDirAndFiles(std::string path, std::vector<std::string>& dirs, std::vector<std::string>& files, bool bIsFindChild, bool bIsCheckEmptyDir, int maxDepth)
{
	try {
		if (!std::filesystem::exists(path)) 
		{
			return false;
		}

		if (bIsFindChild) 
		{
			for (auto it = std::filesystem::recursive_directory_iterator(path); it != std::filesystem::recursive_directory_iterator(); ++it)
			{
				if (maxDepth >= 0 && it.depth() >= maxDepth) 
				{
					// 达到限制深度，不再深入
					it.disable_recursion_pending();
				}
				handleEntry(*it, dirs, files, bIsCheckEmptyDir);
			}
		}
		else 
		{
			for (const auto& entry : std::filesystem::directory_iterator(path)) 
			{
				handleEntry(entry, dirs, files, bIsCheckEmptyDir);
			}
		}

		return true;
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "文件系统错误: " << e.what() << std::endl;
		return false;
	}
}

bool DirTool::getDir(std::string path, std::vector<std::string>& dirs, bool bIsFindChild, bool bIsCheckEmpty)
{
	std::vector<std::string> files;
	return getDirAndFiles(path, dirs, files, bIsFindChild, bIsCheckEmpty);
}

void DirTool::handleEntry(const std::filesystem::directory_entry& entry, std::vector<std::string>& dirs, std::vector<std::string>& files, bool bIsCheckEmptyDir)
{
	if (std::filesystem::is_directory(entry.path())) 
	{
		if (!std::filesystem::is_empty(entry.path())) 
		{
			dirs.push_back(entry.path().string());
		}
		else if (bIsCheckEmptyDir) 
		{
			dirs.push_back(entry.path().string());
		}
	}
	else if (std::filesystem::is_regular_file(entry.path())) 
	{
		files.push_back(entry.path().string());
	}
	else // 其他类型（符号链接等）
	{
		files.push_back(entry.path().string());
	}
}
