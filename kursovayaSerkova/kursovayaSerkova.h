#pragma once

#include "resource.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <iomanip>

using namespace std;




#define NF 30
#define NS 20
#define NL 5
#define NLINE (NF+NS+NL+1)
#define MAX 2*NLINE
#define LenFam 20
#define LenSport 15

#define LenRec (LenFam+LenSport+LenFam+LenFam+LenFam+2+2)
#define Step 4
#define Filename "output.txt"
#define Temp "temp.txt"
#define fstream wfstream 


struct AirBeg {
	int nom;
	TCHAR marka[NS];
	TCHAR mesto[NF];
	int bilet;
	int price;
	int del;
};

struct AirEnd {
	int nom;
	TCHAR marka[NS];
	TCHAR mesto[NF];
	int bilet;
	int price;
	int del;
};

struct StructEnd {
	AirEnd airEnd;
	TCHAR str[150];
};





void add(fstream &stream, AirBeg &airBeg, int n = 0);
fstream& read(fstream&, AirBeg& airBeg, int = 0);
void ChangeMarkToDelete(fstream& stream, HWND hDlg, HWND hListBox, int curItem);
void MarkToDel(fstream& stream, AirBeg airBeg, int n);
void DelMark(fstream& stream, AirBeg airBeg);
AirBeg   GetAir(HWND hDlg);
void ReadAll(fstream& stream, HWND hListBox);
StructEnd  obrabotkaInfo(AirBeg  airBeg);
void putStudEndToStroka(StructEnd& u);
bool remove_line(const char *filename, size_t index);
void inputText(HWND hWnd, HDC hdc, int palitra);
void DrawPlane(HDC hDC, RECT rect, POINT beg, int palitra_pic);
AirBeg InputLineFromFile(int pos);
AirBeg OutputDataToFile(AirBeg airBeg);

void DelMark(fstream& stream);
void MarkToDel(fstream& stream, int n);
void changeStr(AirBeg& airBeg, fstream& stream, int n, TCHAR* nCo, TCHAR* nName_1, TCHAR* nName_2, TCHAR* nName_3);
void SortedPrint(fstream& f,HWND hListBox);



