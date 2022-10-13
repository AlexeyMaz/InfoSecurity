#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

int n, k;
vector<char> CompObj, alphabet;

string result = "";

string RW_gen()
{
	int a = rand() % 2;
	if (a == 0)
		return "R";
	if (a == 1)
		return "W";
}

void InputAlpha(int x)
{
	n = 3;
	k = x;
	alphabet.resize(n);
	alphabet = { '1','2','3' };
}

void PrintCompObjWithCondition(int k)
{
	string ObjToPrint = "";
	for (int i = 0; i < k; i++)
	{
		ObjToPrint += CompObj[i];
	}
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
	int n, m;
	cout << "Введите число субъектов и объектов через пробел: ";
	cin >> n >> m;
	cout << "Ручной ввод - 0, автоматический - 1" << endl;
	int inp = 0;
	cin >> inp;

	vector < vector <string> > RW(n, vector <string>(m));
	vector <int> LS(n);
	vector <int> LO(m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (inp == 0)
				cin >> RW[i][j];
			else
				RW[i][j] = RW_gen();
		}

	InputAlpha(n);
	Process();
	ofstream Output_LS("LS.txt");
	Output_LS << result << endl;
	Output_LS.close();
	CompObj.clear();
	result = "";

	InputAlpha(m);
	Process();
	ofstream Output_LO("LO.txt");
	Output_LO << result << endl;
	Output_LO.close();
	CompObj.clear();
	result = "";

	vector <string> LS_s, LO_s;

	string LS_, LO_;
	ifstream inp_LS("LS.txt");
	while (getline(inp_LS, LS_)) 
	{
		LS_s.push_back(LS_);
	}
	inp_LS.close();

	ifstream inp_LO("LO.txt");
	while (getline(inp_LO, LO_)) 
	{
		LO_s.push_back(LO_);
	}
	inp_LO.close();

	LS_s.pop_back();
	LO_s.pop_back();

	string TMP_S, TMP_O;
	bool isNormal = false;
	for (int p = 0; p < LS_s.size(); p++)
	{
		TMP_S = LS_s[p];
		transform(TMP_S.begin(), TMP_S.end(), LS.begin(), [](char c) {return c - '0'; });

		for (int e = 0; e < LO_s.size(); e++)
		{
			TMP_O = LO_s[e];
			transform(TMP_O.begin(), TMP_O.end(), LO.begin(), [](char c) {return c - '0'; });
			bool ok = true;
			for (int i = 0; i < n; i++)
			{
				if (!ok)
					break;
				for (int j = 0; j < m; j++)
				{

					if ((LS[i] < LO[j] && RW[i][j] == "W") || (LS[i] > LO[j] && RW[i][j] == "R"))
					{
						ok = false;
						break;
					}
				}
			}
			if (ok) 
			{
				isNormal = true;
				goto m;
			}
		}

	}
m:
	cout << "Вывод сгенерированной матрицы на права записи и чтения" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << RW[i][j] << ' ';
		cout << endl;
	}

	cout << "Вывод LS" << endl;
	for (int i = 0; i < n; i++)
		cout << LS[i] << " ";
	cout << endl;

	cout << "Вывод LO" << endl;
	for (int i = 0; i < m; i++)
		cout << LO[i] << " ";
	cout << endl;


	if (isNormal)
		cout << "True" << endl;
	else
		cout << "False" << endl;

}