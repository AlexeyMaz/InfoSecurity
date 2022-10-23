#include <iostream>
#include <vector>

// т.к в задаче не сказано про добавление/удаление/какую-либо
// работу с объектами, то будем считать что в рамках данной задачи
// количество объектов из матрицы извлекается один раз и не меняется
// во время работы программы

using namespace std;
struct Item {
	int subj_i; // можно использовать как имя объекта
	int obj_j;
	string value;
	/*int _subj_name;*/
};

string RW_gen() // рандоматор прав доступа на чтение, запись и отсутствие прав(у меня нет прав(это правда))
{
	string M[2] = { "R","W" };
	int w = 2;
	int i, j, n;
	string buff;
	n = pow(2, w);
	vector <string> RWOX;
	for (int i = 0; i < n; i++)
	{
		for (j = 0; j < w; j++)
			if (i & (1 << j))
				buff += M[j];
		RWOX.push_back(buff);
		buff = "";
	}
	int rander = rand() % 3 + 1;
	int rander_empty_or_not = rand() % 2;
	string for_return;
	if (rander_empty_or_not == 1)
		for_return = RWOX[rander];
	else
		for_return = "_";
	return for_return;
}

bool subj_find(vector <Item> Items, int i)
{
	for (int d = 0; d < Items.size(); d++)
		if (Items[d].subj_i == i)
			return true;
	return false;
}
bool obj_find(vector <Item> Items, int j)
{
	for (int d = 0; d < Items.size(); d++)
		if (Items[d].obj_j == j)
			return true;
	return false;
}
bool tran_find(vector <Item> Items, int i, int j)
{
	for (int d = 0; d < Items.size(); d++)
		if (Items[d].subj_i == i && Items[d].obj_j == j)
			return true;
	return false;

}
int insert_index(vector <Item> Items, int i, int j)
{
	int ind = -1;
	if (!subj_find(Items, i))
	{
		for (int d = 0; d < Items.size() - 1; d++)
		{
			if (Items[d].subj_i < i && Items[d + 1].subj_i > i) // (1,x) (3,x) -> (2,x)
				ind = d + 1;
			else if (Items[d].subj_i > i && Items[d + 1].subj_i < i) // (2,x) (3,x) -> (1,x)
				ind = d;
			else if (Items[d].subj_i < i) // (2,x) (3,x) -> (4,x)
				ind = d + 1;
		}
		if (Items[Items.size() - 1].subj_i < i) // (3,x) (4,x) -> (5,x)
			return Items.size();
		if (ind != -1)
			return ind;
	}
	else if (subj_find(Items, i))
	{
		if (Items[Items.size() - 1].subj_i == i) // (4,x) (5,1) -> (5,2)
			if (Items[Items.size() - 1].obj_j > j)
				ind = Items.size() - 1;
			else if (Items[Items.size() - 1].obj_j < j)
				ind = Items.size();
		if (ind != -1)
			return ind;
	}
	if (subj_find(Items, i) && ind == -1)
		for (int d = 0; d < Items.size() - 1; d++)
		{
			if (Items[d].subj_i == i)
			{
				if (Items[d].obj_j < j && Items[d + 1].subj_i == i && Items[d + 1].obj_j > j) // (1,1) (1,3) -> (1,2)
					ind = d + 1;
				else if (Items[d].obj_j < j && Items[d + 1].subj_i != i) // (1,2) (2,x) -> (1,3)
					ind = d + 1;
				if (Items[d].obj_j > j) // (1,2) (2,x) -> (1,1)
					ind = d;
			}
			if (ind != -1)
				return ind;
		}

	if (ind != -1)
		return ind;
}


void output(vector <Item> Items)
{
	cout << "----------------------------------------" << endl;
	cout << "Вывод сгенерированной разряженной матрицы" << endl;
	cout << "В формате: имя субъекта, имя объекта, права доступа" << endl;
	cout << "" << endl;
	for (int i = 0; i < Items.size(); i++)
	{
		cout << Items[i].subj_i + 1 << " " << Items[i].obj_j + 1 << " " << Items[i].value << endl;
	}
	cout << "----------------------------------------" << endl;
}
void clear(vector <Item>& Items)
{
	for (int d = 0; d < Items.size(); d++)
	{
		if (Items[d].value == "")
		{
			Items.erase(Items.begin() + d);
		}
	}
}

void change_rule(vector <Item>& Items, int act, int i, int j, string rule)
{
	// удаление права - 1, добавление права - 2 отвечает переменная act
	bool standart = false;
	for (int d = 0; d < Items.size(); d++)
	{
		if (Items[d].subj_i == i && Items[d].obj_j)
		{
			standart = true;
		}
		if (Items[d].subj_i == i && Items[d].obj_j == j && act == 1)
		{
			string res = rule;
			for (int inputInd = 0; inputInd < res.size(); inputInd++)
			{
				for (int nowInd = 0; nowInd < Items[d].value.size(); nowInd++)
				{
					if (res[inputInd] == Items[d].value[nowInd])
					{
						Items[d].value = Items[d].value.substr(0, nowInd) + Items[d].value.substr(nowInd + 1, Items[d].value.size() - nowInd - 1);
						break;
					}
				}
			}
		}
		if (Items[d].subj_i == i && Items[d].obj_j == j && act == 2)
		{
			string res = rule;
			for (int inputInd = 0; inputInd < res.size(); inputInd++)
			{
				bool f = true;
				for (int nowInd = 0; nowInd < Items[d].value.size(); nowInd++)
				{
					if (res[inputInd] == Items[d].value[nowInd])
					{
						f = false;
						break;
					}
				}
				if (f)
				{
					Items[d].value += res[inputInd];
				}
			}
			if (Items[d].value == "WR")
				Items[d].value = "RW";

			standart = false;
		}
	}
	if (!tran_find(Items, i, j) && act == 2)
	{
		Item temp;
		temp.subj_i = i;
		temp.obj_j = j;
		temp.value = rule;

		Items.insert(Items.begin() + insert_index(Items, i, j), temp);
	}
	clear(Items);
	output(Items);
}

void insert_new_subj(vector <Item>& Items, int new_subj_i, int obj_count)
{
	Item temp;
	temp.subj_i = new_subj_i;
	temp.value = "R";
	for (int i = 0; i < obj_count; i++)
	{
		temp.obj_j = i;
		Items.insert(Items.begin() + insert_index(Items, new_subj_i, i), temp);
	}
	clear(Items);
	output(Items);
}

void delete_subj(vector <Item>& Items, int del_subj_i)
{
	bool finded = false;
	for (int i = 0; i < Items.size(); i++)
	{
		if (Items[i].subj_i == del_subj_i)
		{
			Items.erase(Items.begin() + i);
			i--;
		}
	}
	clear(Items);
	output(Items);
}

void usage_prc(vector <Item>& Items, int n, int m)
{
	cout << "размер матрицы NxM :" << n << "x" << m << endl;
	cout << "всего клеток в матрице :" << n * m << endl;
	cout << "заполненных клеток в матрице :" << Items.size() << endl;
	cout << "заполненность матрицы :" << float((Items.size() / float(n * m)) * 100) << "%" << endl;
}
void list_for_t(vector <Item>& Items, int obj_index)
{
	vector <int> answer = vector <int>();
	for (int i = 0; i < Items.size(); i++)
	{
		if (!(find(answer.begin(), answer.end(), Items[i].subj_i) != answer.end()) && Items[i].obj_j == obj_index)
			answer.push_back(Items[i].subj_i);
	}
	cout << "вывод списка субъектов с доступом к объекту t" << endl;
	for (int i = 0; i < answer.size(); i++)
	{
		cout << answer[i] << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(0));
	int n, m;
	//cout << "Введите число субъектов и объектов через пробел: ";
	//cin >> n >> m;
	n = 5, m = 3;
	vector <Item> Items = vector <Item>();

	cout << "генерация rw" << endl;
	for (int i = 0; i < n; i++) // строки-субъекты
	{
		for (int j = 0; j < m; j++) // столбцы-объекты
		{
			string temp_RW = RW_gen();
			if (temp_RW != "_")
			{
				Item temp_item;
				temp_item.subj_i = i;
				temp_item.obj_j = j;
				temp_item.value = temp_RW;
				Items.push_back(temp_item);
			}
		}
	}
	output(Items);


	int Inp;
	do
	{
		cout << "\n1 - редактирование содержимого любой ячейки" << endl;
		cout << "2 - добавление нового субъекта в матрицу с указанием его номера" << endl;
		cout << "3 - удаление субъекта из матрицы" << endl;
		cout << "4 - вычисление процента заполненности матрицы(общее число/хранимое число)" << endl;
		cout << "5 - формирование списка субъектов, имеющих доступ к указанному объекту" << endl;
		cout << "0 - выход из программы" << endl;
		cout << "\nВведите команду: ";
		cin >> Inp;
		cout << endl;
		if (Inp == 1)
		{
			cout << "редактирование ячейки" << endl;
			int act, i, j;
			cout << "удаление права - 1, добавление права - 2" << endl;
			cin >> act;
			string rule;
			cout << "введите номер субъекта, номер объекта и право" << endl;
			cin >> i >> j >> rule;
			i--; j--;
			if (!subj_find(Items, i) && (i > n || i < 0))
				cout << "не выполнено, такого субъекта нет" << endl;
			else if (!obj_find(Items, j) && (j > m || j < 0))
				cout << "не выполнено, такого объекта нет" << endl;
			else if (tran_find(Items, i, j) || i <= n && j <= m && i >= 0 && j >= 0)
				change_rule(Items, act, i, j, rule);
		}
		if (Inp == 2)
		{
			cout << "добавление субъекта" << endl;
			int new_subj_i;
			cout << "введите числовой индекс(имя) нового субъекта" << endl;
			cin >> new_subj_i;
			new_subj_i--;
			if (subj_find(Items, new_subj_i))
				cout << "не выполнено, такой субъект уже есть" << endl;
			else
			{
				insert_new_subj(Items, new_subj_i, m);
				n++;
			}
		}
		if (Inp == 3)
		{
			cout << "удаление субъекта" << endl;
			int del_subj_i;
			cout << "введите числовой индекс(имя) удаляемого субъекта" << endl;
			cin >> del_subj_i;
			del_subj_i--;
			if (!subj_find(Items, del_subj_i))
				cout << "не выполнено, такого субъекта нет" << endl;
			else
			{
				delete_subj(Items, del_subj_i);
				n--;
			}
		}
		if (Inp == 4)
		{
			cout << "вычисление заполненности матрицы" << endl;
			usage_prc(Items, n, m);
		}
		if (Inp == 5)
		{
			cout << "список субъектов с доступом к объекту t" << endl;
			cout << "введите числовой индекс объекта t" << endl;
			int obj_m;
			cin >> obj_m;
			obj_m--;
			if (!obj_find(Items, obj_m))
				cout << "не выполнено, такого объекта нет" << endl;
			else
				list_for_t(Items, obj_m);
		}
	} while (Inp != 0);
}