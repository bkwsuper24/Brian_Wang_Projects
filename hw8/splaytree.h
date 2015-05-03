/**
 * splaytree.h
 *  Implements a(n unbalanced) BST storing Key,Value pairs
 */

#include <iostream>
#include <exception>
#include <cstdlib>
 #include <cstdio>
#include <utility>
 #include <map>

/* -----------------------------------------------------
 * Regular Splay Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node {
 public:
  Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
  { return _item.first; }
  
  const ValueType & getValue () const
  { return _item.second; }
  
  /* the next three functions are virtual because for Red-Black-Trees,
     we'll want to use Red-Black nodes, and for those, the 
     getParent, getLeft, and getRight functions should return 
     Red-Black nodes, not just ordinary nodes.
     That's an advantage of using getters/setters rather than a struct. */
  
  virtual Node<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node<KeyType, ValueType> *getRight () const
    { return _right; }
  
  
  void setParent (Node<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class SplayTree 
{
 protected:
  // Main data member of the class
  Node<KeyType, ValueType> *root;


 public:
  /**
   * Constructor
   */
  SplayTree () { root = NULL; }

  /**
   * Destructor
   */
  ~SplayTree () { deleteAll (root); }

  Node<KeyType, ValueType>* Right_Rotate(Node<KeyType, ValueType>* node)
  {
    Node<KeyType, ValueType>* temp = node->getLeft();
    node->getLeft() = temp->getRight();
    temp->getRight() = node;
    return temp;
  }

  Node<KeyType, ValueType>* Left_Rotate(Node<KeyType, ValueType>* node)
  {
    Node<KeyType, ValueType>* temp = node->getRight();
    node->getRight() = temp->getLeft();
    temp->getLeft() = node;
    return temp;
  }

  Node<KeyType, ValueType>* SplayDown(const std::pair<const KeyType, ValueType>* splayitem)
  {
    Node<KeyType, ValueType> head;

    head->getLeft() = NULL;
    head->getRight() = NULL;

    Node<KeyType, ValueType>* LeftTreeBig = &head;
    Node<KeyType, ValueType>* RightTreeSmall = &head;

    while(1)
    {
      if(splayitem->get->Key() > root->getKey())
      {
        if(!splayitem->getRight())
        {
          break;
        }
        if(splayitem->getKey() > root->getLeft()->getKey())
        {
          root = Left_Rotate(root);
          if(!root->getLeft())
          {
            break;
          }
        }

        LeftTreeBig->getRight() = root;
        LeftTreeBig = LeftTreeBig->getRight();

        root = root->getRight();
        LeftTreeBig->getRight() = NULL;
      }
      else if(splayitem->getKey() < root->getKey())
      {
        if(!root->getLeft())
        {
          break;
        }
        if(splayitem->getKey() < root->getLeft()->getKey())
        {
          root = Right_Rotate(root);
          if(!root->getLeft())
          {
            break;
          }
        }

        RightTreeSmall->getLeft() = root;
        RightTreeSmall = RightTreeSmall->getLeft();

        root = root->getLeft();
        RighTreeSmall->getLeft() = NULL;
      }
      break;
    }

    RightTreeSmall->getLeft() = splayitem->second->getRight();
    LeftTreeBig->getRight() = splayitem->second->getLeft();

    root->getLeft() = head.getRight();
    root->getRight() = head.getLeft();

    return (root);    
  }

  Node<KeyType, ValueType>* find(const std::pair<const KeyType, ValueType>* pitem )
  {
    return SplayDown(pitem);
  }

  void insert (const std::pair<const KeyType, ValueType>& new_item)
  
     {
        Node<KeyType, ValueType> *insertNode = new Node<KeyType, ValueType>(new_item.first, new_item.second, NULL);

        if(insertNode == NULL)
        {
          this->root = insertNode;
        }
        
        Node<KeyType, ValueType>* tempNode = rbnRoot;
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


  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }
    
  /**
   * An In-Order iterator
   *  !!! You must implement this !!!
   */
  class iterator {
  public:
    /**
     * Initialize the internal members of the iterator
     */
    iterator(Node<KeyType,ValueType>* ptr)
    {
    	curr = ptr;
    }
    
    std::pair<const KeyType,ValueType>& operator*()
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }

    /**
     * Checks if 'this' iterator's internals have the same value
     *  as 'rhs'
     */
    bool operator==(const iterator& rhs) const
    {
    	if(curr == rhs.curr)
    	{
    		return true;
    	}

    	return false;
    }
    
    /**
     * Checks if 'this' iterator's internals have a different value
     *  as 'rhs'
     */
    bool operator!=(const iterator& rhs) const
    {
    	if(rhs.curr == curr)
    	{
    		return false;
    	}

      	return true;
    }
    
    /**
     * Advances the iterator's location using an in-order sequencing
     */
    iterator& operator++()
    {
      //Case 1 where node has a right subtree
      if(curr->getRight() !=NULL)
      {
        curr = curr->getRight();
        while(curr->getLeft() !=NULL)
        {
          curr = curr->getLeft();
        }
        return *this;
      }
      else
      {
        //Case 2 where node has no right subtree
        while(curr->getParent() != NULL)
        {
          if(curr->getParent()->getLeft() == curr)
          {
            curr = curr->getParent();
            return *this;
          }
          curr = curr->getParent();
        }
      }
      curr = NULL;
      return *this;
    }
    
  protected:
    Node<KeyType, ValueType>* curr;
    //you are welcome to add any necessary variables and helper functions here.

  };
  
  /**
   * Returns an iterator to the "smallest" item in the tree
   */
  iterator begin()
  {

    Node<KeyType, ValueType> *temp = root;

    //std::cout << root->getValue() << std::endl;
  	
  	while((temp->getLeft() != NULL))  
  	{
  		temp = temp->getLeft();
  	}

  	iterator it(temp);

  	return it;
  } 

  /**
   * Returns an iterator whose value means INVALID
   */
  iterator end()
  {
  	iterator it(NULL);
  	return it;
  } 

  /**
   * Returns an iterator to the item with the given key, k
   * or the end iterator if k does not exist in the tree
   */
  iterator find (const KeyType & k) const 
  {
    Node<KeyType, ValueType> *curr = internalFind(k);
    iterator it(curr);
    return it;
  }
  
  
 protected:
  /**
   * Helper function to find a node with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
  Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    Node<KeyType, ValueType> *curr = root;
    while (curr) {
      if (curr->getKey() == k) {
	return curr;
      } else if (k < curr->getKey()) {
	curr = curr->getLeft();
      } else {
	curr = curr->getRight();
      }
    }
    return NULL;
  }
  
  /**
   * Helper function to print the tree's contents
   */
  void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
	std::cout << "[";
	printRoot (r->getLeft());
	std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
	printRoot (r->getRight());
	std::cout << "]";
      }
  }
  
  /**
   * Helper function to delete all the items
   */
  void deleteAll (Node<KeyType, ValueType> *r)
  {
    if (r != NULL)
      {
	deleteAll (r->getLeft());
	deleteAll (r->getRight());
	delete r;
      }
  }
/* Feel free to add member function definitions here if you need */
};

