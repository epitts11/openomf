#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "resources/ids.h"
#include "resources/global_paths.h"
#include "game/utils/settings.h"
#include "utils/log.h"
#include "utils/random.h"

struct music_override_t {
    int id;
    const char *name;
};

int validate_resource_path(char **missingfile) {
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        *missingfile = get_path_by_id(i);
        if(*missingfile != NULL) {
            if(access(*missingfile, F_OK) == -1) {
                return 1;
            }
            free(*missingfile);
        }
    }
    *missingfile = NULL;
    return 0;
}

char* get_path_by_id(int id) {
    const char *path = global_path_get(RESOURCE_PATH);
    const char *filename = get_resource_file(id);
    if(filename != NULL && path != NULL) {
        int len = strlen(path) + strlen(filename) + 1;
        char *out = malloc(len);
        sprintf(out, "%s%s", path, filename);
        return out;
    }
    return NULL;
}

const char* get_resource_file(unsigned int id) {
    // Declare music overrides
    settings *s = settings_get();
    struct music_override_t overrides[] = {
        {PSM_ARENA0, s->sound.music_arena0},
        {PSM_ARENA1, s->sound.music_arena1},
        {PSM_ARENA2, s->sound.music_arena2},
        {PSM_ARENA3, s->sound.music_arena3},
        {PSM_ARENA4, s->sound.music_arena4},
        {PSM_MENU,   s->sound.music_menu},
        {PSM_END,    s->sound.music_end}
    };

    for(int i = 0; i < 7; i++) {
        if(id == overrides[i].id && strlen(overrides[i].name) > 0) {
            DEBUG("Overriding %s to %s.", get_resource_name(id), overrides[i].name);
            return overrides[i].name;
        }
    }

    switch(id) {
        case BK_INTRO:       return "INTRO.BK";
        case BK_MENU:        return "MAIN.BK";
        case BK_ARENA0:      return "ARENA0.BK";
        case BK_ARENA1:      return "ARENA1.BK";
        case BK_ARENA2:      return "ARENA2.BK";
        case BK_ARENA3:      return "ARENA3.BK";
        case BK_ARENA4:      return "ARENA4.BK";
        case BK_NEWSROOM:    return "NEWSROOM.BK";
        case BK_END:         return "END.BK";
        case BK_END1:        return "END1.BK";
        case BK_END2:        return "END2.BK";
        case BK_CREDITS:     return "CREDITS.BK";
        case BK_MECHLAB:     return "MECHLAB.BK";
        case BK_MELEE:       return "MELEE.BK";
        case BK_VS:          return "VS.BK";
        case BK_NORTHAM:     return "NORTH_AM.BK";
        case BK_KATUSHAI:    return "KATUSHAI.BK";
        case BK_WAR:         return "WAR.BK";
        case BK_WORLD:       return "WORLD.BK";
        case AF_JAGUAR:      return "FIGHTR0.AF";
        case AF_SHADOW:      return "FIGHTR1.AF";
        case AF_THORN:       return "FIGHTR2.AF";
        case AF_PYROS:       return "FIGHTR3.AF";
        case AF_ELECTRA:     return "FIGHTR4.AF";
        case AF_KATANA:      return "FIGHTR5.AF";
        case AF_SHREDDER:    return "FIGHTR6.AF";
        case AF_FLAIL:       return "FIGHTR7.AF";
        case AF_GARGOYLE:    return "FIGHTR8.AF";
        case AF_CHRONOS:     return "FIGHTR9.AF";
        case AF_NOVA:        return "FIGHTR10.AF";
        case PSM_MENU:       return "MENU.PSM";
        case PSM_END:        return "END.PSM";
        case PSM_ARENA0:     return "ARENA0.PSM";
        case PSM_ARENA1:     return "ARENA1.PSM";
        case PSM_ARENA2:     return "ARENA2.PSM";
        case PSM_ARENA3:     return "ARENA3.PSM";
        case PSM_ARENA4:     return "ARENA4.PSM";
        case DAT_SOUNDS:     return "SOUNDS.DAT";
        case DAT_ENGLISH:    return "ENGLISH.DAT";
        case DAT_GRAPHCHR:   return "GRAPHCHR.DAT";
        case DAT_CHARSMAL:   return "CHARSMAL.DAT";
        case DAT_ALTPALS:    return "ALTPALS.DAT";
        default: break;
    }
    return NULL;
}

const char* get_resource_name(unsigned int id) {
    switch(id) {
        case BK_INTRO:       return "BK_INTRO";
        case BK_MENU:        return "BK_MAIN";
        case BK_ARENA0:      return "BK_ARENA0";
        case BK_ARENA1:      return "BK_ARENA1";
        case BK_ARENA2:      return "BK_ARENA2";
        case BK_ARENA3:      return "BK_ARENA3";
        case BK_ARENA4:      return "BK_ARENA4";
        case BK_NEWSROOM:    return "BK_NEWSROOM";
        case BK_END:         return "BK_END";
        case BK_END1:        return "BK_END1";
        case BK_END2:        return "BK_END2";
        case BK_CREDITS:     return "BK_CREDITS";
        case BK_MECHLAB:     return "BK_MECHLAB";
        case BK_MELEE:       return "BK_MELEE";
        case BK_VS:          return "BK_VS";
        case BK_NORTHAM:     return "BK_NORTHAM";
        case BK_KATUSHAI:    return "BK_KATUSHAI";
        case BK_WAR:         return "BK_WAR";
        case BK_WORLD:       return "BK_WORLD";
        case AF_JAGUAR:      return "AF_JAGUAR";
        case AF_SHADOW:      return "AF_SHADOW";
        case AF_THORN:       return "AF_THORN";
        case AF_PYROS:       return "AF_PYROS";
        case AF_ELECTRA:     return "AF_ELECTRA";
        case AF_KATANA:      return "AF_KATANA";
        case AF_SHREDDER:    return "AF_SHREDDER";
        case AF_FLAIL:       return "AF_FLAIL";
        case AF_GARGOYLE:    return "AF_GARGOYLE";
        case AF_CHRONOS:     return "AF_CHRONOS";
        case AF_NOVA:        return "AF_NOVA";
        case PSM_MENU:       return "PSM_MENU";
        case PSM_END:        return "PSM_END";
        case PSM_ARENA0:     return "PSM_ARENA0";
        case PSM_ARENA1:     return "PSM_ARENA1";
        case PSM_ARENA2:     return "PSM_ARENA2";
        case PSM_ARENA3:     return "PSM_ARENA3";
        case PSM_ARENA4:     return "PSM_ARENA4";
        case DAT_SOUNDS:     return "DAT_SOUNDS";
        case DAT_ENGLISH:    return "DAT_ENGLISH";
        case DAT_GRAPHCHR:   return "DAT_GRAPHCHR";
        case DAT_CHARSMAL:   return "DAT_CHARSMAL";
        case DAT_ALTPALS:    return "DAT_ALTPALS";
        default: break;
    }
    return NULL;
}

int is_arena(unsigned int id) {
    return (id >= BK_ARENA0 && id <= BK_ARENA4);
}

int is_scene(unsigned int id) {
    return (id >= BK_INTRO && id <= BK_WORLD);
}

int is_har(unsigned int id) {
    return (id >= AF_JAGUAR && id <= AF_NOVA);
}

int is_music(unsigned int id) {
    return (id >= PSM_MENU && id <= PSM_ARENA4);
}

int rand_arena() {
   return BK_ARENA0 + rand_int(5);
}
