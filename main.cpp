#include <iostream>
#include <string.h>
#include "help.cpp"
#include "suffixtree.cpp"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	/* string header;
	string sequence;
	string alphabet;

	determineArgs(argv[1], argv[2], &header, &sequence, &alphabet);

	cout << header << endl;
	cout << sequence << endl;
	cout << alphabet << endl; */

	/* vector<char> v;
		v.push_back('b');
		v.push_back('a');
		v.push_back('n');
		v.push_back('a');
		v.push_back('n');
		v.push_back('a');

	char c = 'z';
	vector<char>::iterator it = v.begin();;

	for(it; it != v.end(); ++it)
	{
		if(c < (*it))
			break;
	}

	v.insert(it, c);
	it = v.begin();;

	for(it; it != v.end(); ++it)
	{
		cout << (*it) << endl;
	} */

	/* string a = "banana";
	char *b = &(a.at(1));
	a[1] = 'c';

	cout << a << endl;
	cout << b << endl; */

	return 0;
}