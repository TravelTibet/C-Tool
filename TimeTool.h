#pragma once
#include <iostream>

class TimeTool
{
public:
	TimeTool() {}
	~TimeTool() {}
public:
	static std::string getNowTime(bool bIsShowHMS);
	static std::string getNowTime(bool showMilli, const std::string& format);
	static std::string getNowMsTime();
	static std::string fromTimestampMsToStdString(int64_t timestamp_ms);
};