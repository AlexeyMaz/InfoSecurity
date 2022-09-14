#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string str; int sum = 0;
    ifstream input("input.txt");
    ofstream output("output.txt");
    while (!input.eof())
    {
        getline(input, str);
        for (int i = 0; i < size(str); ++i)
            sum += str[i] - 48;
        output << 9 * (sum / 9 + 1) - sum;
    }
    input.close();
    output.close();
}