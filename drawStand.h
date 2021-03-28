#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Headers.h"
#include "Common.h"
#include "Inputs.h"
#include "RBeam.h"
#include "supportUBeam.h"
#include "baseUBeam.h"
#include "Horizontal.h"
#include "Diagonal.h"

bool drawTankStand(Ptr<Design> design, double tankHead, double tankCapacity)
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

	calculatePriciplePositions();

	int i = 0;
/*
	//+-----------------------------------------------+
	// Draw 4 Principle support beams                 |
	//+-----------------------------------------------+
	for (int a = 0; a < 4; a++)
	{
		drawRBeam(i, 0, 0, 1);
		extrudeComponent(i, tankHead);
		i++;
	}

	//+-----------------------------------------------+
	//Draw Tank platform beams                        |
	//1. Connecting beams                             |
	//+-----------------------------------------------+
	for (int c = 0; c < 4; c++)
	{
		drawSupportUBeam(i, (c + 1), 0, 0, 1, 4, tankHead);
		extrudeComponent(i, (tankDiameter * 10) + (80));
		i++;
	}

	//+-----------------------------------------------+
	//2. Base beams                                   |
	//+-----------------------------------------------+
	for (int d = 0; d < 8; d++)
	{
		drawBaseUBeam(i, (d + 1), 0, 0, 1, 4, tankHead);
		extrudeComponent(i, (tankDiameter * 10) + (80));
		i++;
	}
	
	//+-----------------------------------------------+
	// Draw structure support beams                   |
	//+-----------------------------------------------+
	for (int b = 0; b < 4; b++)
	{
		double width = 4;
		double thickness = 1;

		b++;

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
*/	
	//+-----------------------------------------------+
	// Draw Diagonal support beams                    |
	//+-----------------------------------------------+
	for (int e = 0; e < 10; e++)
	{
		double width = 4;
		double thickness = 1;

		e++;

		drawLeftDiagonal(i, 0, 0, width, thickness, tankHead, e);
		extrudeComponent(i, tankDiameter);// *10 + 80);
		i++;

		/*drawRightDiagonal(i, 0, 0, width, thickness, tankHead, e);
		extrudeComponent(i, tankDiameter * 10 + 80);
		i++;

		drawUpDiagonal(i, 0, 0, width, thickness, tankHead, e);
		extrudeComponent(i, tankDiameter * 10 + 80);
		i++;

		drawDownDiagonal(i, 0, 0, width, thickness, tankHead, e);
		extrudeComponent(i, tankDiameter * 10 + 80);
		i++;*/
	}

	//assembleComponents();
	return true;

}
#endif // !BEAM_H
