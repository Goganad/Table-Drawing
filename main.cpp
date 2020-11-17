#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>
#include "TableCell.h"

using namespace std;
using namespace Gdiplus;

const SIZE MIN_WINDOW_SIZE = SIZE{400, 350};
const SIZE FIRST_WINDOW_SIZE = SIZE{800, 600};
const COLORREF BACKGROUND_COLOR = RGB(255, 255, 255);
const INT COL_COUNT = 6;

vector<wstring> strings;

vector<TableCell> getCellsPositions(Graphics *graphics, const Font &font, RectF drawRect) {
    REAL cellWidth = drawRect.Width / (REAL) COL_COUNT;

    vector<TableCell> cells = {};

    for (const wstring &string: strings) {
        TableCell cell = TableCell(graphics, string, font, cellWidth, drawRect.Height);
        cells.emplace_back(cell);
    }

    int emptyCellsCount = (int)strings.size() % COL_COUNT;
    for (int i = 0; i < emptyCellsCount; ++i) {
        TableCell cell = TableCell(graphics, L"", font, cellWidth, drawRect.Height);
        cells.emplace_back(cell);
    }

    int rowCount = (int)cells.size() / COL_COUNT;
    REAL rowHeights[rowCount];
    for (int i = 0; i < rowCount; ++i) {
        REAL maxHeight = 0;
        for (int j = 0; j < COL_COUNT; ++j) {
            REAL height = cells[i * COL_COUNT + j].bounds.Height;
            if (height > maxHeight) {
                maxHeight = height;
            }
        }
        rowHeights[i] = maxHeight;

        for (int j = 0; j < COL_COUNT; ++j) {
            cells[i * COL_COUNT + j].bounds.Height = rowHeights[i];
        }

        REAL offsetY = 0;
        for (int q = 0; q < i; ++q) {
            offsetY += rowHeights[q];
        }

        for (int j = 0; j < COL_COUNT; ++j) {
            cells[i * COL_COUNT + j].bounds.X = drawRect.X + cellWidth * (REAL)j;
            cells[i * COL_COUNT + j].bounds.Y = drawRect.Y + offsetY;
        }
    }
    return cells;
}

void drawCells(Graphics *graphics, const vector<TableCell> &cells, const Font &font) {
    for (const TableCell &cell: cells) {
        Pen pen(Color::Black, 2);
        SolidBrush solidBrush(Color::Black);
        graphics->DrawString(cell.string.c_str(), -1, &font, cell.bounds, nullptr, &solidBrush);
        graphics->DrawRectangle(&pen, cell.bounds);
    }
}

void draw(Gdiplus::Graphics *graphics, Gdiplus::RectF drawRect) {
    if (!strings.empty()) {
        FontFamily fontFamily = Gdiplus::FontFamily(L"Comic Sans MS");
        REAL fontSize = 12;
        FontStyle fontStyle = Gdiplus::FontStyleBold;
        Unit fontUnit = Gdiplus::UnitPoint;
        Font font = Gdiplus::Font(&fontFamily, fontSize, fontStyle, fontUnit);

        drawCells(graphics, getCellsPositions(graphics, font, drawRect), font);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Isolation\nTrepidation\nDon't fear nothing\nSnake is bluffing");
    strings.emplace_back(L"Whips his tail\nSends you running");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Vegetation\nAggravation\nFound him hiding\nSnake is smiling");
    strings.emplace_back(L"Whips his tail\nLeaves you riling");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Hibernation\nAltercation\nDon't get angry\nSnake is cranky");
    strings.emplace_back(L"Whips his tail\nIn a frenzy");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");
    strings.emplace_back(L"Rattlesnake, rattlesnake\nRattlesnake, rattles me");

    const wchar_t WINDOW_CLASS[] = L"MAIN_WINDOW_CLASS";
    const wchar_t WINDOW_TITLE[] = L"Table Drawing";

    WNDCLASSEXW wc;
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(BACKGROUND_COLOR);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = WINDOW_CLASS;
    wc.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);

    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(
            0x0,
            WINDOW_CLASS,
            WINDOW_TITLE,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, FIRST_WINDOW_SIZE.cx, FIRST_WINDOW_SIZE.cy,
            nullptr,
            nullptr,
            hInstance,
            nullptr
    );

    if (hwnd == nullptr) {
        MessageBoxW(nullptr, L"Error creating window", L"Attention", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            RECT rcClientRect;
            GetClientRect(hwnd, &rcClientRect);

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            Graphics graphics = Graphics(hdc);

            LONG edgeOffset = 5;
            LONG tableWidth = rcClientRect.right - rcClientRect.left - edgeOffset * 2;
            LONG tableHeight = rcClientRect.bottom - rcClientRect.top - edgeOffset * 2;

            RectF clientRectF(edgeOffset, edgeOffset, tableWidth, tableHeight);
            draw(&graphics, clientRectF);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        case WM_GETMINMAXINFO: {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
            lpMMI->ptMinTrackSize.x = MIN_WINDOW_SIZE.cx;
            lpMMI->ptMinTrackSize.y = MIN_WINDOW_SIZE.cy;
            break;
        }
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    return 0;
}
