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
		// ��ȡ������꾭γ��
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

		// ��ȡ�յ����꾭γ��
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

	// ����·�ζ����С������.
	m_ppLink = new CLink*();
	*(m_ppLink) = new CLink[m_lLinkCount];

	CLink* pTempLink = *m_ppLink;	// ���ò����ľֲ�����.
	int nLinkIndex = 0; 

	OGRRegisterAll();

	OGRDataSource* poDS = OGRSFDriverRegistrar::Open( m_strMapPath.c_str(), FALSE );
	if( poDS == NULL )
	{
		/*LOG4CPLUS_ERROR(g_pSystemLog, "Open failed [" << m_strMapPath << "]");*/
		printf( "Open failed [%s].\n",m_strMapPath.c_str());
		return FALSE;
	}

	// ���multimap����������ʱ�����������洢ʵ��·�ε����Ͷ�Ӧ������ָ��
	multimap<unsigned long, CLink*> NodMultiMap;
	//���Endmultimap����������ʱ�����������洢ʵ��·�ε����Ͷ�Ӧ������ָ��
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
		double dLength(poFeature->GetFieldAsDouble("LENGTH"));// ·�γ���
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

		// ���ݵ������ݿ��е���Ϣ���·������.
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
		//��ʼ��·������ٶȣ�Ϊ������չ·������ʹ��

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
		case 1: // ˫���·
			{
				// ��������·��
				pLink->m_iUpDirect = 1;
				BuildNet(pLink, NodMultiMap,EndNodMultiMap, pOGRLine, true);

				nLinkIndex++;

				// ���췴��·��
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
		case 2: // ����
			{
				pLink->m_iUpDirect = 1;
				BuildNet(pLink, NodMultiMap,EndNodMultiMap, pOGRLine, true);
				nLinkIndex++;
				break;
			}

		case 3: // ����
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
			int iDF = poFeature->GetFieldAsInteger("DF"); // DF=4 ��·ȥ��
			switch(iDF)
			{
			case 0:
			case 1://˫��˫�������ͨ��
				lLinkCount += 2;	// ˫��·
				break;
			case 2://˳���򣺵���ͨ�У�ͨ�з���Ϊ��㵽�յ㷽��
			case 3://�淽�򣺵���ͨ�У�ͨ�з���Ϊ�յ㵽��㷽��
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
	// ����·���ṹ
	size_t nPoints(pOGRLine->getNumPoints());

	assert(nPoints >= 2);
	if (nPoints < 2)
	{
		return;
	}

	// ·�������յ������������ĳ���.
	double vectorLen = 0.0;
	OGRPoint startPoint;
	OGRPoint endPoint;
	pOGRLine->getPoint(0, &startPoint);
	pOGRLine->getPoint(nPoints - 1, &endPoint);
	if (bForward)
	{
		// ����
		pLink->m_pFNode = new CNode();
		pLink->m_pTNode = new CNode();

		pLink->m_pFNode->m_lCarId = pLink->m_lStartNode;
		pLink->m_pFNode->m_dLongitude = startPoint.getX();
		pLink->m_pFNode->m_dLatitude = startPoint.getY();

		pLink->m_pTNode->m_lCarId = pLink->m_lEndNode;
		pLink->m_pTNode->m_dLongitude = endPoint.getX();
		pLink->m_pTNode->m_dLatitude = endPoint.getY();

		pLink->m_iVertexCount = nPoints;

		// ����ڵ���������.
		BuildVertexs(pLink, pOGRLine);

		// ����·�������յ������������ĳ���.
		vectorLen = CGisSupporter::CalculateLength(startPoint.getX(), startPoint.getY(), 
			endPoint.getX(), endPoint.getY());

		// �ж�·���Ƿ�����.
		if(pLink->m_dLength / vectorLen - 1.05 > 1e-6)
			pLink->m_bTortuousLink = true;

		// ����·��ID��·�ζ����Map����.
		char chLinkId[20];
		_ltoa_s(pLink->m_lLinkid,chLinkId,10);
		string strLinkID = chLinkId;
		m_mapLink.insert(std::pair<string, CLink*>(strLinkID + "_1", pLink)); 
		NodMultiMap.insert(multimap<unsigned long,CLink*>::value_type(pLink->m_lStartNode, pLink));
		EndNodMultiMap.insert(multimap<unsigned long,CLink*>::value_type(pLink->m_lEndNode, pLink));
	}
	else
	{
		// ���췴��·��.
		pLink->m_pFNode = new CNode();
		pLink->m_pTNode = new CNode();

		pLink->m_pFNode->m_lCarId = pLink->m_lEndNode;
		pLink->m_pFNode->m_dLongitude = endPoint.getX();
		pLink->m_pFNode->m_dLatitude = endPoint.getY();

		pLink->m_pTNode->m_lCarId = pLink->m_lStartNode;
		pLink->m_pTNode->m_dLongitude = startPoint.getX();
		pLink->m_pTNode->m_dLatitude = startPoint.getY();

		pLink->m_iVertexCount = nPoints;

		// ����ڵ���������.
		BuildVertexs(pLink, pOGRLine);

		// ����·�������յ������������ĳ���.
		vectorLen = CGisSupporter::CalculateLength(startPoint.getX(), startPoint.getY(), 
			endPoint.getX(), endPoint.getY());

		// �ж�·���Ƿ�����.
		if(pLink->m_dLength / vectorLen - 1.05 > 1e-6)
			pLink->m_bTortuousLink = true;

		// ����·��ID��·�ζ����Map����.
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
	*(pLink->m_ppVertex) = new CVertex[iPointCount];//�����ʵ������ 
	
	CVertex* pTmpVertex= *(pLink->m_ppVertex);  //
	
	int nCurIndex(0);
	for(int nTemp = 0; nTemp < iPointCount; nTemp++)
	{
		if(nTrafficFlo == 1)	// ����.
			nCurIndex = nTemp;
		else			// ����. (���ڵ������������Ǵ�0��ʼ�ģ����Բ���iTemp-1)
			nCurIndex = iPointCount - nTemp - 1;

		OGRPoint pPoint;
		pOGRLine->getPoint(nCurIndex, &pPoint);

		pTmpVertex[nTemp].m_dLongitude = pPoint.getX();
		pTmpVertex[nTemp].m_dLatitude = pPoint.getY();
		pTmpVertex[nTemp].m_pLink = pLink; 


		//�����ϸ��㵽��ǰ��֮��ľ��뼰�����
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

	//���һ���ڵ���뼰�������Ϊ0.
	pTmpVertex[iPointCount-1].m_dDistanceToNext = 0;
	pTmpVertex[iPointCount-1].m_iAngleToNext = 0;	
	
	// ·�εķ�������Ϊ·������·���յ�����ɵ������ķ���.
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
	// ����·������.
	typedef multimap<unsigned long, CLink*>::size_type sz_type;
	typedef multimap<unsigned long, CLink*>::iterator mul_map_iter;
	mul_map_iter iter;

	CLink* pTempLink = *m_ppLink;	// ���ò����ľֲ�����.
	for(int i = 0; i < m_lLinkCount; ++i)
	{
		// ��ȡһ��·��.
		CLink* pLocalTempLink = pTempLink + i;
		pLocalTempLink->m_iNextLinkCount = 0;

		// ��TNode Ϊ��ʼ�ڵ��·����.
		sz_type iObjectLinkCount = NodMultiMap.count(pLocalTempLink->m_pTNode->m_lCarId);// ·���յ�ID.
		if(iObjectLinkCount == 0)
			pLocalTempLink->m_ppNextLinks = NULL;
		else
		{
			pLocalTempLink->m_ppNextLinks = new CLink*[iObjectLinkCount];
			memset(pLocalTempLink->m_ppNextLinks, NULL, sizeof(CLink*) * iObjectLinkCount);
		}

		// ��������һ��Ǳ�ڵĺ���·��.
		// ... ���ڿ�����˫��·��������Ҫ�ж�·��ID�Ƿ�һ��.
		iter = NodMultiMap.find(pLocalTempLink->m_pTNode->m_lCarId);

		bool bFindNextRampLink = false;
		pLocalTempLink->m_lTrueNextLinkId = 0;
		for(sz_type cnt = 0; cnt != iObjectLinkCount; ++iter, ++cnt)
		{
			// ��ͬһ��·��.
			if(iter->second->m_lLinkid != pLocalTempLink->m_lLinkid)
			{
				//������
				pLocalTempLink->m_ppNextLinks[pLocalTempLink->m_iNextLinkCount++] = iter->second;
				
				if(iter->second->m_bTortuousLink == true && iter->second->m_iEH == 1 &&
					(iter->second->m_iLinkForm == 4 || iter->second->m_iLinkForm == 5))
					bFindNextRampLink = true;

				//ͬ·����·������һ����ʵ·��
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
	// ����·������.
	typedef multimap<unsigned long, CLink*>::size_type sz_type;
	typedef multimap<unsigned long, CLink*>::iterator mul_map_iter;
	mul_map_iter iter;

	CLink* pTempLink = *m_ppLink;	// ���ò����ľֲ�����.
	for(int i = 0; i < m_lLinkCount; ++i)
	{
		// ��ȡһ��·��.
		CLink* pLocalTempLink = pTempLink + i;
		pLocalTempLink->m_iPreLinkCount = 0;

		// ��TNode Ϊ�յ�ڵ��·����.
		sz_type iObjectLinkCount = NodMultiMap.count(pLocalTempLink->m_pFNode->m_lCarId);// ·���յ�ID.
		if(iObjectLinkCount == 0)
			pLocalTempLink->m_ppPreLinks = NULL;
		else
		{
			pLocalTempLink->m_ppPreLinks = new CLink*[iObjectLinkCount];
			memset(pLocalTempLink->m_ppPreLinks, NULL, sizeof(CLink*) * iObjectLinkCount);
		}

		// ��������һ��Ǳ�ڵĺ���·��.
		// ... ���ڿ�����˫��·��������Ҫ�ж�·��ID�Ƿ�һ��.
		iter = NodMultiMap.find(pLocalTempLink->m_pFNode->m_lCarId);

		bool bFindNextRampLink = false;
		pLocalTempLink->m_lTruePreLinkId = 0;
		for(sz_type cnt = 0; cnt != iObjectLinkCount; ++iter, ++cnt)
		{
			// ��ͬһ��·��.
			if(iter->second->m_lLinkid != pLocalTempLink->m_lLinkid)
			{
				//������
				pLocalTempLink->m_ppPreLinks[pLocalTempLink->m_iPreLinkCount++] = iter->second;

				if(iter->second->m_bTortuousLink == true && iter->second->m_iEH == 1 &&
					(iter->second->m_iLinkForm == 4 || iter->second->m_iLinkForm == 5))
					bFindNextRampLink = true;

				//ͬ·����·������һ����ʵ·��
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