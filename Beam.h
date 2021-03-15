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

bool drawComponents()
{
	// Create sub component 1 under root component
	subOccurrence.push_back(occs->addNewComponent(transform));
	if (!subOccurrence[0])
		return false;

	// Create sketch 1 in sub component 1
	subComponent.push_back(subOccurrence[0]->component());
	if (!subComponent[0])
		return false;

	sketches.push_back(subComponent[0]->sketches());
	if (!sketches[0])
		return false;


	drawComponent1(0);
	// Get the end face of the created extrude
	Ptr<BRepFaces> endFaces = extrudeFeature[0]->endFaces();
	if (!endFaces)
		return false;
	Ptr<BRepFace> endFace = endFaces->item(0);
	if (!endFace)
		return false;
	drawComponent2(0, endFace);


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

	drawComponents();

	//assembleComponents();
}

#endif // !BEAM_H
