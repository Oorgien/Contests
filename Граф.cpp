#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#include <exception>
//#include "tests.h"

using namespace std;


class Graf {
private:
	map<pair<string, string>, int> graf;
	set<string> Points;
	set<vector<string>> Ribs;

public:
	//Добавляет вершины графа из контейнера
	void AddPoints(vector<vector<string>> v);
	//Дает кол-во точек
	size_t GetPoints();
	//Дает кол-во вершин
	size_t GetRibs();
	map<pair<string, string>, int> ShowGraf();
};
//Добавляет вершины графа из контейнера
void Graf::AddPoints(vector<vector<string>> v) {
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j+1 < v[i].size(); j++) {
			auto p = make_pair(v[i][j], v[i][j + 1]);
			if (j == 0 && graf.count(p) == 0) {
				graf[p] = 1;
			}
			else {
				graf[p] += 1;
			}
		}
	}
}
//Дает кол-во точек
size_t Graf::GetPoints() {
	for (auto& item : graf) {
		Points.insert(item.first.first);
		Points.insert(item.first.second);
	}
	return Points.size();
}
//Дает кол-во вершин
size_t Graf::GetRibs() {
	return graf.size();
}
map<pair<string, string>, int> Graf::ShowGraf() {
	return graf;
}

//режет строку на n-2 слова, принимает строку и n - длину слова;
vector<string> CutStr(string& s) {
	size_t n = s.size();
	vector<string> cutted;
	size_t k = 0;
	while (k+2 < n) {
		string tmp = "";
		for (size_t i = k; i < k + 3; i++) {
			tmp += s[i];
		}
		cutted.push_back(tmp);
		tmp.clear();
		++k;
	}
	return cutted;
}

//считывает все К слов, которые вводятся из консоли и режет их на подслова
vector<vector<string>> ReadStrings() {
	int k;
	cin >> k;
	vector<vector<string>> Words;
	while (k > 0) {
		string word;
		vector<string> cutted;
		cin >> word;
		cutted = CutStr(word);
		Words.push_back(cutted);
		k--;
	}
	return Words;
}


ostream& operator<<(ostream& os, map<pair<string, string>, int>& m) {
	int k = 1;
	for (const auto& item : m) {
		if (k != m.size()) {
			os << item.first.first << " " << item.first.second << " " << item.second << endl;
			k++;
		}
		else {
			os << item.first.first << " " << item.first.second << " " << item.second;
		}
	}
	return os;
}

int main() {

	Graf graf;
	vector<vector<string>> Words = ReadStrings();
	graf.AddPoints(Words);
	map<pair<string, string>, int> g = graf.ShowGraf();
	cout <<graf.GetPoints() << endl<< graf.GetRibs() << endl<< g;
	return 0;
}