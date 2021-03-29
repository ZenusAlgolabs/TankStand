#define _CRT_SECURE_NO_WARNINGS 1
#include "WriteCSV.h"

#define DATABASE_EXISTS 0

bool FindFile(string FileName)
{
	int Results;
	struct stat buffer;

	Results = stat(FileName.c_str(), &buffer);

	if (Results == DATABASE_EXISTS)
	{
		return true;
	}
	return false;
}

int Write(
	double PrincipleBeam, 
	double HorizontalUBeam,
	double HorizontalLBeams,
	double DiagonalLBeams)
{
	CSVWriter csv;

	//Automatically check for all database files
	int Results;
	struct stat buffer;

	//cout << "Writing to.."<<name<<"\n";
	std::string FileName = "E:/TankStand Dimensions.csv";
	Results = stat(FileName.c_str(), &buffer);


	if (Results == DATABASE_EXISTS)
	{
		//Prepare the data to be written to file...
		csv << PrincipleBeam
			<< HorizontalUBeam
			<< HorizontalLBeams
			<< DiagonalLBeams;

		//Since the data is being added to a database, append data to existing file if file is found
		csv.writeToFile(FileName.c_str(), true);
	}
	else
	{
		csv << "PrincipleBeam" << "HorizontalUBeams" << "HorizontalLBeams" << "DiagonalLBeams" ;
		//if there is no existing database file, write to new file the headers...
		csv.writeToFile(FileName.c_str());
		//Then append the data
		{
			CSVWriter csv_new;
			//Prepare the data to be written to file...
			csv << PrincipleBeam
				<< HorizontalUBeam
				<< HorizontalLBeams
				<< DiagonalLBeams;

			//Since the data is being added to a database, append data to existing file if file is found
			csv_new.writeToFile(FileName.c_str(), true);
		}
	}

	return 0;
}
