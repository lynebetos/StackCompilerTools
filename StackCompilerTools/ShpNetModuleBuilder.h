#pragma once

#include <map>
#include <string>

using namespace std;

class CLink;
class OGRLineString;
/** 
* @brief 释放对象资源
*/
struct DeleteMapValue1
{
	// 模板化和基类
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

	/* 读取shp文件，构建路网，返回路段数 */
	long Build();
public:
	string m_strMapPath;
	CLink** m_ppLink;

	/// 保存路段指针的hash表
	map<string, CLink*> m_mapLink;
	/// 路段数(带方向)
	long m_lLinkCount;
	/// 路段数(不带方向)
	long m_lRecordCount;

private:
	long GetLinkCount();
	void reviseSENodeInfo(unsigned long& lFjcid,unsigned long& lTjcid,OGRLineString *pOGRLine,map<string, unsigned __int64>& mapReviseInfo,unsigned long &lnNodeId);

	void BuildNet(CLink* pLink, multimap<unsigned long, CLink*>& NodMultiMap,multimap<unsigned long, CLink*>& EndNodMultiMap, OGRLineString *pOGRLine, bool bForward);

	void BuildVertexs(CLink* pLink, OGRLineString *pOGRLine);
	/*void BuildNetTopo(multimap<unsigned long, CLink*>& NodMultiMap );*/
	void BuildNextTopo(multimap<unsigned long, CLink*>& NodMultiMap );//建立后续路链拓扑
	void BuildPreTopo(multimap<unsigned long, CLink*>& NodMultiMap );//建立前继路链拓扑

	void InitializeLinkMaxSpeed(CLink * & pLink);
};
