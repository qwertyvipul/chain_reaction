typedef struct GameNode{
	int index;
	int player;
	int count;
	struct GameNode* up;
	struct GameNode* down;
	struct GameNode* left;
	struct GameNode* right;
}GNode;

typedef GNode* GNodeptr;
#define GBOX (GNode*)malloc(sizeof(GNode))

/*
-------------------------------
----01 02 03 04 05 06 07 08 09
01-|00|00|00|00|00|00|00|00|00|
02-|00|00|00|00|00|00|00|00|00|
03-|00|00|00|00|00|00|00|00|00|
04-|00|00|00|00|00|00|00|00|00|
05-|00|00|00|00|00|00|00|00|00|
06-|00|00|00|00|00|00|00|00|00|
07-|00|00|00|00|00|00|00|00|00|
08-|00|00|00|00|00|00|00|00|00|
09-|00|00|00|00|00|00|00|00|00|
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/
