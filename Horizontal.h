#pragma once
#ifndef HORIZONTAL_H
#define HORIZONTAL_H

#include "Headers.h"
#include "Common.h"

std::vector<double>horizontalPosition;

bool drawLeft(int ID, int refID, int offSet, double width, double thickness)
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

	double x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0, x_4 = 0, y_4 = 0, x_5 = 0, y_5 = 0, x_6 = 0, y_6 = 0;

	x_1 = 0; y_1 = 0;
	x_2 = x_1; y_2 = y_1 + width;
	x_3 = x_2 + thickness; y_3 = y_2;
	x_4 = x_3; y_4 = y_1 + thickness;
	x_5 = x_1 + width; y_5 = y_4;
	x_6 = x_5; y_6 = y_1;

	horizontalPosition.push_back(x_1);
	horizontalPosition.push_back(y_1);
	horizontalPosition.push_back(x_2);
	horizontalPosition.push_back(y_2);
	horizontalPosition.push_back(x_3);
	horizontalPosition.push_back(y_3);
	horizontalPosition.push_back(x_4);
	horizontalPosition.push_back(y_4);
	horizontalPosition.push_back(x_5);
	horizontalPosition.push_back(y_5);
	horizontalPosition.push_back(x_6);
	horizontalPosition.push_back(y_6);

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(horizontalPosition[1], horizontalPosition[0], 0),
		Point3D::create(horizontalPosition[3], horizontalPosition[2], 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(),
		Point3D::create(horizontalPosition[5], horizontalPosition[4], 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(),
		Point3D::create(horizontalPosition[7], horizontalPosition[6], 0));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(),
		Point3D::create(horizontalPosition[9], horizontalPosition[8], 0));
	if (!line4)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(),
		Point3D::create(horizontalPosition[11], horizontalPosition[10], 0));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(),
		line1->startSketchPoint());
	if (!line2)
		return false;
}

bool drawRight(int ID, int refID, int offSet, double width, double thickness)
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

	double x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0, x_4 = 0, y_4 = 0, x_5 = 0, y_5 = 0, x_6 = 0, y_6 = 0;
	width = 4;
	thickness = 1;

	x_1 = 0; y_1 = 0;
	x_2 = x_1; y_2 = y_1 + thickness;
	x_3 = x_2 + width - thickness; y_3 = y_2;
	x_4 = x_3; y_4 = y_1 + width;
	x_5 = x_1 + width; y_5 = y_4;
	x_6 = x_5; y_6 = y_1;

	horizontalPosition.push_back(x_1);
	horizontalPosition.push_back(y_1);
	horizontalPosition.push_back(x_2);
	horizontalPosition.push_back(y_2);
	horizontalPosition.push_back(x_3);
	horizontalPosition.push_back(y_3);
	horizontalPosition.push_back(x_4);
	horizontalPosition.push_back(y_4);
	horizontalPosition.push_back(x_5);
	horizontalPosition.push_back(y_5);
	horizontalPosition.push_back(x_6);
	horizontalPosition.push_back(y_6);

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(horizontalPosition[1], horizontalPosition[0], 0),
		Point3D::create(horizontalPosition[3], horizontalPosition[2], 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(),
		Point3D::create(horizontalPosition[5], horizontalPosition[4], 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(),
		Point3D::create(horizontalPosition[7], horizontalPosition[6], 0));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(),
		Point3D::create(horizontalPosition[9], horizontalPosition[8], 0));
	if (!line4)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(),
		Point3D::create(horizontalPosition[11], horizontalPosition[10], 0));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(),
		line1->startSketchPoint());
	if (!line2)
		return false;

}

bool drawUp(int ID, int refID, int offSet, double width, double thickness)
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

	double z_1 = 0, y_1 = 0, z_2 = 0, y_2 = 0, z_3 = 0, y_3 = 0, z_4 = 0, y_4 = 0, z_5 = 0, y_5 = 0, z_6 = 0, y_6 = 0;
	width = 4;
	thickness = 1;

	z_1 = 0; y_1 = 0;
	z_2 = z_1; y_2 = y_1 + width;
	z_3 = z_2 + thickness; y_3 = y_2;
	z_4 = z_3; y_4 = y_1 + thickness;
	z_5 = z_1 + width; y_5 = y_4;
	z_6 = z_5; y_6 = y_1;

	horizontalPosition.push_back(z_1);
	horizontalPosition.push_back(y_1);
	horizontalPosition.push_back(z_2);
	horizontalPosition.push_back(y_2);
	horizontalPosition.push_back(z_3);
	horizontalPosition.push_back(y_3);
	horizontalPosition.push_back(z_4);
	horizontalPosition.push_back(y_4);
	horizontalPosition.push_back(z_5);
	horizontalPosition.push_back(y_5);
	horizontalPosition.push_back(z_6);
	horizontalPosition.push_back(y_6);

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(0, horizontalPosition[0], horizontalPosition[1]),
		Point3D::create(0, horizontalPosition[2], horizontalPosition[3]));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(),
		Point3D::create(0, horizontalPosition[4], horizontalPosition[5]));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(),
		Point3D::create(0, horizontalPosition[6], horizontalPosition[7]));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(),
		Point3D::create(0, horizontalPosition[8], horizontalPosition[9]));
	if (!line4)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(),
		Point3D::create(0, horizontalPosition[10], horizontalPosition[11]));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(),
		line1->startSketchPoint());
	if (!line2)
		return false;
}

bool drawDown(int ID, int refID, int offSet, double width, double thickness)
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

	double z_1 = 0, y_1 = 0, z_2 = 0, y_2 = 0, z_3 = 0, y_3 = 0, z_4 = 0, y_4 = 0, z_5 = 0, y_5 = 0, z_6 = 0, y_6 = 0;
	width = 4;
	thickness = 1;

	z_1 = 0; y_1 = 0;
	z_2 = z_1; y_2 = y_1 + thickness;
	z_3 = z_2 + width - thickness; y_3 = y_2;
	z_4 = z_3; y_4 = y_1 + width;
	z_5 = z_1 + width; y_5 = y_4;
	z_6 = z_5; y_6 = y_1;

	horizontalPosition.push_back(z_1);
	horizontalPosition.push_back(y_1);
	horizontalPosition.push_back(z_2);
	horizontalPosition.push_back(y_2);
	horizontalPosition.push_back(z_3);
	horizontalPosition.push_back(y_3);
	horizontalPosition.push_back(z_4);
	horizontalPosition.push_back(y_4);
	horizontalPosition.push_back(z_5);
	horizontalPosition.push_back(y_5);
	horizontalPosition.push_back(z_6);
	horizontalPosition.push_back(y_6);

	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(0, horizontalPosition[0], horizontalPosition[1]),
		Point3D::create(0, horizontalPosition[2], horizontalPosition[3]));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(),
		Point3D::create(0, horizontalPosition[4], horizontalPosition[5]));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(),
		Point3D::create(0, horizontalPosition[6], horizontalPosition[7]));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(),
		Point3D::create(0, horizontalPosition[8], horizontalPosition[9]));
	if (!line4)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(),
		Point3D::create(0, horizontalPosition[10], horizontalPosition[11]));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(),
		line1->startSketchPoint());
	if (!line2)
		return false;
}

bool drawHorizontalLBeam(int ID, int refID, int offSet)
{
	double width = 4;
	double thickness = 1;
	if (ID >= 4 && ID < 6)
	{
		drawLeft(ID, 0, 0, width, thickness);
	}
	else if (ID >= 6 && ID < 8)
	{
		drawRight(ID, 0, 0, width, thickness);
	}
	else if (ID >= 8 && ID < 10)
	{
		drawUp(ID, 0, 0, width, thickness);
	}
	else if (ID >= 10 && ID < 12)
	{
		drawDown(ID, 0, 0, width, thickness);
	}
	return true;
}

#endif // ! HORIZONTAL_H
