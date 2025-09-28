#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class CVTool
{
public:
	CVTool() {}
	~CVTool() {}
	static void findMaxContour(const std::vector<std::vector<cv::Point>>& contours,std::vector<cv::Point>& maxContour);
	static void findMaxContour(const std::vector<std::vector<cv::Point>>& contours,int& maxID);
	static void findMaxContour(const std::vector<std::vector<cv::Point>>& contours, std::vector<cv::Point>& maxContour, int& maxID);
};