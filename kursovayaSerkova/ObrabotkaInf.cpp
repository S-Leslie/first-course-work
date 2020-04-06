#include "stdafx.h"
#include "kursovayaSerkova.h"

extern AirEnd studEnd;

AirBeg   GetAir(HWND hDlg) {
	AirBeg airBeg;
	TCHAR buf[100] = TEXT("");
	airBeg.del = 0;
	BOOL 	lpNom = TRUE, lpMarka = TRUE, lpMesto = TRUE, lpBilet = TRUE, lpPrice = TRUE;
	airBeg.nom = GetDlgItemInt(hDlg, IDC_GET_NOM, &lpNom, FALSE);
	GetDlgItemText(hDlg, IDC_GET_MARKA, airBeg.marka, 12);
	if (*airBeg.marka == 0)
	{
		wcscpy(buf + wcslen(buf), TEXT("  ошибка ввода!"));
		lpMarka = FALSE;
	}
	GetDlgItemText(hDlg, IDC_GET_MESTO, airBeg.mesto, 20);
	if (*airBeg.mesto == 0)
	{
		wcscpy(buf, TEXT("  ошибка ввода!"));
		lpMesto = FALSE;
	}
	airBeg.bilet = GetDlgItemInt(hDlg, IDC_GET_BILET, &lpBilet, FALSE);
	airBeg.price = GetDlgItemInt(hDlg, IDC_GET_PRICE, &lpPrice, FALSE);

	if (lpNom == FALSE ||
		lpMarka == FALSE ||
		lpMesto == FALSE ||
		lpBilet == FALSE ||
		lpPrice == FALSE)
	{
		MessageBox(hDlg, buf, TEXT("Сообщение об ошибке ввода"), MB_OK);
		// установки признака пустой не введенной информации         
		airBeg.nom = 0;
		*airBeg.marka = 0;
		*airBeg.mesto = 0;
		airBeg.bilet = 0;
		airBeg.price = 0;

	}


	return  airBeg;
}

void putStudEndToStroka(StructEnd& u)
{


	swprintf(u.str, TEXT(" %-17d ║ %-17s ║ %-15s ║ %-15d ║ %-15d ║%d "), u.airEnd.nom, u.airEnd.marka, u.airEnd.mesto, u.airEnd.bilet, u.airEnd.price,u.airEnd.del);
	//swprintf(u.str, TEXT(" %-17s ║ %-17u%% ║ %15u%% ║ %15u%% ║ %15u%% ║ "), u.airEnd.fam, u.airEnd.sport, u.airEnd.pob1,  u.airEnd.pob2,  u.airEnd.pob3 );

}

StructEnd  obrabotkaInfo(AirBeg airBeg)
{


	StructEnd u;

	u.airEnd.nom = airBeg.nom;
	wcscpy(u.airEnd.marka, airBeg.marka);
	wcscpy(u.airEnd.mesto, airBeg.mesto);
	u.airEnd.bilet = airBeg.bilet;
	u.airEnd.price = airBeg.price;
	u.airEnd.del = airBeg.del;
	putStudEndToStroka(u);

	return u;
}
