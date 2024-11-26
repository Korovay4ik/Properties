#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

constexpr auto Reflexivity = 1;
constexpr auto Antireflexivity = 2;
constexpr auto Symmetry = 3;
constexpr auto Antisymmetry = 4;
constexpr auto Asymmetry = 5;
constexpr auto Transitivity = 6;
constexpr auto Connectivity = 7;
constexpr auto Nothing = 10;

static int reflexivityCheck(vector<vector<int>>& set)
{
	bool isRefl = false, isAntiRefl = false;

	for (size_t i = 0; i < set.size(); i++) {
		if (isRefl && !set[i][i]) {
			isRefl = false;
			break;
		}
		else if (isAntiRefl && set[i][i]) {
			isAntiRefl = false;
			break;
		}

		if (set[i][i]) isRefl = true;
		else if (!set[i][i]) isAntiRefl = true;
	}

	if (isRefl) return Reflexivity;
	else if (isAntiRefl) return Antireflexivity;
	else return Nothing;
}

static int symmetryCheck(vector<vector<int>>& set)
{
	bool exNotSymm = false, exNotAntiSymm = false, exNotASymm = false;
	int correction = set.size() - 1;

	for (size_t i = 0; i < set.size(); i++) {
		for (size_t j = 0; j < set[i].size() - correction; j++) {
			if (set[i][j] && set[j][i]) {
				exNotASymm = true;
				if (i != j) exNotAntiSymm = true;
			}
			else if (set[i][j] != set[j][i]) {
				exNotSymm = true;
			}
		}
		if (correction) correction--;
	}

	if (!exNotSymm) return Symmetry;
	else if (!exNotASymm) return Asymmetry;
	else if (!exNotAntiSymm) return Antisymmetry;
	else return Nothing;
}

static int transitivityCheck(vector<vector<int>>& set)
{
	for (int i = 0; i < set.size(); i++) {
		for (int j = 0; j < set.size(); j++) {
			if (set[i][j]) {
				for (int k = 0; k < set.size(); k++) {
					if (set[j][k]) {
						if (!set[i][k]) {
							return Nothing;
						}
					}
				}
			}
		}
	}
	return Transitivity;
}

static int connectivityCheck(vector<vector<int>>& set)
{
	int correction = set.size() - 1;

	for (int i = 0; i < set.size(); i++) {
		for (int j = 0; j < set.size() - correction; j++) {
			if (i != j) {
				if (!set[i][j] && !set[j][i]) {
					return Nothing;
				}
			}
		}
	}
	return Connectivity;
}

static vector<vector<int>> readMatrix(ifstream& file) {
	vector<vector<int>> set;
	string line;

	while (getline(file, line)) {
		if (line == "=") {
			break;
		}

		vector<int> row;
		for (char ch : line) {
			if (ch != ' ') row.push_back(ch - '0');
		}
		set.push_back(row);
	}
	return set;
}

static vector<int> properties(vector<vector<int>> set)
{
	vector<int> result;

	result.push_back(reflexivityCheck(set));
	result.push_back(symmetryCheck(set));
	result.push_back(transitivityCheck(set));
	result.push_back(connectivityCheck(set));

	return result;
}

int main()
{
	system("chcp 1251>null");
	
	ifstream file("m.txt");

	if (!file.is_open()) {
		cerr << "Ошибка при открытии файла!" << endl;
		return 1;
	}

	int countSets = 0;

	while (true) {
		vector<vector<int>> set = readMatrix(file);
		if (set.empty()) {
			break;
		}

		if (countSets) cout << "\n\n";
		for (size_t i = 0; i < set.size(); i++) {
			for (size_t j = 0; j < set[i].size(); j++) {
				cout << set[i][j] << ' ';
			}
			cout << endl;
		}
		
		vector<int> result = properties(set);

		for (size_t i = 0; i < result.size(); i++) {
			switch (result[i])
			{
			case Reflexivity:
				cout << "Рефлексивно\n";
				break;
			case Antireflexivity:
				cout << "Антирефлексивно\n";
				break;
			case Symmetry:
				cout << "Симметрично\n";
				break;
			case Antisymmetry:
				cout << "Антисимметрично\n";
				break;
			case Asymmetry:
				cout << "Асимметрично\n";
				break;
			case Transitivity:
				cout << "Транзитивно\n";
				break;
			case Connectivity:
				cout << "Связное\n";
				break;
			case Nothing:
				break;
			default:
				break;
			}
		}
		countSets++;
	}

	file.close();
	return 0;
}
