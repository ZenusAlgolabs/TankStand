#pragma once
#ifndef UBeam_h
#define  UBeam_h
#include "Headers.h"
#include "Common.h"

std::vector<double>UBeam_Location;
int UBeamLastLocation = 0;
double UBeamStartPoint = 0;

bool calculateUPosition(int ID, double thickness, double height, double width,double head)
{
	double startPoint_x = UBeamLastLocation;
	double startPoint_z = head / 10;
	double point1_x, point1_z, point2_x, point2_z, point3_x, point3_z, point4_x, point4_z, point5_x, point5_z, point6_x, point6_z, point7_x, point7_z;

	if (ID == 12 || ID == 13)
	{
		if (ID == 12)
		{
			startPoint_x = (tankDiameter / 3);
		}
		if (ID == 13)
		{
			startPoint_x = tankDiameter - (tankDiameter / 3);
		}
		point1_x = startPoint_x;
		point1_z = startPoint_z + height;

		point2_x = point1_x + width;
		point2_z = point1_z;

		point3_x = point2_x;
		//UBeamLastLocation = point3_x + 10;
		point3_z = startPoint_z;

		point4_x = point3_x - thickness;
		point4_z = startPoint_z;

		point5_x = point4_x;
		point5_z = point2_z - thickness;

		point6_x = startPoint_x + thickness;
		point6_z = point5_z;

		point7_x = point6_x;
		point7_z = startPoint_z;
	}
	else
	{
		point1_x = startPoint_x;
		point1_z = startPoint_z + height;

		point2_x = point1_x + width;
		point2_z = point1_z;

		point3_x = point2_x;
		UBeamLastLocation = point3_x + 10;
		point3_z = startPoint_z;

		point4_x = point3_x - thickness;
		point4_z = startPoint_z;

		point5_x = point4_x;
		point5_z = point2_z - thickness;

		point6_x = startPoint_x + thickness;
		point6_z = point5_z;

		point7_x = point6_x;
		point7_z = startPoint_z;
	}

	UBeam_Location.push_back(startPoint_x);
	UBeam_Location.push_back(startPoint_z);
	UBeam_Location.push_back(point1_x);
	UBeam_Location.push_back(point1_z);
	UBeam_Location.push_back(point2_x);
	UBeam_Location.push_back(point2_z);
	UBeam_Location.push_back(point3_x);
	UBeam_Location.push_back(point3_z);
	UBeam_Location.push_back(point4_x);
	UBeam_Location.push_back(point4_z);
	UBeam_Location.push_back(point5_x);
	UBeam_Location.push_back(point5_z);
	UBeam_Location.push_back(point6_x);
	UBeam_Location.push_back(point6_z);
	UBeam_Location.push_back(point7_x);
	UBeam_Location.push_back(point7_z);

	return true;
}

bool drawUBeam(int ID, int refID, int offSet,double head)
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

	if (ID == 12 || ID == 13)
	{
		calculateUPosition(ID, 0.5, 4, 4,head);
		Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
			Point3D::create(UBeamStartPoint, UBeam_Location[0], UBeam_Location[1]),
			Point3D::create(UBeamStartPoint, UBeam_Location[2], UBeam_Location[3]));
		if (!line1)
			return false;

		Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(UBeamStartPoint, UBeam_Location[4], UBeam_Location[5]));
		if (!line2)
			return false;
		Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(UBeamStartPoint, UBeam_Location[6], UBeam_Location[7]));
		if (!line2)
			return false;
		Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(UBeamStartPoint, UBeam_Location[8], UBeam_Location[9]));
		if (!line2)
			return false;
		Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(UBeamStartPoint, UBeam_Location[10], UBeam_Location[11]));
		if (!line2)
			return false;
		Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(UBeamStartPoint, UBeam_Location[12], UBeam_Location[13]));
		if (!line2)
			return false;
		Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(UBeamStartPoint, UBeam_Location[14], UBeam_Location[15]));
		if (!line2)
			return false;
		Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line1->startSketchPoint());
		if (!line2)
			return false;

		extrudeComponent(ID, (tankDiameter * 10) + (80)); //Add the total width of the columns
	}
	else
	{
		calculateUPosition(ID, 0.5, 4, 4,head);
		Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
			Point3D::create(UBeam_Location[0], 0, UBeam_Location[1]),
			Point3D::create(UBeam_Location[2], 0, UBeam_Location[3]));
		if (!line1)
			return false;

		Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(UBeam_Location[4], 0, UBeam_Location[5]));
		if (!line2)
			return false;
		Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(UBeam_Location[6], 0, UBeam_Location[7]));
		if (!line2)
			return false;
		Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(UBeam_Location[8], 0, UBeam_Location[9]));
		if (!line2)
			return false;
		Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(UBeam_Location[10], 0, UBeam_Location[11]));
		if (!line2)
			return false;
		Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(UBeam_Location[12], 0, UBeam_Location[13]));
		if (!line2)
			return false;
		Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(UBeam_Location[14], 0, UBeam_Location[15]));
		if (!line2)
			return false;
		Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line1->startSketchPoint());
		if (!line2)
			return false;

		extrudeComponent(ID, (tankDiameter * 10) + (80));
	}

	UBeam_Location.clear();
}

bool drawHorizontalUBeams(int ID, double _extrusionLength, double head)
{
	drawUBeam(ID, 0, 0,head);
	return true;
}

#endif // !UBeam_h