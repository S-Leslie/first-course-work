#include "stdafx.h"
int strlen(TCHAR* str)
{
	int len;
	for (len = 0; *str; len++, str++);
	return len;
}

void inputText(HWND hWnd, HDC hdc, int palitra)
{
	PAINTSTRUCT ps;

	TCHAR* line[] = { TEXT("Крылатые машины."),
		TEXT("Серкова Олеся"),
		TEXT("8(985)891-63-01"),
		TEXT("Небольшая частная авиакомпания.")
	};
	// макрос  RGB задает палитру цветов от RGB(255,255,255)белый,
	// до RGB(0,0,0) черный
	COLORREF masColor[3][3] = { { RGB(0, 0, 255), RGB(30, 144, 255), RGB(25, 25, 112) },
	{ RGB(255, 99, 71), RGB(250, 128, 114), RGB(255, 105, 180) },
	{ RGB(0, 128, 0), RGB(0, 255, 127), RGB(225, 225, 0) }
	};

	HPEN hPen0 = CreatePen(PS_SOLID, 6, masColor[palitra][0]);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen0);

	static LOGFONT lf;
	lf.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
	// Шаг шрифта DEFAULT_PITCH по умолчанию
	lf.lfItalic = TRUE;
	// запрашивается курсивный шрифт, если TRUE
	lf.lfWeight = FW_BOLD;
	// жирность шрифта 0(FW_DONTCARE),100,200,... 700,..,900
	// значение 0 предписывает выбрать вес по умолчанию
	lf.lfHeight = 70;
	lf.lfCharSet = RUSSIAN_CHARSET;
	// код используемого набора символов

	HFONT hFont0 = CreateFontIndirect(&lf);
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont0);
	SetTextColor(hdc, masColor[palitra][1]);

	int x = 50, y = 30, dX = 80, dY = 80;



	TextOut(hdc, x, y, line[0], strlen(line[0]));

	POINT tabStop[] = { { x + dX,y + 2 * dY },
	{ x + dX,y + 3.5*dY },
	{ x + dX,y + 5 * dY }
	};
	int fontHeight[] = { 40,60,60 };

	MoveToEx(hdc, x, tabStop[0].y - 83, NULL);
	LineTo(hdc, x + 7.7*dX, tabStop[0].y - 83);
	DeleteObject(SelectObject(hdc, hFont0));
	// 
	for (int i = 0; i<3; ++i)
	{
		lf.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
		// Шаг шрифта DEFAULT_PITCH по умолчанию
		lf.lfItalic = FALSE;
		// запрашивается курсивный шрифт, если TRUE
		lf.lfWeight = FW_BOLD;
		// жирность шрифта 0(FW_DONTCARE),100,200,... 700,..,900
		// значение 0 предписывает выбрать вес по умолчанию
		lf.lfHeight = fontHeight[i];
		lf.lfCharSet = RUSSIAN_CHARSET;
		// код используемого набора символов

		hFont0 = CreateFontIndirect(&lf);
		SelectObject(hdc, hFont0);

		SetTextColor(hdc, masColor[palitra][i]);
		TextOut(hdc, tabStop[i].x, tabStop[i].y, line[i + 1], strlen(line[i + 1]));

		DeleteObject(SelectObject(hdc, hFont0));
	}

	DeleteObject(SelectObject(hdc, hOldPen));
	DeleteObject(SelectObject(hdc, hOldFont));
}