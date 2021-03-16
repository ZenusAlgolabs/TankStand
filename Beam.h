#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Headers.h"
#include "Common.h"
#include "Inputs.h"

bool extrudeComponent(int ID, double _extrusionLength)
{
	// Get the profile defined by the circle
	Ptr<Profiles> profiles = (sketch[ID]->profiles());
	if (!profiles)
	{
		displayErrorMessage("profiles");
		return false;
	}

	Ptr<Profile> profile = (profiles->item(0));
	if (!profile)
	{
		displayErrorMessage(std::to_string(ID) + " profile");
		return false;
	}

	// Create an extrude input
	Ptr<Features> features = (subComponent[ID]->features());
	if (!features)
	{
		displayErrorMessage("features");
		return false;
	}

	Ptr<ExtrudeFeatures> extrudeFeatures = (features->extrudeFeatures());
	if (!extrudeFeatures)
	{
		displayErrorMessage("extrude features");
		return false;
	}

	Ptr<ExtrudeFeatureInput> extrudeFeatureInput = (extrudeFeatures->createInput(profile, FeatureOperations::NewBodyFeatureOperation));
	if (!extrudeFeatureInput)
	{
		displayErrorMessage(std::to_string(ID) + "ex-features input");
		return false;
	}

	// Set the extrude input
	Ptr<ValueInput> extrusionDistance = (ValueInput::createByString(std::to_string(_extrusionLength) + " mm"));
	if (!extrusionDistance)
	{
		displayErrorMessage("ex-distance");
		return false;
	}

	extrudeFeatureInput->setDistanceExtent(false, extrusionDistance);
	extrudeFeatureInput->isSolid(true);

	// Create the extrude
	extrudeFeature.push_back(extrudeFeatures->add(extrudeFeatureInput));
	if (!extrudeFeature[ID])
	{
		displayErrorMessage("feature");
		return false;
	}

}

bool drawRBeam(int ID)
{
	getConstructionPlane(ID);
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

bool drawUBeam(int ID)
{
	getConstructionPlane(ID);
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

bool drawVBeam(int ID)
{
	getConstructionPlane(ID);
	getSubOccurrence(ID);

	// Draw two connected lines. 
	Ptr<SketchCurves> sketchCurves=(sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;


	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(17, 8, 0), Point3D::create(16, 7, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(19, 4, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(22, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(21, 8, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(19, 6, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;
}

bool drawLBeam(int ID)
{
	getConstructionPlane(ID);
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

bool drawComponents(int ID, std::string Type, double _extrusionLength)
{

	if (Type == "R-Beam")
	{
		drawRBeam(ID);
	}
	else if (Type == "U-Beam")
	{
		drawUBeam(ID);
	}
	else if (Type == "V-Beam")
	{
		drawVBeam(ID);
	}
	else if (Type == "L-Beam")
	{
		drawLBeam(ID);
	}

	extrudeComponent(ID, _extrusionLength);

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


	for (int i = 0; i < 40; i++)
	{
		if (i >= 0 && i < 10)
		{
			//Draw Rectangular support beams
			drawComponents(i, "R-Beam", 100);
		}
		else if (i >= 1 && i < 20)
		{
			//Draw U-beams
			drawComponents(i, "U-Beam", 40);
		}
		else if (i >= 2 && i < 30)
		{
			//Draw V-beams
			drawComponents(i, "V-Beam", 30);
		}
		else if (i >= 3 && i < 40)
		{
			//Draw L-beams
			drawComponents(i, "L-Beam", 60);
		}
	}

	//assembleComponents();
}

#endif // !BEAM_H
