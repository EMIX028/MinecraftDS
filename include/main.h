#include <stdint.h>
#include <stdbool.h>
#include "ChunkStruct.h"
#include <malloc.h>

#define GRAVITY 0.008f
#define DISPLAY_DISTANCE 30

void subscreenAff(char *pseudo,struct mallinfo info);

void setCam();

void ApplyGravity(chunk_t *chunk_list[],int size);

void updatePerformance(void);