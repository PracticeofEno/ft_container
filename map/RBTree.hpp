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
    std::allocator<Node<T1, T2> > alloc;
    Node<T1, T2> leaf;

    RBTree() : root(0) { leaf.isNull = true;}
    RBTree(std::allocator<Node<T1, T2> > _alloc) : root(0), alloc(_alloc) { leaf.isNull = true; }

    Node<T1, T2> *insert(ft::pair<T1, T2> data)
    {
        Node<T1, T2> *insertNode = alloc.allocate(1);
        Node<T1, T2> *tmp;
        alloc.construct(insertNode, Node<T1, T2>(data));

        Node<T1, T2> *lastNode = 0;
        insertNode->left = &leaf;
        insertNode->right = &leaf;

        if (root == 0)
        {
            root = insertNode;
            root->color = BLACK;
            setLeafNodeParent();
            return insertNode;
        }

        tmp = search(insertNode->_data.first, &lastNode);
        if (tmp == 0)
        {
            if ((*insertNode) > (*lastNode))
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
            setLeafNodeParent();
            return insertNode;
        }
        else
        {
            setLeafNodeParent();
            return tmp;
        }
    }

    Node<T1, T2> *search(const T1 &search, Node<T1, T2> **lastNode)
    {
        Node<T1, T2> *node;

        node = root;
        if (node != 0)
        {
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
        }
        return (0);
    }

    Node<T1, T2> *search(const T1 &search)
    {
        Node<T1, T2> *node;
        node = root;
        if (node != 0)
        {
            while (!(node->isNull))
            {
                if (node->_data.first == search)
                    return node;
                else if (search < node->_data.first)
                    node = node->left;
                else if (search > node->_data.first)
                    node = node->right;
            }
        }
        return (0);
    }

    bool erase(T1 key)
    {
        Node<T1, T2> *lastNode;
        Node<T1, T2> *findNode;

        findNode = search(key, &lastNode);
        if (findNode) // key is exist
        {
            eraseLink(findNode, lastNode);
            alloc.deallocate(findNode, 1);
            return true;
        }
        return false;
    }

    void setAlloc(std::allocator<Node<T1, T2> > _alloc)
    {
        alloc = _alloc;
    }

    Node<T1,T2>* begin()
    {
        Node<T1,T2>* tmp;

        tmp = root;
        while (tmp->isNull == false)
        {
            if (tmp->left->isNull == true)
                return tmp;
            tmp = tmp->left;
        }
        return (0);
    }

    Node<T1,T2>* end()
    {
        Node<T1,T2>* tmp;

        tmp = root;
        while (tmp)
        {
            if (tmp->isNull == true)
                break;
            tmp = tmp->right;
        }
        return (tmp);
    }

private:
    void setLeaf(Node<T1, T2> **tmp)
    {
        *tmp = &leaf;
    }

    void setChildLeaf(Node<T1, T2> *node1, Node<T1, T2> *node2)
    {
        setLeaf(&node1->left);
        setLeaf(&node1->right);
        setLeaf(&node2->left);
        setLeaf(&node2->right);
    }

    void eraseLink(Node<T1, T2> *delNode, Node<T1, T2> *lastNode)
    {
        Node<T1, T2> *removeNode;

        (void)lastNode;
        if (delNode->left == &leaf && delNode->right == &leaf) // case) delnode is  leaf node
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
        else if (delNode->left != &leaf) // case) delnode has two child
        {
            removeNode = findLargestSubtree(delNode->left);
            changeNode(removeNode, delNode);
            delNode->right = 0;
            
            if (delNode->parent->right == delNode) // if removeNode is right
                delNode->parent->right = delNode->left;
            else
                delNode->parent->left = delNode->left;
            
            if (delNode == root)
                root = removeNode;

            delNode->left->color = delNode->left->color + 1;
            delNode->left->parent = delNode->parent;
            if (delNode->color == BLACK)
            {
                eraseRelocation(delNode->left);
                // eraseRelocation
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
                // dealloc removeNode;
            }
            if (delNode->right->color == DBLACK)
            {
                eraseRelocation(delNode->right);
            }
        }
    }

    void eraseRelocation(Node<T1, T2> *dBlackNode)
    {
        Node<T1, T2> *brother;

        brother = getBrother(dBlackNode);
        if (brother != 0)
        {
            if (brother->color == RED)
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

    Node<T1, T2> *getBrother(Node<T1, T2> *node)
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

    Node<T1, T2> *getUncle(Node<T1, T2> *node)
    {
        if (node->parent->parent->left == node->parent)
            return node->parent->parent->right;
        else
            return node->parent->parent->left;
    }

    Node<T1, T2> *findLargestSubtree(Node<T1, T2> *subtree)
    {
        while (subtree->right != &leaf)
        {
            subtree = subtree->right;
        }
        return subtree;
    }

    Node<T1, T2> *findSmallestSubtree(Node<T1, T2> *subtree)
    {
        while (subtree->left != &leaf)
        {
            subtree = subtree->left;
        }
        return subtree;
    }

    void rotateRight(Node<T1, T2> *node)
    {
        Node<T1, T2> *tmp;
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
        tmp->parent = node;
    }

    void rotateLeft(Node<T1, T2> *node)
    {
        Node<T1, T2> *tmp;
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
            node->parent->right = node->right;
        else if (isRightChild == -1)
            node->parent->left = node->right;
        node->right->left = node;
        node->parent = node->right;
        node->right = tmp;
        tmp->parent = node;
    }

    void relocation(Node<T1, T2> *insertNode)
    {
        Node<T1, T2> *uncle;
        Node<T1, T2> *parent;
        Node<T1, T2> *grand = 0;

        parent = insertNode->parent;
        if (insertNode != root)
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
        if (grand->left == parent && parent->left == insert)
        {
            rotateRight(grand);
            parent->color = BLACK;
            grand->color = RED;
            insert->color = RED;

        }
        else if (grand->left == parent && parent->right == insert)
        {
            rotateLeft(parent);
            rotateRight(insert->parent);
            insert->color = BLACK;
            grand->color = RED;
            parent->color = RED;
        }
        else if (grand->right == parent && parent->left == insert)
        {
            rotateRight(parent);
            rotateLeft(insert->parent);
            insert->color = BLACK;
            grand->color = RED;
            parent->color = RED;
        }
        else if (grand->right == parent && parent->right == insert)
        {
            rotateLeft(grand);
            parent->color = BLACK;
            grand->color = RED;
            insert->color = RED;
        }
    }
    /*
    void rotate(Node<T1, T2> *insert, Node<T1, T2> *parent, Node<T1, T2> *grand)
    {
        Node<T1, T2> *mid = 0;
        Node<T1, T2> *low = 0;
        Node<T1, T2> *high = 0;

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
        else // high is middle
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
        setChildLeaf(low, high);
        mid->color = BLACK;
        low->color = RED;
        high->color = RED;
    }
    */

    void changeColor(Node<T1, T2> *node)
    {
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
        root->color = BLACK;
        relocation(node);
    }

    void changeNode(Node<T1,T2> *findNode, Node<T1, T2>* delNode)
    {
        Node<T1, T2> copyA;
        Node<T1, T2> copyB;

        copyA = *findNode;
        copyB = *delNode;

        nodeSwap(delNode, findNode);
        nodeSwap(&copyA, delNode);
        if (findNode->left == findNode)
        {
            findNode->left = delNode;
            delNode->parent = findNode;
        }
        if (findNode->right == findNode)
        {
            findNode->right = delNode;
            delNode->parent = findNode;
        }
        findNode->color = copyB.color;
        delNode->color = copyA.color;
    }

    void nodeSwap(Node<T1,T2> *originNode, Node<T1, T2>* replaceNode)
    {
        if (originNode->left != &leaf)
        {
            originNode->left->parent = replaceNode;
            replaceNode->left = originNode->left;
        }
        else
        {
            replaceNode->left = &leaf;
        }
        
        if (originNode->right != &leaf)
        {
            originNode->right->parent = replaceNode;
            replaceNode->right = originNode->right;
        }
        else
        {
            replaceNode->right = &leaf;
        }

        if (originNode->parent != 0)
        {
            if (originNode->parent->left == originNode)
            {
                replaceNode->parent = originNode->parent;
                originNode->parent->left = replaceNode;
            }
            else
            {
                replaceNode->parent = originNode->parent;
                originNode->parent->right = replaceNode;
            }
        }
        else
        {
            replaceNode->parent = 0;
        }   
    }
    
    void setLeafNodeParent()
    {
        Node<T1,T2>* tmp;

        tmp = root;
        while (tmp->isNull == false)
        {
            if (tmp->right->isNull == true)
                break;
            tmp = tmp->right;
        }
        leaf.parent = tmp;
    }
};
#endif