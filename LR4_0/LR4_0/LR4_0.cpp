#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int n;
int k;
vector<char> CompObj;
vector<char> alphabet;

string result = "";

void InputAlpha()
{
	n = 3;
	k = 8;
	alphabet.resize(n);
	alphabet = { '2','5','7' };
}

bool Condition(string inp)
{
	if (count(inp.begin(), inp.end(), '2') == 2 && count(inp.begin(), inp.end(), '5') == 2)
		return true;
	else
		return false;
}

void PrintCompObjWithCondition(int k)
{
	string ObjToPrint = "";
	for (int i = 0; i < k; i++)
	{
		ObjToPrint += CompObj[i];
	}
	if (Condition(ObjToPrint))
		result += ObjToPrint + "\n";
}

bool HasNextCompObj()
{
	int kol = 0;
	for (int i = 0; i < k; i++)
		if (CompObj[i] == alphabet[n - 1]) kol++;
	return (kol != k);
}
void NextCompObj()
{
	for (int i = k - 1; i > -1; i--)
	{
		if (CompObj[i] == alphabet[n - 1])
		{
			CompObj[i] = alphabet[0];
			continue;
		}
		CompObj[i]++;

		while (!(find(alphabet.begin(), alphabet.end(), CompObj[i]) != alphabet.end()))
		{
			CompObj[i]++;
		}
		break;
	}
}

void Process()
{
	CompObj.resize(k);
	for (int i = 0; i < k; i++)
		CompObj[i] = alphabet[0];
	while (HasNextCompObj())
	{
		PrintCompObjWithCondition(k);
		NextCompObj();
	}
	PrintCompObjWithCondition(k);
}

void main()
{
	setlocale(LC_ALL, "RUS");
	InputAlpha();
	Process();
	fstream Result;
	Result.open("output.txt", fstream::in | fstream::out | fstream::app);
	Result << result << endl;
	Result.close();
}