//
//  RBTree.cpp
//  Phase2
//
//  Created by Obi Bruno Da Silva Ndubueze on 3/13/21.
//
// build a function inside RBTree to create new nodes instead of inside the struct

#include <iostream>

using namespace std;
  
enum Color {RED, BLACK};
template<typename keytype, typename valuetype>

class RBTree
{
    private:
        struct Node
        {
            keytype K;
            valuetype V;
            bool color;
            Node *left, *right, *parent;
            int size;
        };
    
        Node *root;
        int sizeV;
    
        Node *newnode(keytype key, valuetype val)
        {
            Node* nodeTemp = new Node;
            nodeTemp->size = 1;
            nodeTemp->K = key;
            nodeTemp->V = val;
            nodeTemp->left = nodeTemp->right = NULL;
            nodeTemp->parent = NULL;
            nodeTemp->color = RED;
            
            return nodeTemp;
        }
        Node* copy(Node *z) {
                if (z == NULL || z == NULL)
                {
                    return NULL;
                }
                Node* newNode = newnode(z->K,z->V);
                if (z->left != NULL) newNode->left = copy(z->left);
                if (z->right != NULL) newNode->right = copy(z->right);
                newNode->size = z->size;
                return newNode;
            }
        void destructor(Node *z)
        {
            if (z == NULL || z ==NULL) return;
            destructor(z->left);
            if (z->left != NULL) delete z->left;
            destructor(z->right);
            if (z->right != NULL) delete z->right;
        }
        int nodeSize(Node *z)
        {
            if (z == NULL)
            {
                return 0;
            }
            return z->size;
        }
        void fixNodeSize(Node * z)
        {
            if (z == NULL)
            {
                return;
            }
            z->size = nodeSize(z->left) + nodeSize(z->right)  + 1;
        }
        void fixNodeTraverse(Node * z)
        {
            while(z != NULL)
            {
                fixNodeSize(z);
                z = z->parent;
            }
        }
        Node *successorN(keytype z)
        {
            Node* temp = searchNode(z);
            
            if(temp == NULL)
            {
                return NULL;
            }
            
            if(temp->right != NULL)
            {
                temp = temp->right;
                while(temp->left != NULL)
                {
                    temp = temp->left;
                }
                return temp;
            }
            else
            {
                Node* successor = NULL;
                Node* ancestor = root;
                
                while(ancestor != temp)
                {
                    if(temp->K < ancestor->K)
                    {
                        successor = ancestor;
                        ancestor = ancestor->left;
                    }
                    else
                    {
                        ancestor = ancestor->right;
                    }
                }
                return successor;
            }
        }
        Node* predecessorN(keytype z)
        {
            Node* temp = searchNode(z);
            
            if(temp == NULL)
            {
                return NULL;
            }
            
            if(temp->left != NULL)
            {
                temp = temp->left;
                while(temp->right != NULL)
                {
                    temp = temp->right;
                }
                return temp;
            }
            else
            {
                Node* successor = NULL;
                Node* ancestor = root;
                
                while(ancestor != temp)
                {
                    if(temp->K > ancestor->K)
                    {
                        successor = ancestor;
                        ancestor = ancestor->right;
                    }
                    else
                    {
                        ancestor = ancestor->left;
                    }
                }
                return successor;
            }
        }
        void insertFix(Node *z)
        {
            Node* parent_pt = NULL;
            Node* grandParent_pt = NULL;
            
            while (z != root && z->parent->color == RED && z->color != BLACK)
            {
                parent_pt = z->parent;
                grandParent_pt = z->parent->parent;
                //Case A
                if (parent_pt == grandParent_pt->left)
                {
                    Node * uncle_pt = grandParent_pt->right;
                    // Case 1
                    if(uncle_pt != NULL && uncle_pt->color == RED)
                    {
                        parent_pt->color = BLACK;
                        uncle_pt->color = BLACK;
                        grandParent_pt->color = RED;
                        z = grandParent_pt;
                    }
                    else
                    {
                        //Case 2
                        if( z == parent_pt->right)
                        {
                            leftRotate(parent_pt);
                            z = parent_pt;
                            parent_pt = z->parent;
                        }
                        
                        // Case 3
                        rightRotate(grandParent_pt);
                        int tempColor = parent_pt->color;
                        parent_pt->color = grandParent_pt->color;
                        grandParent_pt->color = tempColor;
                        z = z->parent;
                    }
                }
                // Case B
                else
                {
                    Node * uncle_pt = grandParent_pt->left;
                    
                    // Case 1
                    if(uncle_pt != NULL && uncle_pt->color == RED)
                    {
                        grandParent_pt->color = RED;
                        parent_pt->color = BLACK;
                        uncle_pt->color = BLACK;
                        z = grandParent_pt;
                    }
                    else
                    {
                        //Case 2
                        if( z == parent_pt->left)
                        {
                            rightRotate(parent_pt);
                            z = parent_pt;
                            parent_pt = z->parent;
                        }
                        
                        // Case 3
                        
                        leftRotate(z->parent->parent);
                        int tempColor = parent_pt->color;
                        parent_pt->color = grandParent_pt->color;
                        grandParent_pt->color = tempColor;
                        z = z->parent;
                    }
                }
            }
            root->color = BLACK;
        }
        Node *insertBinSearch(Node * z, Node *insertNode)
        {
            if (z == NULL)
            {
                return insertNode;
            }
            if (insertNode->K < z->K)
            {
                z->left = insertBinSearch(z->left, insertNode);
                z->left->parent = z;
            }
            else
            {
                z->right = insertBinSearch(z->right, insertNode);
                z->right->parent = z;
            }
            fixNodeSize(z);
            return z;
        }
        void leftRotate(Node *z)
        {
            Node *y = z->right;
            z->right = y->left;
            
            if (z->right != NULL )
            {
                z->right->parent = z;
            }
            y->parent = z->parent;
            if(z->parent == NULL)
            {
                root = y;
            }
            else if(z == z->parent->left)
            {
                z->parent->left = y;
            }
            else
            {
                z->parent->right = y;
            }
            y->left = z;
            z->parent = y;
            
            fixNodeSize(y->left);
            fixNodeSize(z->parent);
        }
    
        void rightRotate(Node *z)
        {
            Node *y = z->left;
            z->left = y->right;
            if (z->left != NULL)
            {
                z->left->parent = z;
            }
            y->parent = z->parent;
            if(z->parent == NULL)
            {
            root = y;
            }
            else if(z == z->parent->left)
            {
                z->parent->left = y;
            }
            else
            {
                z->parent->right = y;
            }
            y->right = z;
            z->parent = y;
            
            fixNodeSize(y->right);
            fixNodeSize(z->parent);

        }
        
        void inorderPrint(Node *z)
        {
            if (z == NULL)
                    return;
              
            inorderPrint(z->left);
            cout << z->K << " ";
            inorderPrint(z->right);
        }
        void preorderPrint(Node *z)
        {
            if (z == NULL)
                    return;
              
                cout << z->K << " ";
                preorderPrint(z->left);
                preorderPrint(z->right);
        }
        void postorderPrint(Node* z)
        {
            if (z == NULL)
                return;
            postorderPrint(z->left);
            postorderPrint(z->right);
      
            cout << z->K << " ";
        }
        void swapColor(Node *a, Node* b)
        {
            bool temp;
            temp = a->color;
            a->color = b->color;
            b->color = temp;
        }
        void swapValues(Node *a, Node *b)
        {
            keytype temp1 = a->K;
            a->K = b->K;
            b->K = temp1;
            
            valuetype temp2 = a->V;
            a->V = b->V;
            b->V = temp2;
        }
        
        Node *uncle(Node*z)
        {
            if (z->parent == NULL || z->parent->parent == NULL)
            {
                return NULL;
            }
            if(z->parent->isLef())
            {
                return z->parent->parent->right;
            }
            else
            {
                return z->parent->patent->left;
            }
        }
        void redRedFix(Node *z)
        {
            if (z == root)
            {
                z->color = BLACK;
                return;
            }
            
            Node* uncleTemp = z->uncle(z);
            
            if (z->parent->color != BLACK)
            {
                if(uncleTemp != NULL && uncleTemp->color == RED)
                {
                    z->parent->color = BLACK;
                    uncleTemp->color =- BLACK;
                    z->parent->parent->color = RED;
                    redRedFix(z->parent->parent);
                }
                
                else
                {
                    if (isLeft(z->parent))
                    {
                        if (isLeft(z))
                        {
                            swapColor(z->parent, z->parent->parent);
                        }
                        else
                        {
                            leftRotate(z->parent);
                            swapColor(z, z->parent->parent);
                        }
                    }
                    else
                    {
                        if(isLeft(z))
                        {
                            rightRotate(z->parent);
                            swapColor(z, z->parent->parent);
                        }
                        else
                        {
                            swapColor(z->parent, z->parent->parent);
                        }
                        leftRotate(z->parent->parent);
                    }
                }
            }
        }

        Node* nodeReplace(Node *z)
        {
            
            if(z->left != NULL && z->right != NULL)
            {
                keytype keyT = z->K;
                return predecessorN(keyT);
            }
            if(z->left == NULL && z->right == NULL)
            {
                return NULL;
            }
            if(z->left != NULL)
            {
                return z->left;
            }
            else
            {
                return z->right;
            }
        }
        Node *sibling(Node *z)
        {
            if (z->parent == NULL)
            {
                return NULL;
            }
            
            if(z->parent->left == z)
            {
                return z->parent->right;
            }
            return z->parent->left;
        }
        bool isLeft(Node *z)
        {
            return z->parent->left == z;
        }
    
        void nodeDelete(Node *z)
        {
            Node *y = nodeReplace(z);
            
            if (y == NULL)
            {
                if (z == root)
                {
                    root = NULL;
                }
                else
                {
                    if(z->color == BLACK && (y == NULL || y->color == BLACK ))
                    {
                        fix2Black(z);
                    }
                    else
                    {
                        if(sibling(z) != NULL)
                        {
                            sibling(z)->color = RED;
                        }
                    }
                    if(isLeft(z))
                    {
                        z->parent->left = NULL;
                    }
                    else
                    {
                        z->parent->right = NULL;
                    }
                }
                fixNodeTraverse(z->parent);
                delete z;
                return;
            }
            if(z->left == NULL || z->right == NULL)
            {
                if(z == root)
                {
                    z->K = y->K;
                    z->V = y->V;
                    z->left = z->right = NULL;
                    fixNodeTraverse(y->parent);
                    delete y;
                }
                else
                {
                    if (isLeft(z))
                    {
                        z->parent->left = y;
                    }
                    else
                    {
                        z->parent->right = y;
                    }
                    fixNodeTraverse(z->parent);
                    delete z;
                    y->parent = z->parent;
                    
                    if (z->color == BLACK && (y == NULL || y->color == BLACK))
                    {
                        fix2Black(y);
                    }
                    else
                    {
                        y->color = BLACK;
                    }
                }
                return;
            }
            swapValues(y, z);
            nodeDelete(y);
        }
        void fix2Black(Node *z)
        {
            if (z == root)
            {
                return;
            }
             
            Node *siblingN = sibling(z);
                
            if (siblingN == NULL)
            {
                fix2Black(z->parent);
            }
            else
            {
                if (siblingN->color == RED)
                {
                // Sibling red
                    z->parent->color = RED;
                    siblingN->color = BLACK;
                    if (isLeft(siblingN)) {
                    // left case
                        rightRotate(z->parent);
                    }
                    else
                    {
                        // right case
                    leftRotate(z->parent);
                    }
                    fix2Black(z);
                }
                else
                {
                      // Sibling black
                    if ((siblingN->left != NULL && siblingN->left->color == RED) || (siblingN->right != NULL && siblingN->right->color == RED))
                    {
                        // at least 1 red children
                        if (siblingN->left != NULL and siblingN->left->color == RED)
                        {
                            if (isLeft(siblingN))
                            {
                                // left left
                                siblingN->left->color = siblingN->color;
                                siblingN->color = z->parent->color;
                                rightRotate(z->parent);
                              }
                            else
                            {
                                // right left
                                siblingN->left->color = z->parent->color;
                                rightRotate(siblingN);
                                leftRotate(z->parent);
                            }
                        }
                        else
                        {
                            if (isLeft(siblingN))
                            {
                                // left right
                                siblingN->right->color = z->parent->color;
                                leftRotate(siblingN);
                                rightRotate(z->parent);
                            }
                            else
                            {
                                // right right
                                siblingN->right->color = siblingN->color;
                                siblingN->color = z->parent->color;
                                leftRotate(z->parent);
                            }
                        }
                        z->parent->color = BLACK;
                    }
                    else
                    {
                        siblingN->color = RED;
                        if (z->parent->color == BLACK)
                            fix2Black(z->parent);
                        else
                            z->parent->color = BLACK;
                    }
                }
            }
        }
        Node *searchNode(keytype key)
        {
            Node *x = root;

            while(x != NULL)
            {
                if(x->K == key)
                {
                    return x;
                }
                else if(x->K < key)
                {
                    x = x->right;
                }
                else
                {
                    x = x->left;
                }
            }
            return NULL;
        }
        int rankHelper(Node *z, keytype key)
        {
            if (z == NULL) return 0;
            else if (key > z->K) return nodeSize(z->left) + 1 + rankHelper(z->right, key);
            else if (key < z->K) return rankHelper(z->left, key);
            else if (key == z->K) return z->size - nodeSize(z->right);
            else return 0;
        }
            
        keytype selectHelper(Node *z, int k)
        {
            if (z == NULL) return 0;
            int x = nodeSize(z->left) + 1;
            if (k == x) return z->K;
            else if (k < x) return selectHelper(z->left, k);
            else return selectHelper(z->right, k - x);
        }

    public:
        
        RBTree()
        {
            root = NULL;
            sizeV = 0;
        }
        RBTree(keytype key[], valuetype val[], int s)
        {
            root = NULL;
            sizeV = 0;
            for (int i = 0; i < s; i++)
            {
                insert(key[i], val[i]);
            }
        }
        ~RBTree()
        {
            destructor(root);
            delete root;
        }
        RBTree(const RBTree &other) {
            root = copy(other.root);
        }
        RBTree& operator=(const RBTree& other) {
            root = copy(other.root);
            return *this;
        }
        void insert(keytype key, valuetype val)
        {
            sizeV++;
            Node * insertNode = newnode(key, val);
            
            root = insertBinSearch(root, insertNode);
            
            insertFix(insertNode);
        }
        valuetype * search(keytype key)
        {
            Node *x = root;

            while(x != NULL)
            {
                if(x->K == key)
                {
                    return &(x->V);
                }
                else if(x->K < key)
                {
                    x = x->right;
                }
                else
                {
                    x = x->left;
                }
            }
            return NULL;
        }
        
        
        void inorder()
        {
            inorderPrint(root);
            cout << endl;
        }
        void postorder()
        {
            postorderPrint(root);
            cout << endl;
        }
        void preorder()
        {
            preorderPrint(root);
            cout << endl;
        }
        int size()
        {
            return sizeV;
        }
        keytype *successor(keytype k)
        {
            return &(successorN(k)->K);
        }
        keytype *predecessor(keytype k)
        {
            return &(predecessorN(k)->K);
        }
        int remove(keytype k)
        {
           Node *z = searchNode(k);
   
            if ( z == NULL || z->K != k)
            {
                return 0;
            }
            nodeDelete(z);
            sizeV--;
            return 1;
        }
        int rank(keytype k)
        {
            if (root == NULL) return 0;
            return rankHelper(root, k);
        }
        keytype select(int pos)
        {
            if (root == NULL) return 0;
            return selectHelper(root, pos);
        }
        void printk(int k)
        {
            for (int i = 1; i <= k; i++)
            {
                cout << select(i) << " ";
            }
            cout<< endl;
        }
};
