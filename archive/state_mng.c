#ifndef __PRG_MNG_H
#define __PRG_MNG_H

#include "stdint.h"

// Publice Types
typedef struct transition {
    const uint8_t (const * condition)(void);
    const state const * goal;
}
typedef struct state_s {
    const transistion const * transition_table[];
} state;

void



#endif