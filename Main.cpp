#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
//#include "Header.h"

using namespace std;

class Obfuscator
{
public:

	const string OUT = "newCode.c";

	virtual void obfuscate(string fileName) = 0;

	string generateRandomVar() {

		int cnt = 0;                      //counting 7 letters for the random name
		int randNum;
		string finalName = "";            //every letter will be added to the string value
		srand((unsigned int)time(NULL));

		while (cnt < 7) {

			//generates a random number with a maximum of two digits
			randNum = rand() % 100;

			//if the number is within the range of valid numbers in the Ascii table the cnt will be rised
			if (randNum >= 1 && randNum <= 10 || randNum >= 18 && randNum <= 43
				|| randNum == 48 || randNum >= 50 && randNum <= 75) {
				cnt++;

				//checking if the first letter is a number, because variables names can't start with numbers...
				if (finalName.empty() && randNum >= 1 && randNum <= 10) {
					continue;//jumping to start of the loop
				}

				finalName += convertTheAscii(randNum);
			}
		}
		return finalName;
	}

	char convertTheAscii(int num) {
		char c = '0' - 1 + num;
		return c;
	}

	vector<string> parseFileUsingVector(string fileName) {

		fstream myFile;
		vector <string> vec;            //the vector that contains the file lines
		myFile.open(fileName, ios::in); //opening the file on read mode

		if (myFile.is_open()) {                  //if the file is open
			string textLine;
			while (getline(myFile, textLine)) {  //inserting all the file lines, line by line.
				vec.push_back(textLine);         //each element of the vector will be contain one line of the file
			}
			myFile.close();
		}
		return vec;
	}

	int fileLinesCounter(string fileName) {
		fstream myFile;
		int lines = 0;                  //counting the lines for the array size
		string textLine;                 //will be containing the file lines
		myFile.open(fileName, ios::in);  //opening the file at the read mode

		if (myFile.is_open()) {
			while (getline(myFile, textLine)) {     //counting the lines of the file
				lines++;
			}
			return lines;
		}
	}

	string* parseFile(string fileName) {

		fstream myFile;
		int lines = fileLinesCounter(fileName);     //counting the lines for the array size
		int cnt = 0;								//counting the location of the array elements 
		string textLine;							//will be containing the file lines
		myFile.open(fileName, ios::in);				//opening the file at the read mode

		if (myFile.is_open()) {

			////The GETLINE has reached the end of the file, so you have to go back to the beginning 
			//myFile.clear();
			//myFile.seekg(0, ios::beg);

			//creating a dynemic array with the size of the lines
			string* containText = new string[lines];

			//go over the lines of the file again and put it in the array
			while (cnt < lines) {
				getline(myFile, containText[cnt++]);
			};

			myFile.close();
			return containText;        //return the array pointer
		}

	}

	void writeToFile(string* codeArray , string fileName) {
		fstream newCodeFile;
		newCodeFile.open(OUT, ios::out);		//write mode
		int size = fileLinesCounter(fileName);

		if (newCodeFile.is_open()) {
			for (int i = 0; i < size; i++) {  
				//inserting the strings from
				//the array to the file one by one
				newCodeFile << codeArray[i];	
			}
			newCodeFile.close();
		}
	}

};

//need to be fixet
class lineObfuscator : public Obfuscator
{
public:

	void obfuscate(string filename) {

		lineObfuscator obj;
		string randomname = obj.generateRandomVar();

		cout << randomname << endl;
		int stupidnum1;
		int stupidnum2;
		string parseFile;
		
		srand((unsigned int)time(NULL));
		stupidnum1 = rand() % 10000;
		stupidnum2 = rand() % 10000;

		string* getFilelines = obj.parseFile(filename);
		//do: 
		
		obj.writeToFile( getFilelines , filename);



		
	}

};


//comment for a new branch just for the example
int main() {

	//lineObfuscator obj;


	///////////////Experiments: writeToFile() function.
	//string textArray[10];
	//textArray[0] = "#include <iostream>\n";
	//textArray[3] = "int main(){\n";
	//textArray[4] = " cout<< 'b';}\n";
	////int size = sizeof(textArray)/sizeof(string);
	//obj.writeToFile(textArray);


	///////////////Experiments: generateRandomVar() function.
	/*string randomname;
	randomname = obj.generateRandomVar();
	cout << randomname << endl;*/


	///////////////Experiments: parseFile() function.
	/*string filename = "myFile.txt";
	int lines = obj.fileLinesCounter(filename);

	string* getfilelines = new string[lines];
	getfilelines = obj.parseFile(filename);

	for (int i = 0; i < lines; i++) {
		cout << getfilelines[i] <<endl;
	}*/

	//obj.writeToFile(getfilelines, filename);


	///////////////Experiments: obfuscate() function.
	//string fileName = "myFile.txt";
	//obj.obfuscate(fileName);

	//ifstream myStream(fileName);
	//string line;

	//while (getline(myStream, line)) {

	//}



	return 0;
}