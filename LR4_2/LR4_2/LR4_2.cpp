#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    ifstream input("alarm.in.txt");
    vector<int> d;
    vector<vector<int>> corridors;
    int res = 0, n = 0;
    string s;
    
    getline(input, s);
    for (int i = 0; i < s.size(); ++i) 
    {
        n += s[i] - 48;
        n *= 10;
    }
    n /= 10;

    getline(input, s);
    for (int i = 0; i < n * 2 - 1; ++i)
        if (s[i] != ' ') 
            d.push_back(s[i] - 48);

    vector<int> tmp(3);
    while (!input.eof())
    {
        copy_n(istream_iterator<int>(input), 3, tmp.begin());
        corridors.push_back(tmp);
    }
    
    for (int i = 0; i < corridors.size(); ++i) {
        for (int j = 0; j < 3; ++j)
            cout << corridors[i][j] << " ";
        cout << endl;
    }

    ofstream output("alarm.out.txt");
    output << res;
}