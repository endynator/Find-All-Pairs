#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector> 
#include "Source.h"

using namespace std;

void fill(vector<vector<int>>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			arr[i][j] = randInt(0, 10);
		}
	}
}

void delRowsWithZero(vector<vector<int>>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		bool hasZero = false;
		for (int j = 0; j < arr[i].size(); j++) {
			if (arr[i][j] == 0) {
				hasZero = true;
				break;
			}
		}
		if (hasZero) {
			arr.erase(arr.begin() + i);
			i--; //adjust the index since row's been erased
		}
	}
}

void output(vector<vector<int>>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void t2() {
	vector<vector<int>> arr(5, vector<int>(5));

	fill(arr);

	cout << "\nIntial array: " << endl; output(arr);

	delRowsWithZero(arr);

	cout << "Result: " << endl; output(arr);
}