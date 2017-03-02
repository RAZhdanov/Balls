// DSSL_new.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DSSL_new.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


//Thread:
unsigned __stdcall Thread1(void *param);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DSSL_NEW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DSSL_NEW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DSSL_NEW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DSSL_NEW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	static HDC hdc; //контекст диспле€
	static HDC memory_HDC;
	static HBITMAP memory_bitmap;
	static HANDLE hThread;
	static unsigned int timer;


	static RECT rect; //пр€моугольник клиентской области
	GetClientRect(hWnd, &rect);

	
	static std::vector<Circle> ball;

	switch (message)
	{
	case WM_ERASEBKGND: //дл€ двойной буферизации
	{
		return 1;
	}
	case WM_CREATE: // Ќачальное положение шариков - случайное
	{
		srand(time(0)); //‘ункци€ srand выполн€ет инициализацию генератора случайных чисел rand
		timer = SetTimer(hWnd, 1, 10, NULL);//установка таймера
		GetClientRect(hWnd, &rect); //извлекает координаты рабочей области окна
		
		for (int i = 0; i < 5; i++)
			ball.push_back(
			Circle(
			Point((unsigned int)(rand() % (rect.right-rect.left)), (unsigned int)(rand() % (rect.top-rect.bottom))),
			(unsigned int)rand() % 5, 3, Color(rand() % 255, rand() % 255, rand() % 255), HS_CROSS, Color(rand() % 255, rand() % 255, rand() % 255))
			);
		break;
	}
	case WM_TIMER: //ќтрисовка шариков по закону F(r) = 1/r - 1/r^2
	{
		hThread = (HANDLE)_beginthreadex(NULL, 0, Thread1, (&ball), 0, NULL);
		WaitForSingleObject(hThread, INFINITE);
		InvalidateRect(hWnd, &rect, FALSE);
		break;
	}
	case WM_MOUSEWHEEL: //если покрутить колесиком мышки, то можно:
		{
			if (LOWORD(wParam) & MK_SHIFT)
			{
				for (auto circle_iterator = ball.begin(); circle_iterator != ball.end(); ++circle_iterator) // увеличить радиус и массу всех шариков при зажатии Shift
				{
					circle_iterator->Set_radius(circle_iterator->Get_radius() + 1);
					circle_iterator->Set_Mass(circle_iterator->Get_Mass() + 1);
				}

			}
			else
				for(auto circle_iterator = ball.begin(); circle_iterator != ball.end(); ++circle_iterator) // уменьшить радиус и массу всех шариков без зажати€ Shift
				{
					circle_iterator->Set_radius(circle_iterator->Get_radius() -1);
					circle_iterator->Set_Mass(circle_iterator->Get_Mass() - 1);
				}
			break;
		}
	case WM_MOUSEMOVE: //передвижение мышки
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		
		switch (wmId)
		{
		case MK_LBUTTON: // ѕеретаскивание мышкой шарика
		{
			//проходимс€ по всем шарикам
			std::find_if(ball.begin(), ball.end(), [&](Circle &a)->bool
			{
				if ((pow((long double)abs(LOWORD(lParam) - (int)(a.GetPos_X())), 2) + pow((long double)abs(HIWORD(lParam) - (int)(a.GetPos_Y())), 2)) 
					<= pow((long double)a.Get_radius(), 2))
				{
					a.SetPos_X(LOWORD(lParam));
					a.SetPos_Y(HIWORD(lParam));
					return true;
				}
				else
				{
					return false;
				}
			});
			InvalidateRect(hWnd, &rect, FALSE);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}

	case WM_LBUTTONDOWN: // ”даление шарика, если попал по нему, левой кнопкой мыши.
	{		
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		ball.erase( //Ўарик удал€етс€, если координаты мыши совпали с 
			std::remove_if(ball.begin(), ball.end(), 
			[&](const Circle &a)->bool{return ((pow((long double)abs(LOWORD(lParam) - (int)(a.GetPos_X())), 2) + pow((long double)abs(HIWORD(lParam) - (int)(a.GetPos_Y())), 2))) <= pow((long double)a.Get_radius(), 2);}),
			ball.end());
		InvalidateRect(hWnd, &rect, FALSE);
		Sleep(0);
		break;
	}
	case WM_RBUTTONDOWN: // ƒобавление шарика, если попал в пустое место, второй кнопкой мыши.
	{

		//Circle(Point(280, 270), 50, BS_HATCHED, Color(0, 255), HS_DIAGCROSS, Color(0, 0, 255), 3)
		ball.push_back(
			Circle(
			Point((LOWORD(lParam)), (HIWORD(lParam))),
			(unsigned int)rand() % 25,
			BS_HATCHED, Color(rand() % 255, rand() % 255, rand() % 255), HS_DIAGCROSS, Color(rand() % 255, rand() % 255, rand() % 255), 3)
			);
		InvalidateRect(hWnd, &rect, FALSE);
		Sleep(0);
		break;
	}
	case WM_SIZE:
	{
		GetClientRect(hWnd, &rect);
		InvalidateRect(hWnd, &rect, FALSE);
		break;
	}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// –азобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	
	case WM_PAINT:
	{

		hdc = BeginPaint(hWnd, &ps);

		////////////////////////////
		memory_HDC = CreateCompatibleDC(hdc);
		memory_bitmap = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
		int savedDC = SaveDC(memory_HDC);
		SelectObject(memory_HDC, memory_bitmap);
		////////////////////////////

		// TODO: добавьте любой код отрисовки...
		
		for each(auto ball_iter in ball)
		{
			//”словие, если шарик вылетит за границы: восток и юг
			if ((ball_iter.GetPos_X() >= (rect.right - rect.left)) || ball_iter.GetPos_Y() >= (rect.bottom - rect.top))
			{
				if (ball_iter.GetPos_X() >= (rect.right - rect.left)) //условие, если шарик выделел по оси "x" вправо
				{
					ball_iter.Set_Vx((ball_iter.Get_Vx()));
					ball_iter.Set_Vy((ball_iter.Get_Vy()));
					//ball[i].SetPos_X(0);
					//ball[i].SetPos_Y(rect.bottom - ball[i].GetPos_Y());
				}
				else if (ball_iter.GetPos_Y() >= (rect.bottom - rect.top)) //условие, если шарик выделел по оси "y" вниз
				{
					ball_iter.Set_Vx((ball_iter.Get_Vx()));
					ball_iter.Set_Vy((ball_iter.Get_Vy()));
					//ball[i].SetPos_X(rect.right - ball[i].GetPos_X());
					//ball[i].SetPos_Y(0);
				}
			}
			//”словие, если шарик находитс€ в рамках окна
			else if ((ball_iter.GetPos_X() <= (rect.right - rect.left)) || ball_iter.GetPos_Y() <= (rect.bottom - rect.top))
			{
				if (ball_iter.GetPos_X() <= 0) //условие, если шарик выделел по оси "x" влево
				{
					ball_iter.Set_Vx((ball_iter.Get_Vx()));
					ball_iter.Set_Vy((ball_iter.Get_Vy()));
					//ball[i].SetPos_X(rect.right - rect.left);
					//ball[i].SetPos_Y(rect.bottom - ball[i].GetPos_Y());
				}
				else if (ball_iter.GetPos_Y() <= 0) //условие, если шарик выделел по оси "y" вверх
				{
					ball_iter.Set_Vx((ball_iter.Get_Vx()));
					ball_iter.Set_Vy((ball_iter.Get_Vy()));
					//ball[i].SetPos_X(rect.right - ball[i].GetPos_X());
					//ball[i].SetPos_Y(rect.bottom - rect.top);
				}
			}
			ball_iter.Draw(memory_HDC);
		}
		
		////////////////////////////
		BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom + rect.left, memory_HDC, 0, 0, SRCCOPY);
		RestoreDC(memory_HDC, savedDC);
		DeleteObject(memory_bitmap);
		DeleteDC(memory_HDC);
		DeleteDC(hdc);
		////////////////////////////

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CLOSE:
	case WM_DESTROY:
		KillTimer(hWnd, timer);
		CloseHandle(hThread);
		ball.erase(ball.begin(), ball.end());
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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

unsigned __stdcall Thread1(void* param)
{
	const double dt = 0.02;
	std::vector<Circle>* _ball = (std::vector<Circle>*)param;
	static double a, ax, ay, dx, dy, r, rr;
	//важно провести вычисление каждый с каждым
	for (int i = 0; i < (_ball)->size(); i++)
		for (int j = 0; j < (_ball)->size(); j++)
		{
			if (i == j) continue;

			dx = _ball->at(j).GetPos_X() - _ball->at(i).GetPos_X();
			dy = _ball->at(j).GetPos_Y() - _ball->at(i).GetPos_Y();

			rr = dx * dx + dy * dy;
			if (rr < 0.1) rr = 0.1; //избегаем делени€ на очень маленькое число
			a = ((rr - 1) * (_ball)->at(j).Get_Mass()) / rr;

			r = sqrt(rr);

			ax = a * (dx / r);
			ay = a * (dy / r);

			_ball->at(i).Set_Vx(_ball->at(i).Get_Vx()+(ax*dt));
			_ball->at(i).Set_Vy(_ball->at(i).Get_Vy()+(ay*dt));
		}
	for (int i = 0; i < (_ball)->size(); i++)
	{
		//Ќовое положение точки = старое положение точки + (скорость * шаг_вычислени€): v = ds/dt -> ds = v*dt
		(_ball)->at(i).SetPos_X((_ball)->at(i).GetPos_X() + ((_ball)->at(i).Get_Vx()*dt));
		(_ball)->at(i).SetPos_Y((_ball)->at(i).GetPos_Y() + ((_ball)->at(i).Get_Vy()*dt));		
	}

	return 0;
}

