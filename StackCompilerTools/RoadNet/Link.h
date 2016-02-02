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

	unsigned long m_lStartNode;///< 起始连接点编号
	unsigned long m_lEndNode;///< 终止连接点编号
	/* 路名. */
	std::string m_strLinkName;
	/* 路段长度，单位：米 */
	double m_dLength;

	/* 交通流方向. 
	* 1. 双向通行(默认值)
	* 2. 与数字化方向相同可运行
	* 3. 与数字化方向相反可运行
	* 4. 双向禁行 */
	int m_iUpDirect;

	/* 
	* 道路功能等级
	* -0 未分类
	* -1 一级道路
	* -2 二级道路
	* -3 三级道路
	* -4 四级道路
	* -5 五级道路
	* -6 六级道路
	* -7 内部道路
	*/
	int m_iFC;
	/* 道路形态.
	* 1:双线化道路; 
	* 2:非双线化道路; 
	* 3:辅路; 
	* 4:环岛;
	* 5:交通广场; 
	* 6:封闭交通区域; 
	* 7 ~ 14:匝道; 
	* 15~:略 */
	int m_iLinkForm;
	/* 
	* 道路管理等级 作为阈值参考
	* -0 未分类
	* -1 城际高速
	* -2 城市快速
	* -3 国道/城市主干道
	* -4 省道/城市次干道
	* -5 县道/城市支路
	* -6 乡道/其他
	*/
	int m_iLinkDegree;
	/* 道路结构属性
	* 0:无(默认值); 
	* 1:过河桥梁; 
	* 2:高架道路; 
	* 3:隧道 */
	int m_iRS;

	/**
     * @brief  侧道标识
     * 
	 *-0 未定义
	 *-1 主路
	 *-2 侧道
	 *-3 主侧连接线
	 *-9 其他
	 */
	int m_iSR;

	/**
     * @brief  高架标识
     * 
	 *-0 未定义
	 *-1 高架   1
	 *-2 地面   2
	 *-3 上高架匝道 4
	 *-4 下高架匝道 5
	 *-9 其他
	 */
	int m_iEH;

	//int m_iTL; // 信号灯

	//int m_iTS; // 收费站
	
	//double m_dMaxSpeed; // 畅通阈值
	//double m_dMinSpeed; // 拥堵阀值

	double m_dMaxSpeed;//路链最大速度，为扩展路链使用

	/* 后续路段数 */
	int m_iNextLinkCount;

	/*前继路段数*/
	int m_iPreLinkCount;

	///* 内点数 */
	int m_iVertexCount;


	///* 路段起点到终点的向量方位角 */
	int m_iAzimuth;

	///*是否弯曲路段*/
	bool m_bTortuousLink;

	// 20100410修改.
	// 与当前路段路名相同的下一条路段ID.
	unsigned long m_lTrueNextLinkId;
	// 与当前路段路名相同的上一条路段ID.
	unsigned long m_lTruePreLinkId;

	CNode* m_pFNode;
	CLink** m_ppNextLinks;
	CNode* m_pTNode;
	CVertex** m_ppVertex;
	CLink** m_ppPreLinks;

	 bool m_bFindNextRampLink; // 标识在后继路段中是否有拐弯的匝道
	//int m_iLinkYootuType;
	 bool m_bVisited;



protected:
private:

};

#endif