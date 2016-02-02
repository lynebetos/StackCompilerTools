#if !defined(__RoadNet_CVertex_h)
#define __RoadNet_CVertex_h

class CLink;
class CVertex
{
public:
	double m_dLongitude;
	double m_dLatitude;
	/* 到下一个内点之间的距离，最后一个内点此属性值为0。 */
	double m_dDistanceToNext;
	/* 到下一个内点的方向角 */
	int m_iAngleToNext;

	CLink* m_pLink;

	CVertex();
	~CVertex();

protected:
private:

};

#endif