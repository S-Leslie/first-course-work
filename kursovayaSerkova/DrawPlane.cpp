#include "stdafx.h"
void DrawPlane(HDC hDC, RECT rect, POINT beg, int palitra_pic)
{
	//const int yCl=247;
	//const int xCl=567;
	const int yCl = (rect.bottom - rect.top);
	//
	const int xCl = (rect.right - rect.left);
	//


	const double dXPix = xCl / 16;
	const double dYPix = yCl / 13;

	SetMapMode(hDC, MM_ISOTROPIC);
	SetWindowExtEx(hDC, xCl, yCl, NULL);
	SetViewportExtEx(hDC, xCl, -yCl, NULL);
	SetViewportOrgEx(hDC, beg.x, yCl - beg.y, NULL);

	COLORREF myCol[3][6] = { { RGB(0,0,255), RGB(0,0,0), RGB(0,191,255), RGB(30,144, 255), RGB(70,70,70), RGB(200,180,70) },
	{ RGB(255, 20, 147), RGB(0,0,0), RGB(255, 99, 71), RGB(205, 92, 92), RGB(70,70,70), RGB(200,180,70) },
	{ RGB(0, 128, 0), RGB(0,0,0), RGB(0, 255,127), RGB(60, 179, 113), RGB(70,70,70), RGB(200,180,70) }
	};

	//Создаем кисть
	LOGBRUSH lb;
	lb.lbColor = myCol[palitra_pic][0];
	lb.lbStyle = BS_SOLID;
	lb.lbHatch = 5;
	HBRUSH hBrush = CreateBrushIndirect(&lb);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	

	//Турбина
	POINT pl4[] = { { 2 * dXPix,   4.75*dYPix },			// 0
	{ 2.25 * dXPix,	7 * dYPix },	// 1
	{ 3.25 * dXPix,	7 * dYPix }, //2
	{ 3.5 * dXPix,   4.75*dYPix },//3
	{ 2 * dXPix,   4.75 * dYPix } }; //0
	Polyline(hDC, pl4, sizeof(pl4) / sizeof(POINT));
	FloodFill(hDC, 2.5 * dXPix, 5 * dYPix, myCol[palitra_pic][1]);
	//Турбина 2
	POINT pl5[] = { { 12.5 * dXPix,   4.75*dYPix },			// 0
	{ 12.75 * dXPix,	7 * dYPix },	// 1
	{ 13.75 * dXPix,	7 * dYPix }, //2
	{ 14 * dXPix,   4.75*dYPix },//3
	{ 12.5 * dXPix,   4.75 * dYPix } }; //0
	Polyline(hDC, pl5, sizeof(pl5) / sizeof(POINT));
	FloodFill(hDC, 13 * dXPix, 5 * dYPix, myCol[palitra_pic][1]);

	//Меняем цвет кисти
	lb.lbColor = myCol[palitra_pic][2];
	hBrush = CreateBrushIndirect(&lb);
	DeleteObject(SelectObject(hDC, hBrush));

	// Большие крылья
	POINT pl[] = { { 8 * dXPix,   3.5*dYPix },			// 0
	{ 0 ,	7.5*dYPix },	// 1
	{ 16 * dXPix,	7.5*dYPix }, //2
	{ 8 * dXPix,   3.5*dYPix } };	// 3

	Polyline(hDC, pl, sizeof(pl) / sizeof(POINT));

	HRGN kr = CreatePolygonRgn(pl, 4, ALTERNATE);
	PaintRgn(hDC, kr);
	DeleteObject(kr);
		

	// Маленькие крылья
	POINT pl2[] = { { 8 * dXPix,  8 * dYPix },		// 0
	{ 6 * dXPix ,	10.5*dYPix },	// 1
	{ 8 * dXPix,	10 * dYPix },  //2
	{ 10 * dXPix,   10.5*dYPix },  //3
	{ 8 * dXPix,   8 * dYPix } };	// 4

	Polyline(hDC, pl2, sizeof(pl2) / sizeof(POINT));

	//Зарисовываем крылья
		FloodFill(hDC, pl2[0].x , pl2[0].y + 1 * dYPix, myCol[palitra_pic][1]);
	
	//Меняем цвет кисти 
		lb.lbColor = myCol[palitra_pic][0];
		hBrush = CreateBrushIndirect(&lb);
		DeleteObject(SelectObject(hDC, hBrush));

	//Корпус (большая часть)
		POINT po2[] = { { 6 * dXPix,	10 * dYPix },	// 0
		{ 10 * dXPix,	0 },	// 1
		{ 10 * dXPix,	5 * dYPix } };	// 2
		int dCentr1X = (10 * dXPix - 6 * dXPix) / 2;
		int dCentr1Y = (10 * dYPix - 5 * dYPix) / 2;
		HRGN el = CreateEllipticRgn(6 * dXPix, 10 * dYPix, 10 * dXPix, 0);
		FillRgn(hDC, el, hBrush);
		DeleteObject(el);

	//Меняем цвет кисти 
		lb.lbColor = myCol[palitra_pic][3];
		hBrush = CreateBrushIndirect(&lb);
		DeleteObject(SelectObject(hDC, hBrush));

	//Корпус (маленькая часть)
		POINT po3[] = { { 6.5 * dXPix,	6 * dYPix },	// 0
		{ 9.5 * dXPix,	0 },	// 1
		{ 9.5 * dXPix,	3 * dYPix } };	// 2
		int dCentr2X = (9.5 * dXPix - 6.5 * dXPix) / 2;
		int dCentr2Y = (6 * dYPix - 0) / 2;
		for (int i = 0, dL = 14 * dXPix; i < 1; i++)
		{
			Arc(hDC, po3[0].x + i * dL, po3[0].y,
				po3[1].x + i * dL, po3[1].y,
				po3[2].x + i * dL, po3[2].y,
				po3[2].x + i * dL, po3[2].y);
		}
		FloodFill(hDC, 8 * dXPix, 5 * dYPix, myCol[palitra_pic][1]);
		FloodFill(hDC, 8 * dXPix, 2 * dYPix, myCol[palitra_pic][1]);

	//Меняем цвет кисти 
		lb.lbColor = myCol[palitra_pic][0];
		hBrush = CreateBrushIndirect(&lb);
		DeleteObject(SelectObject(hDC, hBrush));

	//Носик
		POINT po4[] = { { 7.25 * dXPix,	1.5 * dYPix },	// 0
		{ 8.75 * dXPix,	0 },	// 1
		{ 8.75 * dXPix,	1.5 * dYPix } };	// 2
		int dCentr4X = (8.75 * dXPix - 7.25 * dXPix) / 2;
		int dCentr4Y = (1.5 * dYPix - 0) / 2;
		for (int i = 0, dL = 14 * dXPix; i < 1; i++)
		{
			Arc(hDC, po4[0].x + i * dL, po4[0].y,
				po4[1].x + i * dL, po4[1].y,
				po4[2].x + i * dL, po4[2].y,
				po4[2].x + i * dL, po4[2].y);
		}
		FloodFill(hDC, 8 * dXPix, 1 * dYPix, myCol[palitra_pic][1]);


	//Меняем цвет кисти 
	lb.lbColor = myCol[palitra_pic][5];
	hBrush = CreateBrushIndirect(&lb);
	DeleteObject(SelectObject(hDC, hBrush));

	//Окно
	POINT pl3[] = { { 8 * dXPix,   2.5*dYPix },			// 0
	{ 7 * dXPix,	3 * dYPix },	// 1
	{ 7 * dXPix,	4 * dYPix }, //2
	{ 8 * dXPix,   3.5*dYPix }, //3
	{ 9 * dXPix,   4 * dYPix }, //4
	{ 9 * dXPix,   3 * dYPix }, //5
	{ 8 * dXPix,   2.5*dYPix } };	//6 

	Polyline(hDC, pl3, sizeof(pl3) / sizeof(POINT));

	FloodFill(hDC, pl3[0].x , pl3[0].y + 0.5 * dYPix, myCol[palitra_pic][1]);

	//Меняем цвет кисти 
	lb.lbColor = myCol[palitra_pic][4];
	hBrush = CreateBrushIndirect(&lb);
	DeleteObject(SelectObject(hDC, hBrush));

	//Турбины (овальчики)

	POINT po[] = { { 2 * dXPix,	5.5 * dYPix },	// 0
	{ 3.5 * dXPix,	4 * dYPix },	// 1
	{ 3.5 * dXPix,	4.75*dYPix } };	// 2
	int dCentrX = (3.5 * dXPix - 2 * dXPix) / 2;
	int dCentrY = (5.5 * dYPix - 4 * dYPix) / 2;
	HRGN el1 = CreateEllipticRgn(2 * dXPix, 5.5 * dYPix, 3.5 * dXPix, 4 * dYPix);
	FillRgn(hDC, el1, hBrush);
	DeleteObject(el1);
	
	POINT po0[] = { { 12.5 * dXPix,	5.5 * dYPix },	// 0
	{ 14 * dXPix,	4 * dYPix },	// 1
	{ 13.25 * dXPix,	4.75*dYPix } };	// 2
	int dCentr0X = (14 * dXPix - 12.5 * dXPix) / 2;
	int dCentr0Y = (5.5 * dYPix - 4 * dYPix) / 2;
	HRGN el0 = CreateEllipticRgn(12.5 * dXPix, 5.5 * dYPix, 14 * dXPix, 4 * dYPix);
	FillRgn(hDC, el0, hBrush);
	DeleteObject(el0);

}