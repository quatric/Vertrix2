#ifndef V3_WIN32_H
#define V3_WIN32_H

#include "process.h"

/* Shared between the modules in vertrix3/win32. */

typedef struct
{
    V3Event *event;
} V3EventObject;

uint32_t v3_main_window(void);
void v3_post_message(uint32_t hwnd, uint32_t message, uint32_t wparam, uint32_t lparam);

#endif
