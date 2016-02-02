#pragma once
#include <string>
#include <map>
#include <vector>

typedef std::map < std::string, std::map<unsigned int, std::map<double,
	std::map<unsigned int, std::vector<Facility> >> >> MapWay;
typedef std::map<unsigned int, std::map<double,
	std::map<unsigned int, std::vector<Facility> >> > MapDir;
typedef std::map<double, std::map<unsigned int, std::vector<Facility> >> MapStake;
typedef std::map<unsigned int, std::vector<Facility> > MapType;


class CFacilityOfRoad
{
public:
	CFacilityOfRoad(std::string strPath);
	~CFacilityOfRoad();

public:
	bool Build(const std::map<std::string, std::map<long long, SWLink>>& mapRoad);
	bool OutToIndexFile(std::string strOutPath);

private:
	bool Load();
	bool BuildOut(std::map<std::string, std::map<long long, SWLink>> mapRoad);

private:
	std::string m_strPath;

	//用来生成文件所需的结果数据集合
	MapWay m_mapFacilityInfo; //roadid, dir, stakeid, type

	//用来存储中间数据的集合
	std::vector<Facility> m_vecFacility;
}; 

