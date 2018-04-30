class ChainReaction{
		int self;
		int gameSize; //the game size (size x size) matrix
		int playerCount; //number of players
		GMap gmap; //index to game node map
		PNodeptr firstPlayer; //the address of the first player to begin with
		
	public:
		ChainReaction(int, int, int);
		//forward declarations for nested calls
		void createGame(); //this will create the game i.e create the players and the game nodes
		void printGame(); //this prints the state of the game including the indexes and players associated with the nodes and the count of the atoms
		void play(); //this will begin the game
		void markIndex(PNodeptr, int); //to mark the move of the player
		int gameLeft(); //to check if the game has finished or if still there are some moves available
		int playerLeft(PNodeptr); //to check if the current player has some valid moves in the game to play
		void burstNode(GNodeptr); //this will start the chain reaction
		int getBestMove(); //this gives the best move for the system
		int getEmptyCorner(); //this gives the index of the empty corner
		int getBurstNode(); //gets the index where the chain exists
};

//cunstructor to initialize the game
ChainReaction::ChainReaction(int self, int gameSize, int playerCount){
	this->self = self;
	this->gameSize = gameSize;
	this->playerCount = playerCount;
	this->createGame();
}

//create the game
void ChainReaction::createGame(){
	this->firstPlayer = createPlayers(this->playerCount); //create the players and return the first player
	GNodeptr up, left;
	for(int rownum = 0; rownum<this->gameSize; rownum++){
		for(int colnum = 0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize + colnum;
			GNodeptr node = GBOX; //creating the game nodes
			gmap[index] = node; //mapping the game nodes
			node->index = index;
			node->player = NULL; //no player is associated initially
			node->count = 0; //the no of atoms held is zero
			node->total = 0; //the total atoms to be held is for now zero but later it will be equal to the number of nodes the curernt node points to
			node->up = NULL;
			node->down = NULL;
			node->right = NULL;
			node->left = NULL;
			if(rownum!=0){
				int uindex = ((index/this->gameSize-1)*this->gameSize + index%this->gameSize);
				node->up = this->gmap[uindex]; //this node points to upper node
				node->total++;
				node->up->down = node; //uppper node points to this
				node->up->total++;
			}
			
			if(colnum!=0){
				int lindex = index-1;
				node->left = this->gmap[lindex]; //this node points to the left node
				node->total++;
				node->left->right = node; //left node points to this
				node->left->total++;
			}
		}
	}
}

//let the game begin
void ChainReaction::play(){
	
	//get the very first move of each player
	PNodeptr pnode = this->firstPlayer;
	do{
		this->printGame();
		cout<<"Player "<<getPlayerName(pnode->pnum)<<" please enter your index: ";
		int index;
		if(this->self==1 && pnode->pnum==1){	
			index = 0; //first move of the system
			cout<<index<<endl;
		}else{	
			cin>>index;
		}
		while(index>=this->gameSize*this->gameSize || this->gmap[index]->player!=0){
			cout<<"Please choose a valid index: "; cin>>index;
		}
		this->markIndex(pnode, index);
		pnode = pnode->next;
	}while(pnode!=this->firstPlayer);
	
	//the game has already begun!!!
	do{
		if(this->playerLeft(pnode)){
			this->printGame();
			cout<<"Player "<<getPlayerName(pnode->pnum)<<" please enter your index: ";
			int index;
			if(this->self==1 && pnode->pnum==1){ //if system turn	
				index = this->getBestMove(); //gets the best move
				cout<<index<<endl;
			}else{	
				cin>>index;
			}
			
			while(index>=this->gameSize*this->gameSize || (this->gmap[index]->player!=NULL && this->gmap[index]->player!=pnode)){
				cout<<"Please choose a valid index: "; cin>>index;
			}
			this->markIndex(pnode, index);
			pnode = pnode->next;
		}else{
			cout<<"Opps Player "<<getPlayerName(pnode->pnum)<<" you have been knocked out of the game."<<endl;
			pnode->next->prev = pnode->prev;
			pnode->prev->next = pnode->next;
			pnode = pnode->next;
			
			if(pnode->next == pnode){
				cout<<"Hurrah! Player "<<getPlayerName(pnode->pnum)<<" has won the game."<<endl;
				return;
			}
		}
	}while(this->gameLeft()); //till the game has not finished
	//cout<<"Hurrah! "<<getPlayerName(pnode->prev->pnum)<<" has won the game."<<endl;
	//this->printGame();
}

//check if the game has valid moves
int ChainReaction::gameLeft(){
	for(int index=0; index<this->gameSize*this->gameSize; index++){
		if(this->gmap[index]->count<this->gmap[index]->total) return 1;
	}
	return 0;
}

//check if the player has valid moves
int ChainReaction::playerLeft(PNodeptr pnode){
	for(int index=0; index<this->gameSize*this->gameSize; index++){
		if(this->gmap[index]->player == pnode) return 1;
	}
	return 0;
}

//mark the moves of the player
void ChainReaction::markIndex(PNodeptr pnode, int index){
	GNodeptr gnode = this->gmap[index];
	gnode->player = pnode; //associate the player to the node
	gnode->count++; //increase the count of the node
	//this->printGame();
	if(gnode->count == gnode->total) this->burstNode(gnode); //start the chain reaction
}

//the chain reaction
void ChainReaction::burstNode(GNodeptr gnode){
	PNodeptr player = this->firstPlayer; //check if the player has not won already
	int flag = 1;
	do{
		if(this->playerLeft(player) && gnode->player!=player){ //there must a opponent left in the game to proceed further
			flag = 0;
			break;
		}
		player = player->next;
	}while(player!=this->firstPlayer);
	if(flag) return; /* MY FAVOURITE PART OF THE CODE */ //if the player has already won stop the chain reaction
	
	gnode->count=0; //the atom count of the bursting node will become zero for the instance
	player = gnode->player; //get the player and store it in a variable
	gnode->player = NULL; //no player will be associated to the bursting node for instance
	if(gnode->left != NULL) this->markIndex(player, gnode->left->index); //burst to the left
	if(gnode->right != NULL) this->markIndex(player, gnode->right->index); //burst to the right
	if(gnode->up != NULL) this->markIndex(player, gnode->up->index); //burst upwards
	if(gnode->down != NULL) this->markIndex(player, gnode->down->index); //burst downwards
}

//print the game
void ChainReaction::printGame(){
	for(int i=0; i<(this->gameSize)*5+1; i++){
		cout<<"-";
	}
	cout<<endl;
	for(int rownum=0; rownum<this->gameSize; rownum++){
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			if(index/10==0) cout<<" 0";
			else cout<<" ";
			cout<<index<<" |";
		}
		cout<<endl;
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			GNodeptr node = this->gmap[index];
			if(node->player == NULL){
				cout<<" 00 |";
			}else{
				cout<<" "<<getPlayerName(node->player->pnum)<<node->count<<" |";
			}
		}
		cout<<endl;
		for(int i=0; i<(this->gameSize)*5+1; i++){
			cout<<"-";
		}
		cout<<endl;
	}
	for(int i=0; i<(this->gameSize)*5+1; i++){
		cout<<"x";
	}
	cout<<endl;
}

//this will give the best move available for the system
int ChainReaction::getBestMove(){
	int index;
	
	index = this->getEmptyCorner(); //get the empty corner
	if(index<gameSize*gameSize){
		cout<<"Empty Corner: ";
		return index;
	}

	index = this->getBurstNode(); //get the node if a chain exists
	if(index<gameSize*gameSize){
		cout<<"Chain burst: ";
		return index;
	}
	
	//generate random move
	do{
		index = (rand()%(this->gameSize*gameSize));
	}while(index>=this->gameSize*this->gameSize || (this->gmap[index]->player!=NULL && this->gmap[index]->player!=this->firstPlayer));
	cout<<"Random move: ";
	return index;
}

//this gives the index of the empty corner
int ChainReaction::getEmptyCorner(){
	if(gmap[0]->player==NULL) return 0;
	else if(gmap[gameSize-1]->player==NULL) return gameSize-1;
	else if(gmap[gameSize*gameSize-gameSize]->player==NULL) return gameSize*gameSize-gameSize;
	else if(gmap[gameSize*gameSize-1]->player==NULL) return gameSize*gameSize-1;
	else return gameSize*gameSize;
}

//this gives the best node for the system to make its move
int ChainReaction::getBurstNode(){
	for(int rownum=0; rownum<gameSize; rownum++){
		for(int colnum=0; colnum<gameSize; colnum++){
			int index = rownum*gameSize + colnum;
			if(gmap[index]->player==this->firstPlayer && gmap[index]->count==gmap[index]->total-1){
				if(gmap[index]->left!=NULL){
					GNodeptr node = gmap[index]->left;
					if(node->player!=NULL && node->player!=this->firstPlayer && node->count==node->total-1){
						return index;
					}
				}
				if(gmap[index]->right!=NULL){
					GNodeptr node = gmap[index]->right;
					if(node->player!=NULL && node->player!=this->firstPlayer && node->count==node->total-1){
						return index;
					}
				}
				if(gmap[index]->up!=NULL){
					GNodeptr node = gmap[index]->up;
					if(node->player!=NULL && node->player!=this->firstPlayer && node->count==node->total-1){
						return index;
					}
				}
				if(gmap[index]->down!=NULL){
					GNodeptr node = gmap[index]->down;
					if(node->player!=NULL && node->player!=this->firstPlayer && node->count==node->total-1){
						return index;
					}
				}
			}
		}
	}
	return gameSize*gameSize;
}
