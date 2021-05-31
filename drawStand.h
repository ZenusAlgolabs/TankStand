#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Common.h"
#include "Calculations.h"
#include "Beam.h"
#include "VerticalSupport.h"
#include "CSV.h"

bool drawTankStand(Ptr<Design> design, string material, double tankHead, double tankCapacity, string fluidType,
	double fluidDensity, double costPerMeter_Sq, double costPerMeter_L, double costPerMeter_U)
{
	design->designType(ParametricDesignType);

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
	tankHead = tankHead * 10;
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
	}
	//+-----------------------------------------------+
	//Draw Tank platform beams                        |
	//+-----------------------------------------------+
	deviation = tankDiameter / (uBeamsCount + 1);
	for (int count = 0; count < 2; count++)
	{
		for (int c = 0; c < uBeamsCount; c++)
		{
			drawUBeam(count, i, (c + 1), 0, 0, thickness, width, tankHead, deviation);
			extrudeComponent(i, (tankDiameter * 10) + (80));
			i++;
		}
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
		}
	}
	//+-----------------------------------------------+
	// Draw Diagonal support beams                    |
	//+-----------------------------------------------+	
	float height = (tankHead / supportCount);

	double a = pow(height, 2);
	double b = pow((tankDiameter * 10), 2);
	double extrusionLength = pow((a + b), 0.5) + 40;
	SlantAngle = atan(height / (tankDiameter * 10)); //in degrees
	//ui->messageBox("Angle :" + to_string(SlantAngle) + "\nDiameter :" + to_string(tankDiameter * 10)
	//	+ "\nHeight :" + to_string(height) + "\nExtrusion :" + to_string(extrusionLength));

	for (int e = 1; e < (supportCount + 1); e++)
	{
		for (int count = 0; count < 8; count++)
		{
			drawDiagonal(count, i, 0, deviation, width, thickness, extrusionLength, e);
			i++;
		}
	}
	//+-----------------------------------------------+
	// Document the CSV file                          |
	//+-----------------------------------------------+	
	int csv_count = 1;
	Write(1345.6, "Steel", "Salty", 20.0, 0, " ", 0, 0, 0, 0, " ", false);

	for (size_t i = 0; i < PrincipleBeams; i++)
	{
		Write(0.0, " ", " ", 0.0, csv_count, "RectangularTube", (i + 2), (i * 2.78), (i * 0.65), 1, "Ubeam for supporting columns", false);
		csv_count++;
	}
	for (size_t i = 0; i < supportCount; i++)
	{
		Write(0.0, " ", " ", 0.0, csv_count, "UType", (i + 2), (i * 2.78), (i * 0.65), 1, "Ubeam for supporting columns", false);
		csv_count++;
	}
	for (size_t i = 0; i < supportCount; i++)
	{
		Write(0.0, " ", " ", 0.0, csv_count, "LType", (i + 2), (i * 2.78), (i * 0.65), 1, "Ubeam for supporting columns", false);
		csv_count++;
	}
	Write(0.0, " ", " ", 0.0, 0, " ", 0, 0, 0, 0, " ", true);

	return true;
}
#endif // !BEAM_H
