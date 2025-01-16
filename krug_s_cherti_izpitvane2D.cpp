// krug_s_cherti_izpitvane2D.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "krug_s_cherti_izpitvane2D.h"
#include <gdiplus.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

int ak = 0;
HDC hdc;
int xend;
int yend;
int centerX = xend / 2; //centura na x
int centerY = yend / 2;// centura na y

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.


    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput,
        NULL);




    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KRUGSCHERTIIZPITVANE2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KRUGSCHERTIIZPITVANE2D));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    GdiplusShutdown(gdiplusToken);

    return (int) msg.wParam;

#pragma comment(lib, "GdiPlus.lib")
}

VOID Venchelistcheta(HDC hdc, int ak, int xend, int yend)
{

    int i = 0;
    Graphics graphics(hdc);  
    graphics.Clear(Color(204, 229, 255));
    int dx = xend / 2;//razpolagane v sredata na x		       
    int dy = yend / 2; //razpolagane v sredata na y		

    //tezi tichki sa za izchertavane na krivoto stublo
    Point p1(xend / 2 + 5, yend / 2 + 5);
    Point p2(xend / 3 - 75, yend / 2 + 25);
    Point p3(xend / 3 - 90, yend / 2 + 50);
    Point p4(xend / 4 - 127, yend / 2 + 400);
    Pen pen(Color(255, 165, 255, 0), 10); //tva 10 oznachava debelina na liniqta za stybloto
    graphics.DrawBezier(&pen, p1, p2, p3, p4); //vikane na funkciq za chertane na stubloto

    for (i = 0; i < ak; i++)
    {
        //tochkite na splaina chertaesht venchelistcheto
        Point p[] = {			
            Point(xend / 2, yend / 2),   
            Point(xend / 2 - 100, 4),    
            Point(xend / 2 + 100, 4),    
            Point(xend / 2, yend / 2),  
        };
        Pen pen(Color(255, 0, 0, 255));

        PointF centre(xend / 2, yend / 2); //pointF zastava v centura
        int angle = i * 30; // ugul na 30 gradusa

        GraphicsPath myPath;

        Gdiplus::Matrix matrix;
        matrix.RotateAt(angle, centre);
        graphics.SetTransform(&matrix);

        myPath.StartFigure();
        myPath.AddBeziers(p, 4);
        SolidBrush Neavybr(Color(255, 255, 255, 255));
        graphics.FillPath(&Neavybr, &myPath);
    }
}

VOID CIRCLE(HDC hdc, int xend, int yend) //izchertava krugcheto na cveteto
{
    Graphics graphics(hdc);
    Rect ellipseRect(xend / 4 + xend / 4 - 40, yend / 2.3, xend / 16, xend / 16);
    SolidBrush yellowPen(Color(255, 255, 255, 0));
    graphics.FillEllipse(&yellowPen, ellipseRect);
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KRUGSCHERTIIZPITVANE2D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KRUGSCHERTIIZPITVANE2D);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps; 
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            RECT rt;
            GetClientRect(hWnd, &rt);

            CIRCLE(hdc, xend, yend);
            Venchelistcheta(hdc, ak, xend, yend);


            InvalidateRect(hWnd, NULL, true); // изчистване на текущия екран
            UpdateWindow(hWnd); // предизвикване на ново изертаване чрез изпращане на съобщение WM_PAINT

            EndPaint(hWnd, &ps); // освобождаване на екрана
        }
        break;

    case WM_RBUTTONDOWN:
    {
        RECT rt;
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        InvalidateRect(hWnd, NULL, true);
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rt);
        Venchelistcheta(hdc, ak, int(rt.right), int(rt.bottom));
        CIRCLE(hdc, int(rt.right), int(rt.bottom));
        if (ak == 12)
            ak = 0;
        else
            ak++;
        EndPaint(hWnd, &ps);
    }
    break;


    case WM_DESTROY:
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
