#pragma once
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "Common.h"

float calculateTankDiameter(float Capacity, std::string TankType, float BaseLength, float BaseWidth)
{
	float LongSide = 0.0;
	float ShortSide = 0.0;

	if (TankType == "Rectangular")
	{

	}
	else if (TankType == "Circular")
	{

	}
	return 0.0;
}

float calculateLoad(float Capacity, std::string Quality)
{
	float density = 1000;
	float load = 0.0;
	if (Quality == "salty")
	{
		density = 1200;
	}
	load = Capacity * density;
	return(load);
}

float calculateBeamHeight(float Head, float Max_Beam_Length)
{
	return (Head / Max_Beam_Length);
}

bool calculateStandDimensions()
{

}

bool calculateDiagonalExtrusionLength(float head,float diameter,int h_support)
{
	float deviation = (head / h_support);

	diagonalExtrusionLength = pow((pow(deviation, 2) + pow(((diameter + (2 * beamSize))*10), 2)), 0.5);
	return true;
}

bool calculateDiagonalSlant(float width, float diameter, float exLenghth)
{
	//diagonalSlant = width / cos(acos(diameter / exLenghth));
	return true;
}
#endif // !CALCULATIONS_H
