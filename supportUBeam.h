#pragma once
#ifndef supportUBeam_h
#define  supportUBeam_h
#include "Headers.h"
#include "Common.h"

std::vector<double>supportUBeam_Location;
double UBeamStartPoint = 0;

bool calculateUPosition(int location, double thickness, double height, double width, double head)
{
	double startPoint_x = 0;
	double startPoint_z = head / 10;
	double point1_x, point1_z, point2_x, point2_z, point3_x, point3_z, point4_x, point4_z, point5_x, point5_z, point6_x, point6_z, point7_x, point7_z;

	if (location == 1)
	{
		startPoint_x = (tankDiameter / 3);
	}
	if (location == 2)
	{
		startPoint_x = tankDiameter - (tankDiameter / 3);
	}

	point1_x = startPoint_x;
	point1_z = startPoint_z + height;

	point2_x = point1_x + width;
	point2_z = point1_z;

	point3_x = point2_x;
	point3_z = startPoint_z;

	point4_x = point3_x - thickness;
	point4_z = startPoint_z;

	point5_x = point4_x;
	point5_z = point2_z - thickness;

	point6_x = startPoint_x + thickness;
	point6_z = point5_z;

	point7_x = point6_x;
	point7_z = startPoint_z;

	supportUBeam_Location.push_back(startPoint_x);
	supportUBeam_Location.push_back(startPoint_z);
	supportUBeam_Location.push_back(point1_x);
	supportUBeam_Location.push_back(point1_z);
	supportUBeam_Location.push_back(point2_x);
	supportUBeam_Location.push_back(point2_z);
	supportUBeam_Location.push_back(point3_x);
	supportUBeam_Location.push_back(point3_z);
	supportUBeam_Location.push_back(point4_x);
	supportUBeam_Location.push_back(point4_z);
	supportUBeam_Location.push_back(point5_x);
	supportUBeam_Location.push_back(point5_z);
	supportUBeam_Location.push_back(point6_x);
	supportUBeam_Location.push_back(point6_z);
	supportUBeam_Location.push_back(point7_x);
	supportUBeam_Location.push_back(point7_z);

	return true;
}

bool drawSupportUBeam(int ID,int location, int refID, int offSet, double head)
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

	calculateUPosition(location, 0.5, 4, 4, head);
	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(UBeamStartPoint, supportUBeam_Location[0], supportUBeam_Location[1]),
		Point3D::create(UBeamStartPoint, supportUBeam_Location[2], supportUBeam_Location[3]));
	if (!line1)
		return false;

	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(UBeamStartPoint, supportUBeam_Location[4], supportUBeam_Location[5]));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(UBeamStartPoint, supportUBeam_Location[6], supportUBeam_Location[7]));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(UBeamStartPoint, supportUBeam_Location[8], supportUBeam_Location[9]));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(UBeamStartPoint, supportUBeam_Location[10], supportUBeam_Location[11]));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(UBeamStartPoint, supportUBeam_Location[12], supportUBeam_Location[13]));
	if (!line2)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(UBeamStartPoint, supportUBeam_Location[14], supportUBeam_Location[15]));
	if (!line2)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;

	extrudeComponent(ID, (tankDiameter * 10) + (80)); //Add the total width of the columns
	supportUBeam_Location.clear();
}

#endif // !supportUBeam_h