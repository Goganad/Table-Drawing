#ifndef TABLE_DRAWING_TABLECELL_H
#define TABLE_DRAWING_TABLECELL_H

#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <string>

using namespace std;
using namespace Gdiplus;

class TableCell {
public:
    wstring string;
    RectF bounds;

    TableCell(Graphics *graphics, const wstring &str, const Font &font, REAL cellWidth, REAL maxHeight) {
        this->string = str;
        bounds = RectF(0, 0, cellWidth, maxHeight);
        const wchar_t *text = string.c_str();
        graphics->MeasureString(text, -1, &font, bounds, &bounds);
        bounds = RectF(0, 0, cellWidth, bounds.Height);
    }
};


#endif //TABLE_DRAWING_TABLECELL_H
