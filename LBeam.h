#pragma once
#ifndef LBeam_h
#define  LBeam_h
#include "Headers.h"
#include "Common.h"

bool drawLBeam(int ID, int refID, int offSet)
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

bool drawHorizontalSupportBeams(int ID, double _extrusionLength)
{
	drawLBeam(ID, 0, 0);
	extrudeComponent(ID, tankDiameter);
	return true;
}

bool drawDiagonalSupportBeams(int ID, double _extrusionLength)
{
	drawLBeam(ID, 0, 0);
	extrudeComponent(ID, _extrusionLength);
	return true;
}

#endif // !LBeam_h
