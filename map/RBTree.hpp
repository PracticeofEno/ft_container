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
                parent->left = insert;
                insert->parent = parent;
                parent->right = last;
                last->parent = parent;
                setChildLeaf(insert, last);
            }
            else
            {
                contentSwap(*parent, *last); //
                parent->left = last;
                last->parent = parent;
                parent->right = insert;
                insert->parent = parent;
                setChildLeaf(insert, last);
            }
        }
        else
        {
            if (*insert < *last)
            {
                contentSwap(*parent, *last); //
                parent->left = insert;
                insert->parent = parent;
                parent->right = last;
                last->parent = parent;
                setChildLeaf(insert, last);
            }
            else
            {
                contentSwap(*parent, *insert); //
                parent->left = last;
                last->parent = parent;
                parent->right = insert;
                insert->parent = parent;
                setChildLeaf(insert, last);
            }
        }
    }
    void changeColor(Node<T> *node)
    {
        node->parent->color = RED;
        node->parent->right->color = BLACK;
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
            else if (*insertNode < *node)
                node = node->left;
            else if (*insertNode > *node)
                node = node->right;
        }
        return (0);
    }

    void setLeaf(Node<T>* tmp)
    {
        leaf = tmp;
    }

private:
    void setChildLeaf(Node<T>* node1, Node<T>* node2)
    {
        node1->left = &leaf;
        node1->right = &leaf;
        node2->left = &leaf;
        node2->right = &leaf;
    }
};
#endif