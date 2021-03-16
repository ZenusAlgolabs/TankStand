#pragma once
#ifndef COMMON_H
#define COMMON_H

#include "Headers.h"

// Globals
Ptr<Application> app;
Ptr<UserInterface> ui;
std::string units = "mm";

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
Ptr<BRepFaces> end_Faces;
Ptr<BRepFace> endFace;
Ptr<ConstructionPlane> constructionPlane;

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

bool getEndFace()
{
	// Get the end face of the created extrude
	end_Faces = extrudeFeature[0]->endFaces();
	if (!end_Faces)
		return false;
	endFace = end_Faces->item(0);
	if (!endFace)
		return false;
}

bool getConstructionPlane(int ID)
{
	if (ID == 0)
	{
		constructionPlane = rootComp->xZConstructionPlane();
		if (!constructionPlane)
			return false;
	}
	else
	{
		Ptr<ConstructionPlanes> ctorPlanes = subComponent[0]->constructionPlanes();
		if (!ctorPlanes)
			return false;

		Ptr<ConstructionPlaneInput> ctorPlaneInput = ctorPlanes->createInput();
		if (!ctorPlaneInput)
			return false;

		getEndFace();
		ctorPlaneInput->setByOffset(endFace, adsk::core::ValueInput::createByString("0 mm"));
		Ptr<ConstructionPlane> ctorPlane = ctorPlanes->add(ctorPlaneInput);
		if (!ctorPlane)
			return false;

		constructionPlane = ctorPlane->createForAssemblyContext(subOccurrence[0]);
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

#endif // !COMMON_H
