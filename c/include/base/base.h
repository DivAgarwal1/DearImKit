#ifndef C_PANEL_H
#define C_PANEL_H

extern "C" {

struct DearImKit_Size {
    int width = -1;
    int height = -1;
};

bool DearImKit_Begin(void* panel, bool* p_open, int flags);

void DearImKit_Image(const char* filename, DearImKit_Size size);

void DearImKit_ImageBackground(const char* filename);

}

#endif
