// Hash_Hw.cpp : Defines the entry point for the console application.
//
//
//Supposed to create a hash table based on the extraction method with collision prevention enabled.

#include "stdafx.h" 
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//since we are working with a large array, knowing the limits of each type will be useful. 
//inspiration for max f(x)/limits found here:http://www.cplusplus.com/reference/limits/numeric_limits/

int main()
{
	cout << "testing..." << endl;//test to see if program runs
	int third, fifth, seventh, eigth;//creation of int variables to store parts of hash keys.
	string charToInt = " "; //helps convert sections of fileLine to third, fifth, seventh, eigth.
	third = 0; fifth = 0; seventh = 0; eigth = 0;
	string fileLine, quadNumString;//for getline of file IO, quadratic probing #.
	int quadNum, fileLineNum;//num for quadratic probing, conversion of fileLine to an int.
	ifstream in;//creating ifstream for file IO
	in.open("everybodys_socials.txt");//opens file

	long int hashTable[99999999];//creates hash table. 
								 //if supposed to contain between 100000000-999999999, a lot of space is needed.
	if (!in.is_open())//if file cannot open, show error message.
	{
		cout << "cannot open file [everybodys_socials.txt]...please try again." << endl;
	}
	cout << "pick a number between 1 and 450 million." << endl; //picks # for quadratic probing.
	cin >> quadNumString; quadNum = atoi(quadNumString.c_str());//grabs quadnum string from user, and converts to int.
	while (quadNum < 1 || quadNum >450000000) //while quadnum is not within this range, repeat lines 29-30. 
	{
		cout << "pick a number between 1 and 450 million." << endl; //picks # for quadratic probing.
		cin >> quadNumString; quadNum = atoi(quadNumString.c_str());//grabs quadnum string from user, and converts to int.
	}
	cout << "\n max value for: \nints: "
		<< std::numeric_limits<int>::max() << "\nfloats: " << std::numeric_limits<float>::max() <<
		"\ndoubles: " << std::numeric_limits<double>::max() << endl;
	if (in.peek() != EOF)/*Reads the file.
						 If looking for the next value does not result in EOF, grabs the next line of code from the file.
						 Prints to screen in Debug.*/
	{
		getline(in, fileLine, ',');//gets a new line (Social Security #, due to ',' limiting a line to just numbers.)
		fileLineNum = atoi(fileLine.c_str());//converts fileLine to int. found here: 
		//cout << "the current value extracted is: " << fileLineNum << endl; //checks if the atoi conversion is succesful.

		/*Lines 36-42 convert parts of fileLine to the ints 3rd, 5th, 7th, 8th. Lines 44-45 print out to screen for debug.*/
		charToInt = fileLine[2];//grabs the third value of fileLine.
		third = atoi(charToInt.c_str());//uses atoi to convert charToInt to int.
		charToInt = fileLine[4];//grabs the fifth value of fileLine.
		fifth = atoi(charToInt.c_str());//uses atoi to convert charToInt to int.
		charToInt = fileLine[6];//grabs the seventh value of fileLine.
		seventh = atoi(charToInt.c_str());//uses atoi to convert charToInt to int.
		charToInt = fileLine[7];//grabs the eigth value of fileLine.
		eigth = atoi(charToInt.c_str());//uses atoi to convert charToInt to int.
										/*cout << "\nThird digit extracted: " << third << "\nFifth digit extracted: " << fifth <<
										"\nSeventh digit extracted: " << seventh << "\nEigth digit extracted: " << eigth << endl;*/
										//these check to see if the digits from fileLineNum are correct.

										//add to hash table, and add in quadratic probing without replacement method. hash table on line 26.

	}
	in.clear(); in.close();//clears buffer and closes file.
	cout << "Program finished..." << endl;//tests if program has run fully.
	return 0;
}

