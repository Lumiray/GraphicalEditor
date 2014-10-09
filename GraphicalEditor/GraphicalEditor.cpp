// GraphicalEditor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Commdlg.h"
#include "GraphicalEditor.h"
#include "ShellAPI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
BOOL isDrawing = FALSE; 
POINT startPoint; 
Shape* shape;
COLORREF color;
int penWidth;
OPENFILENAME openFileName;
HDC memoryDC;
HDC metafileDC;
HBITMAP hBitmap;
RECT rect;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
HDC					InitialiseEnhMetafileDC(HWND hWnd);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GRAPHICALEDITOR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	color = RGB(0, 0, 0);
	penWidth = 1;
	shape = new Pen(color, penWidth);

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHICALEDITOR));
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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHICALEDITOR));
	wcex.hCursor		= LoadCursor(NULL, IDC_CROSS);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GRAPHICALEDITOR);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 900, 600, NULL, NULL, hInstance, NULL);

   openFileName.hInstance = hInst;
   DragAcceptFiles(hWnd, true);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HDC InitialiseEnhMetafileDC(HWND hWnd)
{
	HDC windowDC = GetDC(hWnd);
	RECT newRect;

	int iWidthMM = GetDeviceCaps(windowDC, HORZSIZE); 
	int iHeightMM = GetDeviceCaps(windowDC, VERTSIZE); 
	int iWidthPels = GetDeviceCaps(windowDC, HORZRES); 
	int iHeightPels = GetDeviceCaps(windowDC, VERTRES); 

	newRect.left = (rect.left * iWidthMM * 100)/iWidthPels; 
	newRect.top = (rect.top * iHeightMM * 100)/iHeightPels; 
	newRect.right = (rect.right * iWidthMM * 100)/iWidthPels; 
	newRect.bottom = (rect.bottom * iHeightMM * 100)/iHeightPels;
	metafileDC = CreateEnhMetaFile(windowDC, NULL, &newRect, NULL);

	ReleaseDC(hWnd, windowDC);
	return metafileDC;
}

HENHMETAFILE RefreshMetafileDC(HWND hWnd)
{
	HDC windowDC = GetDC(hWnd);
	HENHMETAFILE metafileHandler = CloseEnhMetaFile(metafileDC);
	ReleaseDC (hWnd, metafileDC);
	metafileDC = InitialiseEnhMetafileDC(hWnd);
	return metafileHandler;
}

COLORREF GetColor(HWND hwnd)
{
	CHOOSECOLOR chooseColor;                 
	static COLORREF crCustClr[16];     

	ZeroMemory(&chooseColor, sizeof(chooseColor));
	chooseColor.lStructSize = sizeof(chooseColor);
	chooseColor.hwndOwner = hwnd;
	chooseColor.lpCustColors = (LPDWORD) crCustClr;
	chooseColor.rgbResult = RGB(0, 0, 0);
	chooseColor.Flags = CC_FULLOPEN | CC_RGBINIT;
	if (ChooseColor(&chooseColor))
		return chooseColor.rgbResult;
	return NULL;
}

VOID ClearWindow(HDC windowDC)
{
	FillRect(windowDC, &rect, (HBRUSH)(COLOR_WINDOW+1));
}

VOID RefreshWindow(HWND hWnd)
{
	HDC windowDC = GetDC(hWnd);
	HENHMETAFILE currentImage = RefreshMetafileDC(hWnd);

	PlayEnhMetaFile(windowDC, currentImage, &rect);
	PlayEnhMetaFile(metafileDC, currentImage, &rect);
	DeleteEnhMetaFile(currentImage);
	ReleaseDC(hWnd, windowDC);
}

VOID SaveMetafile(HWND hWnd)
{ 
	HDC windowDC = GetDC(hWnd);
	HENHMETAFILE currentImage = RefreshMetafileDC(hWnd);
	GetClientRect(hWnd, &rect);
	// Determine the picture frame dimensions.   
	int iWidthMM = GetDeviceCaps(windowDC, HORZSIZE); 
	int iHeightMM = GetDeviceCaps(windowDC, VERTSIZE); 
	int iWidthPels = GetDeviceCaps(windowDC, HORZRES); 
	int iHeightPels = GetDeviceCaps(windowDC, VERTRES); 
	GetClientRect(hWnd, &rect); 
	rect.left = (rect.left * iWidthMM * 100)/iWidthPels; 
	rect.top = (rect.top * iHeightMM * 100)/iHeightPels; 
	rect.right = (rect.right * iWidthMM * 100)/iWidthPels; 
	rect.bottom = (rect.bottom * iHeightMM * 100)/iHeightPels; 
	TCHAR szFilter[MAX_LOADSTRING];
	LoadString(hInst, IDS_FILTERSTRING,(LPWSTR)szFilter, sizeof(szFilter)); 
	for (int i=0; szFilter[i]!='\0'; i++) 
	{
		if (szFilter[i] == '%') 
            szFilter[i] = '\0'; 
	}
	TCHAR szFile[MAX_LOADSTRING];
	TCHAR szFileTitle[MAX_LOADSTRING];
	TCHAR szDefExt[MAX_LOADSTRING];
	LoadString(hInst, IDS_DEFEXTSTRING, (LPTSTR)szDefExt, sizeof(szFilter)); 
	szFile[0] = '\0';  
	openFileName.lStructSize = sizeof(OPENFILENAME); 
	openFileName.hwndOwner = hWnd; 
	openFileName.lpstrFilter = szFilter;
	openFileName.lpstrFile= szFile; 
	openFileName.nMaxFile = sizeof(szFile)/ sizeof(*szFile); 
	openFileName.lpstrFileTitle = szFileTitle; 
	openFileName.nMaxFileTitle = sizeof(szFileTitle); 
	openFileName.lpstrInitialDir = (LPWSTR)NULL; 
	openFileName.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT; 
	openFileName.lpstrDefExt = szDefExt;

	TCHAR szDescription[MAX_LOADSTRING];
	LoadString(hInst, IDS_DESCRIPTIONSTRING, 
     (LPWSTR)szDescription, sizeof(szDescription)); 

	for (int i = 0; szDescription[i]!='\0'; i++) 
	{
		if (szDescription[i] == '%') 
				szDescription[i] = '\0'; 
	}
 
	GetSaveFileName(&openFileName); 
	HDC newMetafileDC = CreateEnhMetaFile(windowDC, (LPTSTR) openFileName.lpstrFile, &rect, (LPWSTR)szDescription);
	GetClientRect(hWnd, &rect); 
	PlayEnhMetaFile(newMetafileDC, currentImage, &rect);
	currentImage = CloseEnhMetaFile(newMetafileDC);
	PlayEnhMetaFile(metafileDC, currentImage, &rect);
	ReleaseDC(hWnd, newMetafileDC);
	DeleteEnhMetaFile(currentImage);
}

VOID OpenMetafile(HWND hWnd)
{
	TCHAR szFilter[MAX_LOADSTRING];
	TCHAR szDefExt[MAX_LOADSTRING];
	TCHAR szFile[MAX_LOADSTRING];
	TCHAR szFileTitle[MAX_LOADSTRING];
	LoadString(hInst, IDS_FILTERSTRING,(LPWSTR)szFilter, sizeof(szFilter)); 
	for (int i=0; szFilter[i]!='\0'; i++) 
	{
		if (szFilter[i] == '%') 
            szFilter[i] = '\0'; 
	}
	LoadString(hInst, IDS_DEFEXTSTRING, (LPTSTR)szDefExt, sizeof(szFilter)); 
	szFile[0] = '\0'; 
	szFileTitle[0] = '\0';
	openFileName.lStructSize = sizeof(OPENFILENAME); 
	openFileName.hwndOwner = hWnd;  
	openFileName.lpstrFilter = szFilter;
	openFileName.lpstrCustomFilter = (LPWSTR)NULL; 
	openFileName.nMaxCustFilter = 0L; 
	openFileName.nFilterIndex = 1L; 
	openFileName.lpstrFile = szFile; 
	openFileName.nMaxFile = MAX_LOADSTRING; 
	openFileName.lpstrFileTitle = szFileTitle; 
	openFileName.nMaxFileTitle = MAX_LOADSTRING; 
	openFileName.lpstrInitialDir = (LPWSTR) NULL; 
	openFileName.lpstrTitle = (LPWSTR)NULL; 
	openFileName.Flags = OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; 
	openFileName.nFileOffset = 0; 
	openFileName.nFileExtension = 0; 
	openFileName.lpstrDefExt = szDefExt;

	GetOpenFileName(&openFileName);
	HDC windowDC = GetDC(hWnd);
	HENHMETAFILE hemf = GetEnhMetaFile(openFileName.lpstrFile);  
	GetClientRect(hWnd, &rect); 
	ClearWindow(windowDC);
	RefreshMetafileDC(hWnd);
	PlayEnhMetaFile(windowDC, hemf, &rect);
	PlayEnhMetaFile(metafileDC, hemf, &rect);
	ReleaseDC(hWnd, windowDC); 
	DeleteEnhMetaFile(hemf);
}

void OpenDropedFile(HWND hWnd, HDROP hDropInfo)
{
	TCHAR szFileName[MAX_PATH];
	DragQueryFile (hDropInfo, 0, szFileName, MAX_PATH);
	HDC windowDC = GetDC(hWnd);
	HENHMETAFILE hemf = GetEnhMetaFile(szFileName);  
	GetClientRect(hWnd, &rect); 
	ClearWindow(windowDC);
	RefreshMetafileDC(hWnd);
	PlayEnhMetaFile(windowDC, hemf, &rect);
	PlayEnhMetaFile(metafileDC, hemf, &rect);
	ReleaseDC(hWnd, windowDC); 
	DeleteEnhMetaFile(hemf);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	PAINTSTRUCT ps;
	HDC windowDC;
	POINT tempPoint;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_EXIT:
			CloseEnhMetaFile(metafileDC);
			DestroyWindow(hWnd);
			break;
		case IDM_SAVE:
			SaveMetafile(hWnd);
			break;
		case IDM_OPEN:
			OpenMetafile(hWnd); 
			break;
		case IDM_PEN:
			shape->~Shape();
			shape = new Pen(color, penWidth);
			break;
		case IDM_ELLIPSE:
			shape->~Shape();
			shape = new EllipseShape(color, penWidth);
			break;
		case IDM_RECTANGLE:
			shape->~Shape();
			shape = new RectangleShape(color, penWidth);
			break;
		case IDM_COLOR:
			COLORREF chosenColor;
			if (chosenColor = GetColor(hWnd))
				color = chosenColor; 
			shape->SetPenColor(color);
			break;
		case IDM_PENWIDTH_1:
			penWidth = 1;
			shape->SetPenWidth(penWidth);
			break;
		case IDM_PENWIDTH_2:
			penWidth = 2;
			shape->SetPenWidth(penWidth);
			break;
		case IDM_PENWIDTH_4:
			penWidth = 4;
			shape->SetPenWidth(penWidth);
			break;
		case IDM_PENWIDTH_8:
			penWidth = 8;
			shape->SetPenWidth(penWidth);
			break;
		case IDM_PENWIDTH_12:
			penWidth = 12;
			shape->SetPenWidth(penWidth);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_CREATE:
		GetClientRect(hWnd, &rect);
		metafileDC = InitialiseEnhMetafileDC(hWnd);
		break;

	case WM_DROPFILES:
		OpenDropedFile(hWnd, (HDROP) wParam);
		break;

	case WM_LBUTTONDOWN: 
		isDrawing = TRUE; 
		startPoint.x = LOWORD(lParam); 
		startPoint.y = HIWORD(lParam); 
		shape->SetStartPoint(startPoint);
		break; 

	case WM_LBUTTONUP: 
		if (isDrawing) 
		{ 
			windowDC = GetDC(hWnd);
			shape->Draw(windowDC, startPoint, lParam);
			shape->Draw(metafileDC, startPoint, lParam);
			ReleaseDC(hWnd, windowDC); 
		} 
		isDrawing = FALSE; 
		UpdateWindow(hWnd);
		break; 
 
	case WM_MOUSEMOVE: 
		if (isDrawing) 
		{ 
			windowDC = GetDC(hWnd);
			if (shape->isContinuous)
			{
				tempPoint = shape->GetStartPoint();
				shape->Draw(metafileDC, startPoint, lParam);
				shape->SetStartPoint(tempPoint);
				shape->Draw(windowDC, startPoint, lParam);
			}
			ReleaseDC(hWnd, windowDC); 
			UpdateWindow(hWnd);
			PostMessage(hWnd, WM_PAINT, NULL, NULL);
		} 
		break; 

	case WM_SIZE:
		RefreshWindow(hWnd);
		break;

	case WM_PAINT:
		windowDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(metafileDC);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
