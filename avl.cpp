#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

struct Node
{
  int key;
  struct Node* left;
  struct Node* right;
  int height;

};

typedef struct Node node;

int max(int a,int b)
{
  if(a>b)
    return a;
  else return b;
}

int height(node* n)
{
  if(n==NULL) return 0;
  else
    {
      int h=max(height(n->left),height(n->right))+1;
      return h;
    }
}


int getbalance(node* n)
{
  if(n==NULL) return 0;

  else return height(n->right)-height(n->left);

}

void rotate_right(node* &y)
{
  if(y->left!=NULL)
    {
      node* x;

      x=y->left;
      y->left=x->right;
      x->right=y;
      y=x;
      //y->height = max(height(y->left), height(y->right))+1;
      //x->height = max(height(x->left), height(x->right))+1;


    }

  

  return;
}

void rotate_left(node* &y)
{
  
  if(y->right!=NULL)
    {
      node *x;

      x=y->right;
      y->right=x->left;
      x->left=y;
      y=x;
      //y->height = max(height(y->left), height(y->right))+1;
      //x->height = max(height(x->left), height(x->right))+1;


    }
}
// void rotate_right(node* &y)
// {
//     node *x = y->left;
//     node *T2 = x->right;
 
//     // Perform rotation
//     x->right = y;
//     y->left = T2;
 
//     // Update heights
//     y->height = max(height(y->left), height(y->right))+1;
//     x->height = max(height(x->left), height(x->right))+1;
 
//     // Return new root
//     //return x;
// }
 
// // A utility function to left rotate subtree rooted with x
// // See the diagram given above.
// void rotate_left(node* &x)
// {
//     node *y = x->right;
//     node *T2 = y->left;
 
//     // Perform rotation
//     y->left = x;
//     x->right = T2;
 
//     //  Update heights
//     x->height = max(height(x->left), height(x->right))+1;
//     y->height = max(height(y->left), height(y->right))+1;
 
//     // Return new root
//     //return y;
// }
node* min_node(node* root)
{
  node* current;

  while(current->left!=NULL)
    current=current->left;

  return current;
}



void insert(node* &root,int key)
{
  if(root==NULL)
    {
      root=(node*)malloc(sizeof(node));
      root->key=key;
      root->right=root->left=NULL;
      root->height=1;
    }


  if(root!=NULL)
    {
      if(root->key>key)
	insert(root->left,key);
      if(root->key<key)
	insert(root->right,key);

      // root->height=1+max(height(root->right),height(root->left));
    

      int b=getbalance(root);

      if(b<-1 && root->left->key>key)
      	rotate_right(root);
      if(b>1 && root->right->key<key)
      	rotate_left(root);

      if(b<-1 && root->left->key<key)
      	{
      	  rotate_left(root->left);
      	  rotate_right(root);
      	}
      if(b>1 && root->right->key>key)
      	{
      	  rotate_right(root->right);
      	  rotate_left(root);
      	}
    }

      

  return;
}

void delete_node(node* &root, int key)
{
  if(root==NULL) return;

  if(root!=NULL)
    {
      if(root->key>key)
	delete_node(root->left,key);

      if(root->key<key)
	delete_node(root->right,key);

      if(root->key==key)
	{
	  if(root->left==NULL && root->right==NULL)
	    {
	      node* temp= NULL;
	      temp=root;
	      root=NULL;
	      free(temp);
	    }

	 else if(root->left==NULL && root->right!=NULL)
	    {
	      node* temp= root->right;
	      //*root=*temp;
	      root=temp;

	      // root->key=temp->key;
	      // root->height=temp->height;
	      // root->right=temp->right;
	      // root->left=temp->left;
	      
	      free(temp);
	    }
	 else if(root->right==NULL && root->left!=NULL)
	    {
	      node* temp=root->left;
	      root=temp;

	      // root->key=temp->key;
	      // root->height=temp->height;
	      // root->right=temp->right;
	      // root->left=temp->left;
	      
	      free(temp);
	    }
	  else
	    {
	      node* temp=min_node(root->right);
	      root->key=temp->key;
	      delete_node(root->right,temp->key);
	    }

	}
    
    }


      if(root!=NULL)
	{

	  //root->height=1+max(height(root->right),height(root->left));


	  int b=getbalance(root);

	  if(b<-1 && root->left->key>key)
	    rotate_right(root);
	  if(b>1 && root->right->key<key)
	    rotate_left(root);

	  if(b<-1 && root->left->key<key)
	    {
	      rotate_left(root->left);
	      rotate_right(root);
	    }
	  if(b>1 && root->right->key>key)
	    {
	      rotate_right(root->right);
	      rotate_left(root);
	    }
	}
}

void inorder_print(node *root,int l)
{
  if(root!=NULL)
    {
      inorder_print(root->left,l+1);
      for(int i=0;i<=l;i++)
	printf("\t");
      printf("%d(%d)\n",root->key,root->height);
      inorder_print(root->right,l+1);
    }
}

int main()
{
  node* tree=NULL;

  

  insert(tree,1);
  insert(tree,2);
  insert(tree,3);
  insert(tree,4);
  insert(tree,5);
  insert(tree,6);
  insert(tree,7);
  insert(tree,8);
  insert(tree,10);
  insert(tree,11);
  insert(tree,12);
  insert(tree,13);
  

  inorder_print(tree,0);


  delete_node(tree,10);

  inorder_print(tree,0);

}
