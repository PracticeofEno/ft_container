#ifndef RBTREE_HPP
#define RBTREE_HPP

#define LEFT 11
#define RIGHT 12

#include "node.hpp"
#include "map.hpp"

template <class T1, class T2>
class RBTree
{
public:
    typedef T1 key_type;
    Node<T1, T2> *root;
    std::allocator<ft::pair<T1,T2> > alloc;
    Node<T1, T2> leaf;

    RBTree(std::allocator<ft::pair<T1,T2> > _alloc) : root(0), alloc(_alloc) { leaf.isNull = true; }

    void insert(Node<T1, T2> *insertNode)
    {
        Node<T1, T2> *lastNode = 0;
        insertNode->left = &leaf;
        insertNode->right = &leaf;

        if (root == 0)
        {
            root = insertNode;
            root->color = BLACK;
        }
        else
        {
            if (search(insertNode->_data.first, &lastNode) == 0)
            {
                if ((*insertNode) > (*lastNode) )
                {
                    lastNode->right = insertNode;
                    insertNode->parent = lastNode;
                }
                else
                {
                    lastNode->left = insertNode;
                    insertNode->parent = lastNode;
                }
                relocation(insertNode);
            }
        }
    }

    Node<T1, T2> *search(T1& search, Node<T1, T2> **lastNode)
    {
        Node<T1, T2> *node;

        node = root;
        while (!(node->isNull))
        {
            *lastNode = node;
            if (node->_data.first == search)
                return node;
            else if (search < node->_data.first)
                node = node->left;
            else if (search > node->_data.first)
                node = node->right;
        }
        return (0);
    }

    void erase(T1 key)
    {
        Node<T1, T2> *lastNode;
        Node<T1, T2> *findNode;

        findNode = search(key, &lastNode);
        if (findNode) // key is exist
        {
            eraseLink(findNode, lastNode);
        }
    }
    

private:

    void setLeaf(Node<T1, T2>** tmp)
    {
        *tmp = &leaf;
    }

    void setChildLeaf(Node<T1, T2>* node1, Node<T1, T2>* node2)
    {
        setLeaf(&node1->left);
        setLeaf(&node1->right);
        setLeaf(&node2->left);
        setLeaf(&node2->right);
    }

    void eraseLink(Node<T1, T2> *delNode, Node<T1, T2>* lastNode)
    {
        Node<T1, T2>* removeNode;

        (void)lastNode;
        if (delNode->left == &leaf && delNode->right == &leaf)  // case) delnode is  leaf node 
        {
            removeNode = delNode;
            if (delNode->parent != 0)
            {
                if (delNode->parent->left == delNode)
                    setLeaf(&(delNode->parent->left));
                else
                    setLeaf(&(delNode->parent->right));
            }
            else
            {
                root = 0;
            }
            leaf.parent = removeNode->parent;
            leaf.color = DBLACK;
            if (removeNode->color == BLACK && root != 0)
                eraseRelocation(&leaf);
        }
        // && delNode->right != &leaf
        else if (delNode->left != &leaf)  // case) delnode has two child
        {
            removeNode = findLargestSubtree(delNode->left);
            contentSwap(*removeNode, *delNode);
            removeNode->right = 0;

            if (removeNode != root)
            {
                if (removeNode->parent->right == removeNode) // if removeNode is right
                    removeNode->parent->right = removeNode->left;
                else
                    removeNode->parent->left = removeNode->left;
            }
            else
            {
                root = delNode->left;
                root->right = delNode->right;
                root->parent = 0;            
            }

            removeNode->left->color = removeNode->left->color + 1;
            removeNode->left->parent = removeNode->parent;
            if (removeNode->color == BLACK)
            {
                eraseRelocation(removeNode->left);
                //eraseRelocation
            }
        }
        else if (delNode->left == &leaf && delNode->right != &leaf)
        {
            delNode->right->parent = delNode->parent;
            removeNode = findSmallestSubtree(delNode->right);
            if (delNode->parent != 0)
            {
                if (delNode->parent->left == delNode)
                    delNode->parent->left = delNode->right;
                else
                    delNode->parent->right = delNode->right;
            }
            else
            {
                root = delNode->right;
                root->parent = 0;
            }

            if (delNode->right->color == BLACK)
            {
                delNode->right->color = DBLACK;
                delNode->right->parent = delNode->parent;
            }
            else if (delNode->right->color == RED)

            {
                delNode->right->color = BLACK;
                //dealloc removeNode;
            }
            if (delNode->right->color == DBLACK)
            {
                eraseRelocation(delNode->right);
            }
        }
        
    }

    void eraseRelocation(Node<T1,T2>* dBlackNode)
    {
        Node<T1, T2>* brother;

        brother = getBrother(dBlackNode);
        if (brother != 0)
        {
            if(brother->color == RED)
            {
                brother->color = BLACK;
                brother->parent->color = RED;
                rotateLeft(dBlackNode->parent);
            }
            else
            {
                if (brother->left->color == RED)
                {
                    rotateRight(brother->parent);
                    brother->color = RED;
                    brother->left->color = BLACK;
                    brother->right->color = BLACK;
                    dBlackNode->color = BLACK;
                }
                else if (brother->left->color > RED && brother->right->color > RED)
                {
                    brother->color = RED;
                    dBlackNode->color = dBlackNode->color - 1;
                    dBlackNode->parent->color = dBlackNode->parent->color + 1;
                    if (dBlackNode->parent->color == DBLACK)
                        eraseRelocation(dBlackNode->parent);
                }
                else if (brother->right->color == RED)
                {
                    brother->color = RED;
                    brother->right->color = BLACK;
                    rotateLeft(brother);
                    eraseRelocation(dBlackNode);
                }
            }
        }
        leaf.color = BLACK;
        root->color = BLACK;
    }

    Node<T1, T2>* getBrother(Node<T1, T2>* node)
    {
        if (node != root)
        {
            if (node->parent->left == node)
                return node->parent->right;
            else
                return node->parent->left;
        }
        else
        {
            return 0;
        }
    }

    Node<T1, T2>* getUncle(Node<T1, T2>* node)
    {
        if (node->parent->parent->left == node->parent)
            return node->parent->parent->right;
        else
            return node->parent->parent->left;
    }

    Node<T1, T2>* findLargestSubtree(Node<T1, T2>* subtree)
    {
        while (subtree->right != &leaf)
        {
            subtree = subtree->right;
        }
        return subtree;
    }

    Node<T1, T2>* findSmallestSubtree(Node<T1, T2>* subtree)
    {
        while (subtree->left != &leaf)
        {
            subtree = subtree->left;
        }
        return subtree;
    }

    void rotateRight(Node<T1, T2>* node)
    {
        Node<T1, T2>* tmp;
        int isRightChild = 0;

        tmp = node->left->right;
        node->left->parent = node->parent;
        if (node != root)
        {
            if (node->parent->left == node)
                isRightChild = -1;
            else
                isRightChild = 1;
        }
        else
        {
            root = node->left;
        }
        
        if (isRightChild == 1)
            node->parent->right = node->left;
        else if (isRightChild == -1)
            node->parent->left = node->left;
        node->left->right = node;
        node->parent = node->left;
        node->left = tmp;
    }

    void rotateLeft(Node<T1, T2>* node)
    {
        Node<T1, T2>* tmp;
        int isRightChild = 0;

        tmp = node->right->left;
        node->right->parent = node->parent;
        if (node != root)
        {
            if (node->parent->left == node)
                isRightChild = -1;
            else
                isRightChild = 1;
        }
        else
        {
            root = node->right;
        }

        if (isRightChild == 1)
           node->parent->right = node->left;
        else if (isRightChild == -1)
            node->parent->left = node->right;
        node->right->left = node;
        node->parent = node->right;
        node->right = tmp;
    }

    void relocation(Node<T1, T2> *insertNode)
    {
        Node<T1, T2>* uncle;
        Node<T1, T2>* parent;
        Node<T1, T2>* grand = 0;

        parent = insertNode->parent;
        if(insertNode != root)
            grand = parent->parent;
        if (grand != 0)
        {
            if (grand->right == parent)
                uncle = grand->left;
            else
                uncle = grand->right;
        }

        if (insertNode->color == RED && insertNode->parent->color == RED)
        {
            if (uncle->color == BLACK)
            {
                rotate(insertNode, parent, grand);
            }
            else if (uncle->color == RED)
            {
                changeColor(grand);
            }
        }
    }

    void rotate(Node<T1, T2> *insert, Node<T1, T2> *parent, Node<T1, T2> *grand)
    {
        Node<T1, T2>* mid = 0;
        Node<T1, T2>* low = 0;
        Node<T1, T2>* high = 0;

        if (grand->right == parent) // low is middle
        {
            if (insert < parent)
            {
                low = grand;
                mid = insert;
                high = parent;
            }
            else
            {
                low = grand;
                mid = parent;
                high = insert;
            }
        }
        else                        // high is middle
        {
            if (insert < parent)
            {
                low = insert;
                mid = parent;
                high = grand;
            }
            else
            {
                low = parent;
                mid = insert;
                high = grand;
            }
        }

        if (grand->parent != 0)
        {
            if (grand->parent->right == grand)
                grand->parent->right = mid;
            else
                grand->parent->left = mid;
        }
        else
            root = mid;
         mid->parent = grand->parent;
         mid->left = low;
         mid->right = high;
         low->parent = mid;
         high->parent = mid;
         setChildLeaf(low,high);
         mid->color = BLACK;
         low->color = RED;
         high->color = RED;
    }
    
    void changeColor(Node<T1, T2> *node)
    {
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
        root->color = BLACK;
        relocation(node);
    }

    
};
#endif