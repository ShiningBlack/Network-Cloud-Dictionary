#ifndef _UI_H__
#define _UI_H__

#include "core.h"
#include "includes.h"

int InitUI(void);
static void Select_UI(int pos);
static void Cancel_UI(int pos);

int Login_Ui(pack_t *pack);
int Register_Ui(pack_t *pack);
int Search_Ui(pack_t *pack);

#endif