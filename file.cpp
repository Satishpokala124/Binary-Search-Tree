# include "Node.cpp"

int main(){
	Node *root = NULL;
	root = insert(root,10);
	root = insert(root,5);
	root = insert(root,7);
	root = insert(root,6);
	root = insert(root,4);
	root = insert(root,2);
	root = insert(root,1);
	root = insert(root,9);
	root = insert(root,11);
	topView(root);
	return 0; 
}

/*
	               10
	              /  \
	            5     11
	          /  \
	        4     7
	      /     /  \
	    2     6     9
	  /
	1

*/