#pragma once
#ifndef baseUBeam_h
#define baseUBeam_h
#include "Headers.h"
#include "Common.h"

bool drawBaseUBeam(int ID, int location, int refID, int offSet, double thickness, double width, double head)
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

	double z_1, y_1, z_2, y_2, z_3, y_3, z_4, y_4, z_5, y_5, z_6, y_6, z_7, y_7, z_8, y_8;

	double deviation = (tankDiameter - (2 * beamSize)) / BaseUBeams;
	z_1 = deviation * location; y_1 = head/10;
	z_2 = z_1; y_2 = y_1 + width;
	z_3 = z_2 + width; y_3 = y_2;
	z_4 = z_3; y_4 = y_1;
	z_5 = z_4 - thickness; y_5 = y_1;
	z_6 = z_5; y_6 = y_3 - thickness;
	z_7 = z_1 + thickness; y_7 = y_6;
	z_8 = z_7; y_8 = y_1;

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(0, y_1, z_1),
		Point3D::create(0, y_2, z_2));
	if (!line1)
		return false;

	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(
		line1->endSketchPoint(),
		Point3D::create(0, y_3, z_3));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(
		line2->endSketchPoint(),
		Point3D::create(0, y_4, z_4));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(
		line3->endSketchPoint(),
		Point3D::create(0, y_5, z_5));
	if (!line4)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(
		line4->endSketchPoint(),
		Point3D::create(0, y_6, z_6));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(
		line5->endSketchPoint(),
		Point3D::create(0, y_7, z_7));
	if (!line6)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(
		line6->endSketchPoint(),
		Point3D::create(0, y_8, z_8));
	if (!line7)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(
		line7->endSketchPoint(),
		line1->startSketchPoint());
	if (!line8)
		return false;
}
#endif // !baseUBeam_h