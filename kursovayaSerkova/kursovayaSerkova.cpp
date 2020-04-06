// kursovayaSerkova.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include <Windows.h>
#include "kursovayaSerkova.h"

#define MAX_LOADSTRING 100



// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
AirBeg airBeg = { 0,TEXT(""),TEXT(""),0,0 };

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK		GetDataDlgProc(HWND , UINT , WPARAM , LPARAM );
INT_PTR CALLBACK	ViewDlgProc(HWND , UINT , WPARAM , LPARAM );
INT_PTR CALLBACK	PutDataDlgProc(HWND , UINT , WPARAM , LPARAM );
BOOL CALLBACK		ChangeDataDlgProc(HWND , UINT , WPARAM , LPARAM );

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KURSOVAYASERKOVA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KURSOVAYASERKOVA));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KURSOVAYASERKOVA));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_KURSOVAYASERKOVA);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	static int picture = 1;
	HDC hdc;
	static int palitra_text = 0, palitra_pic = 0;
	static HMENU hMenu = GetMenu(hWnd);
	fstream stream;
	setlocale(LC_ALL, TEXT("Russian"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	switch (message)
	{
	case WM_CREATE:
		stream.imbue(locale(".1251"));
		stream.open("output.txt", ios::in | ios::out | ios::app);
		if (!stream)
		{
			MessageBox((HWND)GetModuleHandle(NULL), L"Файл не создан!", NULL, MB_OK);
			exit(0);
		}
		stream.close();
		stream.open("output.txt", ios::in | ios::out | ios::ate);
		if (!stream)
		{
			MessageBox((HWND)GetModuleHandle(NULL), L"Невозможно открыть файл!", NULL, MB_OK);
			exit(0);
		}
		stream.close();
		CheckMenuRadioItem(GetSubMenu(hMenu, 1), ID_TEXT_BDB,
			ID_TEXT_GSY, ID_TEXT_BDB, MF_BYCOMMAND);
		CheckMenuRadioItem(GetSubMenu(hMenu, 1), ID_PIC_BDB2,
			ID_PIC_GSY2, ID_PIC_BDB2, MF_BYCOMMAND);
		CheckMenuRadioItem(GetSubMenu(hMenu, 2), ID_FIRST_PIC,
			ID_SECOND_PIC, ID_FIRST_PIC, MF_BYCOMMAND);
		EnableMenuItem(hMenu, ID_TEXT_BDB, MF_BYCOMMAND | MFS_GRAYED);
		EnableMenuItem(hMenu, ID_TEXT_GSY, MF_BYCOMMAND | MFS_GRAYED);
		EnableMenuItem(hMenu, ID_TEXT_TSH, MF_BYCOMMAND | MFS_GRAYED);
		DrawMenuBar(hWnd);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case VIEW:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_VIEW), hWnd, ViewDlgProc);
			break;

		case ID_FIRST_PIC:
			picture = 1;
			CheckMenuRadioItem(GetSubMenu(hMenu, 2), ID_FIRST_PIC,
				ID_SECOND_PIC, LOWORD(wParam), MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_TEXT_BDB, MF_BYCOMMAND | MFS_GRAYED);
			EnableMenuItem(hMenu, ID_TEXT_GSY, MF_BYCOMMAND | MFS_GRAYED);
			EnableMenuItem(hMenu, ID_TEXT_TSH, MF_BYCOMMAND | MFS_GRAYED);
			//DrawMenuBar(hWnd);
			break;
		case ID_SECOND_PIC:

			picture = 2;
			CheckMenuRadioItem(GetSubMenu(hMenu, 2), ID_FIRST_PIC,
				ID_SECOND_PIC, LOWORD(wParam), MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_TEXT_BDB, MF_BYCOMMAND | MFS_ENABLED);
			EnableMenuItem(hMenu, ID_TEXT_GSY, MF_BYCOMMAND | MFS_ENABLED);
			EnableMenuItem(hMenu, ID_TEXT_TSH, MF_BYCOMMAND | MFS_ENABLED);
			//DrawMenuBar(hWnd);
			break;
		case ID_PIC_BDB2:
			palitra_pic = 0;
			CheckMenuRadioItem(GetSubMenu(hMenu, 1), ID_PIC_BDB2,
				ID_PIC_GSY2, LOWORD(wParam), MF_BYCOMMAND);
			break;
		case ID_PIC_TSH2:
			palitra_pic = 1;
			CheckMenuRadioItem(GetSubMenu(hMenu, 1), ID_PIC_BDB2,
				ID_PIC_GSY2, LOWORD(wParam), MF_BYCOMMAND);
			break;
		case ID_PIC_GSY2:
			palitra_pic = 2;
			CheckMenuRadioItem(GetSubMenu(hMenu, 1), ID_PIC_BDB2,
				ID_PIC_GSY2, LOWORD(wParam), MF_BYCOMMAND);
			break;
		case ID_TEXT_BDB:
			palitra_text = 0;
			CheckMenuRadioItem(GetSubMenu(hMenu, 1), ID_TEXT_BDB,
				ID_TEXT_GSY, LOWORD(wParam), MF_BYCOMMAND);
			break;
		case ID_TEXT_TSH:
			palitra_text = 1;
			CheckMenuRadioItem(GetSubMenu(hMenu, 1), ID_TEXT_BDB,
				ID_TEXT_GSY, LOWORD(wParam), MF_BYCOMMAND);
			break;
		case ID_TEXT_GSY:
			palitra_text = 2;
			CheckMenuRadioItem(GetSubMenu(hMenu, 1), ID_TEXT_BDB,
				ID_TEXT_GSY, LOWORD(wParam), MF_BYCOMMAND);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
	{
		POINT beg = { 0, 0 };
		hdc = BeginPaint(hWnd, &ps);
		RECT rect;

		switch (picture) {
		case 1:
			beg.x = 0; beg.y = 0;
			GetClientRect(hWnd, &rect);
			break;
		case 2:
			rect.top = 300;
			rect.right = 767;
			rect.bottom = 547;
			rect.left = 200;
			beg.x = 567; beg.y = -80;
			inputText(hWnd, hdc, palitra_text);
			break;
		}

		DrawPlane(hdc, rect, beg, palitra_pic);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ViewDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	static int nU = 0;
	static HWND hListBox;
	static LOGFONT lf;
	HFONT	hFont1;
	static int ip;


	int polow = 0;
	int curItem=0;

	cin.imbue(locale(".866"));
	fstream	stream(Filename, ios::in|ios::out);
	if (!stream)
	{
		stream.close();
		stream.open(Filename, ios::out);
		stream.close();
		stream.open(Filename, ios::in|ios::out);
	}
	stream.imbue(locale(".1251"));


	switch (message)
	{
	case WM_INITDIALOG:
		hListBox = GetDlgItem(hDlg, IDC_LIST1);
		ReadAll(stream, hListBox);
		SetFocus(hDlg);

		lf.lfHeight = 16;
		lstrcpy((LPWSTR)&lf.lfFaceName, TEXT("Courier"));
		hFont1 = CreateFontIndirect(&lf);
		SendMessage(hListBox, WM_SETFONT, (WPARAM)hFont1, TRUE);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case WM_INITDIALOG:
			hListBox = GetDlgItem(hDlg, IDC_LIST1);

			break;

		case IDOK:
			nU = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
			stream.close();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		case IDCANCEL:
			nU = SendMessage(hListBox, LB_GETCOUNT, 0, 0);

			stream.close();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;

		case IDC_WINNER:
			DialogBox((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PUT_WINNER), hDlg, PutDataDlgProc);
			break;
		case IDC_CHANGE:
		{
			curItem = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

			if (curItem != LB_ERR)
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_REC), hDlg, GetDataDlgProc);
				airBeg.del = 0;
				add(stream, airBeg, curItem + 1);
				SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
				ReadAll(stream, hListBox);
			}
			else
			{
				MessageBox(hDlg, L"сначала надо выделить элемент списка", L"ОШИБКА", MB_OK);
				break;
			}
		}
		break;
		/*DialogBox((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CHANGE), hDlg, ChangeDataDlgProc);
		break;*/
		case IDC_OTMENDEL:
		{
			curItem = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (curItem != LB_ERR)
			{
				TCHAR s[150];
				MarkToDel(stream, curItem + 1);
				ChangeMarkToDelete(stream, hDlg, hListBox, curItem + 1);
				stream.seekg(0,stream.beg);
				SendMessage(hListBox,LB_RESETCONTENT,0,0);
				for(AirBeg u; read(stream, u,0);)
					{
						swprintf(s, TEXT(" %-17d ║ %-17s ║ %-15s ║ %-15d ║ %-15d ║%d "), u.nom, u.marka, u.mesto, u.bilet, u.price,u.del);
						SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)s);
					}
			}
			else
			{
				MessageBox(hDlg, L"сначала надо выделить элемент списка", L"ОШИБКА", MB_OK);
				break;
			}

			break;
		}

		case IDC_DELETE:
			DelMark(stream);
			SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
			ReadAll(stream, hListBox);

			break;
		case IDC_REC_ADD:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_REC), hDlg, GetDataDlgProc);

			StructEnd itemU = obrabotkaInfo(airBeg);
			
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)itemU.str);
			add(stream, airBeg);

		}

		break;
	}

	return (INT_PTR)FALSE;
	
}

INT_PTR CALLBACK GetDataDlgProc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDC_GET_NOM));
		return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			airBeg = GetAir(hDlg);
			EndDialog(hDlg, TRUE);

			return TRUE;

		case IDCANCEL:
			airBeg.nom = 0;
			*airBeg.marka = 0;
			*airBeg.mesto = 0;
			airBeg.bilet = 0;
			airBeg.price = 0;
			EndDialog(hDlg, FALSE);
			return TRUE;
		}

		break;
	}
	return FALSE;
}

INT_PTR CALLBACK PutDataDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	static HWND hListBox;
	static LOGFONT lf;
	HFONT	hFont1;

	fstream	stream(Filename, ios::in|ios::out);
	if (!stream)
	{
		stream.close();
		stream.open(Filename, ios::out);
		stream.close();
		stream.open(Filename, ios::in|ios::out);
	}
	stream.imbue(locale(".1251"));

	switch (message)
	{
	case WM_INITDIALOG:
		hListBox = GetDlgItem(hDlg, IDC_LIST1);
		lf.lfHeight = 16;
		lstrcpy((LPWSTR)&lf.lfFaceName, TEXT("Courier"));
		hFont1 = CreateFontIndirect(&lf);
		SendMessage(hListBox, WM_SETFONT, (WPARAM)hFont1, TRUE);

		SortedPrint(stream,hListBox);

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
