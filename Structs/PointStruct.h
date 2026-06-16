#ifndef __PointStruct__
#define __PointStruct__ 

class Point3D;




class PointStruct
{
public:
	PointStruct();
	PointStruct(Point3D&);
	PointStruct(PointStruct*);
	PointStruct(PointStruct&);
	PointStruct(double*, long);
	~PointStruct();
	void operator=(PointStruct&);
	void SetXYZValue(double*);
	void SetXYZValue(double,double,double);
	void SetID(long);
	double* GetXYZValue();
	long GetID();

private:
	double xyz[3];
	long id;
};

#endif 
