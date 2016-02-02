#if !defined(__RoadNet_CVertex_h)
#define __RoadNet_CVertex_h

class CLink;
class CVertex
{
public:
	double m_dLongitude;
	double m_dLatitude;
	/* ����һ���ڵ�֮��ľ��룬���һ���ڵ������ֵΪ0�� */
	double m_dDistanceToNext;
	/* ����һ���ڵ�ķ���� */
	int m_iAngleToNext;

	CLink* m_pLink;

	CVertex();
	~CVertex();

protected:
private:

};

#endif