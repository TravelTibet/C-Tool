#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

class CVTool
{
public:
	CVTool() {}
	~CVTool() {}
	static void findMaxContour(const std::vector<std::vector<cv::Point>>& contours,std::vector<cv::Point>& maxContour);
	static void findMaxContour(const std::vector<std::vector<cv::Point>>& contours,int& maxID);
	static void findMaxContour(const std::vector<std::vector<cv::Point>>& contours, std::vector<cv::Point>& maxContour, int& maxID);
	//查看Mat的引用数
	static std::string debugMat(const cv::Mat& m, const std::string& name);
};