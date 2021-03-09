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

bool drawComponent()
{
	// Draw a circle.
	/*Ptr<SketchCurves> sketchCurves = sketch->sketchCurves();
	if (!sketchCurves)
		return false;
	Ptr<SketchCircles> circles = sketchCurves->sketchCircles();
	if (!circles)
		return false;
	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint)
		return false;
	Ptr<SketchCircle> circle1 = circles->addByCenterRadius(centerPoint, 2);
	if (!circle1)
		return false;*/

	//Draw a rectangle
			// Draw two connected lines.
	Ptr<SketchCurves> sketchCurves = sketch->sketchCurves();
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;
	// Draw a rectangle by two points.
	Ptr<SketchLineList> innerRectangle = sketchLines->addTwoPointRectangle(Point3D::create(3, 0, 0), Point3D::create(7, 2, 0));
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

	drawComponent();

	getProfile();
	extrudeComponent();
}

#endif // !BEAM_H
