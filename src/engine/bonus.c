#include "bonus.h"

int bonus_assets_load(BONUS_ASSETS *assets, const DOS64_API *api, const char *archive,
    unsigned char *packed, unsigned int packed_capacity, RESOURCE_DICTIONARY *dictionary)
{
    if (!assets || !api || !api->Write || !archive || !packed || !packed_capacity || !dictionary) {
        if (assets) assets->loaded = 0;
        if (api && api->Write) api->Write("Lion King: invalid bonus asset loader arguments.\n");
        return -1;
    }
    assets->loaded = 0;
    if (resources_load_entry(api, archive, "BONUS.MAP", packed, packed_capacity,
            assets->map, sizeof(assets->map), dictionary, &assets->map_size) != 0 ||
        resources_load_entry(api, archive, "TMBUGTOS.MCH", packed, packed_capacity,
            assets->timon, sizeof(assets->timon), dictionary, &assets->timon_size) != 0 ||
        resources_load_entry(api, archive, "TMWKWAIT.MCH", packed, packed_capacity,
            assets->timon_walk, sizeof(assets->timon_walk), dictionary, &assets->timon_walk_size) != 0 ||
        resources_load_entry(api, archive, "PUMBAA.MCH", packed, packed_capacity,
            assets->pumbaa, sizeof(assets->pumbaa), dictionary, &assets->pumbaa_size) != 0 ||
        resources_load_entry(api, archive, "PUMBBURP.MCH", packed, packed_capacity,
            assets->pumbaa_burp, sizeof(assets->pumbaa_burp), dictionary, &assets->pumbaa_burp_size) != 0 ||
        resources_load_entry(api, archive, "BUGS.MCH", packed, packed_capacity,
            assets->bugs, sizeof(assets->bugs), dictionary, &assets->bugs_size) != 0 ||
        resources_load_entry(api, archive, "DESTINY.MCH", packed, packed_capacity,
            assets->destiny, sizeof(assets->destiny), dictionary, &assets->destiny_size) != 0 ||
        resources_load_entry(api, archive, "CIRCLE.MCH", packed, packed_capacity,
            assets->circle, sizeof(assets->circle), dictionary, &assets->circle_size) != 0 ||
        resources_load_entry(api, archive, "PMEAT.MCH", packed, packed_capacity,
            assets->meat, sizeof(assets->meat), dictionary, &assets->meat_size) != 0 ||
        resources_load_entry(api, archive, "BURP", packed, packed_capacity,
            assets->burp_sound, sizeof(assets->burp_sound), dictionary, &assets->burp_sound_size) != 0 ||
        resources_load_entry(api, archive, "COLLECT1", packed, packed_capacity,
            assets->collect_sound, sizeof(assets->collect_sound), dictionary, &assets->collect_sound_size) != 0 ||
        resources_load_entry(api, archive, "BUGHUNT.AMF", packed, packed_capacity,
            assets->hunt_music, sizeof(assets->hunt_music), dictionary, &assets->hunt_music_size) != 0 ||
        resources_load_entry(api, archive, "BUGTOSS.AMF", packed, packed_capacity,
            assets->toss_music, sizeof(assets->toss_music), dictionary, &assets->toss_music_size) != 0) {
        api->Write("Lion King: cannot load bonus game assets.\n");
        return -1;
    }
    assets->loaded = 1;
    return 0;
}
