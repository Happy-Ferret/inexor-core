#pragma once

/// entity types (old Cube2 entity system)
enum
{
    NOTUSED = ET_EMPTY,
    LIGHT = ET_LIGHT,
    MAPMODEL = ET_MAPMODEL,
    PLAYERSTART,
    ENVMAP = ET_ENVMAP,
    PARTICLES = ET_PARTICLES,
    MAPSOUND = ET_SOUND,
    SPOTLIGHT = ET_SPOTLIGHT,
    
    I_SHELLS,
    I_BULLETS,
    I_ROCKETS,
    I_ROUNDS,
    I_GRENADES,
    I_CARTRIDGES,
    I_BOMBS = ET_BOMBS,
    I_BOMBRADIUS,
    I_BOMBDELAY,
    I_HEALTH,
    I_BOOST,
    I_GREENARMOUR,
    I_YELLOWARMOUR,
    I_QUAD,

    TELEPORT,
    TELEDEST,
    MONSTER,
    CARROT,
    JUMPPAD,
    BASE,
    RESPAWNPOINT,
    BOX,
    BARREL,
    PLATFORM,
    ELEVATOR,
    FLAG,
    OBSTACLE = ET_OBSTACLE,
    MAXENTTYPES
};