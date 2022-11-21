#ifndef RBT_HPP
# define RBT_HPP 

#include <stddef.h>

#define RED 1
#define BLACK 0
#define LEFT 0
#define RIGHT 1

template<typename value_type, typename Alloc> 
struct s_node
{
	int _color;
	value_type *_p;
	struct s_node **_child;
	Alloc _allocator;

	s_node()
	{

	}
	s_node(const value_type &c_pair)
	{
		this->_p =  _allocator.allocate(sizeof(value_type)) ;
		this->_allocator.construct(this->_p, c_pair);
		this->_color = RED;

		_child = new s_node* [2];
		this->_child[LEFT] = NULL;
		this->_child[RIGHT] = NULL;
	}
	~s_node()
	{
		std::cout << "s_node distructor called" << std::endl;
		this->_allocator.deallocate(this->_p);
		delete (_child);
	}

};

template<typename value_type, typename Compare, typename Alloc> 
class RBT
{
		private:
				typedef struct s_node<value_type, Alloc> Node;
				Node *_root;
				Compare _comp_obj;

		protected:

			bool isRednode(const Node *node);
			void colorFlip(Node *node);
			Node *getMax(Node *node);
			Node *rotate(Node *node, bool dir);
			Node *doubleRotate(Node *node, bool dir);
			Node *Insert_helper(Node *node, int value);
			Node *BalanceSubTree(Node *node, bool side);
			Node *BalanceDelete(Node *node, bool dir, bool &isBalanced);
			Node *DeleteHelper(Node *node, int value, bool &isBalanced);

		public:
			void  delete_(int data);
			Node *get_root() { return this->_root; }
			void Insert(value_type value);

			RBT(): _root(NULL)
			{
			}

			RBT(const value_type &node)
			{
				this->_root = new Node(node);
			}
			~RBT()
			{

				std::cout << "RBT distuctor called" << std::endl; 
			}
};

#endif /* RBT_HPP */
