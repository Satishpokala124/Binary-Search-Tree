# include <iostream>
# include <algorithm>
# include <map>
# include <vector>

using namespace std;

struct Node{
	int data;
	struct Node *left;
	struct Node *right;
};

typedef struct Node Node;

// DFS Traversal Functions
void preorder(Node *root){
	if(root){
		cout << root->data << " ";
		preorder(root->left);
		preorder(root->right);
	} else {
		cout << "NULL ";
	}
}

void inorder(Node *root){
	if(root){
		inorder(root->left);
		cout << root->data << " ";
		inorder(root->right);
	} else {
		cout << "NULL ";
	}
}

void postorder(Node * root){
	if(root){
		postorder(root->left);
		postorder(root->right);
		cout << root->data << " ";
	} else {
		cout << "NULL ";
	}
}

// Searching

Node * search(Node *root, int data){
	if (root == NULL) return NULL;
	if (root->data < data) return search(root->right, data);
	else if (root->data > data) return search(root->left, data);
	return root;
}

// Minimum

Node * minNode(Node *root){
	if (!root) return NULL;
	if (!root->left) return root;
	return minNode(root->left);
}

// Maximum

Node * maxNode(Node *root){
	if (!root) return NULL;
	if(!root->right) return root;
	return maxNode(root->right);
}

// Insertion 

Node * insert(Node *root, int data){
	if(!root){
		root = new Node;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		cout<<"Inserted "<<data<<endl;
		return root;
	};
	if(data < root->data) 
		root->left = insert(root->left,data);
	else if(data > root->data)
		root->right = insert(root->right,data);
	else
		cout << "Duplicate data. Insertion aborted...." << endl;
	return root;
}

// Deletion

Node * Delete(Node *root, int data){
	if (!root) return root;
	else if (root->data < data){
		root->right = Delete(root->right, data);
		return root;
	}
	else if (root->data > data){
		root->left = Delete(root->left, data);
		return root;
	}
	else {
		if (!root->left && !root->right){
			delete root;
			return NULL;
		} 
		else if (!root->left){
			Node *rightChild = root->right;
			delete root;
			return rightChild;
		}
		else if (!root->right){
			Node *leftChild = root->left;
			delete root;
			return leftChild;
		}
		else {
			Node *MaxNode = maxNode(root->left);
			root->data = MaxNode->data;
			root->left = Delete(root->left, MaxNode->data);
			return root;
		}
	}
}

// Height

int height(Node *root){
	if ((!root) || (!root->left && !root->right)) return 0;
	return 1 + max(height(root->left), height(root->right));
}

// Width

void allWidths(Node *root, int *widths, int h){
	if (!root) return;
	*(widths+h)+=1;
	allWidths(root->left, widths, h-1);
	allWidths(root->right, widths, h-1);
}

int maxWidth(Node *root){
	int h = height(root);
	int widths[h+1] = {0};
	allWidths(root, widths, h);
	return *max_element(widths, widths+h);
}

// Left view

void leftViewSetter(Node *root, int *lview, int h){
	if (!root) return;
	if (*(lview+h)==0){
		*(lview+h) = root->data;
		cout << root->data << endl;
	} 
	leftViewSetter(root->left, lview, h-1);
	leftViewSetter(root->right, lview, h-1);
}

void leftView(Node *root){
	int h = height(root);
	int lview[h+1] = {0};
	leftViewSetter(root, lview, h);
}

// Right view

void rightViewSetter(Node *root, int *rview, int h){
	if(!root) return;
	if(*(rview+h)==0){
		*(rview+h) = root->data;
		cout << root->data << endl;
	}
	rightViewSetter(root->right, rview, h-1);
	rightViewSetter(root->left, rview, h-1);
}

void rightView(Node *root){
	int h = height(root);
	int rview[h+1] = {0};
	rightViewSetter(root, rview, h);
}

// Top view

void topViewSetter(Node *root, map<int,vector<int>> &minimum,
			map<int, vector<int>> &maximum, int h, int y
	){
	if (!root) return;
	map <int, vector<int>> :: iterator minitr;
	map <int, vector<int>> :: iterator maxitr;
	vector<int> :: iterator minvecitr;
	vector<int> :: iterator maxvecitr;
	minitr = minimum.find(h);
	maxitr = maximum.find(h);
	minvecitr = minitr->second.begin();
	maxvecitr = maxitr->second.begin();
	if (y<*(minvecitr+1)) {
		*(minvecitr+1) = y;
		*(minvecitr) = root->data;
	} 
	else if (y>*(maxvecitr+1)) {
		*(maxvecitr+1) = y;
		*(maxvecitr) = root->data;
	}
	topViewSetter(root->left, minimum, maximum, h-1, y-1);
	topViewSetter(root->right, minimum, maximum, h-1, y+1);
}

void topView(Node *root){
	if (!root) return;
	map<int, vector<int>> minimum, maximum;
	int h = height(root)+1;
	int y = 0;
	for(int i=0; i<h; i++){
		vector<int> n;
		(i==h-1) ? n.push_back(root->data) : n.push_back(0); 
		n.push_back(0);
		minimum.insert(make_pair(i+1,n));
		maximum.insert(make_pair(i+1,n));
	}
	map <int, vector<int>> :: iterator itr;
	vector<int> :: iterator j;
	topViewSetter(root->left, minimum, maximum, h-1, y-1);
	topViewSetter(root->right, minimum, maximum, h-1, y+1);
	int min = 0;
	for(auto itr=minimum.rbegin(); itr != minimum.rend();++itr){
		j = itr->second.begin();
		if (itr->first == h+1) continue;
		if (*(j+1)>=min) { *(j) = 0; *(j+1) = 0;} 
		else min = *(j+1);
	}
	int max = 0;
	for(auto itr=maximum.rbegin(); itr!=maximum.rend();++itr){
		j = itr->second.begin();
		if (itr->first == h+1) continue;
		if (*(j+1)<=max) { *(j) = 0; *(j+1) = 0;}
		else max = *(j+1);
	}
	for(itr=minimum.begin(); itr!=minimum.end(); ++itr){
		j = itr->second.begin();
		if(*(j+1)!=0) cout << *(j) << " ";
	}
	cout << root->data << " ";
	for(auto itr=maximum.rbegin(); itr!=maximum.rend(); ++itr){
		j = itr->second.begin();
		if(*(j+1)!=0) cout << *(j) << " ";
	}
	cout << endl;
}