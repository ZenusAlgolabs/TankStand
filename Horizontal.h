#pragma once
#ifndef HORIZONTAL_H
#define HORIZONTAL_H

#include "Headers.h"
#include "Common.h"

// X Y axis
bool drawLeft(int ID, int refID, int offSet, double width, double thickness,double head,int location)
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

	double x_1, y_1, z_1,
		x_2, y_2, z_2,
		x_3, y_3, z_3,
		x_4, y_4, z_4,
		x_5, y_5, z_5,
		x_6, y_6, z_6;

	head = head / 10;
	double deviation = (head / HorizontalSupport);

	x_1 = 0; y_1 = deviation * location;
	x_2 = x_1; y_2 = y_1 + width;
	x_3 = x_2 + thickness; y_3 = y_2;
	x_4 = x_3; y_4 = y_1 + thickness;
	x_5 = x_1 + width; y_5 = y_4;
	x_6 = x_5; y_6 = y_1;

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
}

// X Y axis
bool drawRight(int ID, int refID, int offSet, double width, double thickness, double head, int location)
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

	double x_1, y_1, z_1,
		x_2, y_2, z_2,
		x_3, y_3, z_3,
		x_4, y_4, z_4,
		x_5, y_5, z_5,
		x_6, y_6, z_6;

	head = head / 10;
	double deviation = (head / HorizontalSupport);

	x_1 = tankDiameter + beamSize; y_1 = deviation * location;
	x_2 = x_1; y_2 = y_1 + thickness;
	x_3 = x_2 + (width-thickness); y_3 = y_2;
	x_4 = x_3; y_4 = y_1 + width;
	x_5 = x_1 + width; y_5 = y_4;
	x_6 = x_5; y_6 = y_1;

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
}

bool drawUp(int ID, int refID, int offSet, double width, double thickness, double head, int location)
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

	double x_1, y_1, z_1,
		x_2, y_2, z_2,
		x_3, y_3, z_3,
		x_4, y_4, z_4,
		x_5, y_5, z_5,
		x_6, y_6, z_6;
	width = 4;
	thickness = 1;

	head = head / 10;
	double deviation = (head / HorizontalSupport);

	z_1 = 0; y_1 = deviation * location;
	z_2 = z_1; y_2 = y_1 + width;
	z_3 = z_2 + thickness; y_3 = y_2;
	z_4 = z_3; y_4 = y_1 + thickness;
	z_5 = z_1 + width; y_5 = y_4;
	z_6 = z_5; y_6 = y_1;

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
}

bool drawDown(int ID, int refID, int offSet, double width, double thickness, double head, int location)
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

	double x_1, y_1, z_1,
		x_2, y_2, z_2,
		x_3, y_3, z_3,
		x_4, y_4, z_4,
		x_5, y_5, z_5,
		x_6, y_6, z_6;
	width = 4;
	thickness = 1;

	head = head / 10;
	double deviation = (head / HorizontalSupport);

	z_1 = tankDiameter + beamSize; y_1 = deviation * location;
	z_2 = z_1; y_2 = y_1 + thickness;
	z_3 = z_2 + (width - thickness); y_3 = y_2;
	z_4 = z_3; y_4 = y_1 + width;
	z_5 = z_1 + width; y_5 = y_4;
	z_6 = z_5; y_6 = y_1;

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
}

#endif // ! HORIZONTAL_H
