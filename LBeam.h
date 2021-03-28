#pragma once
#ifndef LBeam_h
#define  LBeam_h

#include "Horizontal.h"
#include "Diagonal.h"

bool drawHorizontalSupportBeams(int ID, double _extrusionLength)
{
	drawHorizontalLBeam(ID, 0, 0);
	extrudeComponent(ID, tankDiameter*10+80);
	return true;
}

bool drawDiagonalSupportBeams(int ID, double _extrusionLength)
{
	drawDiagonalLBeam(ID, 0, 0);
	extrudeComponent(ID, tankDiameter * 10+80);
	return true;
}

#endif // !LBeam_h
