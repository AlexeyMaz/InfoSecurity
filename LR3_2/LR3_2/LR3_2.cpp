#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void main() {
	ifstream input("input.txt");
	string res = "", str = "";
	vector<int> inds;
	int count = 0, last_ind = 0;
	input >> str; input.close();

	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 1; j < str.length(); j++)
			if (str[i] == str[j])
			{
				count++;
				last_ind = j;
			}

		if (count == 0)
		{
			if (find(inds.begin(), inds.end(), last_ind) == inds.end())
				inds.push_back(i);
		}
		else
		{
			count = 0;
			if (find(inds.begin(), inds.end(), last_ind) == inds.end())
				inds.push_back(last_ind);
		}
	}

	sort(inds.begin(), inds.end());
	for (int i = 0; i < inds.size(); i++)
		res += str[inds[i]];

	ofstream output("output.txt");
	output << res;
}