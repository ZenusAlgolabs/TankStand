#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Headers.h"
#include "Common.h"
#include "Inputs.h"

Ptr<Component> rootComp;
Ptr<Occurrences> occs;
Ptr<Matrix3D> transform;

std::vector<Ptr<Occurrence>> subOccurrence;
std::vector<Ptr<Component>> subComponent;
std::vector<Ptr<Sketches>> sketches;
std::vector<Ptr<Sketch>> sketch;
std::vector<Ptr<SketchCurves>> sketchCurves;
std::vector<Ptr<Profiles>> profiles;
std::vector<Ptr<Profile>> profile;
std::vector<Ptr<Features>> features;
std::vector<Ptr<ExtrudeFeatures>> extrudeFeatures;
std::vector<Ptr<ExtrudeFeatureInput>> extrudeFeatureInput;
std::vector<Ptr<ValueInput>> extrusionDistance;
std::vector<Ptr<ExtrudeFeature>> extrudeFeature;

Ptr<Point3D> centerPoint;

//Draw a rectangular beam 

bool drawRectangleBeam(int ID)
{
	//Construction plane
	Ptr<ConstructionPlane> xzPlane = rootComp->xZConstructionPlane();
	if (!xzPlane)
		return false;

	sketch.push_back(sketches[ID]->add(xzPlane));
	if (!sketch[ID])
		return false;

	// Draw two connected lines. 
	sketchCurves.push_back(sketch[ID]->sketchCurves());
	if (!sketchCurves[ID])
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves[ID]->sketchLines();
	if (!sketchLines)
		return false;

	// Draw outer rectangle by two points. 
	Ptr<SketchLineList> outerRectangle = sketchLines->addTwoPointRectangle(Point3D::create((1), (1), 0), Point3D::create((4), (5), 0));
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
	Ptr<SketchLineList> innerRectangle = sketchLines->addTwoPointRectangle(Point3D::create(2, 2, 0), Point3D::create(3, 4, 0));
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

	// Draw two connected lines.

}

bool drawLBeam(int ID)
{
	//Construction plane
	Ptr<ConstructionPlane> xzPlane = rootComp->xZConstructionPlane();
	if (!xzPlane)
		return false;

	sketch.push_back(sketches[ID]->add(xzPlane));
	if (!sketch[ID])
		return false;

	// Draw two connected lines. 
	sketchCurves.push_back(sketch[ID]->sketchCurves());
	if (!sketchCurves[ID])
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves[ID]->sketchLines();
	if (!sketchLines)
		return false;
	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create((2 + ID), (1 + ID), 0), Point3D::create((2 + ID), (6 + ID), 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create((6 + ID),( 6 + ID), 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create((6 + ID), (4 + ID), 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create((4 + ID), (4 + ID), 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create((4 + ID), (1 + ID), 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;
}

bool drawVBeam(int ID)
{
	//Construction plane
	Ptr<ConstructionPlane> xzPlane = rootComp->xZConstructionPlane();
	if (!xzPlane)
		return false;

	sketch.push_back(sketches[ID]->add(xzPlane));
	if (!sketch[ID])
		return false;

	// Draw two connected lines. 
	sketchCurves.push_back(sketch[ID]->sketchCurves());
	if (!sketchCurves[ID])
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves[ID]->sketchLines();
	if (!sketchLines)
		return false;

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(2+ID, 1 + ID, 0), Point3D::create(1 + ID, 2 + ID, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(4 + ID, 5 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(6 + ID, 2 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(5 + ID, 1 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(4 + ID, 4 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;
}

bool drawUBeam(int ID)
{
	//Construction plane
	Ptr<ConstructionPlane> xzPlane = rootComp->xZConstructionPlane();
	if (!xzPlane)
		return false;

	sketch.push_back(sketches[ID]->add(xzPlane));
	if (!sketch[ID])
		return false;

	// Draw two connected lines. 
	sketchCurves.push_back(sketch[ID]->sketchCurves());
	if (!sketchCurves[ID])
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves[ID]->sketchLines();
	if (!sketchLines)
		return false;

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(1 + ID, 2 + ID, 0), Point3D::create(1 + ID, 8 + ID, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(5 + ID, 8 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(5 + ID, 2 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(4 + ID, 2 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(4 + ID, 7 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(2 + ID, 7 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(2 + ID, 2 + ID, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;
}

bool drawComponent1(int ID)
{
	//Construction plane
	Ptr<ConstructionPlane> xzPlane = rootComp->xZConstructionPlane();
	if (!xzPlane)
		return false;

	sketch.push_back(sketches[ID]->add(xzPlane));
	if (!sketch[ID])
		return false;

	//The Sketch
	sketchCurves.push_back(sketch[ID]->sketchCurves());
	if (!sketchCurves[ID])
		return false;
	Ptr<SketchCircles> sketchCircles0 = sketchCurves[ID]->sketchCircles();
	if (!sketchCircles0)
		return false;
	centerPoint = Point3D::create(ID, 0, 0);
	if (!centerPoint)
		return false;
	Ptr<SketchCircle> sketchCircle0 = sketchCircles0->addByCenterRadius(centerPoint, (2.5 + ID));
	if (!sketchCircle0)
		return false;
}

bool drawComponent2(int ID, Ptr<BRepFace> endFace)
{
	// Create a construction plane for extrude 2
	Ptr<ConstructionPlanes> ctorPlanes = subComponent[0]->constructionPlanes();
	if (!ctorPlanes)
		return false;
	Ptr<ConstructionPlaneInput> ctorPlaneInput = ctorPlanes->createInput();
	if (!ctorPlaneInput)
		return false;
	ctorPlaneInput->setByOffset(endFace, adsk::core::ValueInput::createByString("0 mm"));
	Ptr<ConstructionPlane> ctorPlane = ctorPlanes->add(ctorPlaneInput);
	if (!ctorPlane)
		return false;
	Ptr<ConstructionPlane> ctorPlaneProxy = ctorPlane->createForAssemblyContext(subOccurrence[0]);
	if (!ctorPlaneProxy)
		return false;

	// Create sub component 2 under root component
	subOccurrence.push_back(occs->addNewComponent(transform));
	if (!subOccurrence[1])
		return false;

	// Create sketch 2 in sub component 2
	Ptr<Component> subComp1 = subOccurrence[1]->component();
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
}

bool extrudeComponent(int ID)
{
	// Get the profile defined by the circle
	profiles.push_back(sketch[ID]->profiles());
	if (!profiles[ID])
		return false;

	profile.push_back(profiles[ID]->item(ID));
	if (!profile[ID])
		return false;

	// Create an extrude input
	features.push_back(subComponent[ID]->features());
	if (!features[ID])
		return false;

	extrudeFeatures.push_back(features[ID]->extrudeFeatures());
	if (!extrudeFeatures[ID])
		return false;

	extrudeFeatureInput.push_back(extrudeFeatures[ID]->createInput(profile[ID], FeatureOperations::NewBodyFeatureOperation));
	if (!extrudeFeatureInput[ID])
		return false;

	// Set the extrude input
	extrusionDistance.push_back(ValueInput::createByString("5 mm"));
	if (!extrusionDistance[ID])
		return false;

	extrudeFeatureInput[ID]->setDistanceExtent(false, extrusionDistance[ID]);
	extrudeFeatureInput[ID]->isSolid(true);

	// Create the extrude
	extrudeFeature.push_back(extrudeFeatures[ID]->add(extrudeFeatureInput[ID]));
	if (!extrudeFeature[ID])
		return false;

}

bool drawComponents(int ID, std::string Type)
{
	// Create sub component 1 under root component
	subOccurrence.push_back(occs->addNewComponent(transform));
	if (!subOccurrence[ID])
		return false;

	// Create sketch 1 in sub component 1
	subComponent.push_back(subOccurrence[ID]->component());
	if (!subComponent[ID])
		return false;

	sketches.push_back(subComponent[ID]->sketches());
	if (!sketches[ID])
		return false;

	if (Type == "R-Beam")
	{
		drawRectangleBeam(ID);
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
	extrudeComponent(ID);
}

bool assembleComponents()
{
	// Create the AsBuiltJoint
	Ptr<AsBuiltJoints> asBuiltJoints_ = rootComp->asBuiltJoints();
	if (!asBuiltJoints_)
		return false;
	Ptr<AsBuiltJointInput> asBuiltJointInput = asBuiltJoints_->createInput(subOccurrence[0], subOccurrence[1], nullptr);
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


	for (int i = 0; i < 4; i++)
	{
		if (i >= 0 && i < 4)
		{
			//Draw Rectangular support beams
			drawComponents(i,"R-Beam");
		}
		else if (i >= 5 && i < 10)
		{
			//Draw U-beams
			drawComponents(i, "U-Beam");
		}
		else if (i >= 10 && i < 14)
		{
			//Draw V-beams
			drawComponents(i, "V-Beam");
		}
		else if (i >= 14 && i < 20)
		{
			//Draw L-beams
			drawComponents(i, "L-Beam");
		}
	}

	// Get the end face of the created extrude
	Ptr<BRepFaces> endFaces = extrudeFeature[0]->endFaces();
	if (!endFaces)
		return false;
	Ptr<BRepFace> endFace = endFaces->item(0);
	if (!endFace)
		return false;

	//drawComponent2(0, endFace);

	//assembleComponents();
}

#endif // !BEAM_H
