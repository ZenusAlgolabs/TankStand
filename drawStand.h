#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Headers.h"
#include "Common.h"
#include "Inputs.h"
#include "LBeam.h"
#include "RBeam.h"
#include "UBeam.h"

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

	for (int i = 0; i < 30; i++)
	{
		if (i >= 0 && i < 4)
		{
			//Draw Rectangular support beams
			drawVerticalSupportBeams(i, tankHead);
		}
		else if (i >= 4 && i < 12)
		{
			//Draw L-Shape horizontal support beams
			drawHorizontalSupportBeams(i, tankDiameter);
		}
		else if (i >= 12 && i < 20)
		{
			//Draw U-beams
			drawHorizontalUBeams(i, tankDiameter * 2, tankHead);
		}
		else if (i >= 20 && i < 30)
		{
			//Draw L-beams
			drawDiagonalSupportBeams(i, 100);
		}
	}

	//assembleComponents();
	return true;
}

#endif // !BEAM_H
