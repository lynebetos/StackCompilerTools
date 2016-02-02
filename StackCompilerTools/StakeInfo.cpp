#include "stdafx.h"
#include "StakeInfo.h"
#include "proto\MapIndex.pb.h"
#include <fstream>


CStakeInfo::CStakeInfo(std::string strPath)
: m_strPath(strPath)
{
}


CStakeInfo::~CStakeInfo()
{
}

bool CStakeInfo::Load()
{
	OGRRegisterAll();

	OGRDataSource* poDataSource = NULL;

	poDataSource = OGRSFDriverRegistrar::Open(m_strPath.c_str());
	if (poDataSource == NULL)
	{
		printf("Open file faild [%s]", m_strPath.c_str());
		return false;
	}

	OGRLayer  *poLayer;
	OGRFeature *poFeature;
	poLayer = poDataSource->GetLayerByName(CPLGetBasename(m_strPath.c_str()));
	poLayer->ResetReading();
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		StakeInfo stStakeInfo;
		try
		{
			stStakeInfo.routeID = poFeature->GetFieldAsString("RD_NAME");
			stStakeInfo.lLinkID = poFeature->GetFieldAsInteger("LINKID");
			stStakeInfo.dcoord.Lat = poFeature->GetFieldAsDouble("XSWD");
			stStakeInfo.dcoord.Lon = poFeature->GetFieldAsDouble("XSJD");
#ifdef ONLY_STAKE_DATA
			stStakeInfo.strRouteName = poFeature->GetFieldAsString("LXMC");
			stStakeInfo.iDir = poFeature->GetFieldAsInteger("SXX");
			stStakeInfo.stakeID = atoi(poFeature->GetFieldAsString("LCZ"));
#else
			stStakeInfo.stakeID = (int)poFeature->GetFieldAsDouble("LCZ");
#endif // 


			auto itWay = m_mapStakeInfo.find(stStakeInfo.routeID);
			if (itWay != m_mapStakeInfo.end())
			{
				std::map<long long, std::vector<StakeInfo>>& mapStakeLink = itWay->second;
				auto itLink = mapStakeLink.find(stStakeInfo.lLinkID);
				if (itLink != mapStakeLink.end())
				{
					std::vector<StakeInfo>& vecStakeInfo = itLink->second;
					for (int ii = 0;ii < vecStakeInfo.size(); ii++)
					{
						if (vecStakeInfo[ii].stakeID == stStakeInfo.stakeID)
						{
							auto itStake = vecStakeInfo.begin();
							itStake += ii;
							vecStakeInfo.erase(itStake);
						}
					}
					vecStakeInfo.push_back(stStakeInfo);

				}
				else
				{
					std::vector<StakeInfo> vecStakeInfo;
					mapStakeLink.insert(std::pair<long long, std::vector<StakeInfo>>(stStakeInfo.lLinkID, vecStakeInfo));
					itLink = mapStakeLink.find(stStakeInfo.lLinkID);
					itLink->second.push_back(stStakeInfo);
				}
			}
			else
			{
				std::map<long long, std::vector<StakeInfo>> mapStakeLink;
				m_mapStakeInfo.insert(std::pair<std::string, std::map<long long, std::vector<StakeInfo>>>(
					stStakeInfo.routeID, mapStakeLink));
				itWay = m_mapStakeInfo.find(stStakeInfo.routeID);
				std::vector<StakeInfo> vecStakeInfo;
				itWay->second.insert(std::pair<long long, std::vector<StakeInfo>>(stStakeInfo.lLinkID, vecStakeInfo));
				auto itLink = itWay->second.find(stStakeInfo.lLinkID);
				itLink->second.push_back(stStakeInfo);
			}
		}
		catch (const std::exception&)
		{
			return false;
		}

		OGRFeature::DestroyFeature(poFeature);
	}

	OGRDataSource::DestroyDataSource(poDataSource);

	return true;
}

bool CStakeInfo::BuildIndex(const std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>>& mapRoadOut,
	std::vector<DCoord>& vecCoords)
{
	

	unsigned int iLinkCount = 0;
	unsigned int iCoordCount = 0;

	for (auto itWay = mapRoadOut.cbegin(); itWay != mapRoadOut.cend(); ++itWay)
	{	
		auto itStakeWay = m_mapStakeIndex.find(itWay->first);
		if (itStakeWay == m_mapStakeIndex.end()) //添加路线
		{
			std::map<int, CLIndex> mapIndex;
			std::map<int, std::map<int, CLIndex>> mapIndexDir;
			mapIndexDir.insert(std::pair<int, std::map<int, CLIndex>>(1, mapIndex)); //上行
			m_mapStakeIndex.insert(std::pair<std::string, std::map<int, std::map<int, CLIndex>>>(itWay->first, mapIndexDir));
			mapIndexDir.clear();
			mapIndexDir.insert(std::pair<int, std::map<int, CLIndex>>(2, mapIndex)); //下行
			m_mapStakeIndex.insert(std::pair<std::string, std::map<int, std::map<int, CLIndex>>>(itWay->first, mapIndexDir));
			itStakeWay = m_mapStakeIndex.find(itWay->first);
		}

		auto itStakeInfo = m_mapStakeInfo.find(itWay->first);
		if (itStakeInfo == m_mapStakeInfo.end())
		{//没有找到这条路线的里程桩
			printf("High way without stake info! id = %s", itWay->first.c_str());
			continue;
		}

		//分开上下行处理里程桩的
		/*void BuildCLIndex(std::map<int, std::map<int, CLIndex>>& mapIndexDir,
			std::map<long long, std::vector<StakeInfo>>& mapStakeLink,
			const std::map<unsigned int, std::map<unsigned int, SWLink>>& mapRoadDir,
			std::vector<DCoord>& vecCoords, int iDir, unsigned int& iLinkCount, unsigned int& iCoordCount);*/
#ifndef ONLY_STAKE_DATA

		BuildCLIndex(itStakeWay->second, itStakeInfo->second, itWay->second, 
			vecCoords, 1, iLinkCount, iCoordCount); //上行


		BuildCLIndex(itStakeWay->second, itStakeInfo->second, itWay->second,
			vecCoords, 2, iLinkCount, iCoordCount); //下行
#else
		auto itWayDir = itWay->second.find(1);
		if (itWayDir != itWay->second.end())
		{
			auto itStakeDir = itStakeWay->second.find(1);
			if (itStakeDir == itStakeWay->second.end())
			{
				std::map<int, CLIndex> mapIndex;
				std::map<int, std::map<int, CLIndex>> mapIndexDir;
				itStakeWay->second.insert(std::pair<int, std::map<int, CLIndex>>(2, mapIndex)); //上行
			}

			
			for (auto itWayLink = itWayDir->second.cbegin(); itWayLink != itWayDir->second.cend(); ++itWayLink, ++iLinkCount)
			{
				const SWLink& stLink = itWayLink->second;
				const long long lLinkID = stLink.lLinkID;
				auto itStakeList = itStakeInfo->second.find(lLinkID);
				if (itStakeList == itStakeInfo->second.end())
				{
					continue;
				}
				else
				{
					std::vector<StakeInfo>& vecStakeInfo = itStakeList->second;
					size_t iLinkCoordCount = 0;
					for (auto itVecStake = vecStakeInfo.cbegin(); itVecStake != vecStakeInfo.cend(); ++itVecStake)
					{
						unsigned int nlPosPoint = -1;

						//放入到坐标容器中
						int nVecCount = vecCoords.size();
						vecCoords.push_back(itVecStake->dcoord);

						//建立里程桩的坐标索引
						unsigned int iCIndex = nVecCount;
						CLIndex stIndex;
						stIndex.CIndex = iCIndex;
						stIndex.LIndex = iLinkCount;
						itStakeDir->second.insert(std::pair<int, CLIndex>(itVecStake->stakeID, stIndex));

						iLinkCoordCount = stLink.coords.size();
					}
				}

				iCoordCount = vecCoords.size();
			}
		}
#endif // 

	}
	return true;
}

bool CStakeInfo::IsShapePoint(const DCoord& coord, const std::vector<DCoord>& vecCoords, unsigned int& nPos)
{
	auto itCoords = vecCoords.cbegin();
	nPos = 0;
	for (itCoords; itCoords != vecCoords.cend(); ++itCoords)
	{
		if (Equal(coord, *itCoords))
		{
			return true;
		}
		++nPos;
	}

	nPos = -1;
	return false;
}

//依次从容器中取出两点，计算两点间的距离，
//计算出需要插入的点到两个点之间的距离，
//如果两个距离与两点之间的距离相等，将插入点插入到这两点之间
unsigned int CStakeInfo::InserteLinePoint(const DCoord& coord, const std::vector<DCoord>& vecCoords, std::vector<DCoord>& newCoords)
{
	unsigned int nPos = 0;
	newCoords.assign(vecCoords.begin(), vecCoords.end());
	for (auto itCoords = newCoords.cbegin(); (itCoords + 1) != newCoords.cend(); ++itCoords)
	{
		const DCoord& coordA = *itCoords;
		const DCoord& coordB = *(itCoords + 1);
		double dbLenA = CalculateLength(coord.Lon, coord.Lat, coordA.Lon, coordA.Lat);
		double dbLenB = CalculateLength(coord.Lon, coord.Lat, coordB.Lon, coordB.Lat);
		double dbLenAB = CalculateLength(coordA.Lon, coordA.Lat, coordB.Lon, coordB.Lat);
		if (dbLenAB + 0.00005 >= (dbLenA + dbLenB))
		{
			++nPos;
			newCoords.insert(itCoords + 1, coord);
			return nPos;
		}
		
		++nPos;
	}

	return -1;
}

bool CStakeInfo::BuildIndex(std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>>& mapRoadOut,
	std::vector<DCoord>& vecCoords)
{

#ifdef ONLY_STAKE_DATA
	if (mapRoadOut.size() > 0)
	{
		return false;
	}
	
	if (vecCoords.size() > 0)
	{
		return false;
	}

	
	for (auto itWayStake = m_mapStakeInfo.begin(); itWayStake != m_mapStakeInfo.end(); ++itWayStake)
	{

		std::map<double, SWLink, StakeIDLess> mapLinkNetUp;
		std::map<double, SWLink, StakeIDMore> mapLinkNetDown;

		
		auto itWay = mapRoadOut.find(itWayStake->first);
		if (itWay == mapRoadOut.end())
		{
			std::map<unsigned int, std::map<unsigned int, SWLink>> mapDir;
			mapRoadOut.insert(make_pair(itWayStake->first, mapDir));
			itWay = mapRoadOut.find(itWayStake->first);
		}

		for (auto itLinkStake = itWayStake->second.begin(); itLinkStake != itWayStake->second.end(); ++itLinkStake)
		{

			StakeInfo& stStakeInfo = itLinkStake->second.at(0);

			SWLink stLink;
			stLink.strRoadID = stStakeInfo.routeID;
			stLink.lLinkID = stStakeInfo.lLinkID;
			stLink.iDir = stStakeInfo.iDir;
			stLink.dStartStake = stStakeInfo.stakeID;

			//建立每条路线的link序列
			const SWLink& link = stLink;
			double dbStakeStart = link.dStartStake;
			int iDir = link.iDir;

			if (iDir == DIR_UP)
			{
				mapLinkNetUp.insert(std::pair<double, SWLink>(dbStakeStart, link));
			}
			else if (iDir == DIR_DOWN)
			{
				mapLinkNetDown.insert(std::pair<double, SWLink>(dbStakeStart, link));
			}
		}

		//将上下行分成两组来处理
		std::map<unsigned int, SWLink> mapTemp;
		std::map<unsigned int, std::map<unsigned int, SWLink>>& mapRoadSig = itWay->second;
		mapRoadSig.insert(std::pair<unsigned int, std::map<unsigned int, SWLink>>(1, mapTemp));
		mapRoadSig.insert(std::pair<unsigned int, std::map<unsigned int, SWLink>>(2, mapTemp));

		auto itRoadSig = mapRoadSig.find(1);
		std::map<unsigned int, SWLink>& mapLinkOutUP = itRoadSig->second;
		int i = 0;
		auto itNetUp = mapLinkNetUp.cbegin();
		for (itNetUp; itNetUp != mapLinkNetUp.cend(); ++itNetUp, ++i)
		{
			mapLinkOutUP.insert(std::pair<unsigned int, SWLink>(i, itNetUp->second));
		}

		itRoadSig = mapRoadSig.find(2);
		std::map<unsigned int, SWLink>& mapLinkOutDown = itRoadSig->second;
		auto itNetDown = mapLinkNetDown.cbegin();
		for (itNetDown; itNetDown != mapLinkNetDown.cend(); ++itNetDown, ++i)
		{
			mapLinkOutDown.insert(std::pair<unsigned int, SWLink>(i, itNetDown->second));
		}
	}

	return BuildIndex(const_cast<const std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>>&>(mapRoadOut), vecCoords);
#endif //

	return true;
}

bool CStakeInfo::Build(const std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>>& mapRoadOut,
	std::vector<DCoord>& vecCoords)
{
	bool bRet = false;
	bRet = Load();

	if (!bRet)
	{
		printf("Load attrabute file failt!");
		return bRet;
	}

#ifdef ONLY_STAKE_DATA
	bRet = BuildIndex(const_cast<std::map<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>>&>(mapRoadOut), vecCoords);

#else
	bRet = BuildIndex(mapRoadOut, vecCoords);

#endif // ONLY_STAKE_DATA


	if (!bRet)
	{
		printf("Build Net file failt!");
		return bRet;
	}

	return bRet;
}

bool CStakeInfo::OutToIndexFile(std::string strOutPath)
{
	if (strOutPath.empty())
	{
		printf("outputPath is empty");
		return false;
	}
	if (strOutPath.find("\\") != strOutPath.size() - 1)
	{
		strOutPath += "\\";
	}
	std::string strPath = strOutPath;
	strPath += "mapindex.data";
	//outputPath += "mapindex.data";
	std::ofstream ofsFile;
	ofsFile.open(strPath.c_str(), std::ios_base::out | std::ios::binary);
	if (!ofsFile.good())
	{
		printf("coordsFile can not open");
		return false;
	}
	if (m_mapStakeIndex.empty())
	{
		printf( "m_mapStakeIndex is empty");
		return false;
	}

	SK::Index allIndex;
	
	int nWayCount = 0;
	for (auto itStakeWay = m_mapStakeIndex.begin(); itStakeWay != m_mapStakeIndex.end(); ++itStakeWay)
	{
		
		for (auto itStakeDir = itStakeWay->second.begin(); itStakeDir != itStakeWay->second.end(); ++itStakeDir)
		{
			SK::Index::mapIndex& mapIndex = *allIndex.add_mapindexs();
			auto itStake = itStakeDir->second.begin();
			for (itStake; itStake != itStakeDir->second.end(); ++itStake)
			{
				SK::Index::mapIndex::wayIndex& wayIndex = *mapIndex.add_wayindexs();
				wayIndex.set_stakenum(itStake->first);
				wayIndex.set_cindex(itStake->second.CIndex);
				wayIndex.set_lindex(itStake->second.LIndex);
			}

			mapIndex.set_code(itStakeWay->first.c_str());
			mapIndex.set_dir(itStakeDir->first);
			nWayCount++;
		}
		
	}
	allIndex.set_icount(nWayCount);

	if (!allIndex.SerializeToOstream(&ofsFile))
	{
		printf("serilize index in error");
		return false;
	}

	ofsFile.close();
	ofsFile.clear();
	return true;
}

void CStakeInfo::BuildCLIndex(std::map<int, std::map<int, CLIndex>>& mapIndexDir,
	std::map<long long, std::vector<StakeInfo>>& mapStakeLink,
	const std::map<unsigned int, std::map<unsigned int, SWLink>>& mapRoadDir,
	std::vector<DCoord>& vecCoords, int iDir,
	unsigned int& iLinkCount, unsigned int& iCoordCount)
{
	auto itWayDir = mapRoadDir.find(iDir);
	if (itWayDir != mapRoadDir.end())
	{
		auto itStakeDir = mapIndexDir.find(iDir);
		if (itStakeDir == mapIndexDir.end())
		{
			std::map<int, CLIndex> mapIndex;
			std::map<int, std::map<int, CLIndex>> mapIndexDir;
			mapIndexDir.insert(std::pair<int, std::map<int, CLIndex>>(iDir, mapIndex));
		}
		
		for (auto itWayLink = itWayDir->second.cbegin(); itWayLink != itWayDir->second.cend(); ++itWayLink, ++iLinkCount)
		{
			const SWLink& stLink = itWayLink->second;
			const long long lLinkID = stLink.lLinkID;
			auto itStakeList = mapStakeLink.find(lLinkID);
			if (itStakeList == mapStakeLink.end())
			{
				continue;
			}
			else
			{
				std::vector<StakeInfo>& vecStakeInfo = itStakeList->second;
				auto itVecStake = vecStakeInfo.cbegin();
				size_t iLinkCoordCount = 0;
				for (itVecStake; itVecStake != vecStakeInfo.cend(); ++itVecStake)
				{
					unsigned int nPosPoint = -1;
					if (IsShapePoint(itVecStake->dcoord, stLink.coords, nPosPoint))//正好是形状点
					{
						//放入到坐标容器中
						int nVecCount = vecCoords.size();
						vecCoords.insert(vecCoords.end(), stLink.coords.begin(), stLink.coords.end());

						//建立里程桩的坐标索引
						unsigned int iCIndex = nPosPoint + nVecCount;
						CLIndex stIndex;
						stIndex.CIndex = iCIndex;
						stIndex.LIndex = iLinkCount;
						itStakeDir->second.insert(std::pair<int, CLIndex>(itVecStake->stakeID, stIndex));

						iLinkCoordCount = stLink.coords.size();
					}
					else //不是形状点
					{
						//将点插入到坐标容器中
						std::vector<DCoord> vecNewCoords;
						nPosPoint = InserteLinePoint(itVecStake->dcoord, stLink.coords, vecNewCoords);

						//将新的坐标容器放入到总坐标容器中
						int nVecCount = vecCoords.size();
						vecCoords.insert(vecCoords.end(), vecNewCoords.begin(), vecNewCoords.end());

						//建立里程桩的坐标索引
						unsigned int iCIndex = nPosPoint + nVecCount;
						CLIndex stIndex;
						stIndex.CIndex = iCIndex;
						stIndex.LIndex = iLinkCount;
						itStakeDir->second.insert(std::pair<int, CLIndex>(itVecStake->stakeID, stIndex));

						iLinkCoordCount = vecNewCoords.size();

					}
				}
			}

			iCoordCount += iLinkCount;
		}
	}
}