#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>


//加载路段信息数据，以高速路编号作为一级索引，路链编码作为二级索引
class CRoadLink
{
public:
	CRoadLink(const std::string strPath); 
	~CRoadLink();

public:
	bool Build();
	bool OutToLinkFile(std::string strOutPath);

private:
	bool Load();
	bool GetLinkNode(const OGRLinearRing* pOGRLine, std::vector<DCoord>& vecCoord);
	bool BuildNet();
	bool BuildCoords();

private:
	std::string m_strPath;

	//用来生成文件所需的结果数据集合
	std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>> m_mapOutRoad; //RoadID, LinkOrder, atrrabute
	std::vector<DCoord> m_vecCoords;

	//中间结构
	std::map<std::string, std::map<long long, SWLink>> m_mapRoad;  //RoadID,link,atrrabute
	std::map<std::string, std::map<long long, int>> m_mapLinkIndex; //RoadID, link, linkIndex in file;

};

