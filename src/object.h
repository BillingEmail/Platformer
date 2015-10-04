/* object.h - type definition for an object
 *
 * An object is the basic building block for anything that will be
 * part of the world. Every block, wall, character, and the player
 * all have Objects in them. However, blocks are JUST an object,
 * while something like a character CONTAINS a block.
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "texture.h"
#include "spritesheet.h"

/* The Object struct */
typedef struct {
	Spritesheet *spritesheet;  /* Each type of object has a spritesheet, all objects
	                            * of the same type have their spritesheet member set
	                            * to the same value.
	                            */

	SDL_Rect **animations; /* A 2-dimensional, possible jagged, array of rects.
	                        * Each rect is a source rectangle clip for the
	                        * spritesheet. If an object has 4 animations,
	                        * animations[0 through 3] are each animation.
	                        * For example, animations[1] is an object's
	                        * second animation, and animations[1][2] is
	                        * the third sprite of the object's second
	                        * animation.
	                        */

	int animation;         /* The current animation of the object. This will
	                        * be used as the index for animations to determine
	                        * which animation to play. For example, if
	                        * animation is 3, then animations[3] wil be
	                        * played.
	                        */

	SDL_Rect dstrect;      /* The destination rectangle for the object - where
	                        * it is going to be rendered.
	                        * .x, .y: The position/location of the object;
	                        * .w, .h: The dimensions (width and height) of the
	                        * object
	                        */

	bool collision;        /* collision can either be true or false. If true,
	                        * the entire area encapsulated by the object is
	                        * impermeable. This will only be used for objects
	                        * such as level blocks, walls, etc.
	                        */
	
	int sprite_index;      /* The index of the current sprite in animations[animation] */

} Object;

/* Create a new object from a spritesheet with an initial location,
 * width, and height.
 */
Object * New_Object(
	Spritesheet *spritesheet, /* A spritesheet already created. See "texture.h" */
	int x,                /* The original x-position of the object.         */
	int y,                /* The original y-location of the object.         */
	int w,                /* The width of the object.                       */
	int h,                /* The height of the object.                      */
	bool collision,       /* Whether the object is an impermeable block     */
	int default_sprite
);

/* Destroy an object */
void Destroy_Object(Object *o);

/* Draw the object onto the renderer using the object's location,
 * and current sprite
 */
void Object_Render(Object *object, SDL_Renderer *renderer);

/* Set the animation of an object. Typically, an enum for an animation specific
 * to the object type will be used.
 */
void Object_SetAnimation(Object *o, int animation);

/* Increment the current sprite of the object to the next sprite in the
 * animation, resetting to the first sprite of the animation when the
 * sprite passes the final sprite of the animation.
 */
void Object_NextSprite(Object *o);
#endif
