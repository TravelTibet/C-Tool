#pragma once

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
	* @param bIsRemoveCHild 是否把全部子文件夹也同步删除
	* @param bIsRemoveEmptyChild 是否把空的子文件夹删除
	*/
	static void removeDirContent(const char* path, bool bIsRemoveChild = true, bool bIsRemoveEmptyChild = true);
};