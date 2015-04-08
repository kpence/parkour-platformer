#ifndef _ENUMS_H_
#define _ENUMS_H_ 1

enum { D_RIGHT, D_UP, D_LEFT, D_DOWN, D_COUNT };
enum MoveType { Move, Walk, Run, Roll, AirMove, WallJump, Skid, Glide, MoveCount };
enum SolidType { Solid, NotSolid, SemiSolid, Droppable, SolidCount };

#endif
