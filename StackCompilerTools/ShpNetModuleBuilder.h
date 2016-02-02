#pragma once

#include <map>
#include <string>

using namespace std;

class CLink;
class OGRLineString;
/** 
* @brief �ͷŶ�����Դ
*/
struct DeleteMapValue1
{
	// ģ�廯�ͻ���
	template<typename T>
	void operator()(T ptr) const 
	{
		delete ptr.second;
		ptr.second = NULL;
	} 
};
class CShpNetModuleBuilder/* : public CNetModuleBuilder*/
{
public:
	CShpNetModuleBuilder(const string& strShpPath);
	~CShpNetModuleBuilder(void);

	/* ��ȡshp�ļ�������·��������·���� */
	long Build();
public:
	string m_strMapPath;
	CLink** m_ppLink;

	/// ����·��ָ���hash��
	map<string, CLink*> m_mapLink;
	/// ·����(������)
	long m_lLinkCount;
	/// ·����(��������)
	long m_lRecordCount;

private:
	long GetLinkCount();
	void reviseSENodeInfo(unsigned long& lFjcid,unsigned long& lTjcid,OGRLineString *pOGRLine,map<string, unsigned __int64>& mapReviseInfo,unsigned long &lnNodeId);

	void BuildNet(CLink* pLink, multimap<unsigned long, CLink*>& NodMultiMap,multimap<unsigned long, CLink*>& EndNodMultiMap, OGRLineString *pOGRLine, bool bForward);

	void BuildVertexs(CLink* pLink, OGRLineString *pOGRLine);
	/*void BuildNetTopo(multimap<unsigned long, CLink*>& NodMultiMap );*/
	void BuildNextTopo(multimap<unsigned long, CLink*>& NodMultiMap );//��������·������
	void BuildPreTopo(multimap<unsigned long, CLink*>& NodMultiMap );//����ǰ��·������

	void InitializeLinkMaxSpeed(CLink * & pLink);
};
