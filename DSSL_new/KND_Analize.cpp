#include "StdAfx.h"
#include "KND_Analize.h"


KND_Analize::KND_Analize(void):xViewExt(0), yViewExt(0), xWinExt(0), yWinExt(0), nPixPerAlpha1(0),
	nPixPerN1(0),n1Min(0), n1Max(0), Alpha1Min(0), Alpha1Max(0), n1GridStep(0), Alpha1GridStep(0),
	x(0), y(0),
	hPen0(nullptr), hPen1(nullptr), hOldPen(nullptr), hFont0(nullptr), hFont1(nullptr), hOldFont(nullptr),
	alpha1(0), xMin(0), xMax(0),
	n1(0), yMin(0), yMax(0)
{
	
}


KND_Analize::~KND_Analize(void)
{
}

void KND_Analize::DrawGraph(const HWND &hWnd, HDC &hdc)
{
	
	GetClientRect(hWnd, &rect);

	xViewExt = rect.right - rect.left;
	yViewExt = rect.bottom - rect.top;

	xWinExt = xViewExt;
	yWinExt = yViewExt;

	nPixPerAlpha1 = yViewExt / 160.0;
	nPixPerN1 = xViewExt / 60.0;

	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
	SetViewportExtEx(hdc, xViewExt, -yViewExt, NULL);

	SetViewportOrgEx(hdc, 12*(int)nPixPerN1, yViewExt-100, NULL);

	n1Min = 0; //n1
	n1Max = 35; //n1
	Alpha1Min = -10; //alpha1
	Alpha1Max = 110; //alpha1

	n1GridStep = 5;
	Alpha1GridStep = 10;

	const char* xMark[] = {"70", "75", "80", "85", "90", "95", "100", "105"};
	const char* yMark[] = {"-10", "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110"};

	//Сетка
	hPen0 = CreatePen(PS_SOLID, 1, RGB(0, 160, 0)); //Создаем новое перо
	hOldPen = (HPEN)SelectObject(hdc, hPen0);

	//прорисовка сетки по оси x
	alpha1 = Alpha1Min;
	xMin = n1Min * (int)nPixPerN1;
	xMax = n1Max * (int)nPixPerN1;

	for(int i = 0; i < 13; i++)
	{
		y = alpha1 * (int)nPixPerAlpha1;
		MoveToEx(hdc, xMin, y, NULL);
		LineTo(hdc, xMax, y);
		TextOut(hdc, xMin-60, y+8, yMark[i], strlen(yMark[i]));
		alpha1+=Alpha1GridStep;
	}


	//прорисовка сетки по оси x
	n1 = n1Min;
	yMin = Alpha1Min * (int)nPixPerAlpha1;
	yMax = Alpha1Max * (int)nPixPerAlpha1;
	for(int i = 0; i < 8; i++)
	{
		x = n1 * (int)nPixPerN1;
		MoveToEx(hdc, x, yMin, NULL);
		LineTo(hdc, x, yMax);
		TextOut(hdc, x-6, yMin-10, xMark[i], strlen(xMark[i]));
		n1+=n1GridStep;
	}

	//Ось "x"
	hPen1 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(hdc, hPen1);
	MoveToEx(hdc, 0, 0, NULL);
	LineTo(hdc, xMax, 0);
	
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
	lf.lfItalic = TRUE;
	lf.lfWeight = FW_BOLD;
	lf.lfHeight = 20;
	lf.lfCharSet = DEFAULT_CHARSET;
	lstrcpy((LPSTR)&lf.lfFaceName, "Arial");

	hFont0 = CreateFontIndirect(&lf);
	hOldFont = (HFONT)SelectObject(hdc, hFont0);
	SetTextColor(hdc, RGB(0,0,200));

	TextOut(hdc, xMax+10, 10, "n1пр, %", 7);

	//Ось "y"
	MoveToEx(hdc, 0, yMin, NULL);
	LineTo(hdc, 0, yMax);
	TextOut(hdc, -10, yMax+30, "alpha1, IP", 10);

	//график

	//Но логичнее создать новый класс, который будет унаследован от многоугольника сугубо для целей n2
	

	

	//1. Допуск на отладку
	p[0].x = (70-70)*(long)nPixPerN1; p[0].y = (11)*(long)nPixPerAlpha1;
	p[1].x = (82-70)*(long)nPixPerN1; p[1].y = (11)*(long)nPixPerAlpha1;
	p[2].x = (95-70)*(long)nPixPerN1; p[2].y = (107)*(long)nPixPerAlpha1;
	p[3].x = (105-70)*(long)nPixPerN1; p[3].y = (107)*(long)nPixPerAlpha1;
	p[4].x = (105-70)*(long)nPixPerN1; p[4].y = (101)*(long)nPixPerAlpha1;
	p[5].x = (95-70)*(long)nPixPerN1; p[5].y = (101)*(long)nPixPerAlpha1;
	p[6].x = (84-70)*(long)nPixPerN1; p[6].y = (-1)*(long)nPixPerAlpha1;
	p[7].x = (70-70)*(long)nPixPerN1; p[7].y = (-1)*(long)nPixPerAlpha1;
	shape[0] = new PolygonEx(p, 8, BS_HATCHED, Color(0,255,255), HS_FDIAGONAL, Color(0,255,255), 3, 3);


	//2. Допуск на переменный режим
	//левая часть
	p1[0].x = (77-70)*(long)nPixPerN1; p1[0].y = (11)*(long)nPixPerAlpha1;
	p1[1].x = (90-70)*(long)nPixPerN1; p1[1].y = (107)*(long)nPixPerAlpha1;
	p1[2].x = (95-70)*(long)nPixPerN1; p1[2].y = (107)*(long)nPixPerAlpha1;
	p1[3].x = (82-70)*(long)nPixPerN1; p1[3].y = (11)*(long)nPixPerAlpha1;
	shape[1] = new PolygonEx(p1, 4, BS_NULL, Color(255,255,255), HS_DIAGCROSS, Color(), 0, PS_DOT);
	//правая часть
	p2[0].x = (84-70)*(long)nPixPerN1; p2[0].y = (-1)*(long)nPixPerAlpha1;
	p2[1].x = (95-70)*(long)nPixPerN1; p2[1].y = (101)*(long)nPixPerAlpha1;
	p2[2].x = (104-70)*(long)nPixPerN1; p2[2].y = (101)*(long)nPixPerAlpha1;
	p2[3].x = (91-70)*(long)nPixPerN1; p2[3].y = (-1)*(long)nPixPerAlpha1;
	shape[2] = new PolygonEx(p2, 4, BS_NULL, Color(255,255,255), HS_DIAGCROSS, Color(), 0, PS_DOT);

	//3. Допуск на эксплуатацию
	//левая часть
	p3[0].x = (long)(80-70)*(long)nPixPerN1; p3[0].y = (long)(11)*(long)nPixPerAlpha1;
	p3[1].x = (long)(94-70)*(long)nPixPerN1; p3[1].y = (long)(107)*(long)nPixPerAlpha1;
	p3[2].x = (long)(95-70)*(long)nPixPerN1; p3[2].y = (long)(107)*(long)nPixPerAlpha1;
	p3[3].x = (long)(82-70)*(long)nPixPerN1; p3[3].y = (long)(11)*(long)nPixPerAlpha1;
	shape[3] = new PolygonEx(p3, 4, BS_SOLID, Color(206,206,255), HS_DIAGCROSS, Color(0,0,255), 3, 3);
	//правая часть
	p4[0].x = (long)(84-70)*(long)nPixPerN1; p4[0].y = (long)(-1)*(long)nPixPerAlpha1;
	p4[1].x = (long)(95-70)*(long)nPixPerN1; p4[1].y = (long)(101)*(long)nPixPerAlpha1;
	p4[2].x = (long)(96-70)*(long)nPixPerN1; p4[2].y = (long)(101)*(long)nPixPerAlpha1;
	p4[3].x = (long)(85.25-70)*(long)nPixPerN1; p4[3].y = (long)(-1)*(long)nPixPerAlpha1;
	shape[4] = new PolygonEx(p4, 4, BS_SOLID, Color(206,206,255), HS_DIAGCROSS, Color(0,0,255), 3, 3);

	//4. Теоретическая линия
	p5[0].x = (long)(70-70)*(long)nPixPerN1; p5[0].y = (long)(4)*(long)nPixPerAlpha1;
	p5[1].x = (long)(83-70)*(long)nPixPerN1; p5[1].y = (long)(4)*(long)nPixPerAlpha1;
	p5[2].x = (long)(95-70)*(long)nPixPerN1; p5[2].y = (long)(104)*(long)nPixPerAlpha1;
	p5[3].x = (long)(105-70)*(long)nPixPerN1; p5[3].y = (long)(104)*(long)nPixPerAlpha1;
	shape[5] = new PolyLineEx(p5, 4);
	for(int i = 0; i < 6; i++)
		shape[i]->Draw(hdc);
	//...



	
	//Заголовок
	char* title = "Границы допустимых углов входных направляющих аппаратов КНД";
	lf.lfItalic = FALSE;
	lf.lfWeight = FW_BOLD;
	lf.lfHeight = 25;
	hFont1 = CreateFontIndirect(&lf);
	SelectObject(hdc, hFont1);

	SetTextColor(hdc, RGB(0, 200, 0));
	TextOut(hdc, 0, yMax + 70, title, strlen(title));

	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldFont);

	DeleteObject(hPen0);
	DeleteObject(hPen1);
	DeleteObject(hFont0);
	DeleteObject(hFont1);
	for(int i = 0; i < 6; i++)
		delete shape[i];
	delete[] shape;
}