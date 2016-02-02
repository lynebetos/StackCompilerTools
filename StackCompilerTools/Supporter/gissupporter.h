#pragma once

#include <cstdlib>
#include <cmath>
#include <string>
// 坐标加密转换.
#include "gzgpst.h"
//#include "../MapMatch//PathNode.h"
#include "../RoadNet/Vertex.h"
#include "../Common.h"
using namespace std;
class CGisSupporter
{
public:
	static double stringtodouble(string a)
	{
		double b=0.0,c=0.0;
		for(int i=0;i < a.length();i++)
		{
			if(a[i]=='.')
			{
				for(int j=a.length()-1;j>i;j--)
				{
					c=c*0.1+(a[j]-'0')*0.1;
				}
				break;
			}
			else
			{
				b=(b*10)+(a[i]-'0');
			}
		}
		return b+c;
	}
	////////////////////////////////////////////////////////////////////////
	// Name:       void SubGussFs(double X,double Y,double L0, double* B, double* L)
	// Comment:    米制平面坐标转换为经纬度坐标
	// Parameters:
	// - X		   输入横向坐标
	// - Y	       输入纵向坐标
	// - B         输出经度
	// - L         输出纬度
	// - L0  
	// Return: void
	////////////////////////////////////////////////////////////////////////

	static void SubGussFs(double X,double Y,double L0, double* B, double* L)
	{
		double p=57.29577951472;
		const double a=6.378245000e+06;
		const double e2=0.00669342162297;
		const double e12=0.00673852541468;
		const double c0=0.157046064172e-06;
		const double c1=0.005051773759;
		const double c2=0.000029837302;
		const double c3=0.000000238189;

		double bf0 = c0*X;
		double bf0c = cos(bf0);
		double bf0s = sin(bf0);
		double bf = bf0 + bf0c*(c1*bf0s - c2*pow(bf0s,3) + c3* pow(bf0s,5));
		double bt = tan(bf);
		double bc = cos(bf);
		double bs = sin(bf);
		double bi = e12 * pow(bc,2);
		double v2 = 1.0e+0 +bi;
		double bn = a/sqrt(1.0-e2* pow(bs,2));
		double yn=Y/bn;

		// 计算纬度
		double b1 = -v2*bt*pow(yn,2)/2.0;
		double b2 = -(5.0+3.0*pow(bt,2) + bi-9.0*bi* pow(bt,2)) *b1* pow(yn,2) /12.0;
		double b3 = (61.0+90.0* pow(bt,2) + 45.0* pow(bt,4))*b1* pow(yn,4)/360.0;
		*B = bf + b1 + b2 + b3;
		*B = *B * p;

		// 计算经度
		double l1=yn/bc;
		double l2=-(1.0+2.0* pow(bt,2)+bi)*l1*pow(yn,2)/6.0;
		double l3=(5.0+28.0*pow(bt,2)+24.0*pow(bt,4)+6.0*bi+8.0*bi*pow(bt,2))*l1*pow(yn,4)/120.0;
		*L = l1 + l2 + l3;
		*L = *L * p;

		*L += L0;
		if(*L > 360.0)
			*L -= 360.0;
	}


	////////////////////////////////////////////////////////////////////////
	// Name:       void CalGuassToLB(double dX, double dY, double* dLongitude, double* dLatitude)
	// Comment:    将米制平面坐标转换为经纬度坐标的主调函数
	// Parameters:
	// - dX		   输入横向坐标
	// - dY	       输入纵向坐标
	// - dLongitude         输出经度
	// - dLatitude          输出纬度
	// Return: void
	////////////////////////////////////////////////////////////////////////

	static void CalGuassToLB(double dX, double dY, double* dLongitude, double* dLatitude)
	{
		double L0;
		int nZoonNum;

		nZoonNum = (int)(dY/(1.0E+6));
		L0 = nZoonNum * 6-3;

		dY = dY - nZoonNum*1.0E+6;
		SubGussFs(dX, dY-500000,L0, dLatitude, dLongitude);
		*dLongitude = *dLongitude + nZoonNum * 6 - 3 ;
	}


	////////////////////////////////////////////////////////////////////////
	// Name:       void SubGussFs(double* X, double* Y,double B,double L,int nCenterLongi)
	// Comment:    将经纬度转换成米制平面坐标.
	// Parameters:
	// - X		   输出横向坐标
	// - Y	       输出纵向坐标
	// - B         经度
	// - L         纬度
	// - nCenterLongi  
	// Return: void
	////////////////////////////////////////////////////////////////////////

	static void SubGussFs(double* X, double* Y,double B,double L,int nCenterLongi)
	{
		//高斯投影分带
		int nzonenum;
		if(nCenterLongi==0)
		{
			nzonenum = (int)L/6+1;
			nCenterLongi = nzonenum*6-3;
		}
		else
			nzonenum = (int)nCenterLongi/6+1;

		//以弧度为单位的经纬度数值
		double rB = B/180*3.1415926;
		double rL = (L-nCenterLongi)/180*3.1415926;		//同时计算了中央经线
		//1980坐标系参数
		const double a = 6378245.00;		//长轴
		const double b = 6356863.50;		//短轴
		double sqre1 = (a*a-b*b)/(a*a);		//第一偏心率平方
		//B:纬度
		//L:精度
		//子午圈曲率半径
		double sinb = sin(rB);
		double cosb = cos(rB);
		double M = a*(1-sqre1)/(1-sqre1*sinb*sinb)/sqrt(1-sqre1*sinb*sinb);
		//卯酉圈曲率半径
		double N = a/sqrt(1-sqre1*sinb*sinb);
		double sqrita = N/M-1;

		//该纬度点到赤道的子午线弧长
		double s = a * ( 1 - sqre1 ) * ( 1.00505117739 * rB - 0.00506237764/2 * sin(2*rB) + 0.0000106245/4 * sin(4*rB) - 0.00000002081/6 * sin(6*rB));

		double tanb = tan(rB);
		*X = s+rL*rL*N/2*sinb*cosb + rL*rL*rL*rL*N/24*sinb*cosb*cosb*cosb * (5-tanb*tanb + 9*sqrita*sqrita +4*sqrita);
		*Y = rL*N*cosb+rL*rL*rL*N/6*cosb*cosb*cosb*(1-tanb*tanb+sqrita) + rL*rL*rL*rL*rL*N/120*cosb*cosb*cosb*cosb*cosb*(5-18*tanb*tanb+tanb*tanb*tanb*tanb);
		*Y = *Y + 500000 + nzonenum * 1.0e+6;
	}


	////////////////////////////////////////////////////////////////////////
	// Name:       void CalGuassFromLB(double dLongitude, double dLatitude, double* dX, double* dY, long nCenterL)
	// Comment:    将经纬度转换成米制平面坐标方法的主调函数
	// Parameters:
	// - X		   输出横向坐标
	// - Y	       输出纵向坐标
	// - B         经度
	// - L         纬度
	// - nCenterL
	// Return: void
	////////////////////////////////////////////////////////////////////////

	static void CalGuassFromLB(double dLongitude, double dLatitude, double* dX, double* dY, long nCenterL)
	{
		int CenterL = (int)nCenterL;

		SubGussFs(dX, dY, dLatitude, dLongitude, CenterL);
		nCenterL = (long)CenterL;
	}


	////////////////////////////////////////////////////////////////////////
	// Name:       double Calculate(CVertex* pVtx1,CVertex* pVtx2,int nSize)
	// Comment:    计算两点之间距离
	// Parameters:
	// - pVtx1	   第一点
	// - pVtx2     第二点
	// Return: double   两点之间距离
	////////////////////////////////////////////////////////////////////////
	static double CalculateLength(CVertex* pVtx1,CVertex* pVtx2)
	{
		double dLength = 0;
		double x1=0,x2=0,y1=0,y2=0;
		int nCenterL = ((int)(pVtx1->m_dLongitude)/6+1)*6-3;

		CalGuassFromLB(pVtx1->m_dLongitude, pVtx1->m_dLatitude, &x1, &y1, nCenterL);
		CalGuassFromLB(pVtx2->m_dLongitude, pVtx2->m_dLatitude, &x2, &y2, nCenterL);
		dLength += sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		return dLength;
	}

	////////////////////////////////////////////////////////////////////////
	// Name:       double CalcLenght(CVertex* pVtx1,CVertex* pVtx2,int nSize)
	// Comment:    计算两点之间距离
	// Parameters:
	// - dX1	   第一点经度
	// - dY1       第一点纬度
	// - dX2       第二点经度
	// - dY2       第二点纬度
	// Return: double   两点之间距离
	////////////////////////////////////////////////////////////////////////
	static double CalculateLength(double dX1,double dY1,double dX2,double dY2)
	{
		double dLength = 0;
		double x1=0,x2=0,y1=0,y2=0;
		int nCenterL = ((int)dX1/6+1)*6-3;

		CalGuassFromLB(dX1, dY1, &x1, &y1, nCenterL);
		CalGuassFromLB(dX2, dY2, &x2, &y2, nCenterL);
		dLength += sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		return dLength;
	}



	////////////////////////////////////////////////////////////////////////
	// Name:       int CalculateIncludeAngle(int angle1, int angle2)
	// Comment:    计算两个向量的夹角.
	// Parameters:
	// - angle1		第一个向量与正北方向夹角
	// - angle2		第二个向量与正北方向夹角
	// Return: int  向量夹角
	////////////////////////////////////////////////////////////////////////

	static int CalculateIncludeAngle(int angle1, int angle2)
	{

		// 如果两个向量方向中有一个是无效计算出来的
		// ... 保险起见，设置二者之间的夹角为0度.
		if(angle1 == -1 || angle2 == -1)
			return 0;

		int iTemp = abs(angle2 - angle1);
		return  iTemp <= 180 ? iTemp : 360 - iTemp;

	}


	////////////////////////////////////////////////////////////////////////
	// Name:       int CalculateAngle(double x1, double y1, double x2, double y2)
	// Comment:    计算一个向量与正北方向的角度(顺时针0 ～ 360).
	// Parameters:
	// - x1		向量起点经度
	// - y1		向量起点纬度
	// - x2		向量终点经度
	// - y2		向量终点纬度
	// Return: int  向量角度
	////////////////////////////////////////////////////////////////////////

	static int CalculateAngle(double x1, double y1, double x2, double y2)
	{	
		// 计算向量.
		double vertexX = x2 - x1;
		double vertexY = y2 - y1;
		const double Pi = 3.1415926;

		// 判断向量是否在坐标轴上.
		if(fabs(vertexX) < 1e-6 && fabs(vertexY) < 1e-6)// x=0 y=0 相同坐标输入.
			return -1;											
		else if(fabs(vertexX) < 1e-6 && vertexY > 1e-6)// x=0 y>0 经度相同且纬度增大.
			return 0;
		else if(vertexX > 1e-6 && fabs(vertexY) < 1e-6)// x>0 y=0 经度增大且纬度相同.
			return 90;
		else if(fabs(vertexX) < 1e-6 && -1 * vertexY > 1e-6) // x=0 y<0 经度相同且纬度减小.
			return 180;
		else if(-1 * vertexX > 1e-6 && fabs(vertexY) < 1e-6) // x<0 y=0 经度减小且纬度相同.
			return 270;

		// 判断向量处在哪个象限.
		else 
		{
			// 如果在1、2象限.
			if(vertexX > 1e-6)
				return 90 - (int)(atan(vertexY / vertexX) * 180 / Pi);
			else // 在3、4象限.
				return 270 - (int)(atan(vertexY / vertexX) * 180 / Pi);
		}

	}

	////////////////////////////////////////////////////////////////////////
	// Name:       int CalculateAngle(double x1, double y1, double x2, double y2, bool bCareVecLen)
	// Comment:    计算一个向量与正北方向的角度(顺时针0 ～ 360).
	// Comment:    与CalculateAngle的区别，关注向量向量的起点和终点之间距离是否过小.
	// Parameters:
	// - x1		向量起点经度
	// - y1		向量起点纬度
	// - x2		向量终点经度
	// - y2		向量终点纬度
	// Return: int  向量角度
	////////////////////////////////////////////////////////////////////////

	/*static int CalculateAngle(double x1, double y1, double x2, double y2, bool bCareVecLen)
	{
		// 由于GPS坐标存在漂移
		// ... 如果向量的起点和终点距离小于40米，则认为向量方向计算无效，返回-1.

		double dMaxDistance = 10.0;
		
		// bCareVecLen == true. 计算路段位置点与GPS点之间的向量夹角，则两点距离在10米之内.
		// bCareVecLen == false. 计算两个GPS点之间的向量夹角，考虑两个GPS点都存在漂移，则两个GPS点之间的距离在40米之内.
		
		if(bCareVecLen == false)
			dMaxDistance = 40.0;
		
		double dDistance = CalculateLength(x1, y1, x2, y2);
		if(dMaxDistance - dDistance > 1e-6)
			return -1;

		else
			return CalculateAngle(x1, y1, x2, y2);
	}*/

	

	////////////////////////////////////////////////////////////////////////
	// Name:        bool GpsChange(double dCx, double dCy, int iGpsHeight, int iGpsTime, int iGpsDate, double* pOutCx, double* pOutCy)
	// Comments:	坐标加密转换.
	// Parameters: 
	// - dCx	
	// - dCy
	// - iGpsHeight
	// - iGpsTime
	// - iGpsDate
	// - pOutCx
	// - pOutCy
	// Return:     bool 转换是否成功.
	////////////////////////////////////////////////////////////////////////

	static bool GpsChange(double dCx, double dCy, int iGpsHeight, int iGpsTime, int iGpsDate, double* pOutCx, double* pOutCy)
	{
		double dCx1, dTempCx;
		double dCy1, dTempCy;

		const double BEI = 3686400.0;
		const long long PARAM = 1000000;

		dCx1 = dCx * BEI;
		dCy1 = dCy * BEI;

		unsigned int iNewCx, iNewCy;

		if(wgtochina_lb(1, (int)dCx1, (int)dCy1, iGpsHeight, 0, 0, &iNewCx, &iNewCy) != 0x00000000)
		{
			return false;
		}


		dTempCx = (double)iNewCx / BEI;
		dTempCy = (double)iNewCy / BEI;

		// 小数位数截断, 保证小数位数为6 位.
		long long lTempCx = dTempCx * PARAM;
		long long lTempCy = dTempCy * PARAM;

		*pOutCx = (double)lTempCx / (double)PARAM;
		*pOutCy = (double)lTempCy / (double)PARAM;

		return true;
	}
	////////////////////////////////////////////////////////////////////////
	// Name:       CMapMatcher::CalculatePerpendicular(CVertex* pVtx1, CVertex* pVtx2, CGPS* pGPS,CPathNode* pPathNodeOut)
	// Comment:    calculate the perpendicular
	// Parameters:
	// - pVtx1	   SubLink起始内点
	// - pVtx2	   SubLink终止内点
	// - pGPS      GPS采样点
	// - pPathNodeOut	垂点
	// Return:     bool
	////////////////////////////////////////////////////////////////////////
	/*
	static bool CalculatePerpendicular(CVertex* pVtx1, CVertex* pVtx2, CGPS* pGPS,CPathNode* pPathNodeOut)
	{

		// Convert longitude and latitude to Long value.
		const long PARAM = 1000000;

		pVtx1->m_dLongitude = (double)((long)(pVtx1->m_dLongitude * PARAM)) / (double) PARAM;
		pVtx1->m_dLatitude = (double)((long)(pVtx1->m_dLatitude * PARAM)) / (double) PARAM;

		pVtx2->m_dLongitude = (double)((long)(pVtx2->m_dLongitude * PARAM)) / (double)PARAM;
		pVtx2->m_dLatitude = (double)((long)(pVtx2->m_dLatitude * PARAM)) / (double)PARAM;

		pGPS->dLongitude = (double)((long)(pGPS->dLongitude * PARAM)) / (double)PARAM;
		pGPS->dLatitude = (double)((long)(pGPS->dLatitude * PARAM)) / (double)PARAM;


		CPathNode* pPerPenddicular = pPathNodeOut;

		long lVtx1Longitude = (long)(pVtx1->m_dLongitude * PARAM);
		long lVtx1Latitude = (long)(pVtx1->m_dLatitude * PARAM);

		long lVtx2Longitude = (long)(pVtx2->m_dLongitude * PARAM);
		long lVtx2Latitude = (long)(pVtx2->m_dLatitude * PARAM);

		long lGpsLongitude = (long)(pGPS->dLongitude * PARAM);
		long lGpsLatitude = (long)(pGPS->dLatitude * PARAM);

		// The line function involved pVtx1 and pVtx2 is: a * x + b * y + c = 0.
		long long a = lVtx2Latitude - lVtx1Latitude;
		long long b = lVtx1Longitude - lVtx2Longitude;
		double cc = (pVtx2->m_dLongitude * pVtx1->m_dLatitude) - (pVtx1->m_dLongitude * pVtx2->m_dLatitude);
		long long c = (long long)(cc * PARAM * PARAM);


		// The following formula is to calculate the perpendicular.
		long long aa = a * a;
		long long bb = b * b;
		long long ab = a * b;
		long long ac = a * c;
		long long bc = b * c;

		long long x1 = bb * lGpsLongitude - ab * lGpsLatitude - ac;
		long long x2 = aa + bb;
		pPerPenddicular->m_dLongitude = (double)x1 / (double)x2 / (double)PARAM;

		long long y1 = aa * lGpsLatitude - ab * lGpsLongitude - bc;
		long long y2 = x2;
		pPerPenddicular->m_dLatitude = (double)y1 / (double)y2 / (double)PARAM;

		return true;
	}
	*/

	////////////////////////////////////////////////////////////////////////
	// Name:       int CalculateIncludeAngleFrom2To1(int angle1, int angle2)
	// Comment:    计算第二个向量与第一个向量的夹角.
	// Parameters:
	// - angle1		第一个向量与正北方向夹角
	// - angle2		第二个向量与正北方向夹角
	// Return: int  向量夹角
	////////////////////////////////////////////////////////////////////////

	static int CalculateIncludeAngleFrom2To1(int angle1, int angle2)
	{

		// 如果两个向量方向中有一个是无效计算出来的
		// ... 保险起见，设置二者之间的夹角为度.
		if(angle1 == -1 || angle2 == -1)
			return 0;

		int iTemp = angle2 - angle1;
		return  iTemp >= 0 ? iTemp : 360 + iTemp;

	}



	////////////////////////////////////////////////////////////////////////
	// Name:       bool IsOutOfLink(CVertex* pVtx1, CVertex* pVtx2, CGPS* pGPS)
	// Comment:    判断GPS点与另两点构成线端的垂点是否在线段内，如果在外面返回false，否则返回true
	// Parameters:
	// - pVtx1
	// - pVtx2
	// - pGPS
	// Return:     bool
	////////////////////////////////////////////////////////////////////////

	static bool IsOnSubLink(double xToMatch, double yToMatch, 
		double x1, double y1, 
		double x2, double y2)
	{
		int angle1=CalculateAngle(x1,y1,xToMatch,yToMatch);
		int angle3=CalculateAngle(x1,y1,x2,y2);
		int iRet1 = CalculateIncludeAngle(angle1,angle3);

		int angle2=CalculateAngle(x2,y2,xToMatch,yToMatch);
		int angle4=CalculateAngle(x2,y2,x1,y1);
		int iRet2 = CalculateIncludeAngle(angle2,angle4);


		return ( 90 - iRet1 > 1e-6 ) && ( 90 - iRet2 > 1e-6 );
	}

	////////////////////////////////////////////////////////////////////////
	// Name:       CMapMatcher::CalculatePerpendicular(CVertex* pVtx1, CVertex* pVtx2, CGPS* pGPS,CPathNode* pPathNodeOut)
	// Comment:    calculate the perpendicular
	// Parameters:
	// - pVtx1	   SubLink起始内点
	// - pVtx2	   SubLink终止内点
	// - pGPS      GPS采样点
	// - pPathNodeOut	垂点
	// Return:     bool
	////////////////////////////////////////////////////////////////////////

	static bool CalculatePerpendicular(double xToMatch, double yToMatch, 
		double x1, double y1, 
		double x2, double y2,
		double &xIntersect, double &yIntersect)
	{

		// Convert longitude and latitude to Long value.
		const long PARAM = 1000000;

		x1 = (double)((long)(x1 * PARAM)) / (double) PARAM;
		y1 = (double)((long)(y1 * PARAM)) / (double) PARAM;

		x2 = (double)((long)(x2 * PARAM)) / (double)PARAM;
		y2 = (double)((long)(y2 * PARAM)) / (double)PARAM;

		xToMatch = (double)((long)(xToMatch * PARAM)) / (double)PARAM;
		yToMatch = (double)((long)(yToMatch * PARAM)) / (double)PARAM;


		//CPathNode* pPerPenddicular = pPathNodeOut;

		long lVtx1Longitude = (long)(x1 * PARAM);
		long lVtx1Latitude = (long)(y1 * PARAM);

		long lVtx2Longitude = (long)(x2 * PARAM);
		long lVtx2Latitude = (long)(y2 * PARAM);

		long lGpsLongitude = (long)(xToMatch * PARAM);
		long lGpsLatitude = (long)(yToMatch * PARAM);

		// The line function involved pVtx1 and pVtx2 is: a * x + b * y + c = 0.
		long long a = lVtx2Latitude - lVtx1Latitude;
		long long b = lVtx1Longitude - lVtx2Longitude;
		double cc = (x2 * y1) - (x1 * y2);
		long long c = (long long)(cc * PARAM * PARAM);


		// The following formula is to calculate the perpendicular.
		long long aa = a * a;
		long long bb = b * b;
		long long ab = a * b;
		long long ac = a * c;
		long long bc = b * c;

		long long lx1 = bb * lGpsLongitude - ab * lGpsLatitude - ac;
		long long lx2 = aa + bb;
		xIntersect = (double)lx1 / (double)lx2 / (double)PARAM;

		long long ly1 = aa * lGpsLatitude - ab * lGpsLongitude - bc;
		long long ly2 = lx2;
		yIntersect = (double)ly1 / (double)ly2 / (double)PARAM;

		return true;
	}

	
	static double GetPntToLineDis(double xToMatch, double yToMatch, 
		double x1, double y1, 
		double x2, double y2,
		double &xIntersect, double &yIntersect)
	{
		bool bRet = true; //= IsOnSubLink(xToMatch,yToMatch,x1,y1,x2,y2);
		if (bRet)
		{
			double dxMatch = 0;
			double dyMatch = 0;
			CalculatePerpendicular(xToMatch,yToMatch,x1,y1,x2,y2,dxMatch,dyMatch);
			xIntersect = dxMatch;
			yIntersect = dyMatch;
			return CalculateLength(xToMatch,yToMatch,dxMatch,dyMatch);
		}
		else
		{
			double dLenToStart = CalculateLength(xToMatch,yToMatch,x1,y1);
			double dLenToEnd = CalculateLength(xToMatch,yToMatch,x2,y2);
			if (dLenToStart < dLenToEnd)
			{
				xIntersect = x1;
				yIntersect = y1;
				return dLenToStart;
			}
			else
			{
				xIntersect = x2;
				yIntersect = y2;
				return dLenToEnd;

			}

		}
	}
	static double GetPntToLineSecDis(double xToMatch, double yToMatch, 
									double x1, double y1, 
									double x2, double y2,
									double &xIntersect, double &yIntersect)
	{
		double A1,B1,C1; //路段
		double A2,B2,C2; //路段的垂线
		if(x1 == x2)   //是垂直线 斜率为0
		{
			A1 = 1;
			B1 = 0;
			C1 = -x1;
		}
		else
		{
			A1 = (y2 - y1) / (x2 - x1);
			B1 = -1;
			C1 = y2 - A1 * x2;
		}
		if(y2 == y1)   //是垂直线 斜率为0
		{
			A2 = 1;
			B2 = 0;
			C2 = -xToMatch;
		}
		else
		{
			A2 = -(x2 - x1) / (y2 - y1);
			B2 = -1;
			C2 = yToMatch - A2 * xToMatch;
		}
		//求交点		
		double xCross = (C1 * B2 - C2 * B1) / (A2 * B1 - B2 * A1);
		double yCross = (C1 * A2 - C2 * A1) / (B2 * A1 - A2 * B1);
		//投影距离
		//double dis = (fabs(A1 * xToMatch + B1 * yToMatch + C1) / sqrt(A1 * A1 + B1 * B1)) * 100000;
		double dis = CalculateLength(xToMatch,yToMatch,xCross,yCross);
		//交点在线段内
		if(((xCross >= x1 && xCross <= x2) || (xCross <= x1 && xCross >= x2)) && 
			((yCross >= y1 && yCross <= y2) || (yCross <= y1 && yCross >= y2)))
		{
			xIntersect = xCross;
			yIntersect = yCross;
			return dis;
		}
		else
		{
			//点到两个端点的距离
			//double dis1 = (sqrt((xToMatch - x1)*(xToMatch - x1) + (yToMatch - y1)*(yToMatch - y1))) * 100000;
			//double dis2 = (sqrt((xToMatch - x2)*(xToMatch - x2) + (yToMatch - y2)*(yToMatch - y2))) * 100000;
			double dis1 = CalculateLength(xToMatch,yToMatch,x1,y1);
			double dis2 = CalculateLength(xToMatch,yToMatch,x2,y2);

			//double disMin = (dis1 < dis2 ? dis1:dis2);
			double disMin = 0;
			if(dis1 <= dis2)
			{
				disMin = dis1;
				xIntersect = x1;
				yIntersect = y1;
			}
			else
			{
				disMin = dis2;
				xIntersect = x2;
				yIntersect = y2;
			}
			return disMin;
		}
	}


};

