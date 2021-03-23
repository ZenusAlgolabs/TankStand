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

bool calculatePriciplePositions()
{
	int offset = 10;
	int x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4;
	x_1 = Principle[0]; y_1 = Principle[1];
	x_2 = Principle[2]; y_2 = Principle[3]; double width = double(y_2) - double(y_1);
	x_3 = Principle[4]; y_3 = Principle[5];
	x_4 = Principle[6]; y_4 = Principle[7]; double length = double(x_4) - double(x_1);

	int P1_x1, P1_y1, P1_x2, P1_y2, P1_x3, P1_y3, P1_x4, P1_y4;
	P1_x1 = x_1;
	P1_y1 = y_2 + offset;

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
	P2_x1 = x_4 + offset;
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
	P3_x1 = P1_x4 + offset;
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


	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(Point3D::create(11, 7, 0), Point3D::create(11, 4, 0));
	if (!line1)
		return false;
	Ptr<SketchLine> line2 = sketchLines->addByTwoPoints(line1->endSketchPoint(), Point3D::create(14, 4, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line3 = sketchLines->addByTwoPoints(line2->endSketchPoint(), Point3D::create(14, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line4 = sketchLines->addByTwoPoints(line3->endSketchPoint(), Point3D::create(13, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line5 = sketchLines->addByTwoPoints(line4->endSketchPoint(), Point3D::create(13, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line6 = sketchLines->addByTwoPoints(line5->endSketchPoint(), Point3D::create(12, 5, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line7 = sketchLines->addByTwoPoints(line6->endSketchPoint(), Point3D::create(12, 7, 0));
	if (!line2)
		return false;
	Ptr<SketchLine> line8 = sketchLines->addByTwoPoints(line7->endSketchPoint(), line1->startSketchPoint());
	if (!line2)
		return false;
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

bool drawHorizontalSupportBeams(double _extrusionLength)
{
	for (int i = 4; i < 8; i++)
	{
		if (i == 4)
		{
			drawRBeam(i,0,0);
		}
		else
		{
			drawRBeam(i,(i-1),0);
		}
		extrudeComponent(i, _extrusionLength);
	}
	assembleComponents(4,5);
	assembleComponents(5,6);
	assembleComponents(6,7);

	for (int i = 8; i < 12; i++)
	{
		if (i == 8)
		{
			drawRBeam(i, 0,20);
		}
		else
		{
			drawRBeam(i, (i - 1),0);
		}
		extrudeComponent(i, _extrusionLength);
	}
	assembleComponents(8,9);
	assembleComponents(9,10);
	assembleComponents(10,11);

	for (int i = 12; i < 16; i++)
	{
		if (i == 12)
		{
			drawRBeam(i, 0,40);
		}
		else
		{
			drawRBeam(i, (i - 1),0);
		}
		extrudeComponent(i, _extrusionLength);
	}
	assembleComponents(12,13);
	assembleComponents(13,14);
	assembleComponents(14,15);
	
	for (int i = 16; i < 24; i++)
	{
		if (i == 16)
		{
			drawRBeam(i, 0,60);
		}
		else
		{
			drawRBeam(i, (i - 1),0);
		}
		extrudeComponent(i, _extrusionLength);
	}
	assembleComponents(15,16);
	assembleComponents(15,17);
	assembleComponents(17,18);
	
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
	extrudeComponent(ID, _extrusionLength);
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

	for (int i = 0; i < 61; i++)
	{
		if (i >= 0 && i < 4)
		{
			//Draw Rectangular support beams
			drawVerticalSupportBeams(i, _tankHead);
		}
		/*if (i == 4)
		{
			//Draw Rectangular horizontal support beams
			drawHorizontalSupportBeams(50);
		}
		else if (i >= 24 && i < 39)
		{
			//Draw U-beams
			drawHorizontalUBeams(i, 100);
		}
		else if (i >= 39 && i < 51)
		{
			//Draw L-beams
			drawDiagonalSupportBeams(i, 100);
		}*/
	}

	//assembleComponents();
}

#endif // !BEAM_H
