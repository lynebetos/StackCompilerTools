#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>


//����·����Ϣ���ݣ��Ը���·�����Ϊһ��������·��������Ϊ��������
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

	//���������ļ�����Ľ�����ݼ���
	std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>> m_mapOutRoad; //RoadID, LinkOrder, atrrabute
	std::vector<DCoord> m_vecCoords;

	//�м�ṹ
	std::map<std::string, std::map<long long, SWLink>> m_mapRoad;  //RoadID,link,atrrabute
	std::map<std::string, std::map<long long, int>> m_mapLinkIndex; //RoadID, link, linkIndex in file;

};

