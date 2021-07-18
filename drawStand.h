#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Common.h"
#include "Calculations.h"
#include "Beam.h"
#include "VerticalSupport.h"
#include "CSV.h"

bool drawTankStand(Ptr<Design> design, double tankHead, 
double tankCapacity, double costPerMeter_Sq, double costPerMeter_L)
{
	design->designType(ParametricDesignType);

	PrincipleBeams_Cost_per_Meter = costPerMeter_Sq;
	HorizontalBeams_Cost_per_Meter = costPerMeter_L;
	DiagonalBeams_Cost_per_Meter = costPerMeter_L;

	// Get the root component of the active design
	rootComp = design->rootComponent();
	if (!rootComp)
		return false;

	//Create an occurrence to use through out the process
	occs = rootComp->occurrences();
	if (!occs)
		return false;
	transform = adsk::core::Matrix3D::create();
	if (!transform)
		return false;

	Principle.push_back(0);
	Principle.push_back(0);
	Principle.push_back(0);
	Principle.push_back(4);
	Principle.push_back(4);
	Principle.push_back(4);
	Principle.push_back(4);
	Principle.push_back(0);


	int i = 0;
	double deviation = 0.0;
	tankHead = 2000 * 10;
	tankDiameter = pow((tankCapacity / (3.145167 * 2)), 0.5);
	calculatePriciplePositions();
	//+-----------------------------------------------+
	// Draw 4 Principle support beams                 |
	//+-----------------------------------------------+
	for (int a = 0; a < PrincipleBeams; a++)
	{
		drawRBeam(i, 0, 0, thickness);
		extrudeComponent(i, tankHead);
		i++;
		PrincipleBeams_Length = PrincipleBeams_Length + 6096;
	}
	//+-----------------------------------------------+
	//     Draw structure support beams               |
	// 	   Horizontal Support structures              |
	//+-----------------------------------------------+
	deviation = ((tankHead / 10) / supportCount);
	for (int b = 1; b < (supportCount + 1); b++)
	{

		for (int count = 0; count < 4; count++)
		{
			drawHorizontal(count, i, 0, deviation, width, thickness, b);
			extrudeComponent(i, tankDiameter * 10 + 80);
			i++;
			HorizontalBeams_Length = HorizontalBeams_Length + 1550;
		}
	}
	//+-----------------------------------------------+
	// Draw Diagonal support beams                    |
	//+-----------------------------------------------+	
	float height = (tankHead / supportCount);

	double a = pow(height, 2);
	double b = pow((tankDiameter * 10), 2);
	double extrusionLength = pow((a + b), 0.5) + 40;
	SlantAngle = atan(height / (tankDiameter * 10 + 40)); //in degrees

	for (int e = 1; e < (supportCount + 1); e++)
	{
		for (int count = 0; count < 8; count++)
		{
			drawDiagonal(count, i, 0, deviation, width,
			 thickness, extrusionLength, e);
			DiagonalBeams_Length = DiagonalBeams_Length + 
			pow((pow(6096, 2) + pow(1550, 2)), 0.5);
			i++;
		}
	}

	CalculateCost();

	//+-----------------------------------------------+
	// Document the CSV file                          |
	//+-----------------------------------------------+	
	int csv_count = 1;
	Write(2500, 6.096, " ", 0, 0, 0, 0, " ", 0, 0, 0, 0, 0, 0, 0, 0, 0, false);

	Write(0.0, 0.0, "RectangularTube", 4, 50, 50, 2,
	 "Principle Columns", 0, 0, 0, 0, 0, 0, 0, 0, 0, false);
	Write(0.0, 0.0, "Angle Line", 4*3, 25, 25, 3,
	 "Horizontal braces", 0, 0, 0, 0, 0, 0, 0, 0, 0, false);
	Write(0.0, 0.0, "Angle Line", 2*4*3, 25, 25, 3,
	 "Diagonal struts", 0, 0, 0, 0, 0, 0, 0, 0, 0, false);

	Write(0.0, 0.0, " ", 0, 0, 0, 0, " ", PrincipleBeams_Length, 
	PrincipleBeams_Cost_per_Meter, PrincipleBeams_Cost,
		HorizontalBeams_Length, HorizontalBeams_Cost_per_Meter, 
		HorizontalBeams_Cost,DiagonalBeams_Length, DiagonalBeams_Cost_per_Meter,
		 DiagonalBeams_Cost, true);

	return true;
}
#endif // !BEAM_H
