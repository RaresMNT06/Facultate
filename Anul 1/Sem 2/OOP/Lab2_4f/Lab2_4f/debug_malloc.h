#ifndef DEBUG_MALLOC_H
#define DEBUG_MALLOC_H

#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// Redefinim malloc/calloc pentru a vedea fisierul si linia
#ifndef malloc
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#ifndef calloc
#define calloc(c, s) _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Functia care printeaza bannerul tau personalizat
static inline void finish_memory_debug(void) {
    _CrtMemState state;
    _CrtMemCheckpoint(&state);

    // lCounts[1] corespunde _NORMAL_BLOCK
    if (state.lCounts[1] > 0) {
        printf("\n==========================================\n");
        printf("            AVEM MEMORY LEAK! \n");
        printf("==========================================\n");
        _CrtDumpMemoryLeaks();
        printf("==========================================\n");
    }
    else {
        printf("\nNu s-au detectat memory leaks.\n");
    }
}

static inline void setup_memory_debug() {
    // Redirectionam rapoartele catre consola (STDOUT)
    // Daca tot ai linii rosii sub _CRTDBG_MODE_FILE, poti folosi direct cifrele: 
    // Mode: 0x2 (File), File: (void*)1 (Stdout)
    _CrtSetReportMode(_CRT_WARN, 2);
    _CrtSetReportFile(_CRT_WARN, (void*)1);
    _CrtSetReportMode(_CRT_ERROR, 2);
    _CrtSetReportFile(_CRT_ERROR, (void*)1);

    // Inregistram verificarea automata la final
    atexit(finish_memory_debug);

    printf("Memory tracking activat.\n");
}
#else
static inline void setup_memory_debug() {}
#endif

#endif