#ifndef C_PANELMANAGER_H
#define C_PANELMANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

void DearImKit_AddPanel(const char* name, int (*draw)(void*), void* state);

void DearImKit_QueueError(const char* panel_name, const char* title, const char* message);

#ifdef __cplusplus
}
#endif

#endif
