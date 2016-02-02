/***********************************************************************
 * Module:  CLink.cpp
 * Author:  guosm
 * Modified: 2009��4��11�� 11:43:34
 * Purpose: Implementation of the class CLink
 ***********************************************************************/
//#include "stdafx.h"
#include "Link.h"
#include "Node.h"
#include "Vertex.h"


////////////////////////////////////////////////////////////////////////
// Name:       CLink::CLink()
// Purpose:    Implementation of CLink::CLink()
// Return:     
////////////////////////////////////////////////////////////////////////

CLink::CLink()
{
	m_iMeshid = 0;
	m_lLinkid = 0;
	m_lStartNode = 0;
	m_lEndNode = 0;
	m_strLinkName = "";
	m_dLength = 0.;
	m_iUpDirect = 1;
	m_iFC = 0;
	m_iLinkForm = 0;
	m_iLinkDegree = 0;
	m_iRS = 0;
	m_iSR = 0;
	m_iEH = 0;
	//m_iTL = 0;
	//m_iTS = 0;
	
	/*m_dMaxSpeed = 999;
	m_dMinSpeed = -1;*/
	m_iNextLinkCount = 0;
	m_iVertexCount = 0;
	m_iAzimuth = -1;
	m_bTortuousLink = false;
	m_lTrueNextLinkId = 0;
	
	m_pFNode = NULL;
	m_pTNode = NULL;
	m_ppVertex = NULL;
	m_ppNextLinks = NULL;
	m_bFindNextRampLink = false;
	m_bVisited = false;


}

////////////////////////////////////////////////////////////////////////
// Name:       CLink::~CLink()
// Purpose:    Implementation of CLink::~CLink()
// Return:     
////////////////////////////////////////////////////////////////////////

CLink::~CLink()
{
	//�ͷ����ڵ�(�˵�)
	//printf("use!!!\n");
	if (m_pFNode != NULL)
	{
		delete m_pFNode;
		m_pFNode = NULL;
	}

	if (m_pTNode != NULL)
	{
		delete m_pTNode;
		m_pTNode = NULL;
	}


	//�ͷ��ڵ�
	if (m_ppVertex != NULL)
	{
		delete[] *m_ppVertex;
		*m_ppVertex = NULL;
		delete m_ppVertex;
		m_ppVertex = NULL;
	}
	//�ͷź���·��ָ��
	if (m_ppNextLinks != NULL)
	{
		for (int i = 0; i < m_iNextLinkCount; i++)
		{
			m_ppNextLinks[i] = NULL;
		}
		if (m_iNextLinkCount > 0)
			delete[] m_ppNextLinks;
		else
			delete m_ppNextLinks;
		m_ppNextLinks = NULL;
	}
}