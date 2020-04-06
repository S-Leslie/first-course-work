#include "stdafx.h"
#include "kursovayaSerkova.h"


extern AirBeg airBeg;


//+
void add(fstream& stream, AirBeg& airBeg, int n)
{
	HWND hDlg;

	stream.clear();
	if (n)
	{
		stream.seekp((n - 1)*LenRec, ios::beg);
	}
	else
	{
		stream.seekp(0, ios::end);
	}
	try
	{
		stream
			<< setw(LenFam) << airBeg.nom
			<< setw(LenSport) << airBeg.marka
			<< setw(LenFam) << airBeg.mesto
			<< setw(LenFam) << airBeg.bilet
			<< setw(LenFam) << airBeg.price
			<< setw(2) << airBeg.del
			<< endl;
	}
	catch (...)
	{
		MessageBox(hDlg, TEXT("Файл не найден"), TEXT("Ошибка"), MB_OK);
		exit(0);
	}
}

//+
fstream& read(fstream& stream, AirBeg &airBeg, int n)
{

	stream.clear();
	int k;
	if (n)
	{
		k = stream.tellg();
		stream.seekp((n - 1)*LenRec, ios::beg);
		k = stream.tellg();
	}

	stream >> setw(LenFam) >> airBeg.nom
		>> setw(LenSport) >> airBeg.marka
		>> setw(LenFam) >> airBeg.mesto
		>> setw(LenFam) >> airBeg.bilet
		>> setw(LenFam) >> airBeg.price
		>> setw(2) >> airBeg.del;

	if (!stream && !stream.eof())
	{
		exit(0);
	}
	return stream;

}

//+
void ReadAll(fstream& stream, HWND hListBox)
{
	SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
	stream.clear();
	stream.seekg(0);
	StructEnd startU;
	while (read(stream, airBeg, 0))
	{
		startU = obrabotkaInfo(airBeg);
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)startU.str);
	}
}

//-
void MarkToDel(fstream& stream, int n)
{
	stream.clear();
	stream.seekg(0, ios::beg);
	if (read(stream, airBeg, n))
	{
		airBeg.del = !airBeg.del;
	}
	add(stream, airBeg, n);
}

//+
void DelMark(fstream& stream)
{

	fstream temp = fstream(Temp, ios::out);
	temp.imbue(locale(".1251"));
	stream.clear();
	stream.seekg(0, ios::beg);
	for (; read(stream, airBeg);)
	{
		if (airBeg.del == 0)
		{
			add(temp, airBeg);
		}
	}
	temp.close();
	stream.close();
	remove(Filename);
	rename(Temp, Filename);
	stream.open(Filename, ios::in | ios::out);

}

//+
void ChangeMarkToDelete(fstream& stream, HWND hDlg, HWND hListBox, int curItem)
{
	stream.clear();
	stream.seekg(0);
	read(stream, airBeg, curItem);
	switch (airBeg.del)
	{
	case 0:
		SetDlgItemText(hDlg, IDC_POM, L"Нет");
		break;
	case 1:
		SetDlgItemText(hDlg, IDC_POM, L"Да");
		break;
	}
}

void SortedPrint(fstream& f,HWND hListBox)
{
	AirBeg samolets[200]; // Буферны массив
	int AmountOfsamolets = 0; // Кол-во самолетов
	f.clear(); // Сброс потока
	f.seekg(0, ios::beg);
	for (int i = 1; read(f, samolets[i - 1], i); i++, AmountOfsamolets++); // Считываем все в массив самолёты
																		   
	for (int i = 1; i < AmountOfsamolets; i++)
	{
		int j = i;
		// Сравнение суммарной стоимости, для сортировки по убыванию
		while ((samolets[j].bilet*samolets[j].price)>(samolets[j-1].bilet*samolets[j-1].price))
		{
			AirBeg buff = samolets[j - 1]; // Меняем местами
			samolets[j - 1] = samolets[j];
			samolets[j] = buff;
			if (j - 1) j--; // Сдвигаемся с проверкой либо до первого элемента либо пока не будет отсортировано
			else break;
		}
	}
	TCHAR s[150];
	for (int i = 0; i < AmountOfsamolets; i++) 
	{
		swprintf(s, TEXT(" %-17s ║ %-15d"), samolets[i].marka, samolets[i].price);
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)s);
	}
}
