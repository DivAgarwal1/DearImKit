#ifndef C_PANEL_H
#define C_PANEL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DearImKit_Size {
    int width;
    int height;
} DearImKit_Size;

int DearImKit_Begin(const char* panel_name, int* p_open, int flags);

void DearImKit_Image(const char* filename, DearImKit_Size size);

void DearImKit_ImageBackground(const char* filename);

#ifdef __cplusplus
}
#endif

#endif
