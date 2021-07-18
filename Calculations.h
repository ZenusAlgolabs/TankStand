#pragma once
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "Common.h"
#define Gravity 9.81

double PrincipleBeams_Length=0;
double PrincipleBeams_Cost_per_Meter;
double PrincipleBeams_Cost;
double HorizontalBeams_Length=0;
double HorizontalBeams_Cost_per_Meter;
double HorizontalBeams_Cost;
double DiagonalBeams_Length=0;
double DiagonalBeams_Cost_per_Meter;
double DiagonalBeams_Cost;

float calculateLoad(float Capacity, double Head){
	double Tank_Load = Capacity * Gravity;
	double Design_load_1 = 0.4 * pow(10, 3);
	Design_load_1 = Design_load_1 * Head;
	double Total_Load = Design_load_1 + Tank_Load;
	return Total_Load;
}

//2 storried house, 20 feet high, 6.096 meters
void ColumnCalculations(double Capacity, double Head)
{
	double Yield_Stress = 250 * pow(10, 6);
	double Permissible_Axial_Compressible_Stress = 101;
	double Area_Of_Column = calculateLoad(Capacity,Head) / Permissible_Axial_Compressible_Stress;
	double percent_Area_Increase = 25;
	Area_Of_Column = Area_Of_Column * (100 + percent_Area_Increase) / 100;

	double Breath = 5;
	double Width = 5;
	double Thickness = 0.2;

	double rad_of_gyration = 1.98;
	double SegmentLength = Head / supportCount;
	double Slenderness_ratio = SegmentLength / rad_of_gyration;
}

void CalculateCost()
{
	PrincipleBeams_Cost = (PrincipleBeams_Length/1000) * PrincipleBeams_Cost_per_Meter;
	HorizontalBeams_Cost = (HorizontalBeams_Length / 1000)* HorizontalBeams_Cost_per_Meter;
	DiagonalBeams_Cost = (DiagonalBeams_Length / 1000)* DiagonalBeams_Cost_per_Meter;
}
#endif // !CALCULATIONS_H
