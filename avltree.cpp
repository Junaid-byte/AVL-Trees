#include<iostream>
#include<conio.h>

using namespace std;

struct AVL
{
	int data;
	AVL* left;
	AVL* right;
	AVL* next;
	int height;
};

int MaxHeight(int x, int y);
AVL *head = NULL;
AVL *current = NULL;

int height(AVL *H)
{
	if (H == NULL)
	{
		return 0;
	}
	return H->height;

}
int MaxHeight(int x, int y)
{
	return (x > y)?x:y;
}

AVL* Node(int data)
{
	AVL* tree = new AVL();
	tree->data = data;
	tree->left = NULL;
	tree->right = NULL;
	tree->height = 1;
	return (tree);
}

AVL *RotateRight(AVL *b)
{
	AVL *a = b->left;
	AVL *R2 = a->right;

	a->right = b;
	b->left = R2;

	b->height = MaxHeight(height(b ->left),height(b->right)) + 1;
	a->height = MaxHeight(height(a->left), height(a->right)) + 1;

	return a;

}

AVL *RotateLeft(AVL *a)
{
	AVL *b = a->right;
	AVL *R2 = b->right;

	b->left = a;
	a->right = R2;

	a->height = MaxHeight(height(a->left),height(a->right)) + 1;
	b->height = MaxHeight(height(b->left), height(b->right)) + 1;

	return b;
}

int Balance(AVL *A)
{
	if (A == NULL)
	{
		return 0;
	}
	else
	{
		return height(A->left) - height(A->right);
	}
	
}

AVL *Insert(AVL *A, int data) //For Insering data in AVL tree
{
	/* 1. Perform the normal BST insertion */
	if (A == NULL)
	{
		return (Node(data));
	}
	
	if (data < A->data)
	{
		A->left = Insert(A->left, data);
	}
	else if (data > A->data)
	{
		A->right = Insert(A->right, data);
	}
	else // Equal keys are not allowed in BST  
	{
		return A;
	}/* 2. Update height of this ancestor node */
	A->height = 1 + MaxHeight(height(A->left), height(A->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = Balance(A);

	// If this node becomes unbalanced, then  
	// there are 4 cases  

	// Left Left Case 

	if (balance > 1 && data < A->left->data)
	{
		return RotateRight(A);
	}
	// Right Right Case 
	if (balance < -1 && data > A->right->data)
	{
		return RotateLeft(A);
	}
	// Left Right Case  
	if (balance > 1 && data > A->left->data)
	{
		A->left = RotateLeft(A->left);
		return RotateRight(A);
	}
	// Right Left Case  
	if (balance < -1 && data < A->right->data)
	{
		A->right = RotateRight(A->right);
		return RotateLeft(A);
	}
	
	AVL *link = new AVL();
	link->data = data;
	link->next = NULL;

	if (head == NULL)
	{
		head = link;
	}
	current = head;

	/* return the (unchanged) node pointer */
	return A;
} 
AVL *Minvaluetree(AVL *I)
{
	AVL *current = I;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}
AVL *Remove(AVL *Root, int data) //For Removing data from the AVL tree
{
	// STEP 1: PERFORM STANDARD BST DELETE 
	if (Root == NULL)
	{
		return Root;
	}
	// If the key to be deleted is smaller  
	// than the root's key, then it lies 
	// in left subtree 
	if (data < Root->data)
	{
		Root->left = Remove(Root->left, data);
	}
	// If the key to be deleted is greater  
	// than the root's key, then it lies  
	// in right subtree  
	else if (data > Root->data)
	{
		Root->right = Remove(Root->right, data);
	}
	// if key is same as root's key, then  
	// This is the node to be deleted  
	else
	{
		// node with only one child or no child 
		if (Root->left == NULL || Root->right == NULL)
		{
			AVL *T = Root->left ? Root->left : Root->right;
			// No child case  
			if (T == NULL)
			{
				T = Root;
				Root = NULL;
			}
			else // One child case 
			{
				*Root = *T; // Copy the contents of  
                           // the non-empty child  
				free(T);

			}
		}
		else
		{
			// node with two children: Get the inorder  
			// successor (smallest in the right subtree)  
			AVL *T = Minvaluetree(Root->right);
			// Copy the inorder successor's  
			// data to this node  
			Root->data = T->data;
			// Delete the inorder successor  
			Root->right = Remove(Root->right, T->data);
		}
	}
	// If the tree had only one node 
	// then return  
	if (Root == NULL)
	{
		return Root;
	}
	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	Root->height = 1 + MaxHeight(height(Root->left), height(Root->right));
	// STEP 3: GET THE BALANCE FACTOR OF  
	// THIS NODE (to check whether this  
	// node became unbalanced) 
	int balance = Balance(Root);

	// If this node becomes unbalanced,  
	// then there are 4 cases  
	// Left Left Case  
	if (balance > 1 && Balance(Root->left)>= 0)
	{
		return RotateRight(Root);
	}
	// Left Right Case
	if (balance > 1 && Balance(Root->left) < 0)
	{
		Root->left = RotateLeft(Root->left);
		return RotateRight(Root);
	}
	// Right Right Case 
	if (balance < -1 && Balance(Root->right) <= 0)
	{
		return RotateLeft(Root);
	}
	// Right Left Case  
	if(balance < -1 && Balance(Root->right) > 0)
	{
		Root->right = RotateRight(Root->right);
		return RotateLeft(Root);
	}

	return Root;
		
		
}

void Display()
{
	AVL *ptr = head;
	while (ptr != NULL)
	{
		cout << ptr->data << " ";
		ptr = ptr->next;
	}
}

void Update(int old, int New,AVL &Root)
{
	int pos = 0;
	AVL *current = new AVL();
	if (head == NULL)
	{
		cout << "Linked list not Initialized! " << endl;
		return;
	}
	current = &Root;

		while (current->next != NULL)
	    {
			 if (current->data == old)
			{
				current->data = New;
				cout << old << " is found at position " << pos << " replaced with " << New << endl;
			}
		  current = current->next;
		  pos++;
	    }

}

// A utility /function to print preorder  
// traversal of the tree.  
// The function also prints height  
// of every node  

void Preorder(AVL *root) //Creating an AVL tree through this function//
{
	if (root != NULL)
	{
		cout << root->data << " ";
		Preorder(root->left);
		Preorder(root->right);
	}
}



int main()
{
	AVL *root = NULL;
	AVL *ptr = NULL;
	AVL *Root = NULL;
	int data = 0;

	root = Insert(root, 10);
	root = Insert(root, 15);
	root = Insert(root, 20);
	root = Insert(root, 25);
	root = Insert(root, 30);
	
	cout << "Preorder Traversal Of The AVL tree is:- " << endl;
	Preorder(root);

	root = Remove(root, 25);
	cout << endl;

	cout << "Preorder Traversal Of The AVL tree After Removing 25 is:- " << endl;
	Preorder(root);

	Update(10, 75,*root);
	Display();

	_getch();
	return 0;
}
