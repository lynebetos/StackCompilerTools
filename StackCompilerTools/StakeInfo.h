#pragma once

#include <string>
#include <map>
#include <vector>


class CStakeInfo
{
public:
	CStakeInfo(std::string strPath);
	~CStakeInfo();
	 
public:
	bool Build();
	bool OutToIndexFile(std::string strOutPath);

private:
	bool Load();
	bool BuildIndex(const std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>>& mapRoadOut,
		std::vector<DCoord>& vecCoords);
	bool IsShapePoint(const DCoord& coord, const std::vector<DCoord>& vecCoords, unsigned int& nPos);
	unsigned int InserteLinePoint(const DCoord& coord, const std::vector<DCoord>& vecCoords, std::vector<DCoord>& newCoords);
private:
	std::string m_strPath;
	//构建写入文件的结构
	std::map<std::string, std::map<int, std::map<int, CLIndex>>> m_mapStakeIndex;

	//中间存储结构
	std::map<std::string, std::map<long long, std::vector<StakeInfo>>> m_mapStakeInfo;
};
