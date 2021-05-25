#pragma once
#ifndef Beam_h
#define Beam_h

#include "Common.h"

std::vector<int>Principle;
std::vector<int>P1;
std::vector<int>P2;
std::vector<int>P3;

bool calculatePriciplePositions()
{
	int x_1, z_1, x_2, z_2, x_3, z_3, x_4, z_4;
	x_1 = Principle[0]; z_1 = Principle[1];
	x_2 = Principle[2]; z_2 = Principle[3]; double width = double(z_2) - double(z_1);
	x_3 = Principle[4]; z_3 = Principle[5];
	x_4 = Principle[6]; z_4 = Principle[7]; double length = double(x_4) - double(x_1);

	int P1_x1, P1_y1, P1_x2, P1_y2, P1_x3, P1_y3, P1_x4, P1_y4;
	P1_x1 = x_1;
	P1_y1 = z_2 + tankDiameter;

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
	P2_y1 = z_4;

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

bool drawUBeam(int count, int ID, int location, int refID, int offSet, double thickness, double width, double head,double deviation)
{
	x_1 = 0.0; y_1 = 0.0; z_1 = 0.0;
	x_2 = 0.0; y_2 = 0.0; z_2 = 0.0;
	x_3 = 0.0; y_3 = 0.0; z_3 = 0.0;
	x_4 = 0.0; y_4 = 0.0; z_4 = 0.0;
	x_5 = 0.0; y_5 = 0.0; z_5 = 0.0;
	x_6 = 0.0; y_6 = 0.0; z_6 = 0.0;
	x_7 = 0.0; y_7 = 0.0; z_7 = 0.0;
	x_8 = 0.0; y_8 = 0.0; z_8 = 0.0;

	if (count == 0)
	{
		x_1 = (deviation * location); y_1 = head / 10;
		x_2 = x_1; y_2 = y_1 + width;
		x_3 = x_2 + width; y_3 = y_2;
		x_4 = x_3; y_4 = y_1;
		x_5 = x_4 - thickness; y_5 = y_1;
		x_6 = x_5; y_6 = y_3 - thickness;
		x_7 = x_1 + thickness; y_7 = y_6;
		x_8 = x_7; y_8 = y_1;

	}
	else if (count == 1)
	{
	z_1 = (deviation * location); y_1 = head / 10;
	z_2 = z_1; y_2 = y_1 + width;
	z_3 = z_2 + width; y_3 = y_2;
	z_4 = z_3; y_4 = y_1;
	z_5 = z_4 - thickness; y_5 = y_1;
	z_6 = z_5; y_6 = y_3 - thickness;
	z_7 = z_1 + thickness; y_7 = y_6;
	z_8 = z_7; y_8 = y_1;
	}

	Sketch_UBeam(ID, refID, offSet);
	return true;
}

bool drawRBeam(int ID, int refID, int offSet, double thickness)
{
	getConstructionPlane(ID, refID, offSet);
	getSubOccurrence(ID);

	int x_1 = 0, z_1 = 0, x_2 = 0, z_2 = 0, x_3 = 0, z_3 = 0, x_4 = 0, z_4 = 0;

	if (ID == 0)
	{
		x_1 = Principle[0]; z_1 = Principle[1];
		x_2 = Principle[2]; z_2 = Principle[3];
		x_3 = Principle[4]; z_3 = Principle[5];
		x_4 = Principle[6]; z_4 = Principle[7];
	}
	else
	{
		if (ID == 1)
		{
			x_1 = P1[0]; z_1 = P1[1];
			x_2 = P1[2]; z_2 = P1[3];
			x_3 = P1[4]; z_3 = P1[5];
			x_4 = P1[6]; z_4 = P1[7];
		}
		else if (ID == 2)
		{
			x_1 = P2[0]; z_1 = P2[1];
			x_2 = P2[2]; z_2 = P2[3];
			x_3 = P2[4]; z_3 = P2[5];
			x_4 = P2[6]; z_4 = P2[7];
		}
		else if (ID == 3)
		{
			x_1 = P3[0]; z_1 = P3[1];
			x_2 = P3[2]; z_2 = P3[3];
			x_3 = P3[4]; z_3 = P3[5];
			x_4 = P3[6]; z_4 = P3[7];
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
	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(
		Point3D::create(x_1, 0, z_1),
		Point3D::create(x_2, 0, z_2));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(
		line1->endSketchPoint(),
		Point3D::create(x_3, 0, z_3));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(
		line2->endSketchPoint(),
		Point3D::create(x_4, 0, z_4));
	if (!line3)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(
		line3->endSketchPoint(),
		line1->startSketchPoint());
	if (!line4)
		return false;

	// Draw inner rectangle by two points. 
	x_1 = x_1 + thickness;
	z_1 = z_1 + thickness;
	x_2 = x_2 + thickness;
	z_2 = z_2 - thickness;
	x_3 = x_3 - thickness;
	z_3 = z_3 - thickness;
	x_4 = x_4 - thickness;
	z_4 = z_4 + thickness;

	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(
		Point3D::create(x_1, 0, z_1),
		Point3D::create(x_2, 0, z_2));
	if (!line5)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(
		line5->endSketchPoint(),
		Point3D::create(x_3, 0, z_3));
	if (!line5)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(
		line6->endSketchPoint(),
		Point3D::create(x_4, 0, z_4));
	if (!line7)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(
		line7->endSketchPoint(),
		line5->startSketchPoint());
	if (!line8)
		return false;

}

#endif // !Beam_h