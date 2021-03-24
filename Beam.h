#pragma once
#ifndef BEAM_H
#define BEAM_H

#include "Headers.h"
#include "Common.h"
#include "Inputs.h"

std::vector<int>Principle;
std::vector<int>P1;
std::vector<int>P2;
std::vector<int>P3;

std::vector<double>UBeam_Location;

double tankHead = 100;
double tankDiameter = 100;

int UBeamLastLocation = 0;
double UBeamStartPoint = 0;

bool calculatePriciplePositions()
{
	int x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4;
	x_1 = Principle[0]; y_1 = Principle[1];
	x_2 = Principle[2]; y_2 = Principle[3]; double width = double(y_2) - double(y_1);
	x_3 = Principle[4]; y_3 = Principle[5];
	x_4 = Principle[6]; y_4 = Principle[7]; double length = double(x_4) - double(x_1);

	int P1_x1, P1_y1, P1_x2, P1_y2, P1_x3, P1_y3, P1_x4, P1_y4;
	P1_x1 = x_1;
	P1_y1 = y_2 + tankDiameter;

	P1_x2 = P1_x1;
	P1_y2 = P1_y1 + width;

	P1_x3 = P1_x2 + length;
	P1_y3 = P1_y2;

	P1_x4 = P1_x3;
	P1_y4 = P1_y1;

	P1.push_back(P1_x1);
	P1.push_back(P1_y1);
	P1.push_back(P1_x2);
	P1.push_back(P1_y2);
	P1.push_back(P1_x3);
	P1.push_back(P1_y3);
	P1.push_back(P1_x4);
	P1.push_back(P1_y4);

	int P2_x1, P2_y1, P2_x2, P2_y2, P2_x3, P2_y3, P2_x4, P2_y4;
	P2_x1 = x_4 + tankDiameter;
	P2_y1 = y_4;

	P2_x2 = P2_x1;
	P2_y2 = P2_y1 + width;

	P2_x3 = P2_x2 + length;
	P2_y3 = P2_y2;

	P2_x4 = P2_x3;
	P2_y4 = P2_y1;

	P2.push_back(P2_x1);
	P2.push_back(P2_y1);
	P2.push_back(P2_x2);
	P2.push_back(P2_y2);
	P2.push_back(P2_x3);
	P2.push_back(P2_y3);
	P2.push_back(P2_x4);
	P2.push_back(P2_y4);

	int P3_x1, P3_y1, P3_x2, P3_y2, P3_x3, P3_y3, P3_x4, P3_y4;
	P3_x1 = P1_x4 + tankDiameter;
	P3_y1 = P1_y4;

	P3_x2 = P3_x1;
	P3_y2 = P3_y1 + width;

	P3_x3 = P3_x2 + length;
	P3_y3 = P3_y2;

	P3_x4 = P3_x3;
	P3_y4 = P3_y1;
	UBeamStartPoint = P3_x4 + 20;

	P3.push_back(P3_x1);
	P3.push_back(P3_y1);
	P3.push_back(P3_x2);
	P3.push_back(P3_y2);
	P3.push_back(P3_x3);
	P3.push_back(P3_y3);
	P3.push_back(P3_x4);
	P3.push_back(P3_y4);

	return true;
}

bool drawRBeam(int ID,int refID,int offSet)
{
	getConstructionPlane(ID,refID,offSet);
	getSubOccurrence(ID);

	int x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0, x_4 = 0, y_4 = 0;

	if (ID == 0)
	{
		x_1 = Principle[0]; y_1 = Principle[1];
		x_2 = Principle[2]; y_2 = Principle[3];
		x_3 = Principle[4]; y_3 = Principle[5];
		x_4 = Principle[6]; y_4 = Principle[7];
	}
	else
	{
		if (ID == 1)
		{
			x_1 = P1[0]; y_1 = P1[1];
			x_2 = P1[2]; y_2 = P1[3];
			x_3 = P1[4]; y_3 = P1[5];
			x_4 = P1[6]; y_4 = P1[7];
		}
		else if (ID == 2)
		{
			x_1 = P2[0]; y_1 = P2[1];
			x_2 = P2[2]; y_2 = P2[3];
			x_3 = P2[4]; y_3 = P2[5];
			x_4 = P2[6]; y_4 = P2[7];
		}
		else if (ID == 3)
		{
			x_1 = P3[0]; y_1 = P3[1];
			x_2 = P3[2]; y_2 = P3[3];
			x_3 = P3[4]; y_3 = P3[5];
			x_4 = P3[6]; y_4 = P3[7];
		}
	}

	// Draw two connected lines. 
	Ptr<SketchCurves> sketchCurves = (sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;

	// Draw outer rectangle by two points. 
	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(x_1, y_1, 0), Point3D::create(x_2, y_2, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(x_3, y_3, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(x_4, y_4, 0));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), line1->startSketchPoint());
	if (!line4)
		return false;

	// Draw inner rectangle by two points. 
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(Point3D::create(x_1 + 1, y_1 + 1, 0), Point3D::create(x_2 + 1, y_2 - 1, 0));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(x_3 - 1, y_3 - 1, 0));
	if (!line5)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(x_4 - 1, y_4 + 1, 0));
	if (!line7)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line5->startSketchPoint());
	if (!line8)
		return false;

}

bool calculateUPosition(int ID,double thickness,double height,double width)
{
	double startPoint_x = UBeamLastLocation;
	double startPoint_z=0;
	if (ID == 12 || ID == 13)
	{
		if (ID == 12)
		{
			startPoint_z = (tankDiameter / 3);
		}
		if (ID == 13)
		{
			startPoint_z = tankDiameter - (tankDiameter / 3);
		}
	}

	double point1_x = startPoint_x;
	double point1_z = startPoint_z + height;

	double point2_x = point1_x + width;
	double point2_z = point1_z;

	double point3_x = point2_x;
	UBeamLastLocation = point3_x + 10;
	double point3_z = startPoint_z;

	double point4_x = point3_x - thickness;
	double point4_z = startPoint_z;

	double point5_x = point4_x;
	double point5_z = point2_z - thickness;

	double point6_x = startPoint_x + thickness;
	double point6_z = point5_z;

	double point7_x = point6_x;
	double point7_z = startPoint_z;

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

bool drawUBeam(int ID, int refID, int offSet)
{
	getConstructionPlane(ID,refID,offSet);
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
		calculateUPosition(ID,0.5, 4, 4);
		Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
			Point3D::create(UBeamStartPoint,UBeam_Location[0], UBeam_Location[1]),
			Point3D::create(UBeamStartPoint, UBeam_Location[2], UBeam_Location[3]));
		if (!line1)
			return false;

		Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(UBeamStartPoint, UBeam_Location[4],  UBeam_Location[5]));
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

		extrudeComponent(ID, 1100);
	}
	else
	{
		calculateUPosition(ID,0.5, 4, 4);
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

		extrudeComponent(ID, 1100);
	}

	UBeam_Location.clear();
}

bool drawLBeam(int ID,int refID, int offSet)
{
	getConstructionPlane(ID,refID, offSet);
	getSubOccurrence(ID);

	// Draw two connected lines.
	Ptr<SketchCurves> sketchCurves=(sketch[ID]->sketchCurves());
	if (!sketchCurves)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;


	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(2, 7, 0), Point3D::create(2, 4, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(5, 4, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(5, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(3, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(3, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(2, 7, 0));
	if (!line2)
		return false;

}

bool drawVerticalSupportBeams(int ID, double _extrusionLength)
{
	drawRBeam(ID,0,0);
	extrudeComponent(ID, _extrusionLength);
	return true;
}

bool drawHorizontalSupportBeams(int ID,double _extrusionLength)
{
	drawLBeam(ID, 0, 0);
	extrudeComponent(ID, tankDiameter);
	return true;
}

bool drawDiagonalSupportBeams(int ID, double _extrusionLength)
{
	drawLBeam(ID,0,0);
	extrudeComponent(ID, _extrusionLength);
	return true;
}

bool drawHorizontalUBeams(int ID, double _extrusionLength)
{
	drawUBeam(ID,0,0);
	return true;
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

	Principle.push_back(0);
	Principle.push_back(0);
	Principle.push_back(0);
	Principle.push_back(4);
	Principle.push_back(4);
	Principle.push_back(4);
	Principle.push_back(4);
	Principle.push_back(0);

	calculatePriciplePositions();

	for (int i = 0; i < 35; i++)
	{
		if (i >= 0 && i < 4)
		{
			//Draw Rectangular support beams
			drawVerticalSupportBeams(i, tankHead);
		}
		if (i >=4 && i<12)
		{
			//Draw Rectangular horizontal support beams
			drawHorizontalSupportBeams(i,tankDiameter);
		}
		else if (i >= 12 && i < 20)
		{
			//Draw U-beams
			drawHorizontalUBeams(i, tankDiameter * 2);
		}
		/*else if (i >= 20 && i < 35)
		{
			//Draw L-beams
			drawDiagonalSupportBeams(i, 100);
		}*/
	}

	//assembleComponents();
}

#endif // !BEAM_H
