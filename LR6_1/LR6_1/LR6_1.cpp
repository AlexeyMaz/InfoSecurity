#include <iostream>   
#include <vector>  
#include <string>
using namespace std;

string RW_gen()
{
	int a = rand() % 2;
	if (a == 0)
		return "R";
	if (a == 1)
		return "W";
}

int main()
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

	cout << "Генерация RW" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (inp == 0)
				cin >> RW[i][j];
			else
				RW[i][j] = RW_gen();
		}

	cout << "Вывод сгенерированной матрицы на права записи и чтения" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << RW[i][j] << ' ';
		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		if (inp == 0)
			cin >> LS[i];
		else
			LS[i] = rand() % 3 + 1;
	}

	for (int i = 0; i < m; i++)
	{
		if (inp == 0)
			cin >> LO[i];
		else
			LO[i] = rand() % 3 + 1;
	}

	cout << "Вывод LS" << endl;
	for (int i = 0; i < n; i++)
		cout << LS[i] << " ";
	cout << endl;

	cout << "Вывод LO" << endl;
	for (int i = 0; i < m; i++)
		cout << LO[i] << " ";
	cout << endl;

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
		cout << "True" << endl;
	else
		cout << "False" << endl;
}