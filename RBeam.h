#pragma once
#ifndef RBeam_h
#define  RBeam_h
#include "Headers.h"
#include "Common.h"
#include "UBeam.h"

std::vector<int>Principle;
std::vector<int>P1;
std::vector<int>P2;
std::vector<int>P3;

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
	UBeamStartPoint = P3_x4;

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

bool drawRBeam(int ID, int refID, int offSet,double thickness)
{
	getConstructionPlane(ID, refID, offSet);
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
	x_1 = x_1 + thickness;
	y_1 = y_1 + thickness;
	x_2 = x_2 + thickness;
	y_2 = y_2 - thickness;
	x_3 = x_3 - thickness;
	y_3 = y_3 - thickness;
	x_4 = x_4 - thickness;
	y_4 = y_4 + thickness;

	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(Point3D::create(x_1 , y_1 , 0), Point3D::create(x_2 , y_2 , 0));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(x_3 , y_3 , 0));
	if (!line5)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(x_4 , y_4 , 0));
	if (!line7)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line5->startSketchPoint());
	if (!line8)
		return false;

}

bool drawVerticalSupportBeams(int ID, double _extrusionLength)
{
	drawRBeam(ID, 0, 0,1);
	extrudeComponent(ID, _extrusionLength);
	return true;
}


#endif // !RBeam_h