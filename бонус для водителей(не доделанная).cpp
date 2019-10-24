#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> Getprice(const vector<int>& T,int& n) {
	vector<int> Money;
	if (n == 1) {
		return {500};
	}
	for (auto it = begin(T); it != end(T);it++) {
		if (it == begin(T)) {
			Money.push_back(1);
			continue;
		}
		if (*(it - 1) < *it) {
			int k = it - begin(T);
			Money.push_back(Money[k-1] + 1);
		}
		else {		//убывание
			int k = it - begin(T);
			if (*(it-1) == *it) {
				vector<int> Sorted = Money;
				sort(begin(Sorted), end(Sorted));
				Money.push_back(Sorted[0]);
			}
			else {
				Money.push_back(Money[k - 1] - 1);	
			}
		}
	}
	return Money;
}

int FitMoney(vector<int>& Money) {
	int res = 0;
	vector<int> Sorted = Money;
	sort(begin(Sorted), end(Sorted));
	int min = *begin(Sorted);
	if (min <= 0) {
		int MIN = (min + abs(min - 1));
		for (auto& item : Money) {
			item = ((item + abs(min - 1)) * 500) / MIN;
			res += item;
		}
	}
	else {
		for (auto item : Money) {
			item = (item / min) * 500;
			res += item;
		}
	}
	return res;
}

int main() {
	string Number;//количество таксистов
	string Rating;
	int R;
	vector<int> Taxists;
	ifstream input("input.txt");
	input >> Number;
	int n = stoi(Number);
	for (int i = n; i > 0; i--) {
		input >> Rating;
		R = stoi(Rating);
		Taxists.push_back(R);
	}
	vector<int> Money = Getprice(Taxists,n);
	cout << FitMoney(Money);
	return 0;
}