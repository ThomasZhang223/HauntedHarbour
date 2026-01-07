// HauntedHarbour_GD.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "HauntedHarbour_GD.h"
#include "GraphicsObject.h"
#include "PlayerObject.h"
#include "BackgroundObject.h"
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "EnemyObject.h"
#include "LifeBar.h"
#include <stdio.h>

#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

int numBlocks = 0;
int numEnemies = 0;

int windowWidth = 700;
int windowHeight = 580;
int mapPosition = 0;
HDC offScreenDC;

bool bGameStart = false;

// Our objects
PlayerObject viktor;
BackgroundObject backdrop("../pics/Background3.jpg", 0, 0, 5118, 800, 0.2);
BackgroundObject ground("../pics/Ground.bmp", 0, GROUND, 774, 128, 1);
BackgroundObject titleScreen("../pics/TitleScreen.jpg", 0, 0, windowWidth, 550, 0);
GraphicsObject* blocks[100];
EnemyObject* enemies[100];
LifeBar lifeBar(&viktor);


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                SetScreen();
void                DrawScreen(HWND hWnd);
void                LoadMap();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HAUNTEDHARBOURGD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HAUNTEDHARBOURGD));

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

    return (int) msg.wParam;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HAUNTEDHARBOURGD));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HAUNTEDHARBOURGD);
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
      CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   } 
   
   SetScreen();

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
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_RIGHT:
            if (viktor.IsJumping() == true)
            {
                viktor.picY = 86;
                viktor.xSpeed = 10;
                viktor.state = JUMP_RIGHT;
            }
            else
            {
                viktor.SetMoveRight();
            }
            viktor.bIsStoppedRight = false;
            break;
        case VK_LEFT:
            if (viktor.IsJumping() == true)
            {
                viktor.picY = 146;
                viktor.xSpeed = -10;
                viktor.state = JUMP_LEFT;
            }
            else
            {
                viktor.SetMoveLeft();
            }
            viktor.bIsStoppedLeft = false;
            break;
        case VK_UP:
            if (viktor.state == MOVE_RIGHT || viktor.state == STAND_RIGHT)
            {
                viktor.SetJumpRight();
            }
            else if (viktor.state == MOVE_LEFT || viktor.state == STAND_LEFT)
            {
                viktor.SetJumpLeft();
            }
            break;
        case VK_SPACE:
            if (viktor.state == STAND_RIGHT)
            {
                viktor.SetShootRight();
            }
            else if (viktor.state == STAND_LEFT)
            {
                viktor.SetShootLeft();
            }

            if (viktor.state == SHOOT_RIGHT ||
                viktor.state == MOVE_RIGHT ||
                viktor.state == JUMP_RIGHT ||
                viktor.state == STAND_RIGHT)
            {
                viktor.FireBullets(viktor.xPos + viktor.width - 15, viktor.yPos + 10, 20 + viktor.xSpeed, 0);
            }
            else if (viktor.state == SHOOT_LEFT ||
                viktor.state == MOVE_LEFT ||
                viktor.state == JUMP_LEFT ||
                viktor.state == STAND_LEFT)
            {
                viktor.FireBullets(viktor.xPos, viktor.yPos + 10, -20 + viktor.xSpeed, 0);
            }
            break;
        case VK_RETURN:
            if (bGameStart == false)
            {
                bGameStart = true;

                // 50-millisecond timer
                SetTimer(hWnd, 1, 50, NULL);

                LoadMap();
            }
            break;
        }  
        break;
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_RIGHT:
            if (viktor.IsJumping() == false)
            {
                viktor.SetStandRight();
            }
            viktor.bIsStoppedRight = true;
            break;
        case VK_LEFT:
            if (viktor.IsJumping() == false)
            {
                viktor.SetStandLeft();
            }
            viktor.bIsStoppedLeft = true;
            break;
        case VK_SPACE:
            if (viktor.state == SHOOT_RIGHT)
            {
                viktor.SetStandRight();
            }
            else if (viktor.state == SHOOT_LEFT)
            {
                viktor.SetStandLeft();
            }
            break;
        }
        break;
    case WM_TIMER:
        viktor.Move();
        viktor.MoveBullets();
        
        for (int i = 0; i < numEnemies; i++)
        {
            enemies[i]->Move();
            enemies[i]->MoveBullets();

            if (enemies[i]->bIsAlive == true)
            {
                viktor.CheckBulletCollisionWithEntity(enemies[i]);
                enemies[i]->CheckBulletCollisionWithEntity(&viktor);
            }

            for (int j = 0; j < numBlocks; j++)
            {
                enemies[i]->CheckCollisionWithBlock(blocks[j]);
            }
        }

        for (int i = 0; i < numBlocks; i++)
        {
            // no ampersand for arrays
            // array 'container' holds a group of pointers
            viktor.CheckCollisionWithBlock(blocks[i]);
            viktor.CheckBulletCollisionWithBlock(blocks[i]);
        }

        PostMessage(hWnd, WM_PAINT, 0, 0);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            if (bGameStart == true)
            {
                backdrop.Draw(offScreenDC);
                ground.Draw(offScreenDC);
                viktor.Draw(offScreenDC);
                viktor.DrawBullets(offScreenDC);
                lifeBar.Draw(offScreenDC);

                for (int i = 0; i < numEnemies; i++)
                {
                    enemies[i]->Draw(offScreenDC);
                    enemies[i]->DrawBullets(offScreenDC);
                }

                for (int i = 0; i < numBlocks; i++)
                {
                    blocks[i]->Draw(offScreenDC);
                }
            }
            else
            {
                titleScreen.Draw(offScreenDC);
            }

            DrawScreen(hWnd);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        for (int i = 0; i < numEnemies; i++)
        {
            delete enemies[i];
        }
        for (int i = 0; i < numBlocks; i++)
        {
            delete blocks[i];
        }

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

void SetScreen()
{
    HDC _hTempDC;
    HBITMAP _offScreenBMP;

    _hTempDC = GetDC(0);

    // Initialize buffer image
    offScreenDC = CreateCompatibleDC(_hTempDC);
    // TODO: Confirm 800, 600
    _offScreenBMP = CreateCompatibleBitmap(_hTempDC, 800, 600);

    SelectObject(offScreenDC, _offScreenBMP);

    ReleaseDC(0, _hTempDC);
}

// This method passes in the windowm to draw the background image to
void DrawScreen(HWND hWnd)
{
    HDC _screenDC;
    _screenDC = GetDC(hWnd);

    TransparentBlt(
        _screenDC,		    // Destination DC
        0,	                // x position of the Destination DC
        0,					// y position of the Destination DC
        windowWidth,		// width of the Destination DC
        windowHeight,		// height of the Destination DC
        offScreenDC,        // Source DC
        0,					// x position of the Source DC
        0,					// y position of the Source DC
        windowWidth,		// width of the Source DC
        windowHeight,		// height of the Source DC
        RGB(255, 174, 201)  // pink as transparency color
    );

    DeleteDC(_screenDC);
}

void LoadMap()
{
    FILE* _level;
    char _fileBuffer[25]; // max amount of characters allowed for the filepath
    
    int _currentLevel = 1;
    
    char _section[80];
    int _index = 0;
    int _xPos = 0;
    int _yPos = 0;

    // use the file buffer to find the filepath (also use an escape character %d for an integer)
    sprintf_s(_fileBuffer, _countof(_fileBuffer), "../Levels/Level%d.txt", _currentLevel);

    fopen_s(&_level, _fileBuffer, "r");

    while (true)
    {
        fscanf_s(_level, "%s", _section, _countof(_section));

        if (strcmp(_section, "[Viktor]") == 0) // if this string is read correctly
        {
            while (true)
            {
                fscanf_s(_level, "%d %d %d", &_index, &_xPos, &_yPos);

                if (_index == -1)
                {
                    break;
                }

                viktor.xPos = _xPos;
                viktor.yPos = _yPos;
            }
        }

        if (strcmp(_section, "[Little-Block]") == 0)
        {
            while (true)
            {
                fscanf_s(_level, "%d %d %d", &_index, &_xPos, &_yPos);

                if (_index == -1)
                {
                    break;
                }

                blocks[numBlocks] = new GraphicsObject("../Pics/SmallCrate.bmp", _xPos, _yPos, 32, 32);
                numBlocks++;
            }
        }

        if (strcmp(_section, "[Big-Block]") == 0)
        {
            while (true)
            {
                fscanf_s(_level, "%d %d %d", &_index, &_xPos, &_yPos);

                if (_index == -1)
                {
                    break;
                }

                blocks[numBlocks] = new GraphicsObject("../Pics/Crate.bmp", _xPos, _yPos, 64, 64);
                numBlocks++;
            }
        }

        if (strcmp(_section, "[Flying-Enemy]") == 0)
        {
            while (true)
            {
                fscanf_s(_level, "%d %d %d", &_index, &_xPos, &_yPos);

                if (_index == -1)
                {
                    break;
                }

                enemies[numEnemies] = new FlyingEnemy(&viktor, _xPos, _yPos);
                enemies[numEnemies]->xPos = _xPos;
                enemies[numEnemies]->yPos = _yPos;
                numEnemies++;
            }
        }

        if (strcmp(_section, "[Ground-Enemy]") == 0)
        {
            while (true)
            {
                fscanf_s(_level, "%d %d %d", &_index, &_xPos, &_yPos);

                if (_index == -1)
                {
                    break;
                }

                enemies[numEnemies] = new GroundEnemy();
                enemies[numEnemies]->xPos = _xPos;
                enemies[numEnemies]->yPos = _yPos;
                numEnemies++;
            }
        }

        if (strcmp(_section, "[End]") == 0)
        {
            break; // end of document: exit the while loop
        }
    }

    fclose(_level);
}
