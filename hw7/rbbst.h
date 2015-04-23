/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }

    std::string getColorName () const{
    if(color == black){
      return "..black"; 
    }
    return "..red";
  }  
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:

  RedBlackTree()
  {
    rbnRoot = NULL;
  }  



  void print ()
  { 
    printRoot (rbnRoot);
    std::cout << "\n";
  }

  void printRoot (RedBlackNode<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
  std::cout << "[";
  printRoot (r->getLeft());
  if(r == rbnRoot){
      std::cout << " root(" << r->getKey() << ", " << r->getValue() << " " << r->getColorName() << ") ";
  }
  else{
    std::cout << " (" << r->getKey() << ", " << r->getValue() << " " << r->getColorName() << ") ";
  }
  printRoot (r->getRight());
  std::cout << "]";
      }
  }

  void insert (const std::pair<const KeyType, ValueType>& new_item)
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree
     (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */
     {
        RedBlackNode<KeyType, ValueType> *insertNode = new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, NULL);

        if(rbnRoot == NULL)
        {
          rbnRoot = insertNode;
          insert_c1(rbnRoot);
          return;
        }
        
        RedBlackNode<KeyType, ValueType>* tempNode = rbnRoot;
        while(true)
        { 
          if(tempNode->getKey() == new_item.first)
          {
            tempNode->setValue(new_item.second);
            return;
          }
          else if(tempNode->getKey() > new_item.first)
          {
            if(tempNode->getLeft() == NULL)
            {
              tempNode->setLeft(insertNode);
              break;
            }
            else
            {
                tempNode = tempNode->getLeft();
            }
          }
          else
          {
            if(tempNode->getRight() == NULL)
            {
              tempNode->setRight(insertNode);
              break;
            }
            else
            {
              tempNode = tempNode->getRight();
            }
          }
        }
        insertNode->setParent(tempNode);

        insert_c1(insertNode);
     }

private:

//private data variable that stores rbn root
RedBlackNode<KeyType, ValueType>* rbnRoot;


RedBlackNode<KeyType, ValueType>* findmyUncle(RedBlackNode<KeyType, ValueType> *n)
{
  if(n->getParent()!= NULL)
  {
    if(n->getParent() == n->getParent()->getParent()->getLeft())
    {
      return n->getParent()->getParent()->getRight();
    }
    else
    {
      return n->getParent()->getParent()->getLeft();
    }
  }
  return NULL;
}

RedBlackNode<KeyType, ValueType>* findmyGrandparent(RedBlackNode<KeyType, ValueType> *n)
{
  if(n->getParent() != NULL)
  {
    if(n->getParent()->getParent() != NULL)
    {
      return n->getParent()->getParent();
    }
  }

  return NULL;
}

bool AmIaRightChild(RedBlackNode<KeyType, ValueType> *n)
{
  if(n->getParent() != NULL)
  {
    if(n == n->getParent()->getLeft())
    {
      return false;
    }
    
    return true;
  }
  return false;
}

bool AmIaLeftChild(RedBlackNode<KeyType, ValueType> *n)
{
  if(n->getParent() != NULL)
  {
    if(n == n->getParent()->getRight())
    {
      return false;
    }
    return true;
  }
  return false;
}

void RightRotate(RedBlackNode<KeyType, ValueType>* n)
{
  RedBlackNode<KeyType, ValueType>* rotateL = n->getLeft();

  if(n->getParent() == NULL)
  {
    rbnRoot = rotateL;
  }
  else
  {
    if(n == n->getParent()->getLeft())
    {
      n->getParent()->setLeft(rotateL);
    }
    else
    {
      n->getParent()->setRight(rotateL);
    }
  }

  if(rotateL != NULL)
  {
    rotateL->setParent(n->getParent());
  }

  rotateL->setParent(n->getParent());
  
  n->setLeft(rotateL->getRight());

  if(rotateL->getRight() != NULL)
  {
    rotateL->getRight()->setParent(n);
  }

  rotateL->setRight(n);
  n->setParent(rotateL);
}

void LeftRotate(RedBlackNode<KeyType, ValueType>* n)
{
  RedBlackNode<KeyType, ValueType>* rotateR = n->getRight();

  if(n->getParent() == NULL)
  {
    rbnRoot = rotateR;
  }
  else
  {
    if(n == n->getParent()->getLeft())
    {
      n->getParent()->setLeft(rotateR);
    }
    else
    {
      n->getParent()->setRight(rotateR);
    }
  }

  if(rotateR != NULL)
  {
    rotateR->setParent(n->getParent());
  }

  rotateR->setParent(n->getParent());
  n->setRight(rotateR->getLeft());

  if(rotateR->getLeft() != NULL)
  {
    rotateR->getLeft()->setParent(n);
  }

  rotateR->setLeft(n);
  n->setParent(rotateR);
}

//Implement the 5 cases that I need to check for

void insert_c1(RedBlackNode<KeyType, ValueType>* n)
{
  if(n->getParent() != NULL)
  {
    insert_c2(n);
  }
  else
  {
    n->setColor(black);
  }
}

void insert_c2(RedBlackNode<KeyType, ValueType>* n)
{
  if(n->getParent()->getColor() == black)
  {
    return;
  }
  else
  {
    insert_c3(n);
  }
}

void insert_c3(RedBlackNode<KeyType, ValueType>* n)
{
  if(findmyUncle(n) == NULL)
  {
    insert_c4(n);
  }
  else if(findmyUncle(n)->getColor() == red)
  {
    if(n->getParent() != NULL)
    {
      if(findmyGrandparent(n) != NULL)
      {
        n->getParent()->setColor(black);
        findmyUncle(n)->setColor(black);
        findmyGrandparent(n)->setColor(red);

        //recall case 1
        insert_c1(findmyGrandparent(n));
      }
    }
  }
  else
  {
    insert_c4(n);
  }
}

void insert_c4(RedBlackNode<KeyType, ValueType>* n)
{
  if(n->getParent()!= NULL)
  {
    if(n->getParent()->getParent() != NULL)
    {
      if((n == n->getParent()->getLeft()) && (n->getParent() == findmyGrandparent(n)->getRight()))
      {
        RightRotate(n->getParent());
        n = n->getRight();
      }
      else if((n->getParent() == findmyGrandparent(n)->getLeft()) && (n == n->getParent()->getRight()))
      {
        LeftRotate(n->getParent());
        n = n->getLeft();
      }
    }
  }
  insert_c5(n);
}


void insert_c5(RedBlackNode<KeyType, ValueType>* n)
{
  if(n->getParent() != NULL)
  {
    n->getParent()->setColor(black);
    if(n->getParent()->getParent() != NULL)
    {
      findmyGrandparent(n)->setColor(red);

      if((n->getParent() == findmyGrandparent(n)->getRight()) && (n == n->getParent()->getRight()))
      {
        LeftRotate(n->getParent()->getParent());
      }
      else if((n->getParent() == findmyGrandparent(n)->getLeft()) && (n == n->getParent()->getLeft()))
      {
        RightRotate(n->getParent()->getParent());
      }

    }
  }
}

};

