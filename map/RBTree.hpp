#ifndef RBTREE_HPP
#define RBTREE_HPP

#define LEFT 11
#define RIGHT 12

#include "node.hpp"
#include "map.hpp"

template <class T1, class T2, class Compare>
class RBTree
{
public:
    typedef T1 key_type;
    typedef Compare key_compare;

    Node<T1, T2, Compare> *root;
    std::allocator<Node<T1, T2, Compare> > alloc;
    key_compare comp;
    Node<T1, T2, Compare> leaf;

    RBTree() : root(0) { leaf.isNull = true; }
    RBTree(std::allocator<Node<T1, T2, Compare> > _alloc, key_compare _comp) : root(0), alloc(_alloc), comp(_comp) { leaf.isNull = true; }

    Node<T1, T2, Compare> *insert(ft::pair<T1, T2> data)
    {
        Node<T1, T2, Compare> tmp2(data);
        Node<T1, T2, Compare> *insertNode = alloc.allocate(1);
        Node<T1, T2, Compare> *tmp;
        alloc.construct(insertNode, data);
        insertNode->parent = 0;
        insertNode->right = 0;
        insertNode->left = 0;
        insertNode->isNull = 0;
        insertNode->color = RED;
        insertNode->_data = data;

        Node<T1, T2, Compare> *lastNode = 0;
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
            if ( comp(insertNode->_data.first , (lastNode->_data.first)) == false)
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

    Node<T1, T2, Compare> *search(T1 search, Node<T1, T2, Compare> **lastNode) const
    {
        Node<T1, T2, Compare> *node;

        node = root;
        if (node != 0)
        {
            while (!(node->isNull))
            {
                *lastNode = node;
                if ((*(*node)).first == search)
                    return node;
                else if ( comp(search, (*(*node)).first) == true)
                    node = node->left;
                else if (comp(search, (*(*node)).first) == false)
                    node = node->right;
            }
        }
        return (0);
    }

    Node<T1, T2, Compare> *search(T1 search) const
    {
        Node<T1, T2, Compare> *node;
        node = root;
        if (node != 0)
        {
            while (!(node->isNull))
            {
                if ((*(*node)).first == search)
                    return node;
                else if ( comp(search, (*(*node)).first) == true)
                    node = node->left;
                else if (comp(search, (*(*node)).first) == false)
                    node = node->right;
                    /*
                else if (search < (*(*node)).first)
                    node = node->left;
                else if (search > (*(*node)).first)
                    node = node->right;
                    */
            }
        }
        return (0);
    }

    bool erase(T1 key)
    {
        Node<T1, T2, Compare> *lastNode;
        Node<T1, T2, Compare> *findNode;

        findNode = search(key, &lastNode);
        if (findNode) // key is exist
        {
            eraseLink(findNode, lastNode);
            alloc.deallocate(findNode, 1);
            return true;
        }
        return false;
    }

    void setAlloc(std::allocator<Node<T1, T2, Compare> > _alloc, key_compare _comp)
    {
        alloc = _alloc;
        comp = _comp;
    }

    Node<T1, T2, Compare> *begin() const
    {
        Node<T1, T2, Compare> *tmp;

        tmp = root;
        if (tmp != 0)
        {
            while (tmp->isNull == false)
            {
                if (tmp->left->isNull == true)
                    return tmp;
                tmp = tmp->left;
            }
        }
        return (0);
    }

    Node<T1, T2, Compare> *end() const
    {
        Node<T1, T2, Compare> *tmp;

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
    void setLeaf(Node<T1, T2, Compare> **tmp)
    {
        *tmp = &leaf;
    }

    void setChildLeaf(Node<T1, T2, Compare> *node1, Node<T1, T2, Compare> *node2)
    {
        setLeaf(&node1->left);
        setLeaf(&node1->right);
        setLeaf(&node2->left);
        setLeaf(&node2->right);
    }

    void eraseLink(Node<T1, T2, Compare> *delNode, Node<T1, T2, Compare> *lastNode)
    {
        Node<T1, T2, Compare> *removeNode;

        (void)lastNode;
        if (delNode->left == &leaf && delNode->right == &leaf) // case) delnode is  leaf node
        {
            removeNode = delNode;
            if (delNode != root)
            {
                if (delNode->parent->left == delNode)
                    delNode->parent->left = &leaf;
                else if (delNode->parent->right == delNode)
                    delNode->parent->right = &leaf;
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
            delNode->right = &leaf;
            if (delNode == root)
                root = removeNode;
            if (delNode->parent->left == delNode)
            {
                 delNode->parent->left = delNode->left;
                 delNode->left->parent = delNode->parent;
            }
            else if (delNode->parent->right == delNode)
            {
                delNode->parent->right = delNode->left;
                delNode->left->parent = delNode->parent;
            }

            if (delNode->color == BLACK)
            {
                if (delNode->left->color == RED)
                    delNode->left->color = BLACK;
                else if (delNode->left->color == BLACK)
                    delNode->left->color = DBLACK;
                if (delNode->left->color == DBLACK)
                    eraseRelocation(delNode->left);
            }
        }
        else if (delNode->left == &leaf && delNode->right != &leaf)
        {
            removeNode = findSmallestSubtree(delNode->right);
            changeNode(removeNode, delNode);
            delNode->left = &leaf;
            delNode->right = &leaf;
            if (delNode == root)
                root = removeNode;
            if (delNode->parent->left == delNode)
                delNode->parent->left = &leaf;
            else if (delNode->parent->right == delNode)
                delNode->parent->right = &leaf;

            if (delNode->color == BLACK)
            {
                if (removeNode->right->color == RED)
                    removeNode->left->color = BLACK;
                else if (removeNode->left->color == BLACK)
                    removeNode->left->color = DBLACK;
                if (removeNode->left->color == DBLACK)
                    eraseRelocation(removeNode->left);
            }
        }
    }

    void eraseRelocation(Node<T1, T2, Compare> *dBlackNode)
    {
        Node<T1, T2, Compare> *brother;
        Node<T1, T2, Compare> *parentTmp = 0;

        brother = getBrother(dBlackNode);
        if (brother != 0)
        {
            parentTmp = brother->parent;
            if (brother->color == RED)
            {
                if (brother->parent->left == brother)
                {
                    rotateRight(dBlackNode->parent);
                    brother->color = BLACK;
                    brother->right->color = RED;
                }
                else if (brother->parent->right == brother)
                {
                    rotateLeft(dBlackNode->parent);
                    brother->color = BLACK;
                    brother->left->color = RED;
                }
                if(dBlackNode == &leaf)
                    dBlackNode->parent = parentTmp;
                eraseRelocation(dBlackNode);
            }
            else
            {
                if (brother->left->color == RED && brother->right->color == RED)
                {
                    if (brother->parent->left == brother)
                    {
                        rotateRight(brother->parent);
                        leaf.color = BLACK;
                        brother->left->color = BLACK;
                    }
                    else
                    {
                        rotateLeft(brother->parent);
                        leaf.color = BLACK;
                        brother->right->color = BLACK;
                    }
                }
                else if (brother->left->color == RED)
                {
                    if (brother->parent->left == brother)
                    {
                        dBlackNode->color = BLACK;
                        brother->left->color = BLACK;
                        rotateRight(dBlackNode->parent);
                    }
                    else
                    {
                        rotateRight(brother);
                        brother->color = RED;
                        brother->parent->color = BLACK;
                        if(dBlackNode == &leaf)
                            dBlackNode->parent = parentTmp;
                        eraseRelocation(dBlackNode);
                    }
                }
                else if (brother->left->color > RED && brother->right->color > RED)
                {
                    brother->color = RED;
                    dBlackNode->color = BLACK;
                    if (dBlackNode->parent->color == RED)
                        dBlackNode->parent->color = BLACK;
                    else if (dBlackNode->parent->color == BLACK)
                        dBlackNode->parent->color = DBLACK;
                    if (dBlackNode->parent->color == DBLACK)
                        eraseRelocation(dBlackNode->parent);
                }
                else if (brother->right->color == RED)
                {
                    if (brother->parent->left == brother)
                    {
                        rotateLeft(brother);
                        brother->parent->color = BLACK;
                        brother->color = RED;
                        if(dBlackNode == &leaf)
                            dBlackNode->parent = parentTmp;
                        eraseRelocation(dBlackNode);
                    }
                    else
                    {
                        rotateLeft(brother->parent);
                        brother->color = BLACK;
                        brother->right->color = BLACK;
                        leaf.color = BLACK;
                    }
                }
            }

            /*

            if (brother->color == RED)
            {
                brother->color = BLACK;
                brother->parent->color = RED;
                rotateLeft(dBlackNode->parent);
                eraseRelocation(dBlackNode);
            }
            else
            {
                if (brother->left->color == RED && brother->right->color == RED)
                {
                    if (brother->parent->left == brother)
                    {
                        rotateRight(brother->parent);
                        leaf.color = BLACK;
                        brother->left->color = BLACK;
                    }
                    else
                    {
                        rotateLeft(brother->parent);
                        leaf.color = BLACK;
                        brother->right->color = BLACK;
                    }
                }
                else if (brother->left->color == RED)
                {
                    rotateRight(brother->parent);
                    brother->parent->color = BLACK;
                    brother->color = RED;
                    if (dBlackNode == &leaf)
                        dBlackNode->parent = parentTmp;
                    eraseRelocation(dBlackNode);
                }
                else if (brother->left->color > RED && brother->right->color > RED)
                {
                    brother->color = RED;
                    dBlackNode->color = BLACK;
                    if (dBlackNode->parent->color == RED)
                        dBlackNode->parent->color = BLACK;
                    else if (dBlackNode->parent->color == BLACK)
                        dBlackNode->parent->color = DBLACK;
                    if (dBlackNode->parent->color == DBLACK)
                        eraseRelocation(dBlackNode->parent);

                }
                else if (brother->right->color == RED)
                {
                    rotateLeft(brother);
                    brother->color = RED;
                    brother->parent->color = BLACK;
                    if (dBlackNode == &leaf)
                        dBlackNode->parent = parentTmp;
                    eraseRelocation(dBlackNode);
                }
            }
            */
        }
        leaf.color = BLACK;
        root->color = BLACK;
    }

    void eraseRelocation(Node<T1, T2, Compare> *dBlackNode, bool nested)
    {
        (void)nested;
        Node<T1, T2, Compare> *brother;
        Node<T1, T2, Compare> *parentTmp = 0;

        brother = getBrother(dBlackNode);
        if (brother != 0)
        {
            parentTmp = brother->parent;
            if (brother->color == RED)
            {
                brother->color = BLACK;
                brother->parent->color = RED;
                if (brother->parent->left == brother)
                    rotateRight(dBlackNode->parent);
                else
                    rotateLeft(dBlackNode->parent);
                if (dBlackNode == &leaf)
                    dBlackNode->parent = parentTmp;
                eraseRelocation(dBlackNode);
            }
            else
            {
                if (brother->left->color == RED && brother->right->color == RED)
                {
                    if (brother->parent->left == brother)
                    {
                        rotateRight(brother->parent);
                        leaf.color = BLACK;
                        brother->left->color = BLACK;
                    }
                    else
                    {
                        rotateLeft(brother->parent);
                        leaf.color = BLACK;
                        brother->right->color = BLACK;
                    }
                }
                else if (brother->left->color == RED)
                {
                    rotateRight(brother->parent);
                    brother->parent->color = BLACK;
                    brother->color = RED;
                    if (dBlackNode == &leaf)
                        dBlackNode->parent = parentTmp;
                    eraseRelocation(dBlackNode);
                }
                else if (brother->left->color > RED && brother->right->color > RED)
                {
                    brother->color = RED;
                    dBlackNode->color = BLACK;
                    if (dBlackNode->parent->color == RED)
                        dBlackNode->parent->color = BLACK;
                    else if (dBlackNode->parent->color == BLACK)
                        dBlackNode->parent->color = DBLACK;
                    if (dBlackNode->parent->color == DBLACK)
                        eraseRelocation(dBlackNode->parent);
                }
                else if (brother->right->color == RED)
                {
                    rotateLeft(brother);
                    brother->color = RED;
                    brother->parent->color = BLACK;
                    if (dBlackNode == &leaf)
                        dBlackNode->parent = parentTmp;
                    eraseRelocation(dBlackNode);
                }
            }
        }
        leaf.color = BLACK;
        root->color = BLACK;
    }

    Node<T1, T2, Compare> *getBrother(Node<T1, T2, Compare> *node)
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

    Node<T1, T2, Compare> *getUncle(Node<T1, T2, Compare> *node)
    {
        if (node->parent->parent->left == node->parent)
            return node->parent->parent->right;
        else
            return node->parent->parent->left;
    }

    Node<T1, T2, Compare> *findLargestSubtree(Node<T1, T2, Compare> *subtree)
    {
        while (subtree->right != &leaf)
        {
            subtree = subtree->right;
        }
        return subtree;
    }

    Node<T1, T2, Compare> *findSmallestSubtree(Node<T1, T2, Compare> *subtree)
    {
        while (subtree->left != &leaf)
        {
            subtree = subtree->left;
        }
        return subtree;
    }

    void rotateRight(Node<T1, T2, Compare> *node)
    {
        Node<T1, T2, Compare> *tmp;
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
            node->left->parent = 0;
            node->parent = node->left;
        }

        if (isRightChild == 1)
            node->parent->right = node->left;
        else if (isRightChild == -1)
            node->parent->left = node->left;
        node->left->right = node;
        node->parent = node->left;
        if (tmp != 0)
        {
            node->left = tmp;
            tmp->parent = node;
        }
        else
            node->left = &leaf;
    }

    void rotateLeft(Node<T1, T2, Compare> *node)
    {
        Node<T1, T2, Compare> *tmp;
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
        if (tmp != 0)
        {
            node->right = tmp;
            tmp->parent = node;
        }
        else
            node->right = &leaf;
    }

    void relocation(Node<T1, T2, Compare> *insertNode)
    {
        Node<T1, T2, Compare> *uncle;
        Node<T1, T2, Compare> *parent;
        Node<T1, T2, Compare> *grand = 0;

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
    void rotate(Node<T1, T2, Compare> *insert, Node<T1, T2, Compare> *parent, Node<T1, T2, Compare> *grand)
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

    void changeColor(Node<T1, T2, Compare> *node)
    {
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
        root->color = BLACK;
        relocation(node);
    }

    void changeNode(Node<T1, T2, Compare> *replaceNode, Node<T1, T2, Compare> *delNode)
    {
        Node<T1, T2, Compare> copyA(*replaceNode);
        Node<T1, T2, Compare> copyB(*delNode);

        nodeSwap(delNode, replaceNode);
        nodeSwap(&copyA, delNode);
        if (replaceNode->left == replaceNode)
        {
            replaceNode->left = copyA.left;
            replaceNode->left->parent = replaceNode;
            delNode->parent = replaceNode;
        }
        if (replaceNode->right == replaceNode)
        {
            replaceNode->right = copyA.right;
            replaceNode->right->parent = replaceNode;
            delNode->parent = replaceNode;
        }
        replaceNode->color = copyB.color;
        delNode->color = copyA.color;
    }

    void nodeSwap(Node<T1, T2, Compare> *originNode, Node<T1, T2, Compare> *replaceNode)
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
        Node<T1, T2, Compare> *tmp;

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