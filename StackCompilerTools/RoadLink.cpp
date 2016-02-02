#include "stdafx.h"
#include "RoadLink.h"
#include "proto\CoordInfo.pb.h"


CRoadLink::CRoadLink(const std::string strPath)
{
	m_strPath = strPath;
}


CRoadLink::~CRoadLink()
{
}

bool CRoadLink::Build()
{
	bool bRet = false;
	bRet = Load();

	if (!bRet)
	{
		printf("Load attrabute file failt!");
		return bRet;
	}

	bRet = BuildNet();

	if (!bRet)
	{
		printf("Build Net file failt!");
		return bRet;
	}

	return bRet;
}

//加载文件，获取link的属性值
bool CRoadLink::Load() 
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
		SWLink stRoadInfo;
		try
		{
			stRoadInfo.strRoadID = poFeature->GetFieldAsString("LXBM");
			stRoadInfo.strRouteName = poFeature->GetFieldAsString("LXMC");
			stRoadInfo.iDir = poFeature->GetFieldAsInteger("SXX");
			stRoadInfo.lLinkID = poFeature->GetFieldAsInteger("LinkID");
			stRoadInfo.strProvince = poFeature->GetFieldAsString("FDSSS");
			stRoadInfo.strCity = poFeature->GetFieldAsString("FDDJS");
			stRoadInfo.strBCity = poFeature->GetFieldAsString("FDQDX");
			stRoadInfo.strEcity = poFeature->GetFieldAsString("FDZDX");
			stRoadInfo.dStartStake = poFeature->GetFieldAsDouble("QDZH");
			stRoadInfo.dEndStake = poFeature->GetFieldAsDouble("ZDZH");
			
			if (stRoadInfo.strRoadID == "")
				continue;

			//获取路链的轨迹
			OGRLinearRing *pOGRLine = (OGRLinearRing*)poFeature->GetGeometryRef();

			bool bRet = GetLinkNode(pOGRLine, stRoadInfo.coords);

			auto itWay = m_mapRoad.find(stRoadInfo.strRoadID);
			if (itWay != m_mapRoad.end())
			{
				map<long long, SWLink>& mapLink = itWay->second;
				auto itLink = mapLink.find(stRoadInfo.lLinkID);
				if (itLink != mapLink.end())
				{
					printf("link id is repead, id = %I64d ", stRoadInfo.lLinkID);
				}
				else
				{
					mapLink.insert(std::pair<long long, SWLink>(stRoadInfo.lLinkID, stRoadInfo));
				}
			}
			else
			{
				map<long long, SWLink> mapLink;
				mapLink.insert(std::pair<long long, SWLink>(stRoadInfo.lLinkID, stRoadInfo));
				m_mapRoad.insert(std::pair<std::string, std::map<long long, SWLink>>(stRoadInfo.strRoadID, mapLink));
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

//获取每条link的轨迹
bool CRoadLink::GetLinkNode(const OGRLinearRing* pOGRLine, std::vector<DCoord>& vecCoord)
{
	int iNodeCount = pOGRLine->getNumPoints();

	if (iNodeCount == 0)
	{
		printf("link's point num is 0!");
		return false;
	}

	for (int i = 0; i < iNodeCount; ++i)
	{
		DCoord coord;
		coord.Lat = pOGRLine->getY(i);
		coord.Lon = pOGRLine->getX(i);

		vecCoord.push_back(coord);
	}

	return true;
}

//建立每条路线的拓扑
bool CRoadLink::BuildNet()
{
	if (m_mapRoad.size() <= 0)
	{
		return false;
	}

	auto itWay = m_mapRoad.cbegin();
	for (itWay; itWay != m_mapRoad.cend(); itWay++)
	{
		const std::map<long long, SWLink>& mapLink = itWay->second;
		auto itLink = mapLink.cbegin();

		//建立每条路线的link序列
		std::map<double, SWLink, StakeIDLess> mapLinkNetUp;
		std::map<double, SWLink, StakeIDMore> mapLinkNetDown;
		for (itLink; itLink != mapLink.cend(); itLink++)
		{
			const SWLink& link = itLink->second;
			double dbStakeStart = link.dStartStake;
			int iDir = link.iDir;

			if (iDir == DIR_UP)
			{
				mapLinkNetUp.insert(std::pair<double, SWLink>(dbStakeStart, link));
			}
			else if(iDir == DIR_DOWN)
			{
				mapLinkNetDown.insert(std::pair<double, SWLink>(dbStakeStart, link));
			}
		}

		//将上下行分成两组来处理
		std::map<unsigned int, SWLink> mapTemp;
		std::map<unsigned int, std::map<unsigned int, SWLink>> mapRoadSig;
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

		m_mapOutRoad.insert(std::pair<std::string, std::map<unsigned int, std::map<unsigned int, SWLink>>>(itWay->first, mapRoadSig));
	}

	return true;
}

bool CRoadLink::OutToLinkFile(std::string strOutPath)
{
	if (strOutPath.empty())
	{
		printf("outputPath is empty");
		return false;
	}
	if (strOutPath.rfind("\\") != strOutPath.size() - 1)
	{
		strOutPath += "\\";
	}
	string strPath = strOutPath;
	strPath += "link.txt";
	//outputPath += "link.txt";
	ofstream ofsFile;
	ofsFile.open(strPath.c_str(), ios::binary);
	if (!ofsFile.good())
	{
		printf("output file can not open" );
		return false;
	}
	if (m_mapOutRoad.size() == 0)
	{
		printf("highway struct is empty");
		return false;
	}
	ofsFile.setf(ios::fixed);
	ofsFile.setf(ios::showpoint);
	ofsFile.precision(5);
	//写正向的link
	auto itWay = m_mapOutRoad.begin();
	for (; itWay != m_mapOutRoad.end(); ++itWay)
	{
		map<unsigned int, map<unsigned int, SWLink>>& refGroupLinks = itWay->second;
		auto itDirLink = refGroupLinks.begin();
		for (; itDirLink != refGroupLinks.end(); ++itDirLink)
		{
			map<unsigned int, SWLink>& refLinks = itDirLink->second;
			auto itLink = refLinks.begin();
			for (; itLink != refLinks.end(); ++itLink)
			{

				SWLink& refLink = itLink->second;
				ofsFile << refLink.strRoadID << "," << refLink.strRouteName << "," << refLink.lLinkID << ","
					<< refLink.iLineGroup << "," << refLink.iPartialOrder << "," << refLink.iDir << ","
					<< refLink.iPrimary << "," << refLink.strProvince << "," << refLink.strBCity << ","
					<< refLink.strEcity << "," << refLink.iClass << "," << refLink.dLength << ","
					<< refLink.iRouteNum << "," << refLink.iWidth << "," << refLink.iSpeed << ","
					/*<<refLink.dStartStake<<","<<refLink.dEndStake<<","*/ << refLink.strPhoneNum << endl;
			}
		}
	}
	ofsFile.close();

	return true;
}

bool CRoadLink::OutToCoordFileProto(std::string strOutPath)
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
	strPath += "coords.data";
	//outputPath += "mapindex.data";
	std::ofstream ofsFile;
	ofsFile.open(strPath.c_str(), std::ios_base::out | std::ios::binary);
	if (!ofsFile.good())
	{
		printf("coordsFile can not open");
		return false;
	}
	if (m_vecCoords.empty())
	{
		printf("m_mapStakeIndex is empty");
		return false;
	}

	SK::CoordInfo allCoord;
	for (auto itVecCoords = m_vecCoords.begin(); itVecCoords != m_vecCoords.end(); ++itVecCoords)
	{
		DCoord& refDCoord = *itVecCoords;
		SK::CoordInfo::Coord& coord = *allCoord.add_coords();
		coord.set_lat(refDCoord.Lat);
		coord.set_lon(refDCoord.Lon);
	}
	allCoord.set_icount(static_cast<int>(m_vecCoords.size()));

	if (!allCoord.SerializeToOstream(&ofsFile))
	{
		printf("serilize index in error");
		return false;
	}

	ofsFile.close();
	ofsFile.clear();
	return true;
}

bool CRoadLink::OutToCoordFileBinary(std::string strOutPath)
{
	string strPath = strOutPath;
	strPath += "\\coords.data";
	//outputPath += "coords.data";
	ofstream ofsFile;
	ofsFile.open(strPath.c_str(), ios::out | ios::binary);
	if (!ofsFile.good())
	{
		cout << "coordsFile can not open" << endl;
		return false;
	}
	//if (m_mapCoord.empty())
	if (m_vecCoords.empty())
	{
		cout << "m_vecCoords is empty" << endl;
		return false;
	}
	//unsigned int offset = 0;

	__int64 coordNum = 0;
	//ofsFile.write((char*) &coordNum,sizeof(__int64));
	vector<DCoord>::iterator iterCoord = m_vecCoords.begin();
	for (; iterCoord != m_vecCoords.end(); iterCoord++)
	{
		//vector<DCoord>& refCoords = iterCoord->second;
		//coordNum += refCoords.size();
		//for (int i=0;i<refCoords.size();i++)
		{
			// 			double Lat = refCoords[i].Lat/100000.0;
			// 			double Lon = refCoords[i].Lon/100000.0;
			double Lat = iterCoord->Lat;
			double Lon = iterCoord->Lon;
			DCoord tempCoord;
			tempCoord.Lat = Lat;
			tempCoord.Lon = Lon;
			//ofsFile.write((char*)&Lat,sizeof(double));
			//ofsFile.write((char*)&Lon,sizeof(double));
			ofsFile.write((char*)&tempCoord, sizeof(DCoord));
		}
	}
	ofsFile.seekp(0);
	int iSize = m_vecCoords.size();
	//ofsFile.write((char*) &iSize,sizeof(__int64));
	ofsFile.close();
	ofsFile.clear();

	return true;
}