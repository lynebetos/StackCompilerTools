#include "stdafx.h"
#include "ShpNetModuleBuilder.h"
#include "gdal/ogrsf_frmts.h"
#include "./RoadNet/Link.h"
#include "./Supporter/GisSupporter.h"
#include <assert.h>
//#include "Global.h"
#include <algorithm>

//#include "../Global.h"

//#include <boost/format.hpp>
//#include <boost/lexical_cast.hpp>
//using namespace boost;

CShpNetModuleBuilder::CShpNetModuleBuilder(const string& strShpPath)
{
	m_strMapPath = strShpPath;
	m_lLinkCount = -1;
}

CShpNetModuleBuilder::~CShpNetModuleBuilder(void)
{
	if (NULL != m_ppLink)
	{
		if (NULL != *m_ppLink)
		{
			delete[] *m_ppLink;
			*m_ppLink = NULL;
		}

		delete m_ppLink;
		m_ppLink = NULL;
	}
	///for_each(m_mapLink.begin(), m_mapLink.end(), DeleteMapValue1());
	map<string, CLink*> mapLink;
	m_mapLink.swap(mapLink);
	mapLink.clear();
}
void CShpNetModuleBuilder::reviseSENodeInfo(unsigned long& lFjcid,unsigned long& lTjcid,OGRLineString *pOGRLine,map<string, unsigned __int64>& mapReviseInfo,unsigned long &lnNodeId)
{
		// 获取起点坐标经纬度
		double x = pOGRLine->getX(0);
		double y = pOGRLine->getY(0);
		// double lReviseData = x + y;
		//string strRevise = boost::str(boost::format("%.6f_%.6f") %x %y);
		char chBufferX[11];
		sprintf_s(chBufferX,"%.6f",x);
		string strRevise = chBufferX;
		strRevise += "_";
		char chBufferY[11];
		sprintf_s(chBufferY,"%.6f",y);
		strRevise += chBufferY;
		map<string, unsigned __int64>::iterator itReviseFind = mapReviseInfo.find(strRevise);
		if (itReviseFind == mapReviseInfo.end())
		{
			mapReviseInfo.insert(make_pair(strRevise, lnNodeId));
			lFjcid = lnNodeId;
			lnNodeId++;
		}
		else
		{
			lFjcid = itReviseFind->second;
		}

		// 获取终点坐标经纬度
		int pn = pOGRLine->getNumPoints();
		double x1 = pOGRLine->getX(pn - 1);
		double y1 = pOGRLine->getY(pn - 1);
		char chBufferX1[11];
		sprintf_s(chBufferX1,"%.6f",x1);
		string strRevise1 = chBufferX1;
		strRevise1 += "_";
		char chBufferY1[11];
		sprintf_s(chBufferY1,"%.6f",y1);
		strRevise1 += chBufferY1;
		//string strRevise1 = boost::str(boost::format("%.6f_%.6f") %x1 %y1);
		map<string, unsigned __int64>::iterator itReviseFind1 = mapReviseInfo.find(strRevise1);
		if (itReviseFind1 == mapReviseInfo.end())
		{
			mapReviseInfo.insert(make_pair(strRevise1, lnNodeId));
			lTjcid = lnNodeId;
			lnNodeId++;
		}
		else
		{
			lTjcid = itReviseFind1->second;
		}
}

long CShpNetModuleBuilder::Build()
{
	m_lLinkCount = GetLinkCount();

	if (m_lLinkCount <= 0)
	{
		return -1;
	}

	// 设置路段对象大小的数组.
	m_ppLink = new CLink*();
	*(m_ppLink) = new CLink[m_lLinkCount];

	CLink* pTempLink = *m_ppLink;	// 设置操作的局部变量.
	int nLinkIndex = 0; 

	OGRRegisterAll();

	OGRDataSource* poDS = OGRSFDriverRegistrar::Open( m_strMapPath.c_str(), FALSE );
	if( poDS == NULL )
	{
		/*LOG4CPLUS_ERROR(g_pSystemLog, "Open failed [" << m_strMapPath << "]");*/
		printf( "Open failed [%s].\n",m_strMapPath.c_str());
		return FALSE;
	}

	// 这个multimap仅仅用作临时变量，用来存储实际路段的起点和对应的链接指针
	multimap<unsigned long, CLink*> NodMultiMap;
	//这个Endmultimap仅仅用作临时变量，用来存储实际路段的起点和对应的链接指针
	multimap<unsigned long, CLink*> EndNodMultiMap;

	OGRLayer  *poLayer = poDS->GetLayerByName( CPLGetBasename(m_strMapPath.c_str()));
	poLayer->ResetReading();
	OGRFeature *poFeature;
	m_lRecordCount = poLayer->GetFeatureCount();
	map<string, unsigned __int64> mapReviseInfo;
	unsigned long lnNodeId = 1;
	int iReNum = 0;
	while( (poFeature = poLayer->GetNextFeature()) != NULL )
	{
		iReNum++;
		if (nLinkIndex ==  1054964)
		{
			int a = 0;
		}
		int iMeshid(poFeature->GetFieldAsInteger("MESHID"));// MESHID
		unsigned long lLinkId = strtoul(poFeature->GetFieldAsString("LINKID"),0,10);
		//char chLinkId[20];
		//ltoa(lLinkId,chLinkId,10);
		//unsigned long lFjcid = strtoul(poFeature->GetFieldAsString("FJCID"),0,10);
		//unsigned long lTjcid = strtoul(poFeature->GetFieldAsString("TJCID"),0,10);
		string strBynamec(poFeature->GetFieldAsString("NAME"));// 
		double dLength(poFeature->GetFieldAsDouble("LENGTH"));// 路段长度
		int iDF(poFeature->GetFieldAsInteger("DF"));	// 
		int iNR(poFeature->GetFieldAsInteger("NR")); 
		int iFW(poFeature->GetFieldAsInteger("FW"));
		int iFC(poFeature->GetFieldAsInteger("FC"));
		int iRstruct(poFeature->GetFieldAsInteger("RS"));
		int iSR(poFeature->GetFieldAsInteger("SR"));
		int iEH(poFeature->GetFieldAsInteger("EH"));
		int iTL(poFeature->GetFieldAsInteger("TL"));
		int iTS(poFeature->GetFieldAsInteger("TS"));
		//double dMaxspeed(poFeature->GetFieldAsDouble("MAXSPEED"));
		//double dMinspeed(poFeature->GetFieldAsDouble("MINSPEED"));
		
		OGRLineString *pOGRLine = (OGRLineString *)poFeature->GetGeometryRef();

		// 根据地理数据库中的信息填充路段属性.
		CLink* pLink = pTempLink + nLinkIndex;
		pLink->m_iMeshid = iMeshid;
		pLink->m_lLinkid = lLinkId;
		//pLink->m_lStartNode = lFjcid;
		//pLink->m_lEndNode = lTjcid;
		pLink->m_strLinkName = strBynamec;
		pLink->m_dLength = dLength;
		pLink->m_iLinkDegree = iNR;
		pLink->m_iLinkForm = iFW;
		pLink->m_iFC = iFC;
		pLink->m_iRS = iRstruct;
		pLink->m_iSR = iSR;
		pLink->m_iEH = iEH;
		//初始化路链最大速度，为计算扩展路链长度使用

		//pLink->m_iTL = iTL;
		//pLink->m_iTS = iTS;
		//pLink->m_dMaxSpeed = dMaxspeed;
		//pLink->m_dMinSpeed = dMinspeed;
		InitializeLinkMaxSpeed(pLink);
		unsigned long lFjcid;
		unsigned long lTjcid;
		
		reviseSENodeInfo(lFjcid,lTjcid,pOGRLine,mapReviseInfo,lnNodeId);
		pLink->m_lStartNode = lFjcid;
		pLink->m_lEndNode = lTjcid;
		switch(iDF)	
		{
		case 0:
		case 1: // 双向道路
			{
				// 构造正向路段
				pLink->m_iUpDirect = 1;
				BuildNet(pLink, NodMultiMap,EndNodMultiMap, pOGRLine, true);

				nLinkIndex++;

				// 构造反向路段
				CLink* pLink = pTempLink + nLinkIndex;
				pLink->m_iMeshid = iMeshid;
				pLink->m_lLinkid = lLinkId;
				pLink->m_lStartNode = lFjcid;
				pLink->m_lEndNode = lTjcid;
				pLink->m_strLinkName = strBynamec;
				pLink->m_dLength = dLength;
				pLink->m_iLinkDegree = iNR;
				pLink->m_iLinkForm = iFW;
				pLink->m_iFC = iFC;
				pLink->m_iRS = iRstruct;
				pLink->m_iSR = iSR;
				pLink->m_iEH = iEH;
				//pLink->m_iTL = iTL;
				//pLink->m_iTS = iTS;
				//pLink->m_dMaxSpeed = dMaxspeed;
				//pLink->m_dMinSpeed = dMinspeed;
				InitializeLinkMaxSpeed(pLink);
				pLink->m_iUpDirect = 2;
				BuildNet(pLink, NodMultiMap,EndNodMultiMap, pOGRLine, false);

				nLinkIndex++;
				break;
			}
		case 2: // 正向
			{
				pLink->m_iUpDirect = 1;
				BuildNet(pLink, NodMultiMap,EndNodMultiMap, pOGRLine, true);
				nLinkIndex++;
				break;
			}

		case 3: // 反向
			{
				pLink->m_iUpDirect = 2;
				BuildNet(pLink, NodMultiMap,EndNodMultiMap, pOGRLine, false);
				nLinkIndex++;
				break;
			}
		case 4:
		default:
			break;
		}

		OGRFeature::DestroyFeature( poFeature );
	}

	OGRDataSource::DestroyDataSource( poDS );
	mapReviseInfo.clear();
	BuildNextTopo(NodMultiMap);
	BuildPreTopo(EndNodMultiMap);
	return m_lLinkCount;
}
void CShpNetModuleBuilder::InitializeLinkMaxSpeed(CLink * &  pLink)
{
	if (1 == pLink->m_iFC)
	{
		pLink->m_dMaxSpeed = 100;
	}
	else if (2 == pLink->m_iFC)
	{
		pLink->m_dMaxSpeed = 80;
	}
	else if (pLink->m_iFC > 2 && pLink->m_iFC <= 6)
	{
		pLink->m_dMaxSpeed = 60;
	}
	else
		pLink->m_dMaxSpeed = 50;

}

long CShpNetModuleBuilder::GetLinkCount()
{
	long lLinkCount(0);
	OGRRegisterAll();

	OGRDataSource* poDS;

	poDS = OGRSFDriverRegistrar::Open( m_strMapPath.c_str(), FALSE );
	if( poDS == NULL )
	{
		/*LOG4CPLUS_ERROR(g_pSystemLog, "Open failed [" << m_strMapPath << "]");*/
		printf( "Open failed [%s].\n",m_strMapPath.c_str() );
		return FALSE;
	}

	OGRLayer  *poLayer;
	OGRFeature *poFeature;
	poLayer = poDS->GetLayerByName( CPLGetBasename(m_strMapPath.c_str()) );
	poLayer->ResetReading();
	while( (poFeature = poLayer->GetNextFeature()) != NULL )
	{
		try
		{ 
			int iDF = poFeature->GetFieldAsInteger("DF"); // DF=4 的路去掉
			switch(iDF)
			{
			case 0:
			case 1://双向：双方向可以通行
				lLinkCount += 2;	// 双向路
				break;
			case 2://顺方向：单向通行，通行方向为起点到终点方向
			case 3://逆方向：单向通行，通行方向为终点到起点方向
				lLinkCount += 1;
				break;
			case 4:
			default:
				;
			}
		}
		catch (std::exception& e)
		{
			printf("The layer is not the SIWEI WEB standard format.\n");
			printf("%s\n",e.what());
			OGRFeature::DestroyFeature( poFeature );
			OGRDataSource::DestroyDataSource( poDS );

			return -1;
		}
		OGRFeature::DestroyFeature( poFeature );
	}

	OGRDataSource::DestroyDataSource( poDS );
	return lLinkCount;
}

void CShpNetModuleBuilder::BuildNet( CLink* pLink, multimap<unsigned long, CLink*>& NodMultiMap, multimap<unsigned long, CLink*>& EndNodMultiMap, OGRLineString *pOGRLine, bool bForward )
{
	// 构建路网结构
	size_t nPoints(pOGRLine->getNumPoints());

	assert(nPoints >= 2);
	if (nPoints < 2)
	{
		return;
	}

	// 路段起点和终点所构成向量的长度.
	double vectorLen = 0.0;
	OGRPoint startPoint;
	OGRPoint endPoint;
	pOGRLine->getPoint(0, &startPoint);
	pOGRLine->getPoint(nPoints - 1, &endPoint);
	if (bForward)
	{
		// 正向
		pLink->m_pFNode = new CNode();
		pLink->m_pTNode = new CNode();

		pLink->m_pFNode->m_lCarId = pLink->m_lStartNode;
		pLink->m_pFNode->m_dLongitude = startPoint.getX();
		pLink->m_pFNode->m_dLatitude = startPoint.getY();

		pLink->m_pTNode->m_lCarId = pLink->m_lEndNode;
		pLink->m_pTNode->m_dLongitude = endPoint.getX();
		pLink->m_pTNode->m_dLatitude = endPoint.getY();

		pLink->m_iVertexCount = nPoints;

		// 填充内点数组数据.
		BuildVertexs(pLink, pOGRLine);

		// 计算路段起点和终点所构成向量的长度.
		vectorLen = CGisSupporter::CalculateLength(startPoint.getX(), startPoint.getY(), 
			endPoint.getX(), endPoint.getY());

		// 判断路段是否弯曲.
		if(pLink->m_dLength / vectorLen - 1.05 > 1e-6)
			pLink->m_bTortuousLink = true;

		// 插入路段ID与路段对象的Map数组.
		char chLinkId[20];
		_ltoa_s(pLink->m_lLinkid,chLinkId,10);
		string strLinkID = chLinkId;
		m_mapLink.insert(std::pair<string, CLink*>(strLinkID + "_1", pLink)); 
		NodMultiMap.insert(multimap<unsigned long,CLink*>::value_type(pLink->m_lStartNode, pLink));
		EndNodMultiMap.insert(multimap<unsigned long,CLink*>::value_type(pLink->m_lEndNode, pLink));
	}
	else
	{
		// 构造反向路段.
		pLink->m_pFNode = new CNode();
		pLink->m_pTNode = new CNode();

		pLink->m_pFNode->m_lCarId = pLink->m_lEndNode;
		pLink->m_pFNode->m_dLongitude = endPoint.getX();
		pLink->m_pFNode->m_dLatitude = endPoint.getY();

		pLink->m_pTNode->m_lCarId = pLink->m_lStartNode;
		pLink->m_pTNode->m_dLongitude = startPoint.getX();
		pLink->m_pTNode->m_dLatitude = startPoint.getY();

		pLink->m_iVertexCount = nPoints;

		// 填充内点数组数据.
		BuildVertexs(pLink, pOGRLine);

		// 计算路段起点和终点所构成向量的长度.
		vectorLen = CGisSupporter::CalculateLength(startPoint.getX(), startPoint.getY(), 
			endPoint.getX(), endPoint.getY());

		// 判断路段是否弯曲.
		if(pLink->m_dLength / vectorLen - 1.05 > 1e-6)
			pLink->m_bTortuousLink = true;

		// 插入路段ID与路段对象的Map数组.
		char chLinkId[20];
		_ltoa_s(pLink->m_lLinkid,chLinkId,10);
		string strLinkID = chLinkId;
		m_mapLink.insert(std::pair<string, CLink*>(strLinkID+ "_2", pLink)); 
		NodMultiMap.insert(multimap<unsigned long, CLink*>::value_type(pLink->m_lEndNode, pLink));
		EndNodMultiMap.insert(multimap<unsigned long,CLink*>::value_type(pLink->m_lStartNode, pLink));
	}
}

void CShpNetModuleBuilder::BuildVertexs( CLink* pLink, OGRLineString *pOGRLine )
{
	int nTrafficFlo = pLink->m_iUpDirect;	
	int iPointCount = pOGRLine->getNumPoints();
	if (iPointCount < 1)
	{
		return;
	}

	pLink->m_iVertexCount = iPointCount;
	pLink->m_ppVertex= new CVertex*();
	*(pLink->m_ppVertex) = new CVertex[iPointCount];//分配的实际数组 
	
	CVertex* pTmpVertex= *(pLink->m_ppVertex);  //
	
	int nCurIndex(0);
	for(int nTemp = 0; nTemp < iPointCount; nTemp++)
	{
		if(nTrafficFlo == 1)	// 正向.
			nCurIndex = nTemp;
		else			// 反向. (在内点数组中我们是从0开始的，所以采用iTemp-1)
			nCurIndex = iPointCount - nTemp - 1;

		OGRPoint pPoint;
		pOGRLine->getPoint(nCurIndex, &pPoint);

		pTmpVertex[nTemp].m_dLongitude = pPoint.getX();
		pTmpVertex[nTemp].m_dLatitude = pPoint.getY();
		pTmpVertex[nTemp].m_pLink = pLink; 


		//计算上个点到当前点之间的距离及方向角
		if(nTemp>0)
		{
			pTmpVertex[nTemp-1].m_dDistanceToNext =
				CGisSupporter::CalculateLength(pTmpVertex[nTemp-1].m_dLongitude, 
				pTmpVertex[nTemp-1].m_dLatitude, 
				pTmpVertex[nTemp].m_dLongitude, 
				pTmpVertex[nTemp].m_dLatitude);

			pTmpVertex[nTemp-1].m_iAngleToNext = 
				CGisSupporter::CalculateAngle(pTmpVertex[nTemp-1].m_dLongitude,
				pTmpVertex[nTemp-1].m_dLatitude,
				pTmpVertex[nTemp].m_dLongitude,
				pTmpVertex[nTemp].m_dLatitude);

		}
	}

	//最后一个内点距离及方向角设为0.
	pTmpVertex[iPointCount-1].m_dDistanceToNext = 0;
	pTmpVertex[iPointCount-1].m_iAngleToNext = 0;	
	
	// 路段的方向设置为路段起点和路段终点所组成的向量的方向.
	pLink->m_iAzimuth = CGisSupporter::CalculateAngle(pTmpVertex[0].m_dLongitude, 
	pTmpVertex[0].m_dLatitude, 
	pTmpVertex[iPointCount-1].m_dLongitude, 
	pTmpVertex[iPointCount-1].m_dLatitude);
}

//void CShpNetModuleBuilder::BuildNetTopo(multimap<unsigned long, CLink*>& NodMultiMap )
//{
//	BuildNextTopo(NodMultiMap);
//	BuildPreTopo(NodMultiMap);
//}
void CShpNetModuleBuilder::BuildNextTopo(multimap<unsigned long, CLink*>& NodMultiMap )
{
	// 建立路网拓扑.
	typedef multimap<unsigned long, CLink*>::size_type sz_type;
	typedef multimap<unsigned long, CLink*>::iterator mul_map_iter;
	mul_map_iter iter;

	CLink* pTempLink = *m_ppLink;	// 设置操作的局部变量.
	for(int i = 0; i < m_lLinkCount; ++i)
	{
		// 获取一条路段.
		CLink* pLocalTempLink = pTempLink + i;
		pLocalTempLink->m_iNextLinkCount = 0;

		// 以TNode 为起始节点的路段数.
		sz_type iObjectLinkCount = NodMultiMap.count(pLocalTempLink->m_pTNode->m_lCarId);// 路段终点ID.
		if(iObjectLinkCount == 0)
			pLocalTempLink->m_ppNextLinks = NULL;
		else
		{
			pLocalTempLink->m_ppNextLinks = new CLink*[iObjectLinkCount];
			memset(pLocalTempLink->m_ppNextLinks, NULL, sizeof(CLink*) * iObjectLinkCount);
		}

		// 对于任意一条潜在的后续路段.
		// ... 由于可能有双向路，所以需要判断路段ID是否一样.
		iter = NodMultiMap.find(pLocalTempLink->m_pTNode->m_lCarId);

		bool bFindNextRampLink = false;
		pLocalTempLink->m_lTrueNextLinkId = 0;
		for(sz_type cnt = 0; cnt != iObjectLinkCount; ++iter, ++cnt)
		{
			// 非同一条路段.
			if(iter->second->m_lLinkid != pLocalTempLink->m_lLinkid)
			{
				//建拓扑
				pLocalTempLink->m_ppNextLinks[pLocalTempLink->m_iNextLinkCount++] = iter->second;
				
				if(iter->second->m_bTortuousLink == true && iter->second->m_iEH == 1 &&
					(iter->second->m_iLinkForm == 4 || iter->second->m_iLinkForm == 5))
					bFindNextRampLink = true;

				//同路名线路，找下一条真实路链
				string strLinkName = pLocalTempLink->m_strLinkName;
				string strNextLinkName = iter->second->m_strLinkName;

				int iLinkDegree = pLocalTempLink->m_iLinkDegree;
				int iNextLinkDegree = iter->second->m_iLinkDegree;

				if(strLinkName == strNextLinkName && iLinkDegree == iNextLinkDegree)
					pLocalTempLink->m_lTrueNextLinkId = iter->second->m_lLinkid;
			}
		}

		if(bFindNextRampLink == true && pLocalTempLink->m_iNextLinkCount > 1)
			pLocalTempLink->m_bFindNextRampLink = true;
	}

}
void CShpNetModuleBuilder::BuildPreTopo(multimap<unsigned long, CLink*>& NodMultiMap )
{
	// 建立路网拓扑.
	typedef multimap<unsigned long, CLink*>::size_type sz_type;
	typedef multimap<unsigned long, CLink*>::iterator mul_map_iter;
	mul_map_iter iter;

	CLink* pTempLink = *m_ppLink;	// 设置操作的局部变量.
	for(int i = 0; i < m_lLinkCount; ++i)
	{
		// 获取一条路段.
		CLink* pLocalTempLink = pTempLink + i;
		pLocalTempLink->m_iPreLinkCount = 0;

		// 以TNode 为终点节点的路段数.
		sz_type iObjectLinkCount = NodMultiMap.count(pLocalTempLink->m_pFNode->m_lCarId);// 路段终点ID.
		if(iObjectLinkCount == 0)
			pLocalTempLink->m_ppPreLinks = NULL;
		else
		{
			pLocalTempLink->m_ppPreLinks = new CLink*[iObjectLinkCount];
			memset(pLocalTempLink->m_ppPreLinks, NULL, sizeof(CLink*) * iObjectLinkCount);
		}

		// 对于任意一条潜在的后续路段.
		// ... 由于可能有双向路，所以需要判断路段ID是否一样.
		iter = NodMultiMap.find(pLocalTempLink->m_pFNode->m_lCarId);

		bool bFindNextRampLink = false;
		pLocalTempLink->m_lTruePreLinkId = 0;
		for(sz_type cnt = 0; cnt != iObjectLinkCount; ++iter, ++cnt)
		{
			// 非同一条路段.
			if(iter->second->m_lLinkid != pLocalTempLink->m_lLinkid)
			{
				//建拓扑
				pLocalTempLink->m_ppPreLinks[pLocalTempLink->m_iPreLinkCount++] = iter->second;

				if(iter->second->m_bTortuousLink == true && iter->second->m_iEH == 1 &&
					(iter->second->m_iLinkForm == 4 || iter->second->m_iLinkForm == 5))
					bFindNextRampLink = true;

				//同路名线路，找下一条真实路链
				string strLinkName = pLocalTempLink->m_strLinkName;
				string strNextLinkName = iter->second->m_strLinkName;

				int iLinkDegree = pLocalTempLink->m_iLinkDegree;
				int iNextLinkDegree = iter->second->m_iLinkDegree;

				if(strLinkName == strNextLinkName && iLinkDegree == iNextLinkDegree)
					pLocalTempLink->m_lTruePreLinkId = iter->second->m_lLinkid;
			}
		}

		if(bFindNextRampLink == true && pLocalTempLink->m_iPreLinkCount > 1)
			pLocalTempLink->m_bFindNextRampLink = true;
	}
}