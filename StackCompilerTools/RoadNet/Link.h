#if !defined(__RoadNet_CLink_h)
#define __RoadNet_CLink_h

#include <string>

#include "Node.h"
#include "Vertex.h"
using namespace std;

class CLink
{
public:
	CLink();
	~CLink();

    int m_iMeshid;
	unsigned long m_lLinkid;

	unsigned long m_lStartNode;///< ��ʼ���ӵ���
	unsigned long m_lEndNode;///< ��ֹ���ӵ���
	/* ·��. */
	std::string m_strLinkName;
	/* ·�γ��ȣ���λ���� */
	double m_dLength;

	/* ��ͨ������. 
	* 1. ˫��ͨ��(Ĭ��ֵ)
	* 2. �����ֻ�������ͬ������
	* 3. �����ֻ������෴������
	* 4. ˫����� */
	int m_iUpDirect;

	/* 
	* ��·���ܵȼ�
	* -0 δ����
	* -1 һ����·
	* -2 ������·
	* -3 ������·
	* -4 �ļ���·
	* -5 �弶��·
	* -6 ������·
	* -7 �ڲ���·
	*/
	int m_iFC;
	/* ��·��̬.
	* 1:˫�߻���·; 
	* 2:��˫�߻���·; 
	* 3:��·; 
	* 4:����;
	* 5:��ͨ�㳡; 
	* 6:��ս�ͨ����; 
	* 7 ~ 14:�ѵ�; 
	* 15~:�� */
	int m_iLinkForm;
	/* 
	* ��·����ȼ� ��Ϊ��ֵ�ο�
	* -0 δ����
	* -1 �Ǽʸ���
	* -2 ���п���
	* -3 ����/�������ɵ�
	* -4 ʡ��/���дθɵ�
	* -5 �ص�/����֧·
	* -6 ���/����
	*/
	int m_iLinkDegree;
	/* ��·�ṹ����
	* 0:��(Ĭ��ֵ); 
	* 1:��������; 
	* 2:�߼ܵ�·; 
	* 3:��� */
	int m_iRS;

	/**
     * @brief  �����ʶ
     * 
	 *-0 δ����
	 *-1 ��·
	 *-2 ���
	 *-3 ����������
	 *-9 ����
	 */
	int m_iSR;

	/**
     * @brief  �߼ܱ�ʶ
     * 
	 *-0 δ����
	 *-1 �߼�   1
	 *-2 ����   2
	 *-3 �ϸ߼��ѵ� 4
	 *-4 �¸߼��ѵ� 5
	 *-9 ����
	 */
	int m_iEH;

	//int m_iTL; // �źŵ�

	//int m_iTS; // �շ�վ
	
	//double m_dMaxSpeed; // ��ͨ��ֵ
	//double m_dMinSpeed; // ӵ�·�ֵ

	double m_dMaxSpeed;//·������ٶȣ�Ϊ��չ·��ʹ��

	/* ����·���� */
	int m_iNextLinkCount;

	/*ǰ��·����*/
	int m_iPreLinkCount;

	///* �ڵ��� */
	int m_iVertexCount;


	///* ·����㵽�յ��������λ�� */
	int m_iAzimuth;

	///*�Ƿ�����·��*/
	bool m_bTortuousLink;

	// 20100410�޸�.
	// �뵱ǰ·��·����ͬ����һ��·��ID.
	unsigned long m_lTrueNextLinkId;
	// �뵱ǰ·��·����ͬ����һ��·��ID.
	unsigned long m_lTruePreLinkId;

	CNode* m_pFNode;
	CLink** m_ppNextLinks;
	CNode* m_pTNode;
	CVertex** m_ppVertex;
	CLink** m_ppPreLinks;

	 bool m_bFindNextRampLink; // ��ʶ�ں��·�����Ƿ��й�����ѵ�
	//int m_iLinkYootuType;
	 bool m_bVisited;



protected:
private:

};

#endif