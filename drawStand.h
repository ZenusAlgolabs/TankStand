#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Common.h"
#include "Calculations.h"
#include "Beam.h"
#include "Horizontal.h"
#include "Diagonal.h"
#include "CSV.h"

bool drawTankStand(Ptr<Design> design, double tankHead, double tankCapacity)
{
	int csv_count = 1;
	Write(1345.6, "Steel", "Salty", 20.0, 0, " ", 0, 0, 0, 0, " ",false);

	for (size_t i = 0; i < PrincipleBeams; i++)
	{
		Write(0.0, " ", " ", 0.0, csv_count, "RectangularTube", (i + 2), (i * 2.78), (i * 0.65), 1, "Ubeam for supporting columns", false);
		csv_count++;
	}
	for (size_t i = 0; i < HorizontalSupport; i++)
	{
		Write(0.0, " ", " ", 0.0, csv_count, "UType", (i + 2), (i * 2.78), (i * 0.65), 1, "Ubeam for supporting columns", false);
		csv_count++;
	}
	for (size_t i = 0; i < DiagonalSupport; i++)
	{
		Write(0.0, " ", " ", 0.0, csv_count, "LType", (i + 2), (i * 2.78), (i * 0.65), 1, "Ubeam for supporting columns", false);
		csv_count++;
	}
	Write(0.0, " ", " ", 0.0, 0, " ", 0, 0, 0, 0, " ", true);

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

	calculatePriciplePositions();

	int i = 0;

	//+-----------------------------------------------+
	// Draw 4 Principle support beams                 |
	//+-----------------------------------------------+
	for (int a = 0; a < PrincipleBeams; a++)
	{
		drawRBeam(i, 0, 0, 1);
		extrudeComponent(i, tankHead);
		i++;
	}

	//+-----------------------------------------------+
	//Draw Tank platform beams                        |
	//1. Connecting beams                             |
	//+-----------------------------------------------+
	for (int c = 0; c < SupportUBeams; c++)
	{
		drawSupportUBeam(i, (c + 1), 0, 0, 1, 4, tankHead);
		extrudeComponent(i, (tankDiameter * 10) + (80));
		i++;
	}

	//+-----------------------------------------------+
	//2. Base beams                                   |
	//+-----------------------------------------------+
	for (int d = 0; d < BaseUBeams; d++)
	{
		drawBaseUBeam(i, (d + 1), 0, 0, 1, 4, tankHead);
		extrudeComponent(i, (tankDiameter * 10) + (80));
		i++;
	}
	
	//+-----------------------------------------------+
	//     Draw structure support beams               |
	// 	   Horizontal Support structures              |
	//+-----------------------------------------------+
	for (int b = 1; b < (HorizontalSupport+1); b++)
	{
		double width = 4;
		double thickness = 1;

		drawLeft(i, 0, 0, width, thickness, tankHead, b);
		extrudeComponent(i, tankDiameter * 10 + 80);
		i++;

		drawRight(i, 0, 0, width, thickness, tankHead, b);
		extrudeComponent(i, tankDiameter * 10 + 80);
		i++;

		drawUp(i, 0, 0, width, thickness, tankHead, b);
		extrudeComponent(i, tankDiameter * 10 + 80);
		i++;

		drawDown(i, 0, 0, width, thickness, tankHead, b);
		extrudeComponent(i, tankDiameter * 10 + 80);
		i++;
	}

	//+-----------------------------------------------+
	// Draw Diagonal support beams                    |
	//+-----------------------------------------------+

	calculateDiagonalExtrusionLength(tankHead,tankDiameter,HorizontalSupport);
	calculateDiagonalSlant(4, tankDiameter, diagonalExtrusionLength);
	for (int e = 1; e < (DiagonalSupport+1); e++)
	{
		double width = 4;
		double thickness = 1;

		drawLeftDiagonal(i, 0, 0, width, thickness, tankHead, e,diagonalSlant);
		extrudeComponent(i, diagonalExtrusionLength);
		i++;
	
		drawRightDiagonal(i, 0, 0, width, thickness, tankHead, e, diagonalSlant);
		extrudeComponent(i, diagonalExtrusionLength);
		i++;

		drawUpDiagonal(i, 0, 0, width, thickness, tankHead, e, diagonalSlant);
		extrudeComponent(i, diagonalExtrusionLength);
		i++;
		
		drawDownDiagonal(i, 0, 0, width, thickness, tankHead, e, diagonalSlant);
		extrudeComponent(i, diagonalExtrusionLength);
		i++;
		
	}

	//assembleComponents();
	return true;

}
#endif // !BEAM_H
