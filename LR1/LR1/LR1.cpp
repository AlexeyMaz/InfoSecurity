#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	string s, word, t; int i;
	vector <string> all_words;
	ifstream input("input.txt");
	ofstream output("output.txt");

	while (!input.eof())
	{
		getline(input, s);
		stringstream str(s);
		while (str >> word)
		{
			all_words.push_back(word);
		}
		for (i = 0; i < all_words.size(); i++)
		{
			t = all_words[i];
			if (size(all_words[i]) > 3)
				rotate(t.rbegin(), t.rbegin() + 3, t.rend());
			else if (size(all_words[i]) == 2)
				rotate(t.rbegin(), t.rbegin() + 1, t.rend());
			output << t + ' ';
			cout << t + ' ';
		}
	}
	input.close();
	output.close();
	cout << "\n";
}