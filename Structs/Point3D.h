#pragma once
#ifndef __Point3D__
#define __Point3D__ 
class Point3D
{
public:
	Point3D();
	Point3D(double*);
	Point3D(double,double,double);

	double x;
	double y;
	double z;
};
#endif

