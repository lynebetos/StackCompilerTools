#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

const double PI				= 3.14159265358979323846; //4.0*atan(1.0);
const double DEG_TO_RAD     = PI /180.;   // 角度到弧度
const double EARTH_RADIUS	= 6378.137;   // 地球赤道半径


#define MISSING -1
#define MAX_FIELD 100;

#define DIR_UP 1
#define DIR_DOWN 2

typedef struct tagSakeIndex
{
	std::string strRoadCode;
	unsigned int iStakeID;
	unsigned int iOriLng;
	unsigned int iOriLat;
	unsigned int iNowLng;
	unsigned int iNowLat;
	unsigned int iLinkID;
	unsigned int iStart;
	unsigned int iEnd;
	unsigned int iType;
	unsigned int iID;
}SIndex;
typedef struct tagLinkIndex
{
	std::string iRoadCode;
	unsigned int iName;
	unsigned int iGroup;
	unsigned int iNumInGroup;
	unsigned int iLinkID;
	unsigned int iDir;
	unsigned int iPri;
	unsigned int iProvince;
	unsigned int iCity;
	unsigned int iSCounty;
	unsigned int iECounty;
	unsigned int iClass;
	unsigned int iLength;
	unsigned int iLufu;
	unsigned int iWidth;
	unsigned int iSpeed;
// 	unsigned int iSStake = MAX_FIELD;
// 	unsigned int iEStake = MAX_FIELD;
// 	unsigned int iCompany = MAX_FIELD;
// 	unsigned int iComPhong = MAX_FIELD;
	unsigned int iPhong;
	unsigned int iLoc;
}KIndex;

//经纬度结构体
typedef struct tagCoordinate
{
	int Lat;
	int Lon;
}Coord;
typedef struct tagDCoordinate
{
	double Lat;
	double Lon;
}DCoord;
//typedef vector<DCoord> DCoords;
//经纬度数组
typedef vector<Coord> Coords;
//
typedef unsigned int LinkIndex;
typedef struct tagSequentialStake
{
	bool isMissing;
	vector<unsigned int> vecMissing;
	vector<unsigned int> vecDiff;
	vector<pair<unsigned int,unsigned int>> vecOutOfRange; 
	unsigned int iValid;
	void Init()
	{
		isMissing = false;
		iValid = 0;
		vecMissing.reserve(10);
		vecDiff.reserve(10);
		vecOutOfRange.reserve(10);
	}
	tagSequentialStake()
	{
		Init();
	}
	~tagSequentialStake()
	{
		Init();
	}
	void Copy(tagSequentialStake& seqstake)
	{
		this->isMissing = seqstake.isMissing;
		if (seqstake.isMissing)
		{
			for (std::size_t i = 0; i < seqstake.vecMissing.size(); i++)
			{
				this->vecMissing[i] = seqstake.vecMissing[i];
			}
		}
		for (std::size_t i = 0; i < seqstake.vecDiff.size(); i++)
		{
			this->vecDiff[i] = seqstake.vecDiff[i];
		}
		for (std::size_t i = 0; i < seqstake.vecOutOfRange.size(); i++)
		{
			this->vecOutOfRange[i].first = seqstake.vecOutOfRange[i].first;
			this->vecOutOfRange[i].second = seqstake.vecOutOfRange[i].second;
		}
	}
}SeqStake;

typedef struct tagSiWeiLink
{
	string strRoadID;
	string strRouteName;
	long long lLinkID;
	unsigned int iLineGroup;//线段组
	unsigned int iPartialOrder;//分段顺序号
	int iDir;//上下行标志
	unsigned int iPrimary;//主干道
	string strProvince;//所在省
	string strCity;//所在市
	string strBCity;//起始县级市
	string strEcity;//终止县级市
	unsigned int iClass;
	double dLength;
	unsigned int iRouteNum;//路幅
	unsigned int iWidth;
	unsigned int iSpeed;
	double dStartStake;
	double dEndStake;
	string strPhoneNum;
	vector<DCoord> coords;
	void Init()
	{
		strRoadID = "";;
		strRouteName = "";
		lLinkID = 0;
		iLineGroup = INT_MAX;//线段组
		iPartialOrder = INT_MAX;//分段顺序号
		iDir = -1;//上下行标志
		iPrimary;//主干道
		strProvince = "";//所在省
		strCity = "";//所在市
		strBCity = "";//起始县级市
		strEcity = "";//终止县级市
		iClass = INT_MAX;
		dLength = 0.0;
		iRouteNum = 0;//路幅
		iWidth = 0;
		iSpeed = INT_MAX;
		dStartStake = 0.0;
		dEndStake = 0.0;
		strPhoneNum = "";
		coords.clear();
	}
	tagSiWeiLink()
	{
		Init();
	}
	~tagSiWeiLink()
	{
		Init();
	}
	void assign(tagSiWeiLink& link)
	{
		this->strRoadID = link.strRoadID;
		this->strRouteName = link.strRouteName;
		this->lLinkID = link.lLinkID;
		this->iLineGroup = link.iLineGroup;
		this->iPartialOrder = link.iPartialOrder;
		this->iDir = link.iDir;
		this->iPrimary = link.iPrimary;
		this->strProvince = link.strProvince;
		this->strCity = link.strCity;
		this->strBCity = link.strBCity;
		this->strEcity = link.strEcity;
		this->iClass = link.iClass;
		this->dLength = link.dLength;
		this->iRouteNum = link.iRouteNum;
		this->iWidth = link.iWidth;
		this->iSpeed = link.iSpeed;
		this->strPhoneNum = link.strPhoneNum;
		this->dStartStake = link.dStartStake;
		this->dEndStake = link.dEndStake;
		this->coords.reserve(link.coords.size());
		this->coords.clear();
		for (std::size_t i = 0; i < link.coords.size(); i++)
		{
			this->coords.push_back(link.coords[i]);
		}
	}
}SWLink;

typedef struct tagFacilityOfRoad
{
	std::string strRoadID;
	int iDir;
	int iPoiID;
	long long lLinkID;
	double dbStakeInLine;
	std::string strName;
	DCoord coord;
	int iType;

	void Init()
	{
		strRoadID = "";
		iDir = -1;
		iPoiID = -1;
		lLinkID = -1;
		dbStakeInLine = -1.0;
		strName = "";
		iType = -1;
	}
	tagFacilityOfRoad()
	{
		Init();
	}
	~tagFacilityOfRoad()
	{
		Init();
	}
}Facility;

typedef struct tagFilesName 
{
	string AttPath;
	string StaPath;
	string FacPath;
}FilesName;

typedef struct tagStakeInfo
{
	std::string routeID;
	int stakeID;
	DCoord dcoord;
	long long lLinkID;
	int stakeFlag;
	int Pre_Cindex;
	int Nex_Cindex;
	//map<unsigned int, vector<p>>
}StakeInfo;
inline bool Equal(const DCoord& d1,const DCoord& d2)
{
	double abs1 = abs(d1.Lat - d2.Lat);
	double abs2 = abs(d1.Lon - d2.Lon);
	return abs1<0.00001 && abs2<0.00001;
}
// inline bool LessBegin(const SWLink& h1,const SWLink& h2)
// {
// 	return h1.dStartStake < h2.dStartStake;
// }
// inline bool LessEnd(const SWLink& h1,const SWLink& h2)
// {
// 	return h1.dEndStake < h2.dEndStake;
// }
inline bool EqualCoord(DCoord& c1,DCoord& c2)
{
	return (c1.Lon == c2.Lon) && (c1.Lat == c2.Lat);
}
inline bool LessStakeID(StakeInfo& stake1,StakeInfo& stake2)
{
	return stake1.stakeID < stake2.stakeID;
}

class StakeCompare
{
	bool operator()(StakeInfo& stake1, StakeInfo& stake2)
	{
		return LessStakeID(stake1, stake2);
	}
};

class StakeIDLess
{
public:
	bool operator()(double id1, double id2)
	{
		return id1 < id2;
	}
};

class StakeIDMore
{
public:
	bool operator()(double id1, double id2)
	{
		return id1 > id2;
	}
};


inline void StringSplit(string strLine,vector<string>& refVec,char token = ',')
{
	stringstream ss(strLine);
	string item;
	while(getline(ss, item, token)) 
	{
		if(item.size() > 0)
			refVec.push_back(item);
	}
}
typedef struct tagBinaryLink
{
	LinkIndex iIndex;
	unsigned int iMeshID;
	long long lLinkID;
	unsigned int iLength;
	char chDir;
	double dStakeBegin;
	double dStakeEnd;
}BLink;
typedef struct tagConfig
{
	string inputPath;
	string outputPath;
}Config;

typedef struct tagPOIIndex
{
	int nPTIndex;  //POI类型
	int nPIIndex;	  //POI信息
	
	void init()
	{
		nPTIndex = 0;
		nPIIndex = 0;
	}
	tagPOIIndex()
	{
		init();
	}
	~tagPOIIndex()
	{
		init();
	}

}PIndex;


typedef struct tagCoordAndLinkIndex
{
	int CIndex;
	int LIndex;
	vector<PIndex> vecPIndexs;
	tagCoordAndLinkIndex()
	{
		CIndex = 0;
		LIndex = 1;
	}
	tagCoordAndLinkIndex(int ci,int li)
	{
		CIndex = ci;
		LIndex = li;
	}
}CLIndex;

inline double ApproximateDistance( const int lat1, const int lon1, const int lat2, const int lon2 ) 
{
	static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
	//Earth's quatratic mean radius for WGS-84
	static const double EARTH_RADIUS_IN_METERS = 6372797.560856;
	double latitudeArc  = ( lat1/100000. - lat2/100000. ) * DEG_TO_RAD;
	double longitudeArc = ( lon1/100000. - lon2/100000. ) * DEG_TO_RAD;
	double latitudeH = sin( latitudeArc * 0.5 );
	latitudeH *= latitudeH;
	double lontitudeH = sin( longitudeArc * 0.5 );
	lontitudeH *= lontitudeH;
	double tmp = cos( lat1/100000. * DEG_TO_RAD ) * cos( lat2/100000. * DEG_TO_RAD );
	double distanceArc =  2.0 * asin( sqrt( latitudeH + tmp * lontitudeH ) );
	return EARTH_RADIUS_IN_METERS * distanceArc;
}
inline void encodeNumber(int numberToEncode, string & output) {
	while (numberToEncode >= 0x20) {
		int nextValue = (0x20 | (numberToEncode & 0x1f)) + 63;
		output += (static_cast<char> (nextValue));
		if(92 == nextValue)
			output += (static_cast<char> (nextValue));
		numberToEncode >>= 5;
	}

	numberToEncode += 63;
	output += (static_cast<char> (numberToEncode));
	if(92 == numberToEncode)
		output += (static_cast<char> (numberToEncode));
}

inline void encodeVectorSignedNumber(vector<int> & numbers, string & output) {
	for(unsigned i = 0; i < numbers.size(); ++i) {
		numbers[i] <<= 1;
		if (numbers[i] < 0) {
			numbers[i] = ~(numbers[i]);
		}
	}
	for(unsigned i = 0; i < numbers.size(); ++i) {
		encodeNumber(numbers[i], output);
	}
}
inline string & replaceAll(std::string &s, const std::string &sub, const std::string &other) {
	size_t b = 0;
	for (;;) {
		b = s.find(sub, b);
		if (b == s.npos) break;
		s.replace(b, sub.size(), other);
		b += other.size();
	}
	return s;
}

inline void printEncodedString(vector<DCoord> &vecResultCoords,string& strOut) 
{
		vector<int> deltaNumbers;
		DCoord &resultCoord = vecResultCoords[0];
		if(vecResultCoords.size() > 0)
		{
			Coord lastCoordinate;
			lastCoordinate.Lat = (int)floor(resultCoord.Lat * 100000 );
			lastCoordinate.Lon = (int)floor(resultCoord.Lon * 100000);
			deltaNumbers.push_back( lastCoordinate.Lon );
			deltaNumbers.push_back( lastCoordinate.Lat );
			for (std::size_t i = 1; i < vecResultCoords.size(); ++i)
			{
				deltaNumbers.push_back( (int)floor(vecResultCoords[i].Lon * 100000 ) - lastCoordinate.Lon );
				deltaNumbers.push_back( (int)floor(vecResultCoords[i].Lat * 100000 ) - lastCoordinate.Lat );
				lastCoordinate.Lat = (int)floor(vecResultCoords[i].Lat * 100000 );
				lastCoordinate.Lon = (int)floor(vecResultCoords[i].Lon * 100000 );
			}
			encodeVectorSignedNumber(deltaNumbers,strOut);
			replaceAll(strOut,"\\\\","\\");
			deltaNumbers.clear();
		}
}

static double CalculateLength(double dLng1, double dLat1, double dLng2, double dLat2) 
{
	double radLat1(dLat1 * DEG_TO_RAD);
	double radLat2(dLat2 * DEG_TO_RAD);
	double a(radLat1 - radLat2);
	double b((dLng1 - dLng2) * DEG_TO_RAD);
	double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));
	s = s * EARTH_RADIUS * 1000;
	return s;
}
