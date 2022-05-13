#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>
#include<map>
#include<string>

using namespace std;

bool comp(string s1, string s2) {
	if (s1.size() < s2.size()) return true;
	else if (s1.size() == s2.size() && s1 < s2) return true;
	else return false;
}

bool comp2(pair <vector <vector <int>>, string> s1, pair <vector <vector <int>>, string> s2) {
	if (s1.second.size() < s2.second.size()) return true;
	else if (s1.second.size() == s2.second.size() && s1.second < s2.second) return true;
	else return false;
}

int find_number(char* els, int n, char x) {
	for (int i = 0; i < n; i++) {
		if (els[i] == x)
			return i;
	}
}

bool assoc(char** v, char* els, int n) {
	int checker = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (v[find_number(els, n, v[i][j])][k] != v[i][find_number(els, n, v[j][k])])
					return false;
			}
		}
	}
	return true;
}


bool check_uniq(vector <char> v, int n, char x) {
	for (int i = 0; i < n; i++)
		if (v[i] == x)
			return false;
	return true;
}

vector <char> find_xi_(char** v, int n, vector <char> xi, int m, char* els) {
	vector <char> res;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			char vij = v[find_number(els, n, xi[i])][find_number(els, n, xi[j])];
			if (check_uniq(res, res.size(), vij)) {
				res.push_back(vij);
			}
		}
	}
	return res;
}


vector <char> xi_union(vector <char> xi, int n, vector <char> xi_, int m) {
	vector <char> res(n);
	for (int i = 0; i < n; i++) {
		res[i] = xi[i];
	}
	for (int i = 0; i < m; i++) {
		if (check_uniq(res, res.size(), xi_[i]))
			res.push_back(xi_[i]);
	}
	return res;
}


void alg_1(char** v, int n, vector <char> v0, int m, char* els) {
	vector <char> xi(m);
	vector <char> xi_;
	for (int i = 0; i < m; i++)
		xi[i] = v0[i];
	while (true) {
		xi_ = find_xi_(v, n, xi, xi.size(), els);
		vector <char> x_new = xi_union(xi, xi.size(), xi_, xi_.size());
		if (xi.size() == x_new.size())
			break;
		else
			xi = x_new;
	}
	sort(xi.begin(), xi.end());
	cout << endl;
	for (int i = 0; i < xi.size(); i++) {
		cout << xi[i] << " ";
	}
}




map <pair<string, string>, string> kely;

vector <vector <int>> my_multiplication(vector <vector <int>> v1, vector <vector <int>> v2, int n) {
	vector <vector <int>> res(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int count = 0;
			for (int k = 0; k < n; k++) {
				if (v1[i][k] * v2[k][j]) {
					count = 1;
					break;
				}
			}
			res[i].push_back(count);
		}
	}
	return res;
}


bool checker_uniq(vector <pair <vector <vector <int>>, string>> v, int l, vector <vector <int>> x) {
	for (int i = 0; i < l; i++) {
		if (v[i].first == x)
			return false;
	}
	return true;
}


bool checker_uniq_kely(vector <pair <vector <vector <int>>, string>> v, int l, vector <vector <int>> x, string xi, string xj) {
	for (int i = 0; i < l; i++) {
		if (v[i].first == x) {
			kely[make_pair(xi, xj)] = v[i].second;
			return false;
		}
	}
	return true;
}


vector <pair <vector <vector <int>>, string>> find_multi(vector <pair <vector <vector <int>>, string>> v, int l, int n) {
	vector <pair <vector <vector <int>>, string>> res;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++) {
			vector <vector <int>> mult = my_multiplication(v[i].first, v[j].first, n);
			if (checker_uniq_kely(res, res.size(), mult, v[i].second, v[j].second)) {
				res.push_back(make_pair(mult, v[i].second + v[j].second));
				kely[make_pair(v[i].second, v[j].second)] = v[i].second + v[j].second;
			}
		}
	}
	return res;
}


vector <pair <vector <vector <int>>, string>> find_union_matr(vector <pair <vector <vector <int>>, string>> v1, vector <pair <vector <vector <int>>, string>> v2, int l1, int l2, int n) {
	vector <pair <vector <vector <int>>, string>> res = v1;

	for (int i = 0; i < l2; i++) {
		if (checker_uniq(res, res.size(), v2[i].first)) {
			res.push_back(v2[i]);
		}
	}
	return res;
}


void alg_2(vector <pair <vector <vector <int>>, string>> matr, int l, int n) {
	vector <pair <vector <vector <int>>, string>> xi = matr;

	while (true) {
		vector <pair <vector <vector <int>>, string>> xi_ = find_multi(xi, xi.size(), n);
		vector <pair <vector <vector <int>>, string>> x_new = find_union_matr(xi, xi_, xi.size(), xi_.size(), n);
		if (xi.size() == x_new.size())
			break;
		else
			xi = x_new;
	}


	sort(xi.begin(), xi.end(), comp2);
	cout << endl << "ОТВЕТ" << endl;
	for (int i = 0; i < xi.size(); i++) {
		cout << xi[i].second << ":" << endl;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				cout << xi[i].first[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	cout << endl;


	cout << setw(7) << "";
	for (pair <vector <vector <int>>, string> ans : xi)
		cout << setw(7) << ans.second;

	cout << endl;
	for (pair <vector <vector <int>>, string> ans : xi) {
		cout << setw(7) << ans.second << setw(7);
		for (pair <vector <vector <int>>, string> ans2 : xi) {
			pair<string, string> res = make_pair(ans.second, ans2.second);
			cout << kely[res] << setw(7);
		}
		cout << endl;
	}
	cout << endl;
}



set<string> setOfr;
map<string, string> r;
set<string> s, s_cur, s_tmp, s_i_tmp;
int mx = 0;
int mn = 0;
int cnt;
string cur_word;
map<string, string> help;


void handler(string word, int check)
{
	cur_word = "";
	if (word.size() >= 0) {
		if (setOfr.find(word) != setOfr.end()) {
			s_i_tmp.insert(word);
			for (string x : s_i_tmp) {
				if (x != word)
					help[x] = word;

			}
			for (int i = 0; i < 1; i++) {
				map <string, string> ::iterator it = help.begin();
				while (it != help.end()) {
					if (help[it->second] != "")
						help[it->first] = help[it->second];
					it++;
				}
			}

			if (s.find(word) != s.end()) {
				help[word] = word;
			}

			return;
		}
		s_i_tmp.insert(word);
		help[word] = word;


		string word_ = word;

		int tmp = mx;
		while (tmp >= mn)
		{
			for (int i = word_.size() - 1; i >= 0; i--)
			{
				cur_word = "";
				string part = "";
				if (tmp > word.size() || tmp > i + 1)
					break;
				int j, j_Start, j_end;
				for (j = i; j > i - tmp; j--) {
					part = word_[j] + part;
					j_Start = i - tmp + 1;
				}

				if (r.find(part) != r.end()) {
					for (int k = 0; k < j_Start; ++k)
						cur_word = cur_word + word_[k];

					cur_word = cur_word + r[part];

					for (int k = i + 1; k < word_.size(); k++)
						cur_word = cur_word + word_[k];


					if (s_i_tmp.find(cur_word) == s_i_tmp.end()) {

						if (cur_word.size() < word.size())
						{
							s_i_tmp.insert(cur_word);
							help[word] = cur_word;
							for (int i = 0; i < 1; i++) {
								map <string, string> ::iterator it = help.begin();
								while (it != help.end()) {
									if (help[it->second] != "")
										help[it->first] = help[it->second];
									it++;
								}
							}
							handler(cur_word, check + 1);
							return;
						}

						else if (setOfr.find(cur_word) != setOfr.end()) {
							for (string x : s_i_tmp) {
								help[x] = cur_word;
								for (int i = 0; i < 1; i++) {
									map <string, string> ::iterator it = help.begin();
									while (it != help.end()) {
										if (help[it->second] != "")
											help[it->first] = help[it->second];
										it++;
									}
								}
							}
							s_i_tmp.insert(cur_word);
							return;
						}

						else {
							s_i_tmp.insert(cur_word);
							handler(cur_word, check + 1);
							if (check > 0)
								return;
							else continue;

						}
					}
				}

			}
			tmp--;
		}


		vector<string> res;
		for (string ans : s_i_tmp) {
			res.push_back(ans);
		}
		sort(res.begin(), res.end(), comp);

		for (string x : res) {
			setOfr.insert(x);
		}
		string max_s;
		for (string x : res) {
			max_s = x;
			break;
		}

		for (int i = 0; i < 1; i++) {
			map <string, string> ::iterator it = help.begin();
			while (it != help.end()) {
				if (help[it->second] != "")
					help[it->first] = help[it->second];
				it++;
			}
		}

		for (string x : res) {
			if (x != max_s)
				help[x] = max_s;
		}

		for (int i = 0; i < 2; i++) {
			map <string, string> ::iterator it = help.begin();
			while (it != help.end()) {
				if (help[it->second] != "")
					help[it->first] = help[it->second];
				it++;
			}
		}

		if (help[max_s] != "")
			s.insert(help[max_s]);
		setOfr.insert(word);
		return;

	}
}





int main() {
	setlocale(LC_ALL, "Russian");
	int w = 999;
	while (w > 0) {
		cout << endl;
		cout << "1 - алгоритм построения подполугрупп по таблице Кэли" << endl;
		cout << "2 - алгоритм построения полугруппы бинарных отношений по заданному порождающему множеству" << endl;
		cout << "3 - алгоритм построения полугруппы по порождающему множеству и определяющим соотношениям" << endl;
		cout << "0 - выход" << endl;
		cin >> w;
		if (w == 1) {
			int n;
			cout << "Введите количество элементов полугруппы. n = ";
			cin >> n;
			char* els = new char[n];
			cout << "Введите элементы: ";
			for (int i = 0; i < n; i++)
				cin >> els[i];

			char** v1;
			v1 = new char* [n];
			cout << endl;
			cout << "Введите таблицу Кэли:" << endl;
			for (int i = 0; i < n; i++) {
				v1[i] = new char[n];
				for (int j = 0; j < n; j++) {
					cin >> v1[i][j];
				}
			}

			int m;
			cout << "Введите количество элементов подмножества. m = ";
			cin >> m;
			vector <char> podmn(m);
			cout << "Введите элементы подмножества: ";
			for (int i = 0; i < m; i++)
				cin >> podmn[i];

			if (assoc(v1, els, n))
				alg_1(v1, n, podmn, m, els);
			else
				cout << "Операция НЕ обладает свойством ассоциативности" << endl;
		}


		if (w == 2) {
			int l, n;
			cout << "Введите количество отношений. L = ";
			cin >> l;
			cout << "Введите количество элементов множества. n = ";
			cin >> n;
			vector <pair <vector <vector <int>>, string>> matr;

			for (int i = 0; i < l; i++) {
				cout << "Введите " << i + 1 << "-ю матрицу:" << endl;
				vector <vector <int>> help1;
				for (int j = 0; j < n; j++) {
					vector <int> help2;
					for (int k = 0; k < n; k++) {
						int x;
						cin >> x;
						help2.push_back(x);
					}
					help1.push_back(help2);
				}
				matr.push_back(make_pair(help1, to_string(i + 1)));
			}


			alg_2(matr, l, n);

		}


		if (w == 3) {
			int n, m;
			set<string> a;
			cout << "Введите количество символов в алфавите: ";
			cin >> n;

			cout << "Введите алфавит А: ";
			for (int i = 0; i < n; ++i)
			{
				string ai;
				cin >> ai;
				a.insert(ai);
				s.insert(ai);
				setOfr.insert(ai);
				help[ai] = ai;
			}

			cout << endl << "Введите количество определяющий отношений: ";
			cin >> m;

			puts("Введите определяющие отношения:");
			for (int i = 0; i < m; i++)
			{
				string r1, r2;
				cin >> r1 >> r2;

				if (r1.size() > mx)
					mx = r1.size();
				if (r2.size() > mx)
					mx = r2.size();

				if (r1.size() < r2.size()) {
					r[r2] = r1;
					help[r2] = r1;
					s.insert(r1);
					setOfr.insert(r1);
					setOfr.insert(r2);
				}
				else if (r1.size() > r2.size()) {
					r[r1] = r2;
					help[r1] = r2;
					s.insert(r2);
					setOfr.insert(r2);
					setOfr.insert(r1);
				}
				else
				{

					if (r1 < r2) {
						r[r1] = r2;
						r[r2] = r1;
						help[r1] = r1;
						help[r2] = r1;
						s.insert(r1);
						setOfr.insert(r1);
						setOfr.insert(r2);
					}
					else {
						r[r1] = r2;
						r[r2] = r1;
						help[r1] = r2;
						help[r2] = r2;
						s.insert(r2);
						setOfr.insert(r2);
						setOfr.insert(r1);
					}
				}
			}

			cnt = 1;
			s_cur = a;
			while (!s_cur.empty())
			{
				cnt++;
				for (string si : s_cur)
				{
					for (string letter : a)
					{
						s_i_tmp.clear();
						string si_ = si + letter;
						cur_word = "";
						handler(si_, 0);
					}
				}
				s_cur.clear();
				for (auto ss : s)
					if (ss.size() == cnt)
						s_cur.insert(ss);
			}

			vector<string> res;
			for (string ans : s) {
				res.push_back(ans);
			}
			sort(res.begin(), res.end(), comp);

			cout << endl << "Полугруппа S = { ";
			for (string ans : s)
				cout << ans << " ";
			cout << "}" << endl;

			map <string, string> ::iterator it = help.begin();

			it = help.begin();

			int max_size = 0;
			for (string str : res) {
				max_size = str.size();
			}


			s_cur = s;
			set<string> s_plus;
			while (max_size > 0) {
				s_plus.clear();
				for (string si : s_cur)
				{
					for (string letter : a)
					{
						s_i_tmp.clear();
						string si_ = si + letter;
						handler(si_, 0);
						s_plus.insert(si_);
					}
				}
				s_cur.clear();
				for (auto ss : s_plus) {
					if (max_size > 0) {
						s_cur.insert(ss);
					}
				}
				max_size--;
			}



			int for_res = 0;
			cout << setw(7) << "";
			for (string ans : res)
				cout << setw(7) << ans;

			cout << endl;
			for (string ans : res) {
				cout << setw(7) << ans << setw(7);
				for (string ans2 : res) {
					cur_word = (ans + ans2);
					cout << help[cur_word] << setw(7);
				}
				cout << endl;
			}
			cout << endl;

		}
	}
	return 0;
}