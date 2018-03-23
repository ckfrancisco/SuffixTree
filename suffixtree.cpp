#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class Node
{
	public:
		int id;

		int index;
		int length;

		int stringDepth;

		Node *parent;
		Node *suffixLink;
		vector<Node*> children;

		Node(int id, int index, int length, int stringDepth, Node *parent, Node *suffLink = NULL)
		{
			this->id = id;
			this->index = index;
			this->length = length;
			this->stringDepth = stringDepth;
			this->parent = parent;
			this->suffixLink = suffixLink;
		}

		~Node()
		{

		}

		Node* insertChild(string sequence, int id, int index, int length, int stringDepth)
		{
			Node *n = new Node(id, index, length, stringDepth, this);

			vector<Node*>::iterator it = this->children.begin();

			//determine lexicographic index
			for(it; it != this->children.end(); ++it)
			{
				if(sequence[index] < sequence[(*it)->index])
					break;
			}

			this->children.insert(it, n);
			
			return n;
		}
};

class SuffixTree
{
	public:
		Node *root;
		int numNodes;

		SuffixTree(string sequence)
		{
			root = new Node(0, 0, 0, 0, root, root);
		}

		~SuffixTree()
		{

		}

		void construction(string sequence, string alphabet)
		{
			Node *n = root;
			sequence += "$";

			//insert all of sequence's suffixes
			for(int index = 0; index < sequence.length(); index++)
			{
				n = findPath(sequence, alphabet, n->parent, index);
			}
		}

		Node* findPath(string sequence, string alphabet, Node* u, int index)
		{
			
		}

		Node* nodeHops(Node* u)
		{
			
		}

		void displayChildren(Node *u)
		{
			// iterate through children
			for(vector<Node*>::iterator it = u->children.begin(); it != u->children.end(); ++it)
			{
				cout << (*it)->id << " ";
			}

			cout << endl;
		}

		void depthFirstSearch()
		{
			int counter = 0;

			// begin depth first search from root
			depthFirstSearchHelper(root, &counter);
		}

		void depthFirstSearchHelper(Node *u, int *counter)
		{
			// print current node's string depth
			cout << u->stringDepth << " ";
			(*counter)++;
			if(*counter % 10 == 0)
				cout << endl;

			// depth first search through children
			for(vector<Node*>::iterator it = u->children.begin(); it != u->children.end(); ++it)
			{
				depthFirstSearchHelper(*it, counter);
			}
		}
};