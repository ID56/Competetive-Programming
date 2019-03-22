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

int cmp(point p,point q){
    if (p.x>q.x) return 1;
    if (p.x<q.x) return -1;
    if (p.y>q.y) return 1;
    if (p.y<q.y) return -1;
    return 0;
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

struct node * minValueNode(struct node* node) {
    struct node* current = node;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    return current;
}
struct
 node* deleteNode(struct node* root, point key){
    /// STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
    /// If the key to be deleted is smaller than the
    /// root's key, then it lies in left subtree
    if ( cmp(key,root->p)==-1 )
        root->left = deleteNode(root->left, key);

    /// If the key to be deleted is greater than the
    /// root's key, then it lies in right subtree
    else if( cmp(key,root->p)==1 )
        root->right = deleteNode(root->right, key);

    /// if key is same as root's key, then this is the node to be deleted
    else{
        /// node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) ){
            struct node *temp = root->left ? root->left : root->right;
            /// No child case
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else /// One child case
             *root = *temp; /// Copy the contents of the non-empty child
            free(temp);
        }
        else{
            /// node with two children: Get the inorder
            /// successor (smallest in the right subtree)
            struct node* temp = minValueNode(root->right);

            /// Copy the inorder successor's data to this node
            root->p = temp->p;

            /// Delete the inorder successor
            root->right = deleteNode(root->right, temp->p);
        }
    }

    /// If the tree had only one node then return
    if (root == NULL)
      return root;

    /// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),height(root->right));

    /// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    /// check whether this node became unbalanced)
    int balance = getBalance(root);

    /// If this node becomes unbalanced, then there are 4 cases

    /// Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    /// Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    /// Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
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

void inOrder(node *root){
    if (root!=NULL){
        inOrder(root->left);
        cout<<root->p.x<<" "<<root->p.y<<endl;
        inOrder(root->right);
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

  cout<<"Inorder traversal:"<<endl;
  inOrder(root);

  point q;
  cin>>q.x>>q.y;
  root=deleteNode(root,q);
  cout<<"After deleting: "<<endl;
  postOrder(root);

}

/**
8
5 5
2 3
1 1
4 7
2 9
5 4
7 1
8 9
**/
