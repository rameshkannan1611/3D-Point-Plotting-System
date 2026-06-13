#ifndef __DataStruct__
#define __DataStruct__ 
#include "PointStruct.h"
class DataStruct
{
public:
	DataStruct();
	~DataStruct();
	
	PointStruct* GetPnts();
	void AddPoint(PointStruct&);
	void AddPoint(Point3D&);
	void AddPoints(PointStruct*, long);
	void AddPoints(Point3D*, long);
	void RemovePoint(long);
	void RemovePoints();
private:
	PointStruct* m_Pnts;
	long m_NbPnts;
	long m_NbPntsCapacity;
	long m_HighestPntID;
};
#endif

