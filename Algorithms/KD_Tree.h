#pragma once

#include <vector>

class Point3D;

class KD_Tree
{

public:
	KD_Tree() = delete;
	KD_Tree(KD_Tree const&) = delete;
	KD_Tree operator=(KD_Tree const&) = delete;

	KD_Tree(std::vector<Point3D>const&);

private:
	std::vector<Point3D> _vecAllPoints;

};

