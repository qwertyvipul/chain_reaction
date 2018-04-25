class ChainReaction{
	public: //Yes I know, but can't resist the easy way ;-)
		int gameSize;
		int playerCount;
		GMap gmap;
		PNodeptr firstPlayer;
		
		ChainReaction(int, int);
		
		//forward declaration for nested calls
		void createGame();
		void printRawGame();
		void printGame();
		void printRawNodeCount();
		void play();
		void markIndex(PNodeptr, int);
		int gameLeft();
		int playerLeft();
};

ChainReaction::ChainReaction(int gameSize, int playerCount){
	this->gameSize = gameSize;
	this->playerCount = playerCount;
}

void ChainReaction::createGame(){
	this->firstPlayer = createPlayers(this->playerCount);
	GNodeptr up, left;
	for(int rownum = 0; rownum<this->gameSize; rownum++){
		if(rownum == 0) up = NULL;
		for(int colnum = 0; colnum<this->gameSize; colnum++){
			if(colnum == 0) left = NULL;
			int index = rownum*gameSize + colnum;
			GNodeptr node = GBOX;
			gmap[index] = node;
			node->index = index;
			node->player = 0;
			node->count = 0;
			if(rownum==0){
				node->up = NULL;
			}else{
				int uindex = ((index/this->gameSize-1)*this->gameSize + index%this->gameSize);
				node->up = this->gmap[uindex];
				node->total++;
				node->up->down = node;
				node->up->total++;
			}
			
			if(colnum==0){
				node->left = NULL;
			}else{
				int lindex = index-1;
				node->left = this->gmap[lindex];
				node->total++;
				node->left->right = node;
				node->left->total++;
			}
		}
	}
}

void ChainReaction::play(){
	
	//get the first moves to initialize the game
	PNodeptr pnode = this->firstPlayer;
	do{
		this->printGame();
		cout<<"Player "<<getPlayerName(pnode->player)<<" please enter your index: ";
		int index;
		cin>>index;
		while(index>=this->gameSize*this->gameSize || this->gmap[index]->player!=0){
			cout<<"Please choose a valid index: "; cin>>index;
		}
		this->markIndex(pnode, index);
		pnode = pnode->next;
	}while(pnode!=this->firstPlayer);
	
	//the game has already begun!!!
	do{
		if(this->playerLeft()){
			this->printGame();
			cout<<"Player "<<getPlayerName(pnode->player)<<" please enter your index: ";
			int index;
			cin>>index;
			while(index>=this->gameSize*this->gameSize || this->gmap[index]->count == this->gmap[index]->total || this->gmap[index]->player!=pnode){
				cout<<"Please choose a valid index: "; cin>>index;
			}
			this->markIndex(pnode, index);
			pnode = pnode->next;
		}else{
			
		}
	}while(this->gameLeft());
	cout<<"Hurrah! "<<getPlayerName(pnode->prev->player)<<" has won the game."<<endl;
	//this->printGame();
}


int ChainReaction::gameLeft(){
	for(int index=0; index<this->gameSize*this->gameSize; index++){
		if(this->gmap[index]->count<this->gmap[index]->total) return 1;
	}
	return 0;
}


void ChainReaction::markIndex(PNodeptr pnode, int index){
	GNodeptr gnode = this->gmap[index];
	gnode->player = pnode->player;
	gnode->count++;
}

void ChainReaction::printGame(){
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
	for(int rownum=0; rownum<this->gameSize; rownum++){
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			GNodeptr node = this->gmap[index];
			if(node->player == 0){
				if(index/10==0) cout<<"0";
				cout<<index<<"|";
			}else{
				cout<<getPlayerName(node->player)<<node->count<<"|";
			}
		}
		cout<<endl;
	}
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"x";
	}
	cout<<endl;
}


void ChainReaction::printRawGame(){
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
	for(int rownum=0; rownum<this->gameSize; rownum++){
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			if(index/10==0) cout<<"0";
			cout<<index<<"|";
		}
		cout<<endl;
	}
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
}

void ChainReaction::printRawNodeCount(){
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
	for(int rownum=0; rownum<this->gameSize; rownum++){
		cout<<"|";
		for(int colnum=0; colnum<this->gameSize; colnum++){
			int index = rownum*gameSize+colnum;
			cout<<"0"<<this->gmap[index]->total<<"|";
		}
		cout<<endl;
	}
	for(int i=0; i<(this->gameSize*2 + this->gameSize+1); i++){
		cout<<"-";
	}
	cout<<endl;
}
