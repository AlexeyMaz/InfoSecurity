#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main() {
	ifstream input("input.txt");
	string text;
	input >> text;
	input.close();

	int i = 0, len = text.length();
	while (i < len - 1)
	{
		if (text[i] == text[i + 1])
		{
			text = text.substr(0, i) + text.substr(i + 2, len - i - 2);
			if (i > 0)
				i--;
			len -= 2;
		}
		else
			i++;
	}

	ofstream output("output.txt");
	output << text;
}