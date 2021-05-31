#pragma once
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "Common.h"

float calculateLoad(float Capacity, std::string Quality){
	float density = 1000;
	float load = 0.0;
	if (Quality == "salty"){density = 1200;}
	load = Capacity * density;
	return(load);
}

float calculateBeamHeight(float Head, float Max_Beam_Length){
	return (Head / Max_Beam_Length);
}

bool calculateStandDimensions()
{

}

#endif // !CALCULATIONS_H
