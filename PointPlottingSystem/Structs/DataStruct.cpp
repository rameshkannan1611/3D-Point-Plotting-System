#include "DataStruct.h"
#include "Point3D.h"

///////////////////////////////////////////////////////////////////////
DataStruct::DataStruct()
{
	m_NbPntsCapacity = 100;
	m_Pnts = new PointStruct[100];
	m_NbPnts = 0;
	m_HighestPntID = 1;
}
///////////////////////////////////////////////////////////////////////
DataStruct::~DataStruct()
{
	if (m_Pnts)delete[]m_Pnts;
}
///////////////////////////////////////////////////////////////////////
void DataStruct::AddPoint(PointStruct&pntStrct)
{
	if (m_Pnts)
	{
		m_Pnts[m_NbPnts].SetXYZValue(pntStrct.GetXYZValue());
		if (m_HighestPntID < pntStrct.GetID())
			m_HighestPntID = pntStrct.GetID();
		m_Pnts[m_NbPnts].SetID(m_HighestPntID++);
		++m_NbPnts;
	}
}
///////////////////////////////////////////////////////////////////////
void DataStruct::AddPoint(Point3D&pnt)
{
	if (m_Pnts)
	{
		m_Pnts[m_NbPnts].SetXYZValue(pnt.x, pnt.y, pnt.z);
		m_Pnts[m_NbPnts].SetID(m_HighestPntID++);
		++m_NbPnts;
	}
}
///////////////////////////////////////////////////////////////////////
void DataStruct::AddPoints(PointStruct*xyz, long cnt)
{
	if (m_Pnts)
	{
		for (long i = 0;i < cnt;++i)
		{
			AddPoint(xyz[i]);
		}
	}
}
///////////////////////////////////////////////////////////////////////
void DataStruct::AddPoints(Point3D*xyz, long cnt)
{
	if (m_Pnts)
	{
		for (long i = 0;i < cnt;++i)
		{
			AddPoint(xyz[i]);
		}
	}
}
///////////////////////////////////////////////////////////////////////
void DataStruct::RemovePoint(long indx)
{
	if (!m_Pnts || m_NbPnts < indx || indx<0)
		return;
	
	for (long i = indx;i < m_NbPnts-1;++i)
	{
		m_Pnts[i] = m_Pnts[i + 1];
	}
	m_NbPnts--;
}
///////////////////////////////////////////////////////////////////////
void DataStruct::RemovePoints()
{
	if (m_Pnts)delete[]m_Pnts;
	m_Pnts = nullptr;
}
///////////////////////////////////////////////////////////////////////
PointStruct* DataStruct::GetPnts()
{
	return m_Pnts;
}
///////////////////////////////////////////////////////////////////////
