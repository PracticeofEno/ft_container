#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "node.hpp"

template <class T>
class RBTree
{
public:
    Node<T> *root;
    Node<T> leaf;

    RBTree() : root(0) { leaf.isLeaf = true; }

    void rotate(Node<T> *insert, Node<T> *last, Node<T> *parent)
    {
        Node<T> tmp;

        if (*parent < *last)
        {
            if (*insert < *last)
            {
                contentSwap(*parent, *insert); //
                insert->left = parent;
                insert->right = last;
            }
            else
            {
                contentSwap(*parent, *last); //
                last->left = parent;
                last->right = insert;
            }
        }
        else
        {
            if (*insert < *last)
            {
                contentSwap(*parent, *last); //
                last->left = insert;
                last->right = parent;
            }
            else
            {
                contentSwap(*parent, *insert); //
                insert->left = last;
                insert->right = parent;
            }
        }
    }
    void changeColor(Node<T> *node)
    {
        node->parent->color = RED;
        if (node->parent->left == node)
            node->parent->right->color = BLACK;
        else
            node->parent->left->color = BLACK;
        root->color = BLACK;
    }

    void insert(Node<T> *insertNode)
    {
        Node<T> *lastNode = 0;
        insertNode->left = &leaf;
        insertNode->right = &leaf;

        if (root == 0)
        {
            root = insertNode;
            root->color = BLACK;
        }
        else
        {
            if (search(insertNode, &lastNode) == 0)
            {
                if ((*lastNode) < (*insertNode))
                {
                    lastNode->right = insertNode;
                    insertNode->parent = lastNode;
                }
                else
                {
                    lastNode->left = insertNode;
                    insertNode->parent = lastNode;
                }
                if (lastNode->color == RED)
                    relocation(insertNode, lastNode);
            }
        }
    }

    void relocation(Node<T> *insertNode, Node<T> *lastNode)
    {
        if (lastNode->parent->right->color == BLACK)
        {
            rotate(insertNode, lastNode, lastNode->parent);
        }
        else if (lastNode->parent->right->color == RED)
        {
            changeColor(lastNode);
        }
    }

    Node<T> *search(Node<T> *insertNode, Node<T> **lastNode)
    {
        Node<T> *node;

        node = root;
        while (!(node->isLeaf))
        {
            *lastNode = node;
            if (node == insertNode)
                return node;
            else if (node < insertNode)
                node = node->left;
            else if (node > insertNode)
                node = node->right;
        }
        return (0);
    }

    void setLeaf(Node<T>* tmp)
    {
        leaf = tmp;
    }

private:
};
#endif