#pragma once
#ifndef VerticalSupport_H
#define VerticalSupport_H

#include "Common.h"

// X Y axis
bool drawDiagonal(int count, int ID, int refID, double deviation, 
double width, double thickness, double extrusionLength, int location)
{
	double slantAngle = SlantAngle;

	x_1 = 0.0; y_1 = 0.0; z_1 = 0.0;
	x_2 = 0.0; y_2 = 0.0; z_2 = 0.0;
	x_3 = 0.0; y_3 = 0.0; z_3 = 0.0;
	x_4 = 0.0; y_4 = 0.0; z_4 = 0.0;
	x_5 = 0.0; y_5 = 0.0; z_5 = 0.0;
	x_6 = 0.0; y_6 = 0.0; z_6 = 0.0;

	if (count == 0)
	{
		//Left
		x_1 = 0;    y_1 = deviation * location;  z_1 = 0;
		x_2 = x_1;  y_2 = y_1 + thickness * cos(slantAngle);   
		z_2 = z_1 + thickness;
		x_3 = x_2 + thickness; y_3 = y_2;     z_3 = z_2;
		x_4 = x_3;  y_4 = y_1 + width * cos(slantAngle);
		       z_4 = z_1 + width;
		x_5 = x_1 + width; y_5 = y_4;   z_5 = z_4;
		x_6 = x_5;    y_6 = y_1;     z_6 = z_1;
	}
	else if (count == 1)
	{
		//Left
		x_1 = 0;                        y_1 = deviation * location;  
		z_1 = tankDiameter + 2 * beamSize;
		x_2 = x_1;                y_2 = y_1 + thickness * cos(slantAngle);
		           z_2 = z_1 - thickness;
		x_3 = x_2 + thickness;          y_3 = y_2;        z_3 = z_2;
		x_4 = x_3;               y_4 = y_1 + width * cos(slantAngle);
		       z_4 = z_1 - width;
		x_5 = x_1 + width;              y_5 = y_4;      z_5 = z_4;
		x_6 = x_5;                      y_6 = y_1;      z_6 = z_1;
		extrusionLength = extrusionLength * -1;
	}

	else if (count == 2)
	{
		//Right
		x_1 = tankDiameter + beamSize;   y_1 = deviation * location;
		  z_1 = 0;
		x_2 = x_1;            y_2 = y_1 + thickness * cos(slantAngle);    
		z_2 = z_1 + thickness;
		x_3 = x_2 + (width - thickness); y_3 = y_2;         z_3 = z_2;
		x_4 = x_3;             y_4 = y_1 + width * cos(slantAngle);         
		z_4 = z_1 + width;
		x_5 = x_1 + width;               y_5 = y_4;           z_5 = z_4;
		x_6 = x_5;                       y_6 = y_1;        z_6 = z_1;
	}
	else if (count == 3)
	{
		//Right
		x_1 = tankDiameter + beamSize;   y_1 = deviation * location; 
		z_1 = tankDiameter + beamSize * 2;
		x_2 = x_1;         y_2 = y_1 + thickness * cos(slantAngle);    
		z_2 = z_1 - thickness;
		x_3 = x_2 + (width - thickness); y_3 = y_2;         z_3 = z_2;
		x_4 = x_3;           y_4 = y_1 + width * cos(slantAngle);         
		z_4 = z_1 - width;
		x_5 = x_1 + width;               y_5 = y_4;         z_5 = z_4;
		x_6 = x_5;                       y_6 = y_1;       z_6 = z_1;
		extrusionLength = extrusionLength * -1;
	}

	else if (count == 4)
	{
		//Up
		z_1 = 0;               y_1 = deviation * location;  x_1 = 0;
		z_2 = z_1;             y_2 = y_1 + width * cos(slantAngle);      
		x_2 = x_1 + width;
		z_3 = z_2 + thickness; y_3 = y_2;          x_3 = x_2;
		z_4 = z_3;             y_4 = y_1 + thickness * cos(slantAngle);   
		x_4 = x_1 + thickness;
		z_5 = z_1 + width;     y_5 = y_4;           x_5 = x_4;
		z_6 = z_5;             y_6 = y_1;            x_6 = x_1;
	}
	else if (count == 5)
	{
		//Up
		z_1 = 0;               y_1 = deviation * location; 
		x_1 = tankDiameter + beamSize * 2;
		z_2 = z_1;             y_2 = y_1 + width * cos(slantAngle);         
		x_2 = x_1 - width;
		z_3 = z_2 + thickness; y_3 = y_2;           x_3 = x_2;
		z_4 = z_3;             y_4 = y_1 + thickness * cos(slantAngle);    
		x_4 = x_1 - thickness;
		z_5 = z_1 + width;     y_5 = y_4;            x_5 = x_4;
		z_6 = z_5;             y_6 = y_1;            x_6 = x_1;
		extrusionLength = extrusionLength * -1;
	}

	else if (count == 6)
	{
		//Down
		z_1 = tankDiameter + beamSize;   y_1 = deviation * location; 
		 x_1 = 0;
		z_2 = z_1;            y_2 = y_1 + thickness * cos(slantAngle);   
		x_2 = x_1 + thickness;
		z_3 = z_2 + (width - thickness); y_3 = y_2;           x_3 = x_2;
		z_4 = z_3;                       y_4 = y_1 + width * cos(slantAngle);       
		x_4 = x_1 + width;
		z_5 = z_1 + width;               y_5 = y_4;           x_5 = x_4;
		z_6 = z_5;                       y_6 = y_1;             x_6 = x_1;
	}
	else if (count == 7)
	{
		//Down
		z_1 = tankDiameter + beamSize;   y_1 = deviation * location; 
		x_1 = tankDiameter + beamSize * 2;
		z_2 = z_1;               y_2 = y_1 + thickness * cos(slantAngle);     
		x_2 = x_1 - thickness;
		z_3 = z_2 + (width - thickness); y_3 = y_2;          x_3 = x_2;
		z_4 = z_3;                  y_4 = y_1 + width * cos(slantAngle);       
		x_4 = x_1 - width;
		z_5 = z_1 + width;               y_5 = y_4;             x_5 = x_4;
		z_6 = z_5;                       y_6 = y_1;           x_6 = x_1;
		extrusionLength = extrusionLength * -1;
	}

	Sketch_LBeam(ID, refID);
	extrudeComponent(ID, extrusionLength);

	return true;
}

bool drawHorizontal(int count, int ID, int refID, double deviation, 
	double width, double thickness, int location)
{
	x_1 = 0.0; y_1 = 0.0; z_1 = 0.0;
	x_2 = 0.0; y_2 = 0.0; z_2 = 0.0;
	x_3 = 0.0; y_3 = 0.0; z_3 = 0.0;
	x_4 = 0.0; y_4 = 0.0; z_4 = 0.0;
	x_5 = 0.0; y_5 = 0.0; z_5 = 0.0;
	x_6 = 0.0; y_6 = 0.0; z_6 = 0.0;
	if (count == 0)
	{
		//Left
		x_1 = 0; y_1 = deviation * location;
		x_2 = x_1; y_2 = y_1 + width;
		x_3 = x_2 + thickness; y_3 = y_2;
		x_4 = x_3; y_4 = y_1 + thickness;
		x_5 = x_1 + width; y_5 = y_4;
		x_6 = x_5; y_6 = y_1;
	}
	else if (count == 1)
	{
		//Right
		x_1 = tankDiameter + beamSize; y_1 = deviation * location;
		x_2 = x_1; y_2 = y_1 + thickness;
		x_3 = x_2 + (width - thickness); y_3 = y_2;
		x_4 = x_3; y_4 = y_1 + width;
		x_5 = x_1 + width; y_5 = y_4;
		x_6 = x_5; y_6 = y_1;
	}
	else if (count == 2)
	{
		//Up
		z_1 = 0; y_1 = deviation * location;
		z_2 = z_1; y_2 = y_1 + width;
		z_3 = z_2 + thickness; y_3 = y_2;
		z_4 = z_3; y_4 = y_1 + thickness;
		z_5 = z_1 + width; y_5 = y_4;
		z_6 = z_5; y_6 = y_1;
	}
	else if (count == 3)
	{
		//Down
		z_1 = tankDiameter + beamSize; y_1 = deviation * location;
		z_2 = z_1; y_2 = y_1 + thickness;
		z_3 = z_2 + (width - thickness); y_3 = y_2;
		z_4 = z_3; y_4 = y_1 + width;
		z_5 = z_1 + width; y_5 = y_4;
		z_6 = z_5; y_6 = y_1;
	}

	Sketch_LBeam(ID, refID);
	return true;
}

#endif // !VerticalSupport_H
