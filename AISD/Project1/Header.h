#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;
bool createFileWithRandomNumbers(const char* fileName, const int numbersCount, const int maxNumberValue) {
	ofstream file(fileName);

	if (!file.is_open()) {
		cout << "cant open file" << endl;
		return false;
	}

	srand(time(0));
	int x = 0;
	for (int i = 0; i < numbersCount; i++)
		file << rand() % maxNumberValue << " ";

	file.close();
	return true;
}

bool isFileContainsSortedArray(const char* fileName) {
	ifstream file(fileName);

	int number1, number2;
	file >> number1;

	while (file >> number2) {
		if (number2 < number1)
			return false;

		number1 = number2;
	}

	return true;
}
