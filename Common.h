#pragma once
#ifndef COMMON_H
#define COMMON_H
#define _USE_MATH_DEFINES

#include <Core/CoreAll.h>
#include <Fusion/FusionAll.h>
#include <sstream>
#include <math.h>
#include <memory>
#include <vector>
#include <string>
#include <windows.h>

using namespace adsk::core;
using namespace adsk::fusion;

// Globals
Ptr<Application> app;
Ptr<UserInterface> ui;
std::string units = "m";

// Global command input declarations.
Ptr<DropDownCommandInput> _waterQuality;
Ptr<DropDownCommandInput> _structureMaterial;
Ptr<ValueCommandInput> _tankCapacity;
Ptr<ValueCommandInput> _tankHead;

Ptr<TextBoxCommandInput> _errMessage;
Ptr<ImageCommandInput> _imgInput;

Ptr<Component> rootComp;
Ptr<Occurrences> occs;
Ptr<Matrix3D> transform;

std::vector<Ptr<Occurrence>> subOccurrence;
std::vector<Ptr<Component>> subComponent;
std::vector<Ptr<Sketches>> sketches;
std::vector<Ptr<Sketch>> sketch;
std::vector<Ptr<ExtrudeFeature>> extrudeFeature;

Ptr<Point3D> centerPoint;
Ptr<BRepFaces> endFaces;
Ptr<BRepFace> endFace;
Ptr<ConstructionPlane> constructionPlane;

double tankDiameter = 100;
double beamSize = 4;
int SupportUBeams = 4;
int BaseUBeams = 8;
int HorizontalSupport = 4;

int DiagonalSupport = 4;
double diagonalExtrusionLength = 0;
double diagonalSlant_a = 0;
double diagonalSlant_b = 0;
double diagonalSlant = 0;

bool checkReturn(Ptr<Base> returnObj)
{
    if (returnObj)
        return true;
    else
        if (app && ui)
        {
            std::string errDesc;
            app->getLastError(&errDesc);
            ui->messageBox(errDesc);
            return false;
        }
        else
            return false;
}

bool is_digits(const std::string& str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

void displayErrorMessage(std::string section)
{
    // get error message
    std::string errorMessage;
    int errorCode = app->getLastError(&errorMessage);
    if (GenericErrors::Ok != errorCode)
        ui->messageBox(section+": "+errorMessage);
}

bool getEndFace(int refID)
{
	// Get the end face of the created extrude
	endFaces = extrudeFeature[refID]->endFaces();
	if (!endFaces)
		return false;
	endFace = endFaces->item(0);
	if (!endFace)
		return false;
}

bool getConstructionPlane(int ID,int refID,int offSet)
{
	if (ID == 0)
	{
		constructionPlane = rootComp->xYConstructionPlane();
		if (!constructionPlane)
			return false;
	}
	else
	{
		Ptr<ConstructionPlanes> ctorPlanes = subComponent[refID]->constructionPlanes();
		if (!ctorPlanes)
			return false;

		Ptr<ConstructionPlaneInput> ctorPlaneInput = ctorPlanes->createInput();
		if (!ctorPlaneInput)
			return false;

		getEndFace(refID);
		//ctorPlaneInput->setByOffset(endFace, adsk::core::ValueInput::createByString(std::to_string(offSet)+" mm"));
		Ptr<ConstructionPlane> ctorPlane = ctorPlanes->add(ctorPlaneInput);
		if (!ctorPlane)
			return false;

		constructionPlane = ctorPlane->createForAssemblyContext(subOccurrence[refID]);
		if (!constructionPlane)
			return false;
	}
}

bool getSubOccurrence(int ID)
{
	subOccurrence.push_back(occs->addNewComponent(transform));
	if (!subOccurrence[ID])
		return false;

	subComponent.push_back(subOccurrence[ID]->component());
	if (!subComponent[ID])
		return false;

	sketches.push_back(subComponent[ID]->sketches());
	if (!sketches[ID])
		return false;

	sketch.push_back(sketches[ID]->add(constructionPlane));
	if (!sketch[ID])
		return false;
}

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

bool assembleComponents(int componentID_1,int componentID_2)
{
	// Create the AsBuiltJoint
	Ptr<AsBuiltJoints> asBuiltJoints_ = rootComp->asBuiltJoints();
	if (!asBuiltJoints_)
		return false;
	Ptr<AsBuiltJointInput> asBuiltJointInput = asBuiltJoints_->createInput(subOccurrence[componentID_1], subOccurrence[componentID_2], nullptr);
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

#endif // !COMMON_H
