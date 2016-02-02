#include "stdafx.h"
#include "FacilityOfRoad.h"
#include "proto\POIIndex.pb.h"
#include <fstream>


CFacilityOfRoad::CFacilityOfRoad(std::string strPath)
	: m_strPath(strPath)
{
}


CFacilityOfRoad::~CFacilityOfRoad()
{
}

bool CFacilityOfRoad::Build(const std::map<std::string, std::map<long long, SWLink>>& mapRoad)
{
	bool bRet = false;
	bRet = Load();

	if (!bRet)
	{
		printf("Load attrabute file failt!");
		return bRet;
	}

	bRet = BuildOut(mapRoad);

	if (!bRet)
	{
		printf("Build Net file failt!");
		return bRet;
	}

	return bRet;

	return true;
}

bool CFacilityOfRoad::OutToIndexFile(std::string strOutPath)
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
	strPath += "poiindex.data";
	//outputPath += "mapindex.data";
	std::ofstream ofsFile;
	ofsFile.open(strPath.c_str(), std::ios_base::out | std::ios::binary);
	if (!ofsFile.good())
	{
		printf("coordsFile can not open");
		return false;
	}
	if (m_mapFacilityInfo.empty())
	{
		printf("m_mapStakeIndex is empty");
		return false;
	}

	SK::POIIndex allIndex;
	for (auto itFacWay = m_mapFacilityInfo.begin(); itFacWay != m_mapFacilityInfo.end(); itFacWay++)
	{
		MapDir& mapFacDir = itFacWay->second;
		for (auto itFacDir = mapFacDir.begin(); itFacDir != mapFacDir.end(); itFacDir++)
		{
			MapStake& mapFacStake = itFacDir->second;
			SK::POIIndex::mapPOI& mapPoi = *allIndex.add_roads();
			mapPoi.set_code(itFacWay->first);
			mapPoi.set_dir(itFacDir->first);
			for (auto itFacStake = mapFacStake.begin(); itFacStake != mapFacStake.end(); itFacStake++)
			{
				MapType& mapFacType = itFacStake->second;
				SK::POIIndex::mapPOI::stakePOI& stakePoi = *mapPoi.add_stakepois();
				stakePoi.set_stakenum(static_cast<int>(itFacStake->first));
				for (auto itFacType = mapFacType.begin(); itFacType != mapFacType.end(); itFacType++)
				{
					std::vector<Facility>& vecFacility = itFacType->second;
					SK::POIIndex::mapPOI::stakePOI::typePOI& typePoi = *stakePoi.add_typepois();
					typePoi.set_type(itFacType->first);
					for (auto itVecFac = vecFacility.begin(); itVecFac != vecFacility.end(); itVecFac++)
					{
						Facility& refFacility = *itVecFac;
						SK::POIIndex::mapPOI::stakePOI::typePOI::POI& poi = *typePoi.add_pois();
						poi.set_name(refFacility.strName);
						poi.set_lat(refFacility.coord.Lat);
						poi.set_lon(refFacility.coord.Lon);
					}
				}
			}
		}
	}
	allIndex.set_icount(static_cast<int>(m_mapFacilityInfo.size()));

	if (!allIndex.SerializeToOstream(&ofsFile))
	{
		printf("serilize index in error");
		return false;
	}

	ofsFile.close();
	ofsFile.clear();
	
	return false;
}

bool CFacilityOfRoad::Load()
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
		Facility stFacility;
		try
		{
			stFacility.strRoadID = poFeature->GetFieldAsString("LXBM");
			stFacility.iPoiID = poFeature->GetFieldAsInteger("POI_ID");
			stFacility.lLinkID = poFeature->GetFieldAsInteger("LINKID");
			stFacility.iType = poFeature->GetFieldAsInteger("Kind");
			stFacility.iDir = poFeature->GetFieldAsInteger("SXX");
			stFacility.dbStakeInLine = poFeature->GetFieldAsDouble("FWQZXZH");
			stFacility.strName = poFeature->GetFieldAsString("FWQMC");

			OGRPoint* pOGRPoint = (OGRPoint*)poFeature->GetGeometryRef();
			stFacility.coord.Lat = pOGRPoint->getX();
			stFacility.coord.Lon = pOGRPoint->getY();

			m_vecFacility.push_back(stFacility);
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

bool CFacilityOfRoad::BuildOut(const std::map<std::string, std::map<long long, SWLink>> mapRoad)
{
	auto itVecFacility = m_vecFacility.begin();
	for (itVecFacility; itVecFacility != m_vecFacility.end(); ++itVecFacility)
	{
		Facility& refFacility = *itVecFacility;
		auto itWay = mapRoad.find(refFacility.strRoadID);
		if (itWay != mapRoad.end())
		{
			auto itWayLink = itWay->second.find(refFacility.lLinkID);
			if (itWayLink == itWay->second.end())
			{
				continue;
			}

			const SWLink& refLink = itWayLink->second;
			refFacility.iDir = refLink.iDir;

			auto itFacWay = m_mapFacilityInfo.find(refFacility.strRoadID);
			if (itFacWay == m_mapFacilityInfo.end())
			{
				MapDir mapFacDir;
				m_mapFacilityInfo.insert(std::pair<std::string, MapDir>(refFacility.strRoadID, mapFacDir));
				itFacWay = m_mapFacilityInfo.find(refFacility.strRoadID);
			}

			auto itFacDir = itFacWay->second.find(refFacility.iDir);
			if (itFacDir == itFacWay->second.end())
			{
				MapDir& mapFacDir = itFacWay->second;
				MapStake mapFacStake;
				mapFacDir.insert(std::pair<unsigned int, MapStake>(refFacility.iDir, mapFacStake));
				itFacDir = itFacWay->second.find(refFacility.iDir);
			}

			auto itFacStake = itFacDir->second.find(refFacility.dbStakeInLine);
			if (itFacStake == itFacDir->second.end())
			{
				MapStake& mapFacStake = itFacDir->second;
				MapType mapFacility;
				mapFacStake.insert(std::pair<double, MapType>(refFacility.dbStakeInLine, mapFacility));
				itFacStake = itFacDir->second.find(refFacility.dbStakeInLine);
			}

			auto itFacType = itFacStake->second.find(refFacility.iType);
			if (itFacType == itFacStake->second.end())
			{
				MapType& mapFacility = itFacStake->second;
				std::vector<Facility> vecFacility;
				mapFacility.insert(std::pair<unsigned int, std::vector<Facility>>(refFacility.iType, vecFacility));
				itFacType = itFacStake->second.find(refFacility.iType);
			}

			itFacType->second.push_back(refFacility);

		}
		else
		{

		}
	}
	return true;
}

