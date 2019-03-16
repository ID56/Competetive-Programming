#include <bits/stdc++.h>
using namespace std;

/***AVL Tree with points as keys***/
struct point{
    int x;
    int y;

    point(){x=0;y=0;}
    point(int a,int b){x=a;y=b;}
};

struct node{
    point p;
    node *left;
    node *right;
    int height;
};

int height(struct node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

node* newNode(point q){
    node* n = new node;
    n->p   = q;
    n->left   = NULL;
    n->right  = NULL;
    n->height = 1;
    return(n);
}

node *rightRotate(node *y) {
    node *x = y->left;
    node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

node *leftRotate(node *x) {
    node *y = x->right;
    node *temp = y->left;

    y->left = x;
    x->right = temp;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return y;
}

int getBalance(node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int cmp(point a,point b){
    if (a.x==b.x and a.y==b.y)
        return 0;
    else if (a.x<b.x || (a.x==b.x)&&(a.y<b.y))
        return -1;
    else
        return 1;
}
node* insert(node* n, point q){
    if (n == NULL)
        return(newNode(q));

    if (cmp(q,n->p)==-1)        ///key less than node
        n->left  = insert(n->left, q);
    else if (cmp(q,n->p)==1)    ///key more than node
        n->right = insert(n->right, q);
    else                        ///Equal keys not allowed
        return n;

    n->height = 1 + max(height(n->left),height(n->right));

    int balance = getBalance(n);

    ///Unbalanced contention

    if (balance > 1 && cmp(q,n->left->p)==-1)
        return rightRotate(n);

    if (balance < -1 && cmp(q,n->right->p)==1)
        return leftRotate(n);

    if (balance > 1 && cmp(q,n->left->p)==-1){
        n->left =  leftRotate(n->left);
        return rightRotate(n);
    }

    if (balance < -1 && cmp(q,n->right->p)==-1){
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }

    return n;
}

node * minValueNode(node* node){ ///find leftmost leaf, for rearranging after delete
    struct node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

///Recursively delete a node, and then balance the tree
node* deleteNode(node* root, point key)
{
    if (root == NULL)                     ///Key not found
        return root;

    if (cmp(key,root->p)==-1)             ///Key present to the left
        root->left = deleteNode(root->left, key);

    else if(cmp(key,root->p)==1)          ///Key present to the right
        root->right = deleteNode(root->right, key);

    else{                                 ///Key found, and to be deleted
        if( (root->left == NULL) || (root->right == NULL) )         ///One or no child
        {
            node *temp = (root->left!=NULL)? root->left : root->right;

            if (temp == NULL){            /// No child case
                temp = root;
                root = NULL;
            }
            else                          /// One child case
             *root = *temp;
            free(temp);
        }
        else{                             ///Node with two children
            node* temp = minValueNode(root->right);
            root->p = temp->p;
            root->right = deleteNode(root->right, temp->p);
        }
    }

    if (root == NULL)
      return root;

    ///Update height
    root->height = 1 + max(height(root->left), height(root->right));

    ///Balance
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0){
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void preOrder(node *root){
    if(root != NULL)
    {
        cout<<root->p.x<<" "<<root->p.y<<endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(node *root){
    if(root!=NULL){
        postOrder(root->left);
        postOrder(root->right);
        cout<<root->p.x<<" "<<root->p.y<<endl;
    }

}


int main()
{
  node *root = NULL;

  int n,i;
  cin>>n;

  for (i=0;i<n;i++){
    point q;
    cin>>q.x>>q.y;
    root=insert(root,q);
  }

  cout<<"Preorder traversal:"<<endl;
  preOrder(root);

  cout<<"Postorder traversal:"<<endl;
  postOrder(root);
}

/**
8
5 2
8 3
11 4
1 4
3 6
12 7
10 7
2 9
**/
