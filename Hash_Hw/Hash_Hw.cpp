// Hash_Hw.cpp : Defines the entry point for the console application.
//
//
//Supposed to create a hash table based on the extraction method with collision prevention enabled.

#include "stdafx.h" 
#include "stdio.h"
#include "stdlib.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//since we are working with a large array, knowing the limits of each type will be useful. 
//inspiration for max f(x)/limits found here:http://www.cplusplus.com/reference/limits/numeric_limits/
int printHash(int Hashtable[])//prints hash table. original code found from here: http://en.cppreference.com/w/cpp/memory/c/calloc
{
	ofstream out; string outString;
	out.open("hashed_socials.txt");
	int hashSize = 340000000;//Hashtable.size();
	if (Hashtable&& out.is_open())
	{
		for (int n = 0; n < hashSize - 1; ++n) // print the array
		{
			if (Hashtable[n] != NULL)//checking for errors in case of printing a value not in the array.
			{
				outString = outString + std::to_string(Hashtable[n]) + ","; // link: http://www.cplusplus.com/reference/string/to_string/
				//std::cout << "hashTable[" << n << "] == " << Hashtable[n] << '\n';
			}
		}
		out << outString;
		out.close();
	}return 0;
}
int quad_probe(int Hashtable[], int key, int quadNum)//quadratic probe code adapted struture from linear probe
{
	int pos, i;
	i = 0;
	pos = key%quadNum; //(previously hash(key))
	if (Hashtable[pos] == 0)
	{
		Hashtable[pos] = key;
		return pos;
	}
	else		//slot is not empty...move onto next slot. pos is the taken position. 
				//(pos + i*i) % 450000000 is  the quad_probe formula, enacted for this instance.
	{
		for (i = (pos + i*i); i % 450000000 != pos; i++)
		{
			if (Hashtable[i] == 0)
			{
				Hashtable[i] = key;
				return i;
			}
		}
	}
	return -1;	//table overflow
}
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
	int *hashTable1 = (int*)calloc(340000000, sizeof(int*));/* int *hashTable2 = (int*)calloc(240000000, sizeof(int*)); 
	int *hashTable3 = (int*)calloc(250000000, sizeof(int*)); int *hashTable4 = (int*)calloc(250000000, sizeof(int*));*/
	//allocates memory for large hash table. http://www.cplusplus.com/reference/cstdlib/calloc/
	//if supposed to contain between 100000000-999999999, a lot of space is needed. need to split among 4 tables for it to work. ^^"
	/*int i;
	for (i = 0; i < 999999999; i++)
	{
		std::cout << "hash1: " << hashTable1[i] << endl;
		//cout << "hash2: " << hashTable2[i] << endl;
		//cout << "hash3: " << hashTable3[i] << endl;
		//cout << "hash4: " << hashTable4[i] << endl;
	}*/
	if (hashTable1 == NULL) //|| hashTable2 == NULL || hashTable3 == NULL || hashTable4 == NULL)
	{
		printf("Error! memory not allocated.");//prevents errors. found here: http://www.programiz.com/c-programming/c-dynamic-memory-allocation
		exit(0);
	}
	if (!in.is_open())//if file cannot open, show error message.
	{
		std::cout << "cannot open file [everybodys_socials.txt]...please try again." << endl;
	}
	std::cout << "pick a number between 1 and 450 million." << endl; //picks # for quadratic probing.
	cin >> quadNumString; quadNum = atoi(quadNumString.c_str());//grabs quadnum string from user, and converts to int.
	while (quadNum < 1 || quadNum >450000000) //while quadnum is not within this range, repeat lines 29-30. 
	{
		std::cout << "pick a number between 1 and 450 million." << endl; //picks # for quadratic probing.
		cin >> quadNumString; quadNum = atoi(quadNumString.c_str());//grabs quadnum string from user, and converts to int.
	}
	while (in.peek() != EOF)/*Reads the file.
						 If looking for the next value does not result in EOF, grabs the next line of code from the file.
						 Prints to screen in Debug.*/
	{
		getline(in, fileLine, ',');//gets a new line (Social Security #, due to ',' limiting a line to just numbers.)
		fileLineNum = atoi(fileLine.c_str());//converts fileLine to int. found here: 
		//cout << "the current value extracted is: " << fileLineNum << endl; //checks if the atoi conversion is succesful.
		while (fileLine.size() < 9)
		{	
			string tempfileLine = fileLine;//holds old values from fileline.
			std::cout << "fileLine is not the correct size...please wait." << endl;
			getline(in, fileLine, ',');//grabs more ints until the next ','.
			tempfileLine = tempfileLine + fileLine;
			fileLine= tempfileLine;//pushes all values to fileLine.
		}
		/*Lines 36-42 convert parts of fileLine to the ints 3rd, 5th, 7th, 8th, all stored in 8th. Lines 44-45 print out to screen for debug.*/
		charToInt = fileLine[2];//grabs the third value of fileLine.
		charToInt = fileLine[2];//grabs the third value of fileLine.
		//std::cout << charToInt << endl;
		charToInt = charToInt + fileLine[4];//grabs the fifth value of fileLine, adds to line 50 code.
		//std::cout << charToInt << endl;
		charToInt = charToInt + fileLine[6];//grabs the seventh value of fileLine.
		//std::cout << charToInt << endl;
		charToInt = charToInt + fileLine[7];//grabs the eigth value of fileLine.
		//std::cout << charToInt << endl;
		eigth = atoi(charToInt.c_str());//uses atoi to convert charToInt to int.
		//cout << "\ndigits extracted: " << eigth << endl;
										//these check to see if the digits from fileLineNum are correct.
		//std::cout << eigth << endl;
										//add to hash table, and add in quadratic probing without replacement method. hash table on line 26.
		//hashTable[eigth%quadNum] = eigth;//store each value to the hash table...debug mode only. 
		//all actual additions are handled by quad_probe below.
		quad_probe(hashTable1, eigth, quadNum);//does a check to make sure that the position for eigth is free in the table, and if not finds a new one. Adds eigth to the hash table.
		printHash(hashTable1);//prints hashtable to screen. 
	}
	in.clear(); in.close();//clears buffer and closes file.
	
	std::cout << "Program finished..." << endl;//tests if program has run fully.
	//free(hashTable);//cleans up memory allocated for hashTable
	return 0;
}


