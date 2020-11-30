// CP_1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "CP_1.h"

#define MAX_LOADSTRING 100

//1.+++
#define ACTION_MENU_START 201
#define ACTION_MENU_STOP  202
#define TIMER_TEXT 301

void CreateMyMenu(HWND hWnd);

int x = 10;
int y = 10;

HMENU hMainMenu;
HDC hdc;
BOOL textCreated = FALSE;
HCURSOR hCurs;
//1.---

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.
    

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CP1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CP1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    //1.+++
    wcex.hIcon          = LoadIcon(nullptr, IDI_ASTERISK);
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    //1.---
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CP1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_WINLOGO));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    //1.+++
    case WM_CREATE:
        {
        CreateMyMenu(hWnd);
        break;
        }
    //1.---
    case WM_COMMAND:
        {
            //1.+++
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case ACTION_MENU_START:
                textCreated = true;
                SetTimer(hWnd, TIMER_TEXT, 50, NULL);
                break;
            case ACTION_MENU_STOP:
                KillTimer(hWnd, TIMER_TEXT);
                break;
            //1.---
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            //1.+++
            if (textCreated) {
                TextOut(hdc, x, y, L"HELP!", 5);
            }
            //1.---
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_TIMER:
        {
        switch (wParam) {
        //1.+++
        case TIMER_TEXT:
            x++;
            y++;
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        }
        //1.---
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

// 1.+++
void CreateMyMenu(HWND hWnd) 
{ 
    hMainMenu = CreateMenu();
    
    HMENU hActionMenu = CreateMenu();
    AppendMenu(hActionMenu, MF_STRING, ACTION_MENU_START,  _T("Старт"));
    AppendMenu(hActionMenu, MF_STRING, ACTION_MENU_STOP, _T("Стоп"));

    AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR)hActionMenu , _T("Действия"));

    SetMenu(hWnd, hMainMenu);
}

// 1.---
