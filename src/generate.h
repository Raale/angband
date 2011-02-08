/* generate.h - dungeon generation interface */

#ifndef GENERATE_H
#define GENERATE_H

void place_object(struct cave *c, int y, int x, int level, bool good, bool great);
void place_gold(struct cave *c, int y, int x, int level);
void place_secret_door(struct cave *c, int y, int x);
void place_closed_door(struct cave *c, int y, int x);
void place_random_door(struct cave *c, int y, int x);

extern struct vault *random_vault(int typ);

struct tunnel_profile {
	const char *name;
    int rnd; /* % chance of choosing random direction */
    int chg; /* % chance of changing direction */
    int con; /* % chance of extra tunneling */
    int pen; /* % chance of placing doors at room entrances */
    int jct; /* % chance of doors at tunnel junctions */
};

struct streamer_profile {
	const char *name;
    int den; /* Density of streamers */    
    int rng; /* Width of streamers */
    int mag; /* Number of magma streamers */
    int mc; /* 1/chance of treasure per magma */
    int qua; /* Number of quartz streamers */
    int qc; /* 1/chance of treasure per quartz */
};

/*
* cave_builder is a function pointer which builds a level.
*/
typedef bool (*cave_builder) (struct cave *c, struct player *p);


struct cave_profile {
	const char *name;
	cave_builder builder; /* Function used to build the level */
    int dun_rooms; /* Number of rooms to attempt */
    int dun_unusual; /* Level/chance of unusual room */
    int max_rarity; /* Max number of rarity levels used in room generation */
    int n_room_profiles; /* Number of room profiles */
	struct tunnel_profile tun; /* Used to build tunnels */
	struct streamer_profile str; /* Used to build mineral streamers*/
    const struct room_profile *room_profiles; /* Used to build rooms */
	int cutoff; /* Used to see if we should try this dungeon */
};


/*
* room_builder is a function pointer which builds rooms in the cave given
* anchor coordinates.
*/
typedef bool (*room_builder) (struct cave *c, int y0, int x0);


/**
 * This tracks information needed to generate the room, including the room's
 * name and the function used to build it.
 */
struct room_profile {
	const char *name;
	room_builder builder; /* Function used to build the room */
	int height, width; /* Space required in blocks */
	int level; /* Minimum dungeon level */
	bool crowded; /* Whether this room is crowded or not */
	int rarity; /* How unusual this room is */
	int cutoff; /* Upper limit of 1-100 random roll for room generation */
};

#endif /* !GENERATE_H */