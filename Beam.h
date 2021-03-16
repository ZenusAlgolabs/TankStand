#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Headers.h"
#include "Common.h"
#include "Inputs.h"

bool drawRBeam(int ID,int refID,int offSet)
{
	getConstructionPlane(ID,refID,offSet);
	getSubOccurrence(ID);

	// Draw two connected lines. 
	Ptr<SketchCurves> sketchCurves = (sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;

	// Draw outer rectangle by two points. 
	Ptr<SketchLineList> outerRectangle = sketchLines->addTwoPointRectangle(Point3D::create((7), (7), 0), Point3D::create((10), (4), 0));
	if (!outerRectangle)
		return false;

	// Use the returned lines to add some constraints. 
	Ptr<GeometricConstraints> outerRectangle_constraints = sketch[ID]->geometricConstraints();
	if (!outerRectangle_constraints)
		return false;
	Ptr<HorizontalConstraint> outerRectangle_HConstraint = outerRectangle_constraints->addHorizontal(outerRectangle->item(0));
	if (!outerRectangle_HConstraint)
		return false;
	outerRectangle_HConstraint = outerRectangle_constraints->addHorizontal(outerRectangle->item(2));
	if (!outerRectangle_HConstraint)
		return false;
	Ptr<VerticalConstraint> outerRectangle_VConstraint = outerRectangle_constraints->addVertical(outerRectangle->item(1));
	if (!outerRectangle_VConstraint)
		return false;
	outerRectangle_VConstraint = outerRectangle_constraints->addVertical(outerRectangle->item(3));
	if (!outerRectangle_VConstraint)
		return false;
	Ptr<SketchDimensions> outerRectangle_sketchDimensions = sketch[ID]->sketchDimensions();
	if (!outerRectangle_sketchDimensions)
		return false;
	Ptr<SketchDimension> outerRectangle_sketchDimension = outerRectangle_sketchDimensions->addDistanceDimension(outerRectangle->item(0)->startSketchPoint(), outerRectangle->item(0)->endSketchPoint(), HorizontalDimensionOrientation, Point3D::create(5.5, -1, 0));
	if (!outerRectangle_sketchDimension)
		return false;

	// Draw inner rectangle by two points. 
	Ptr<SketchLineList> innerRectangle = sketchLines->addTwoPointRectangle(Point3D::create(8, 6, 0), Point3D::create(9, 5, 0));
	if (!innerRectangle)
		return false;
	// Use the returned lines to add some constraints. 
	Ptr<GeometricConstraints> innerRectangle_constraints = sketch[ID]->geometricConstraints();
	if (!innerRectangle_constraints)
		return false;
	Ptr<HorizontalConstraint> innerRectangle_HConstraint = innerRectangle_constraints->addHorizontal(innerRectangle->item(0));
	if (!innerRectangle_HConstraint)
		return false;
	innerRectangle_HConstraint = innerRectangle_constraints->addHorizontal(innerRectangle->item(2));
	if (!innerRectangle_HConstraint)
		return false;
	Ptr<VerticalConstraint> innerRectangle_VConstraint = innerRectangle_constraints->addVertical(innerRectangle->item(1));
	if (!innerRectangle_VConstraint)
		return false;
	innerRectangle_VConstraint = innerRectangle_constraints->addVertical(innerRectangle->item(3));
	if (!innerRectangle_VConstraint)
		return false;
	Ptr<SketchDimensions> innerRectangle_sketchDimensions = sketch[ID]->sketchDimensions();
	if (!innerRectangle_sketchDimensions)
		return false;
	Ptr<SketchDimension> innerRectangle_sketchDimension = innerRectangle_sketchDimensions->addDistanceDimension(innerRectangle->item(0)->startSketchPoint(), innerRectangle->item(0)->endSketchPoint(), HorizontalDimensionOrientation, Point3D::create(5.5, -1, 0));
	if (!innerRectangle_sketchDimension)
		return false;
}

bool drawUBeam(int ID, int refID, int offSet)
{
	getConstructionPlane(ID,refID,offSet);
	getSubOccurrence(ID);

	// Draw two connected lines. 
	Ptr<SketchCurves> sketchCurves = (sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;


	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(11, 7, 0), Point3D::create(11, 4, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(14, 4, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(14, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(13, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(13, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(12, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(12, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;
}

bool drawLBeam(int ID,int refID, int offSet)
{
	getConstructionPlane(ID,refID, offSet);
	getSubOccurrence(ID);

	// Draw two connected lines.
	Ptr<SketchCurves> sketchCurves=(sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;


	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(2, 7, 0), Point3D::create(2, 4, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(5, 4, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(5, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(3, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(3, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(2, 7, 0));
	if (!line2)
		return false;

}

bool drawVerticalSupportBeams(int ID, double _extrusionLength)
{
	drawRBeam(ID,0,0);
	extrudeComponent(ID, _extrusionLength);
	return true;
}

bool drawHorizontalSupportBeams(double _extrusionLength)
{
	for (int i = 4; i < 8; i++)
	{
		if (i == 4)
		{
			drawRBeam(i,0,0);
		}
		else
		{
			drawRBeam(i,(i-1),0);
		}
		extrudeComponent(i, _extrusionLength);
	}
	assembleComponents(4,5);
	assembleComponents(5,6);
	assembleComponents(6,7);

	for (int i = 8; i < 12; i++)
	{
		if (i == 8)
		{
			drawRBeam(i, 0,20);
		}
		else
		{
			drawRBeam(i, (i - 1),0);
		}
		extrudeComponent(i, _extrusionLength);
	}
	assembleComponents(8,9);
	assembleComponents(9,10);
	assembleComponents(10,11);

	for (int i = 12; i < 16; i++)
	{
		if (i == 12)
		{
			drawRBeam(i, 0,40);
		}
		else
		{
			drawRBeam(i, (i - 1),0);
		}
		extrudeComponent(i, _extrusionLength);
	}
	assembleComponents(12,13);
	assembleComponents(13,14);
	assembleComponents(14,15);
	
	for (int i = 16; i < 24; i++)
	{
		if (i == 16)
		{
			drawRBeam(i, 0,60);
		}
		else
		{
			drawRBeam(i, (i - 1),0);
		}
		extrudeComponent(i, _extrusionLength);
	}
	assembleComponents(15,16);
	assembleComponents(15,17);
	assembleComponents(17,18);
	
	return true;
}

bool drawDiagonalSupportBeams(int ID, double _extrusionLength)
{
	drawLBeam(ID,0,0);
	extrudeComponent(ID, _extrusionLength);
	return true;
}

bool drawHorizontalUBeams(int ID, double _extrusionLength)
{
	drawUBeam(ID,0,0);
	extrudeComponent(ID, _extrusionLength);
	return true;
}

Ptr<Component> drawTankStand(Ptr<Design> design)
{
	Ptr<Attributes> attribs = design->attributes();
	attribs->add("TankStand", "waterQuality", _waterQuality->selectedItem()->name());
	attribs->add("TankStand", "structureMaterial", _structureMaterial->selectedItem()->name());

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

	for (int i = 0; i < 61; i++)
	{
		if (i >= 0 && i < 4)
		{
			//Draw Rectangular support beams
			drawVerticalSupportBeams(i, _tankHead);
		}
		if (i == 4)
		{
			//Draw Rectangular horizontal support beams
			drawHorizontalSupportBeams(50);
		}
		else if (i >= 24 && i < 39)
		{
			//Draw U-beams
			drawHorizontalUBeams(i, 100);
		}
		else if (i >= 39 && i < 51)
		{
			//Draw L-beams
			drawDiagonalSupportBeams(i, 100);
		}
	}

	//assembleComponents();
}

#endif // !BEAM_H
