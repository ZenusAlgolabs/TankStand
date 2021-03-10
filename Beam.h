#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Headers.h"
#include "Common.h"
#include "Inputs.h"

Ptr<Features> feats;
Ptr<Component> rootComp;
Ptr<BaseFeature> baseFeat;
Ptr<Sketch> sketch;
Ptr<Profile> prof;

	// Create construction plane in base feature
bool createConstructionPlane()
{
	Ptr<ConstructionPlanes> planes = rootComp->constructionPlanes();
	if (!planes)
		return false;
	Ptr<ConstructionPlaneInput> planeInput = planes->createInput();
	if (!planeInput)
		return false;
	planeInput->targetBaseOrFormFeature(baseFeat);
	planeInput->setByOffset(rootComp->xYConstructionPlane(), ValueInput::createByReal(1));
	Ptr<ConstructionPlane> plane = planes->add(planeInput);
	if (!plane)
		return false;
}

// Create sketch in base feature
bool createSketch()
{
	Ptr<Sketches> sketches = rootComp->sketches();
	if (!sketches)
		return false;
	Ptr<ConstructionPlane> xyPlane = rootComp->xYConstructionPlane();
	if (!xyPlane)
		return false;
	sketch = sketches->addToBaseOrFormFeature(xyPlane, baseFeat, true);
	if (!sketch)
		return false;
}

	//Draw a rectangular beam
bool drawRectangleBeam()
{
	// Draw two connected lines.
	Ptr<SketchCurves> sketchCurves = sketch->sketchCurves();
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;

	// Draw outer rectangle by two points.
	Ptr<SketchLineList> outerRectangle = sketchLines->addTwoPointRectangle(Point3D::create(1, 1, 0), Point3D::create(4, 5, 0));
	if (!outerRectangle)
		return false;

	// Use the returned lines to add some constraints.
	Ptr<GeometricConstraints> outerRectangle_constraints = sketch->geometricConstraints();
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

	Ptr<SketchDimensions> outerRectangle_sketchDimensions = sketch->sketchDimensions();
	if (!outerRectangle_sketchDimensions)
		return false;
	Ptr<SketchDimension> outerRectangle_sketchDimension = outerRectangle_sketchDimensions->addDistanceDimension(outerRectangle->item(0)->startSketchPoint(), outerRectangle->item(0)->endSketchPoint(), HorizontalDimensionOrientation, Point3D::create(5.5, -1, 0));
	if (!outerRectangle_sketchDimension)
		return false;

	// Draw inner rectangle by two points.
	Ptr<SketchLineList> innerRectangle = sketchLines->addTwoPointRectangle(Point3D::create(2, 2, 0), Point3D::create(3, 4, 0));
	if (!innerRectangle)
		return false;

	// Use the returned lines to add some constraints.
	Ptr<GeometricConstraints> innerRectangle_constraints = sketch->geometricConstraints();
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

	Ptr<SketchDimensions> innerRectangle_sketchDimensions = sketch->sketchDimensions();
	if (!innerRectangle_sketchDimensions)
		return false;
	Ptr<SketchDimension> innerRectangle_sketchDimension = innerRectangle_sketchDimensions->addDistanceDimension(innerRectangle->item(0)->startSketchPoint(), innerRectangle->item(0)->endSketchPoint(), HorizontalDimensionOrientation, Point3D::create(5.5, -1, 0));
	if (!innerRectangle_sketchDimension)
		return false;

// Draw two connected lines.
}

bool drawLBeam()
{
	Ptr<SketchCurves> sketchCurves = sketch->sketchCurves();
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;
	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(2, 1, 0), Point3D::create(2, 6, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(6, 6, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(6, 4, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(4, 4, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(4, 1, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;

}

	// Get the profile defined by the sketch.
bool getProfile()
{
	Ptr<Profiles> profs = sketch->profiles();
	if (!profs)
		return false;
	prof = profs->item(0);
	if (!prof)
		return false;
}

// Create an extrusion input to be able to define the input needed for an extrusion
// while specifying the profile and that a new component is to be created
bool extrudeComponent()
{
	Ptr<ExtrudeFeatures> extrudes = feats->extrudeFeatures();
	if (!extrudes)
		return false;
	Ptr<ExtrudeFeatureInput> extInput = extrudes->createInput(prof, FeatureOperations::NewBodyFeatureOperation);
	if (!extInput)
		return false;

	// Define that the extent is a distance extent of 5 cm.
	Ptr<ValueInput> distance = ValueInput::createByReal(5);
	if (!distance)
		return false;
	extInput->setDistanceExtent(false, distance);
	extInput->targetBaseFeature(baseFeat);

	// Create the extrusion.
	Ptr<ExtrudeFeature> ext = extrudes->add(extInput);
	if (!ext)
		return false;
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

	feats = rootComp->features();
	if (!feats)
		return false;

	// Create a base feature
	Ptr<BaseFeatures> baseFeats = feats->baseFeatures();
	if (!baseFeats)
		return false;

	baseFeat = baseFeats->add();
	if (!baseFeat)
		return false;

	baseFeat->startEdit();

	createConstructionPlane();
	createSketch();

	//drawRectangleBeam();
	drawLBeam();

	getProfile();
	extrudeComponent();
}

#endif // !BEAM_H
