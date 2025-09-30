#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>		//ifstream
#include <filesystem>

class DirTool
{
public:
	DirTool() {};
	~DirTool() {};
public:
	//根据路径创建目录，不存在才创建
	static void makeDir(const char* path);
	/* 删除指定路径下的全部内容
	* @param path 绝对或者相对路径
	* @param bIsRemoveRoot 是否把根目录也删除
	* @param bIsRemoveEmptyChild 是否把空的子文件夹删除
	* @param bIsRemoveCHild 是否把全部子文件夹也同步删除
	*/

	static void removeDirContent(const char* path, bool bIsRemoveRoot = false, bool bIsRemoveEmptyChild = true, bool bIsRemoveChild = false);
	/* 获取指定路径下的目录和文件
	*  @param path 绝对或者相对路径
	*  @param dirs 返回的目录信息
	*  @param files 返回的文件信息
	*  @param bIsFindChild 是否继续递归搜索
	*  @param bIsCheckEmptyDIr 是否搜索空目录
	*  @param maxDepth 递归深度
	* 
	*  bIsFindChild 和 bIsFindChild 同时为flase也可以搜索指定路径下的第一层目录
	*  bIsFindChild 和 bIsFindChild 同时为true可以搜索全部路径和文件
	*/
	static bool getDirAndFiles(std::string path, std::vector<std::string>& dirs, std::vector<std::string>& files,
		bool bIsFindChild, bool bIsCheckEmptyDIr, int maxDepth = -1);

	/* 获取指定路径下的目录
	*  @param path 绝对或者相对路径
	*  @param dirs 返回的目录信息
	*  @param bIsFindChild 是否继续递归搜索
	*  @param bIsCheckEmptyDIr 是否搜索空目录
	*/
	static bool getDir(std::string path, std::vector<std::string>& dirs, bool bIsFindChild, bool bIsCheckEmpty);
private:

	static void handleEntry(const std::filesystem::directory_entry& entry, std::vector<std::string>& dirs, std::vector<std::string>& files,
		bool bIsCheckEmptyDir);
};