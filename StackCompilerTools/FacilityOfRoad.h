#pragma once
#include <string>


class CFacilityOfRoad
{
public:
	CFacilityOfRoad(std::string strPath);
	~CFacilityOfRoad();

public:
	bool Build();
	bool OutToIndexFile(std::string strOutPath);

private:
	bool Load();

private:
	std::string m_strPath;

}; 

