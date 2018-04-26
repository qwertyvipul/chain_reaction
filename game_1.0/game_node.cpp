typedef struct GameNode{
	int index; //the index of the node
	PNodeptr player; //the player associated with the index
	int count; //the count of atoms held in node
	int total; //the total atoms the node can hold
	struct GameNode* up; //the upper node
	struct GameNode* down; //the lower node
	struct GameNode* left; //the left node
	struct GameNode* right; //the right node
}GNode; //the game node

typedef GNode* GNodeptr; //the game node pointer
#define GBOX (GNode*)malloc(sizeof(GNode)) //memory allocation to the nodes
