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
Ptr<DropDownCommandInput> _fluidType;
Ptr<ValueCommandInput> _tankCapacity;
Ptr<ValueCommandInput> _tankHead;
Ptr<ValueCommandInput> _fluidDensity;
Ptr<ValueCommandInput> _costPerMeter_Sq;
Ptr<ValueCommandInput> _costPerMeter_L;
Ptr<ValueCommandInput> _costPerMeter_U;

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

double beamSize = 4;
float SlantAngle = 0.0;
int PrincipleBeams = 4;
int uBeamsCount = 3;
int supportCount = 4;
double tankDiameter = 0.0;
double width = 4;
double thickness = 1;

double x_1, y_1, z_1,
x_2, y_2, z_2,
x_3, y_3, z_3,
x_4, y_4, z_4,
x_5, y_5, z_5,
x_6, y_6, z_6,
x_7, y_7, z_7,
x_8, y_8, z_8;

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

bool getConstructionPlane(int ID,int refID)
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

bool Sketch_LBeam(int ID, int refID)
{
	getConstructionPlane(ID, refID);
	getSubOccurrence(ID);

	// Draw two connected lines.
	Ptr<SketchCurves> sketchCurves = (sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(x_1, y_1, z_1),
		Point3D::create(x_2, y_2, z_2));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(),
		Point3D::create(x_3, y_3, z_3));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(),
		Point3D::create(x_4, y_4, z_4));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(),
		Point3D::create(x_5, y_5, z_5));
	if (!line4)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(),
		Point3D::create(x_6, y_6, z_6));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(),
		line1->startSketchPoint());
	if (!line6)
		return false;
	return true;
}

bool Sketch_UBeam(int ID, int refID)
{
	getConstructionPlane(ID, refID);
	getSubOccurrence(ID);

	// Draw two connected lines. 
	Ptr<SketchCurves> sketchCurves = (sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(x_1, y_1, z_1),
		Point3D::create(x_2, y_2, z_2));
	if (!line1)
		return false;

	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(
		line1->endSketchPoint(),
		Point3D::create(x_3, y_3, z_3));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(
		line2->endSketchPoint(),
		Point3D::create(x_4, y_4, z_4));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(
		line3->endSketchPoint(),
		Point3D::create(x_5, y_5, z_5));
	if (!line4)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(
		line4->endSketchPoint(),
		Point3D::create(x_6, y_6, z_6));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(
		line5->endSketchPoint(),
		Point3D::create(x_7, y_7, z_7));
	if (!line6)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(
		line6->endSketchPoint(),
		Point3D::create(x_8, y_8, z_8));
	if (!line7)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(
		line7->endSketchPoint(),
		line1->startSketchPoint());
	if (!line8)
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

#endif // !COMMON_H
