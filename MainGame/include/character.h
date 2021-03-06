/* character.h - type definition for CharacterType and CHaracter
 *
 * Characters work very similarly to objects, and are really just
 * one level higher than them - they are simply objects that also move.
 * CharacterTypes are made, and they essentially have an ObjectType,
 * and traits specific to the character, such as if they are affected
 * by gravity.
 *
 * Authors: Sean Rapp, Satya Patel
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "object.h"
//just to store an x and y value
typedef struct {
	float x;
	float y;
} vector;

/* How a kind of character behaves - may use the player */
typedef void (*BehaviorFunction)(void *character_type, int instance_index, void *player);

/* 
Traits unique to characters 
Deal with whether you can attack or not, your health, your speed, etc.
*/
typedef struct _character_traits {
	vector velocity;
	vector acceleration;
	int hitpoints;
	int numActions;
	int actionCost;
	int actionRegen;
	float hitDelta;
	bool is_dead;
	bool is_on_floor;
	bool is_hit;
	bool is_attacking;
} CharacterTraits;

typedef struct _charactertype {
	ObjectType *object_type; /* The ObjectType used for the CharacterType */

	CharacterTraits *character_traits; /* Array of character traits for each
	                                    *character of the type */

	int character_traits_count; /* Count for traits array */

	int character_traits_size; /* size of traits array */

	//Defaults for the charactertype as a whole, so every character instance has these
	int defaultHP;
	int defaultactionCost;
	int defaultactionRegen;
	
	//How the character reacts to the player
	BehaviorFunction behavior;

} CharacterType;

/* Create a new character type from an ObjectType and whether or not it falls */
CharacterType * New_CharacterType(ObjectType *ot, BehaviorFunction behavior, int HP, int defaultactionCost, int defaultactionRegen);

/* Destroy a charactertype, including it's objecttype etc */
void Destroy_CharacterType(CharacterType *t);

/* Render a specific instance of a CharacterType */
#define CharacterType_RenderCharacter(CT, II, DT,  C) ObjectType_RenderObject((CT)->object_type, (II), (DT), (C))

/* Add another instance of the CharacterType to the list of instances */
 
//	ObjectType_AddObject((CT)->object_type, (X), (Y), (DA), (DS))
void CharacterType_AddCharacter(CharacterType *ct, int x, int y);
/* Returns the count of instances of a character type */
#define CharacterType_Count(CT) ObjectType_Count((CT)->object_type)

/* Kill a character - play it's death animation and destroy the instance */
void CharacterType_KillCharacter(CharacterType *ct, int instance_index);

/* Update a character - temporary */
void CharacterType_UpdateCharacter(CharacterType *ct, int instance_index, unsigned int dt, void *player);

/* Update the hitboxes to where the dstrect is */
void CharacterType_AdjustHitboxes(CharacterType *ct, int instance_index);

/* Sets the animation to a certain animation type */
void CharacterType_SetCharacterAnimation(CharacterType *c, int ii, int animation, unsigned int delay);

/* Moves the character through its animation frame by frame */
void CharacterType_AnimateCharacter(CharacterType *ct, int ii, int animation, unsigned int *delay, unsigned int duration);


#endif
