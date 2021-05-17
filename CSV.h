#define _CRT_SECURE_NO_WARNINGS 1
#define DATABASE_EXISTS 0

#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>

using namespace std;

class CSVWriter
{
public:
	CSVWriter() {
		this->firstRow = true;
		this->seperator = ",";
		this->columnNum = -1;
		this->valueCount = 0;
	}

	CSVWriter(int numberOfColums) {
		this->firstRow = true;
		this->seperator = ",";
		this->columnNum = numberOfColums;
		this->valueCount = 0;
	}

	CSVWriter(string seperator) {
		this->firstRow = true;
		this->seperator = seperator;
		this->columnNum = -1;
		this->valueCount = 0;
	}

	CSVWriter(string seperator, int numberOfColums) {
		this->firstRow = true;
		this->seperator = seperator;
		this->columnNum = numberOfColums;
		this->valueCount = 0;
		cout << this->seperator << endl;
	}

	CSVWriter& add(const char* str) {
		return this->add(string(str));
	}

	CSVWriter& add(char* str) {
		return this->add(string(str));
	}

	CSVWriter& add(string str) {
		//if " character was found, escape it
		size_t position = str.find("\"", 0);
		bool foundQuotationMarks = position != string::npos;
		while (position != string::npos) {
			str.insert(position, "\"");
			position = str.find("\"", position + 2);
		}
		if (foundQuotationMarks) {
			str = "\"" + str + "\"";
		}
		else if (str.find(this->seperator) != string::npos) {
			//if seperator was found and string was not escapted before, surround string with "
			str = "\"" + str + "\"";
		}
		return this->add<string>(str);
	}

	template<typename T>
	CSVWriter& add(T str) {
		if (this->columnNum > -1) {
			//if autoNewRow is enabled, check if we need a line break
			if (this->valueCount == this->columnNum) {
				this->newRow();
			}
		}
		if (valueCount > 0)
			this->ss << this->seperator;
		this->ss << str;
		this->valueCount++;

		return *this;
	}

	template<typename T>
	CSVWriter& operator<<(const T& t) {
		return this->add(t);
	}

	void operator+=(CSVWriter& csv) {
		this->ss << endl << csv;
	}

	string toString() {
		return ss.str();
	}

	friend ostream& operator<<(std::ostream& os, CSVWriter& csv) {
		return os << csv.toString();
	}

	CSVWriter& newRow() {
		if (!this->firstRow || this->columnNum > -1) {
			ss << endl;
		}
		else {
			//if the row is the first row, do not insert a new line
			this->firstRow = false;
		}
		valueCount = 0;
		return *this;
	}

	bool writeToFile(string filename) {
		return writeToFile(filename, false);
	}

	bool writeToFile(string filename, bool append) {
		ofstream file;
		if (append)
			file.open(filename.c_str(), ios::out | ios::app);
		else
			file.open(filename.c_str(), ios::out | ios::trunc);
		if (!file.is_open())
			return false;
		if (append)
			file << endl;
		file << this->toString();
		file.close();
		return file.good();
	}

	void enableAutoNewRow(int numberOfColumns) {
		this->columnNum = numberOfColumns;
	}

	void disableAutoNewRow() {
		this->columnNum = -1;
	}
protected:
	bool firstRow;
	string seperator;
	int columnNum;
	int valueCount;
	stringstream ss;

};

int Write(double Capacity, string Material, string WaterQuality, double TankHead, int BeamID, std::string Type, int Quantity, double Length, double  Width, double  Thickness, std::string Comment) {
	CSVWriter csv;
	CSVWriter csv_1;
	CSVWriter csv_2;
	CSVWriter csv_3;
	CSVWriter csv_4;
	CSVWriter csv_5;

	//Automatically check for all database files
	int Results;
	struct stat buffer;

	std::string FileName = "C:/Users/Gachanja/Documents/Data.csv";
	Results = stat(FileName.c_str(), &buffer);

	if (Results == DATABASE_EXISTS) { //Prepare the data to be written to file...
		csv << BeamID << Type << Quantity << Length << Width << Thickness << Comment;

		//Since the data is being added to a database, append data to existing file if file is found
		csv.writeToFile(FileName.c_str(), true);
	}
	else {
		csv << "Capacity" << NULL << Capacity;
		csv.writeToFile(FileName.c_str());
		csv_1 << "Material" << NULL << Material;
		csv_1.writeToFile(FileName.c_str());
		csv_2 << "Water Quality" << NULL << WaterQuality;
		csv_2.writeToFile(FileName.c_str());
		csv_3 << "TankHead" << NULL << TankHead;
		csv_3.writeToFile(FileName.c_str());
		csv_4 << "BeamID" << "Type" << "Quantity" << "Length" << "Width" << "Thickness" << "Comment";
		csv_4.writeToFile(FileName.c_str());
	}
	return 0;
}
