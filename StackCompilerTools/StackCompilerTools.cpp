// StackCompilerTools.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RoadLink.h"
#include "StakeInfo.h"
#include "FacilityOfRoad.h"

string GetTheRootPath(char *argv[])
{
	string strPath(argv[0]);
	if (strPath != "")
	{
		strPath = strPath.substr(0, strPath.rfind('\\') + 1);
	}
	return strPath;
}

bool LoadConfig(string strPath, Config& config)
{
	ifstream ifsCon;
	setlocale(LC_ALL, "chs");
	ifsCon.open(strPath.c_str(), ios::in);
	if (!ifsCon.good())
	{
		cout << "config file open failure" << endl;
		setlocale(LC_ALL, NULL);
		return false;
	}
	setlocale(LC_ALL, NULL);
	string strLine;
	while (!ifsCon.eof())
	{
		getline(ifsCon, strLine);
		//如果内容为空或者是注释，则不处理
		if (strLine.empty() || strLine.find('#') != string::npos)
		{
			continue;
		}
		int pos = strLine.find('=');
		if (pos == string::npos)
		{
			cout << "the format of config is illegal" << endl;
			return false;
		}
		string strFirst, strSecond;
		strFirst = strLine.substr(0, pos);
		strSecond = strLine.substr(pos + 1);
		if (strFirst == "inputPath")
		{
			config.inputPath = strSecond;
		}
		// 		if (strFirst == "proPath")
		// 		{
		// 			config.proPath = strSecond;
		// 		}
		if (strFirst == "outputPath")
		{
			config.outputPath = strSecond;
		}
		strLine = "";
	}
	return true;
}

int main(int argc, char* argv[])
{
	string strConfPath = GetTheRootPath(argv) + "config.ini";
	Config config;
	if (!LoadConfig(strConfPath, config))
	{
		cout << "load config in error" << endl;
	}
	std::string strPath = config.inputPath.c_str();
	std::string strOutpath = config.outputPath.c_str();
	
	std::string strOutPath = strPath + "\\out";
	int iRes = _mkdir(strOutPath.c_str());

	std::string strLinkFile = strPath + "\\link.shp";
	CRoadLink roadLink(strLinkFile);

#ifndef ONLY_STAKE_DATA
	if (!roadLink.Build())
	{
		return -1;
	}
#endif // !ONLY_STAKE_DATA

	const MapRoad& mapRoad = roadLink.GetRoad();
	VecCoords& vecCoords = roadLink.GetCoords();
	const MapRoadInfo& mapRoadInfo = roadLink.GetRoadInfo();

	std::string strStakeFile = strPath + "\\stake.shp";
	CStakeInfo stakeInfo(strStakeFile);
	if (!stakeInfo.Build(mapRoad, vecCoords))
	{
		return -1;
	}

#ifndef ONLY_STAKE_DATA

	std::string strPoiFile = strPath + "\\poi_1.shp";
	CFacilityOfRoad facilityOfRoad(strPoiFile);
	if (!facilityOfRoad.Build(mapRoadInfo))
	{
		return -1;
	}

#endif // !ONLY_STAKE_DATA

	if (!roadLink.OutToLinkFile(strOutPath))
	{
		return -1;
	}

	if (!roadLink.OutToCoordFileBinary(strOutPath))
	{
		return -1;
	}

	if (!stakeInfo.OutToIndexFile(strOutPath))
	{
		return -1;
	}

    return 0;
}

