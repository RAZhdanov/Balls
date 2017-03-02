#pragma once
#include "node.h"
#include "PolygonEx.h"
#include "PolyLineEx.h"
class KND_Analize :
	public Node
{
public:
	KND_Analize(void);
	void DrawGraph(const HWND &hWnd, HDC &hdc);
	~KND_Analize(void);
private:
	RECT rect;
	int xViewExt;
	int yViewExt;

	int xWinExt;
	int yWinExt;

	double nPixPerAlpha1;
	double nPixPerN1;

	int n1Min; //n1
	int n1Max; //n1
	int Alpha1Min; //alpha1
	int Alpha1Max; //alpha1

	int n1GridStep;
	int Alpha1GridStep;

	int x, y;

	HPEN hPen0;
	HPEN hPen1;	
	HPEN hOldPen;

	HFONT hFont0;
	HFONT hFont1;
	HFONT hOldFont;

	int alpha1;
	int xMin;
	int xMax;	

	int n1;
	int yMin;
	int yMax;

	LOGFONT lf;
	Shape *shape[6];
	POINT p[8], p1[4], p2[4], p3[4], p4[4], p5[4];
};

