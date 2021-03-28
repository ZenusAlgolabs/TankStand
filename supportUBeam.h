#pragma once
#ifndef supportUBeam_h
#define  supportUBeam_h
#include "Headers.h"
#include "Common.h"

double UBeamStart = 0;

bool drawSupportUBeam(int ID,int location, int refID, int offSet, double thickness, double width, double head)
{
	getConstructionPlane(ID, refID, offSet);
	getSubOccurrence(ID);

	// Draw two connected lines. 
	Ptr<SketchCurves> sketchCurves = (sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;

	double x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, x_5, y_5, x_6, y_6, x_7, y_7,x_8,y_8;

	x_1 = tankDiameter - (tankDiameter / location); y_1 = head/10;
	x_2 = x_1; y_2 = y_1 + width;
	x_3 = x_2 + width; y_3 = y_2;
	x_4 = x_3; y_4 = y_1;
	x_5 = x_4 - thickness; y_5 = y_1;
	x_6 = x_5; y_6 = y_3 - thickness;
	x_7 = x_1 + thickness; y_7 = y_6;
	x_8 = x_7; y_8 = y_1;

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(x_1, y_1, 0),
		Point3D::create(x_2, y_2, 0));
	if (!line1)
		return false;

	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(
		line1->endSketchPoint(), 
		Point3D::create(x_3, y_3, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(
		line2->endSketchPoint(), 
		Point3D::create(x_4, y_4, 0));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(
		line3->endSketchPoint(), 
		Point3D::create(x_5, y_5, 0));
	if (!line4)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(
		line4->endSketchPoint(), 
		Point3D::create(x_6, y_6, 0));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(
		line5->endSketchPoint(),
		 Point3D::create(x_7, y_7, 0));
	if (!line6)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(
		line6->endSketchPoint(),
		 Point3D::create(x_8, y_8, 0));
	if (!line7)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(
		line7->endSketchPoint(), 
		line1->startSketchPoint());
	if (!line8)
		return false;
}

#endif // !supportUBeam_h