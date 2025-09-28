#include "pch.h"
#include "TimeTool.h"
#include <sstream>
#include <time.h>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace std::chrono;

string TimeTool::getNowTime(bool bIsShowHMS)
{
	time_t time_seconds = time(NULL);
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);
	stringstream ssDate, ssTime;
	ssDate << now_time.tm_year + 1900 << "-" << now_time.tm_mon + 1 << "-" << now_time.tm_mday;
	ssTime << " " << now_time.tm_hour << ":" << now_time.tm_min << ":" << now_time.tm_sec;
	string strTime = ssDate.str();
	if (bIsShowHMS)
	{
		strTime += ssTime.str();
	}
	return strTime;
}

string TimeTool::getNowTime(bool showMilli = false, const string& format = "%Y-%m-%d %H:%M:%S")
{
    using namespace std::chrono;

    // 获取当前时间点
    auto now = system_clock::now();
    auto time_t_now = system_clock::to_time_t(now);

    // 转换成本地时间
    std::tm local_tm{};
    localtime_s(&local_tm, &time_t_now);

    // 格式化输出
    std::ostringstream oss;
    oss << std::put_time(&local_tm, format.c_str());

    // 如果需要毫秒
    if (showMilli)
    {
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        oss << '.' << std::setw(3) << std::setfill('0') << ms.count();
    }
    return oss.str();
}

string TimeTool::getNowMsTime()
{
    auto now = system_clock::now();

    auto t = system_clock::to_time_t(now);

    // 转换为 tm（线程安全）
    std::tm tm{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);  // Windows
#else
    localtime_r(&t, &tm);  // Linux / Unix
#endif

    // 计算毫秒部分
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // 格式化输出
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << ms.count();
    return oss.str();
}

std::string TimeTool::fromTimestampMsToStdString(int64_t timestamp_ms)
{
    using namespace std::chrono;

    // 1. 拆分秒和毫秒
    auto seconds = timestamp_ms / 1000;
    auto millis = timestamp_ms % 1000;

    // 2. 转换成 time_t
    std::time_t t = static_cast<time_t>(seconds);
    std::tm tm_time;
#ifdef _WIN32
    localtime_s(&tm_time, &t); // Windows 安全版本
#else
    localtime_r(&t, &tm_time); // Linux 安全版本
#endif

    // 3. 格式化
    std::ostringstream oss;
    oss << std::put_time(&tm_time, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << millis;

    return oss.str();
}
