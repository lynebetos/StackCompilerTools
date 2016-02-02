#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>

typedef std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>> MapRoad;
typedef std::map<std::string, std::map<long long, SWLink>> MapRoadInfo;
typedef std::vector<DCoord> VecCoords;

//����·����Ϣ���ݣ��Ը���·�����Ϊһ��������·��������Ϊ��������
class CRoadLink
{
public:
	CRoadLink(const std::string strPath); 
	~CRoadLink();

public:
	bool Build();
	bool OutToLinkFile(std::string strOutPath);
	bool OutToCoordFileProto(std::string strOutPath);
	bool OutToCoordFileBinary(std::string strOutPath);
	const MapRoad& GetRoad()
	{
		return m_mapOutRoad;
	}
	std::vector<DCoord>& GetCoords()
	{
		return m_vecCoords;
	}
	const MapRoadInfo& GetRoadInfo()
	{
		return m_mapRoad;
	}

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

