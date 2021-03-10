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

bool drawVBeam()
{
	Ptr<SketchCurves> sketchCurves = sketch->sketchCurves();
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;
	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(2, 1, 0), Point3D::create(1, 2, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(4, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(6, 2, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(5, 1, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(4, 4, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;

}

bool drawUBeam()
{
	Ptr<SketchCurves> sketchCurves = sketch->sketchCurves();
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;
	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(1, 2, 0), Point3D::create(1, 8, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(5, 8, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(5, 2, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(4, 2, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(4, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(2, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(2, 2, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line1->startSketchPoint());
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

bool assembleComponents()
{
	// Create sub component 1 under root component
	Ptr<Occurrences> occs = rootComp->occurrences();
	if (!occs)
		return false;
	Ptr<Matrix3D> transform = adsk::core::Matrix3D::create();
	if (!transform)
		return false;
	Ptr<Occurrence> subOcc0 = occs->addNewComponent(transform);
	if (!subOcc0)
		return false;

	// Create sketch 1 in sub component 1
	Ptr<Component> subComp0 = subOcc0->component();
	if (!subComp0)
		return false;
	Ptr<Sketches> sketches0 = subComp0->sketches();
	if (!sketches0)
		return false;
	Ptr<ConstructionPlane> xzPlane = rootComp->xZConstructionPlane();
	if (!xzPlane)
		return false;
	Ptr<Sketch> sketch0 = sketches0->add(xzPlane);
	if (!sketch0)
		return false;
	Ptr<SketchCurves> sketchCurves0 = sketch0->sketchCurves();
	if (!sketchCurves0)
		return false;
	Ptr<SketchCircles> sketchCircles0 = sketchCurves0->sketchCircles();
	if (!sketchCircles0)
		return false;
	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint)
		return false;
	Ptr<SketchCircle> sketchCircle0 = sketchCircles0->addByCenterRadius(centerPoint, 2.5);
	if (!sketchCircle0)
		return false;

	// Get the profile defined by the circle
	Ptr<Profiles> profs0 = sketch0->profiles();
	if (!profs0)
		return false;
	Ptr<Profile> profile0 = profs0->item(0);
	if (!profile0)
		return false;

	// Create an extrude input
	Ptr<Features> feats0 = subComp0->features();
	if (!feats0)
		return false;
	Ptr<ExtrudeFeatures> extrudes0 = feats0->extrudeFeatures();
	if (!extrudes0)
		return false;
	Ptr<ExtrudeFeatureInput> extInput0 = extrudes0->createInput(profile0, FeatureOperations::NewBodyFeatureOperation);
	if (!extInput0)
		return false;

	// Set the extrude input
	Ptr<ValueInput> distance0 = ValueInput::createByString("5 mm");
	if (!distance0)
		return false;
	extInput0->setDistanceExtent(false, distance0);
	extInput0->isSolid(true);

	// Create the extrude
	Ptr<ExtrudeFeature> ext = extrudes0->add(extInput0);
	if (!ext)
		return false;

	// Get the end face of the created extrude
	Ptr<BRepFaces> endFaces = ext->endFaces();
	if (!endFaces)
		return false;
	Ptr<BRepFace> endFace = endFaces->item(0);
	if (!endFace)
		return false;

	// Create a construction plane for extrude 2
	Ptr<ConstructionPlanes> ctorPlanes = subComp0->constructionPlanes();
	if (!ctorPlanes)
		return false;
	Ptr<ConstructionPlaneInput> ctorPlaneInput = ctorPlanes->createInput();
	if (!ctorPlaneInput)
		return false;
	ctorPlaneInput->setByOffset(endFace, adsk::core::ValueInput::createByString("20 mm"));
	Ptr<ConstructionPlane> ctorPlane = ctorPlanes->add(ctorPlaneInput);
	if (!ctorPlane)
		return false;
	Ptr<ConstructionPlane> ctorPlaneProxy = ctorPlane->createForAssemblyContext(subOcc0);
	if (!ctorPlaneProxy)
		return false;

	// Create sub component 2 under root component
	Ptr<Occurrence> subOcc1 = occs->addNewComponent(transform);
	if (!subOcc1)
		return false;

	// Create sketch 2 in sub component 2
	Ptr<Component> subComp1 = subOcc1->component();
	if (!subComp1)
		return false;
	Ptr<Sketches> sketches1 = subComp1->sketches();
	if (!sketches1)
		return false;
	Ptr<Sketch> sketch1 = sketches1->add(ctorPlaneProxy);
	if (!sketch1)
		return false;
	Ptr<SketchCurves> sketchCurves1 = sketch1->sketchCurves();
	if (!sketchCurves1)
		return false;
	Ptr<SketchCircles> sketchCircles1 = sketchCurves1->sketchCircles();
	if (!sketchCircles1)
		return false;
	Ptr<SketchCircle> sketchCircle1 = sketchCircles1->addByCenterRadius(centerPoint, 0.5);
	if (!sketchCircle1)
		return false;

	// Get the profile defined by the circle
	Ptr<Profiles> profs1 = sketch1->profiles();
	if (!profs1)
		return false;
	Ptr<Profile> profile1 = profs1->item(0);
	if (!profile1)
		return false;

	// Create an extrude input
	Ptr<Features> feats1 = subComp1->features();
	if (!feats1)
		return false;
	Ptr<ExtrudeFeatures> extrudes1 = feats1->extrudeFeatures();
	if (!extrudes1)
		return false;
	Ptr<ExtrudeFeatureInput> extInput1 = extrudes1->createInput(profile1, FeatureOperations::NewBodyFeatureOperation);
	if (!extInput1)
		return false;

	// Set the extrude input
	Ptr<ValueInput> distance1 = ValueInput::createByString("50 mm");
	if (!distance1)
		return false;
	extInput1->setDistanceExtent(false, distance1);
	extInput1->isSolid(false);

	// Create the extrude
	Ptr<ExtrudeFeature> extrude1 = extrudes1->add(extInput1);
	if (!extrude1)
		return false;

	// Create the AsBuiltJoint
	Ptr<AsBuiltJoints> asBuiltJoints_ = rootComp->asBuiltJoints();
	if (!asBuiltJoints_)
		return false;
	Ptr<AsBuiltJointInput> asBuiltJointInput = asBuiltJoints_->createInput(subOcc0, subOcc1, nullptr);
	if (!asBuiltJointInput)
		return false;
	Ptr<AsBuiltJoint> asBuiltJoint = asBuiltJoints_->add(asBuiltJointInput);
	if (!asBuiltJoint)
		return false;

	// Fit to window
	Ptr<Viewport> viewPort = app->activeViewport();
	if (!viewPort)
		return false;
	Ptr<Camera> cam = viewPort->camera();
	if (!cam)
		return false;
	cam->isFitView(true);
	viewPort->camera(cam);

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
	//drawLBeam();
	//drawVBeam();
	//drawUBeam();

	//getProfile();
	//extrudeComponent();

	assembleComponents();
}

#endif // !BEAM_H
