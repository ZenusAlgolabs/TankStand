#pragma once
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "Common.h"

bool calculateTankDiameter(double Capacity)
{

}

bool calculateLoad(double Capacity,std::string Quality)
{

}

bool calculateBeamHeight(double Load)
{

}

bool calculateStandDimensions()
{

}

bool calculateDiagonalExtrusionLength(double head,double diameter,int h_support)
{
	double deviation = (head / h_support);

	diagonalExtrusionLength = pow((pow(deviation, 2) + pow(((diameter + (2 * beamSize))*10), 2)), 0.5);
	return true;
}

bool calculateDiagonalSlant(double width, double diameter, double exLenghth)
{
	//diagonalSlant = width / cos(acos(diameter / exLenghth));
	return true;
}
#endif // !CALCULATIONS_H
