#ifndef C_PANELMANAGER_H
#define C_PANELMANAGER_H

extern "C" {

void DearImKit_AddPanel(const char* name, bool (*draw)(void*), void* state);

}

#endif
