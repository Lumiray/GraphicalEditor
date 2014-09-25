// GraphicalEditor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Commdlg.h"
#include "GraphicalEditor.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
BOOL isDrawing = FALSE; 
POINT startPoint; 
Shape* shape;
COLORREF color = RGB(0, 0, 0);
int penWidth = 1;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHICALEDITOR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GRAPHICALEDITOR);
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
      CW_USEDEFAULT, 0, 700, 500, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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

HDC CreateMetafile(HDC hdc, HWND hWnd)
{ 
	// Determine the picture frame dimensions.   
	int iWidthMM = GetDeviceCaps(hdc, HORZSIZE); 
	int iHeightMM = GetDeviceCaps(hdc, VERTSIZE); 
	int iWidthPels = GetDeviceCaps(hdc, HORZRES); 
	int iHeightPels = GetDeviceCaps(hdc, VERTRES);  
	// Retrieve the coordinates of the client  
	// rectangle, in pixels.  
	RECT rect;
	GetClientRect(hWnd, &rect); 
 
	//// Convert client coordinates to .01-mm units.  
	//// Use iWidthMM, iWidthPels, iHeightMM, and  
	//// iHeightPels to determine the number of  
	//// .01-millimeter units per pixel in the x-  
	////  and y-directions.  
	//rect.left = (rect.left * iWidthMM * 100)/iWidthPels; 
	//rect.top = (rect.top * iHeightMM * 100)/iHeightPels; 
	//rect.right = (rect.right * iWidthMM * 100)/iWidthPels; 
	//rect.bottom = (rect.bottom * iHeightMM * 100)/iHeightPels; 
 //
	//// Load the filename filter from the string table.   
	//LoadString(hInst, IDS_FILTERSTRING, 
	//	 (LPSTR)szFilter, sizeof(szFilter)); 
 //
	//// Replace the '%' separators that are embedded  
	//// between the strings in the string-table entry  
	//// with '\0'.  
 //
	//for (i=0; szFilter[i]!='\0'; i++) 
	//	if (szFilter[i] == '%') 
	//			szFilter[i] = '\0'; 
 //
	//// Load the dialog title string from the table.  
 //
	//LoadString(hInst, IDS_TITLESTRING, 
	//	 (LPSTR)szTitle, sizeof(szTitle)); 
 //
	//// Initialize the OPENFILENAME members.  
 //
	//szFile[0] = '\0'; 
 //
	//Ofn.lStructSize = sizeof(OPENFILENAME); 
	//Ofn.hwndOwner = hWnd; 
	//Ofn.lpstrFilter = szFilter; 
	//Ofn.lpstrFile= szFile; 
	//Ofn.nMaxFile = sizeof(szFile)/ sizeof(*szFile); 
	//Ofn.lpstrFileTitle = szFileTitle; 
	//Ofn.nMaxFileTitle = sizeof(szFileTitle); 
	//Ofn.lpstrInitialDir = (LPSTR)NULL; 
	//Ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT; 
	//Ofn.lpstrTitle = szTitle; 
 //
	//// Display the Filename common dialog box. The  
	//// filename specified by the user is passed  
	//// to the CreateEnhMetaFile function and used to  
	//// store the metafile on disk.  
 //
	//GetSaveFileName(&Ofn); 
 //
	//// Load the description from the string table.  
 //
	//LoadString(hInst, IDS_DESCRIPTIONSTRING, 
	//	 (LPSTR)szDescription, sizeof(szDescription)); 
 //
	//// Replace the '%' string separators that are  
	//// embedded between strings in the string-table  
	//// entry with '\0'.  
 //
	//for (i=0; szDescription[i]!='\0'; i++) 
	//{
	//	if (szDescription[i] == '%') 
	//			szDescription[i] = '\0'; 
	//}
 
	// Create the metafile device context.  
 //
	//return CreateEnhMetaFile(hdc, 
	//		  (LPTSTR) Ofn.lpstrFile, 
	//		  &rect, (LPSTR)szDescription); 
	return NULL;
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
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_PEN:
			shape = new Pen(color, penWidth);
			break;
		case IDM_ELLIPSE:
			shape = new EllipseShape(color, penWidth);
			break;
		case IDM_RECTANGLE:
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
	case WM_LBUTTONDOWN: 
		isDrawing = TRUE; 
		startPoint.x = LOWORD(lParam); 
		startPoint.y = HIWORD(lParam); 
		break; 
	case WM_CREATE: 
		shape = new Pen(color, penWidth);
		break;
	case WM_LBUTTONUP: 
		if (isDrawing) 
		{ 
			hdc = GetDC(hWnd);
			shape->Draw(hdc, startPoint, lParam);
			ReleaseDC(hWnd, hdc); 
		} 
		isDrawing = FALSE; 
		break; 
 
	case WM_MOUSEMOVE: 
		if (isDrawing) 
		{ 
			hdc = GetDC(hWnd); 
			shape->Draw(hdc, startPoint, lParam);
			ReleaseDC(hWnd, hdc); 
			//PostMessage(hWnd, WM_PAINT, NULL, NULL);
		} 
		break; 

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
