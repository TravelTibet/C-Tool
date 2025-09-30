#include "CVTool.h"

using namespace cv;
using namespace std;

void CVTool::findMaxContour(const vector<vector<Point>>& contours, vector<Point>& maxContour)
{
	int nMaxID = -1;
	double dbMaxArea = -1.0;
	double dbTemp = -1.0;
	vector<Point> contour;
	int nSize = contours.size();
	for (int i = 0; i < nSize; ++i)
	{
		contour = contours[i];
		dbTemp = contourArea(contour);
		if (dbTemp > dbMaxArea)
		{
			dbMaxArea = dbTemp;
			nMaxID = i;
		}
	}
	maxContour = contours[nMaxID];
}

void CVTool::findMaxContour(const vector<vector<Point>>& contours,int &maxID)
{
	int nMaxID = -1;
	double dbMaxArea = -1.0;
	double dbTemp = -1.0;
	vector<Point> contour;
	int nSize = contours.size();
	for (int i = 0; i < nSize; ++i)
	{
		contour = contours[i];
		dbTemp = contourArea(contour);
		if (dbTemp > dbMaxArea)
		{
			dbMaxArea = dbTemp;
			nMaxID = i;
		}
	}
	maxID = nMaxID;
}

void CVTool::findMaxContour(const vector<vector<Point>>& contours, vector<Point>& maxContour, int& maxID)
{
	int nMaxID = -1;
	double dbMaxArea = -1.0;
	double dbTemp = -1.0;
	vector<Point> contour;
	int nSize = contours.size();
	for (int i = 0; i < nSize; ++i)
	{
		contour = contours[i];
		dbTemp = contourArea(contour);
		if (dbTemp > dbMaxArea)
		{
			dbMaxArea = dbTemp;
			nMaxID = i;
		}
	}
	maxContour = contours[nMaxID];
	maxID = nMaxID;
}

string CVTool::debugMat(const cv::Mat& m, const string& strLog)
{
	string str = "";
	if (!m.empty() && m.u) 
	{
		str = strLog + " Mat's refcount = ";
		str += to_string(m.u->refcount);
	}
	else 
	{
		str = strLog + " Mat is empty!";
	}
	return str;
}
