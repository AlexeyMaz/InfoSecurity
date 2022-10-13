#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//дан гамильтонов граф - граф,содержащий гамильтонов цикл - цикл,который проходит через все вершины графа,причём один раз
//минимальное количество сирен в наборе, удовлетворяющее условиям безопасности - количество компонент связности 

vector<int> g[1000];  // вектор смежности
bool used[1000];  // вектор помеченных вершин
vector<int> comp;  // вектор компонент связности
vector<int> d;  // вектор вершин
int matr[1000][1000];

//обход в глубину
void dfs(int v)
{
	used[v] = true;
	comp.push_back(v);
	for (int i = 0; i < g[v].size(); ++i)
	{
		if (v == i)
			continue;
		int to = g[v][i];
		if (!used[to] && abs(d[v] - matr[v][i]) >= 0)
		{
			if (d[v] < d[i] - d[v])
				d[v] = d[i] - d[v];
			dfs(to);
		}
	}
}

//поиск компонент связности
int find_comps(int n)
{
	int ans = 0;
	for (int i = 0; i < n; ++i)
		if (!used[i])
		{
			comp.clear();
			dfs(i);
		}

	ans = comp.size();
	return ans;
}

int main()
{
	ifstream input("alarm.in.txt");
	ofstream output("alarm.out.txt");
	int n = 0, a, b, c;

	if (!input.eof())
	{
		input >> n;
		for (int i = 0; i < n; i++)
		{
			input >> a;
			d.push_back(a);
		}
	}

	while (!input.eof())
	{
		input >> a;
		input >> b;
		input >> c;
		g[a].push_back(b);
		matr[a][b] = c;
	}
	input.close();
	output << find_comps(n);
}