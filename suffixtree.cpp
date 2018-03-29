#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class Node
{
	public:
		int mId;

		int mIndex;
		int mLength;

		int mStringDepth;

		Node *mParent;
		Node *mSuffixLink;
		vector<Node*> mChildren;

		Node(int id, int index, int length, int stringDepth, Node *parent, Node *suffixLink = NULL)
		{
			this->mId = id;
			this->mIndex = index;
			this->mLength = length;
			this->mStringDepth = stringDepth;
			this->mParent = parent;
			this->mSuffixLink = suffixLink;
		}

		~Node()
		{

		}

		Node* insertChild(string sequence, int id, int index)
		{
			index += mStringDepth;
			int length = sequence.length() - index;
			int stringDepth = mStringDepth + length;

			Node *n = new Node(id, index, length, stringDepth, this);

			vector<Node*>::iterator it = mChildren.begin();

			// determine lexicographic index
			for(it; it != mChildren.end(); ++it)
			{
				if(sequence[index] < sequence[(*it)->mIndex])
					break;
			}

			mChildren.insert(it, n);
			
			return n;
		}



		Node* insertInternal(int id, int length, vector<Node*>::iterator it)
		{
			int index = (*it)->mIndex;
			int stringDepth = mStringDepth + length;

			Node *n = new Node(id, index, length, stringDepth, this);
			Node *child = *it;

			mChildren.insert(it, n);
			
			// determine iterator position of child to remove
			for(it = mChildren.begin(); it != mChildren.end(); ++it)
			{
				if((*it) == child)
				{
					break;
				}
			}

			mChildren.erase(it);

			child->mIndex += length;
			child->mLength -= length;
			child->mParent = n;

			n->mChildren.push_back(child);

			return n;
		}
};

class SuffixTree
{
	public:
		string mSequence;
		Node *mRoot;
		int mNumInternals;
		int mNumLeaves;

		SuffixTree(string sequence)
		{
			mSequence = sequence + "$";
			mRoot = new Node(0, 0, 0, 0, mRoot, mRoot);
			mNumInternals = -1;
			mNumLeaves = 0;
		}

		~SuffixTree()
		{

		}

		void construction()
		{
			int x = 0;
			Node *n = mRoot;

			// insert all of sequence's suffixes
			for(int index = 0; index < mSequence.length(); index++)
			{
				n = findPath(mRoot, index);
				x++;
			}
		}

		Node* findPath(Node* n, int index)
		{
			vector<Node*>::iterator it = n->mChildren.begin();

			// 1: iterate through children to find edge to traverse
			for(it; it != n->mChildren.end(); ++it)
			{
				if(mSequence[(*it)->mIndex] == mSequence[index + n->mStringDepth])
				{
					break;
				}
			}

			// 2: edge found
			if(it != n->mChildren.end())
			{
				int i = 0;

				// 3: iterate through edge to find break point
				for(i; i < (*it)->mLength; i++)
				{
					if(mSequence[(*it)->mIndex + i] != mSequence[index + n->mStringDepth + i])
					{
						break;
					}
				}

				// 4: break point found
				if(i < (*it)->mLength)
				{
					// 5: insert a new internal node
					Node *internal = n->insertInternal(mNumInternals--, i, it);
					return internal->insertChild(mSequence, mNumLeaves++, index);
				}

				// 4: break point not found (edge exhausted)
				else
				{
					// 5: continue traversal from child node via recursion
					return findPath(*it, index);
				}
			}

			// 2: edge not found
			else
			{
				// 3: insert a new child node
				return n->insertChild(mSequence, mNumLeaves++, index);
			}

		}

		Node* nodeHops(Node* n, string beta, int index)
		{
			if(index == beta.length())
			{
				return n;
			}

			vector<Node*>::iterator it = n->mChildren.begin();

			// 1: iterate through children to find edge to traverse
			for(it; it != n->mChildren.end(); ++it)
			{
				cout << mSequence[(*it)->mIndex] << " " << beta[index] << endl;
				if(mSequence[(*it)->mIndex] == beta[index])
				{	
					// 2: recurse to next child node and return result
					return nodeHops(*it, beta, index + (*it)->mLength);
				}
			}
		}

		void displayChildren(Node *u)
		{
			// iterate through children
			for(vector<Node*>::iterator it = u->mChildren.begin(); it != u->mChildren.end(); ++it)
			{
				cout << (*it)->mId << " ";
			}

			cout << endl;
		}

		void depthFirstSearch()
		{
			int counter = 0;

			// begin depth first search from root
			depthFirstSearchHelper(mRoot, &counter);
		}

		void depthFirstSearchHelper(Node *u, int *counter)
		{
			// print current node's string depth
			cout << u->mStringDepth << " ";
			(*counter)++;
			if(*counter % 10 == 0)
				cout << endl;

			// depth first search through children
			for(vector<Node*>::iterator it = u->mChildren.begin(); it != u->mChildren.end(); ++it)
			{
				depthFirstSearchHelper(*it, counter);
			}
		}

		void depthFirstSearchPrint()
		{
			string dfsString = "";

			// begin depth first search from root
			depthFirstSearchPrintHelper(mRoot, dfsString);
		}

		void depthFirstSearchPrintHelper(Node *n, string dfsString)
		{
			dfsString += mSequence.substr(n->mIndex, n->mLength);

			if(n->mChildren.size() < 1)
			{
				cout << n->mId << "   " << n->mStringDepth << "   " << dfsString <<  endl;
				return;
			}

			for(vector<Node*>::iterator it = n->mChildren.begin(); it != n->mChildren.end(); ++it)
			{
				depthFirstSearchPrintHelper(*it, dfsString);
			}
		}
};