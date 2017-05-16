#include <cstdlib>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <algorithm>
#include <vector>

__int64 ticksProSek = 0;
double sekProTick = 0.0;
__int64 startZeit = 0;
__int64 aktuelleZeit = 0;

//Zeitmessungsfunktion: http://stackoverflow.com/questions/13156031/measuring-time-in-c
//Prototyp für addArrays
void addArrays(int* arr1, int* arr2, int* result);
void addEven(int* arr1, int* arr2, int* result);

int main(int argc, char** argv) {
	//2 große Arrays anlegen 
	int arr1[10000];
	int arr2[10000];
	int* result = (int*)malloc(10000 * sizeof(int));
	//Zufallsgenerator seeden
	srand(time(NULL));
	//Arrays füllen
	for (int i = 0; i < 10000; i++) {
		arr1[i] = rand() % 1024;
		arr2[i] = rand() % 1024;
	}


	QueryPerformanceCounter((LARGE_INTEGER*)&startZeit);
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksProSek);
	sekProTick = 1.0 / (double)ticksProSek;
	for (int i = 0; i < 100000; i++) {
		addArrays(arr1, arr2, result);
	}
	// Standard end-start stuff, account for clock speed
	QueryPerformanceCounter((LARGE_INTEGER*)&aktuelleZeit);
	std::cout << "Benötigte Zeit - ohne Branching: " << std::endl << (aktuelleZeit - startZeit)*sekProTick << " sec\n";

	//Branching OHNE Sortieren
	/* 

	QueryPerformanceCounter((LARGE_INTEGER*)&startZeit);
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksProSek);
	sekProTick = 1.0 / (double)ticksProSek;
	for (int i = 0; i < 100000; i++) {
		addEven(arr1, arr2, result);
	}


	// Standard end-start stuff, account for clock speed
	QueryPerformanceCounter((LARGE_INTEGER*)&aktuelleZeit);
	std::cout << "Benötigte Zeit - mit Conditional Branching: " << std::endl << (aktuelleZeit - startZeit)*sekProTick << " sec\n";
	*/

	QueryPerformanceCounter((LARGE_INTEGER*)&startZeit);
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksProSek);
	sekProTick = 1.0 / (double)ticksProSek;
	//Arrays vorher sortieren

	std::sort(std::begin(arr1), std::end(arr1));
	// Standard end-start stuff, account for clock speed
	QueryPerformanceCounter((LARGE_INTEGER*)&aktuelleZeit);
	std::cout << "std::sort, arr1, 10k Elemente - Dauer: "
		<< std::endl << (aktuelleZeit - startZeit)*sekProTick << " sec\n";

	QueryPerformanceCounter((LARGE_INTEGER*)&startZeit);
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksProSek);
	sekProTick = 1.0 / (double)ticksProSek;
	//Arrays vorher sortieren

	std::sort(std::begin(arr2), std::end(arr2));
	// Standard end-start stuff, account for clock speed
	QueryPerformanceCounter((LARGE_INTEGER*)&aktuelleZeit);
	std::cout << "std::sort, arr2, 10k Elemente - Dauer: "
		<< std::endl << (aktuelleZeit - startZeit)*sekProTick << " sec\n";

	QueryPerformanceCounter((LARGE_INTEGER*)&startZeit);
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksProSek);
	sekProTick = 1.0 / (double)ticksProSek;
	for (int i = 0; i < 100000; i++) {
		addEven(arr1, arr2, result);
	}
	// Standard end-start stuff, account for clock speed
	QueryPerformanceCounter((LARGE_INTEGER*)&aktuelleZeit);
	std::cout << "Benötigte Zeit - mit Conditional Branching - sortiert: " 
		<< std::endl << (aktuelleZeit - startZeit)*sekProTick << " sec\n";


}

//Funktion addArrays
void addArrays(int* arr1, int* arr2, int* res) {
	for (int i = 0; i < 10000; i++) {
		res[i] = arr1[i] + arr2[i];
	}
}

void addEven(int* arr1, int* arr2, int* res) {
	for (int i = 0; i < 10000; i++) {
		if (arr1[i] % 2 == 0) {
			res[i] = arr1[i] + arr2[i];
		}
	}
}