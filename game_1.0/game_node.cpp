typedef struct GameNode{
	int index;
	PNodeptr player;
	int count;
	int total;
	struct GameNode* up;
	struct GameNode* down;
	struct GameNode* left;
	struct GameNode* right;
}GNode;

typedef GNode* GNodeptr;
#define GBOX (GNode*)malloc(sizeof(GNode))
