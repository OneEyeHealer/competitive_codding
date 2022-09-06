#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <tuple>
#include <map>

using namespace std;

vector<int> pairSum(vector<int> arr, int sum) {
	unordered_set<int> s;
	vector<int> result;
	for (int i = 0; i < arr.size(); i++)
	{
		int expected_value = sum - arr[i];
		if (s.find(expected_value) != s.end()) {
			result.push_back(expected_value);
			result.push_back(arr[i]);
			return result;
		}

		s.insert(arr[i]);
	}

	return {};
}

void print_Vector(vector<int> arr) {
	for (auto& x : arr)
	{
		cout << x << endl;
	}
}

void print_2D_vector(vector<vector<int>> grid, int row , int col) {
	cout << "*******Vector*******" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << grid[i][j] << ", ";
		}
		cout << endl;
	}
	cout << "*******end*******" << endl;
}

vector<int> times_2(vector<int> arr) {
	for (auto& y : arr)
	{
		y *= 2;
	}
	
	cout << "inside function" << endl;
	print_Vector(arr);
	return arr;
}

vector<vector<int>> triplateSum(vector<int> arr, int sum) {

	sort(arr.begin(), arr.end());
	int n = arr.size();
	vector<vector<int>> result;

	for (int i = 0; i <= n - 3; i++)
	{
		int j = i + 1;
		int k = n - 1;

		while (j < k) {
			int current_sum = arr[i];
			current_sum += arr[j];
			current_sum += arr[k];

			if (current_sum == sum) {
				result.push_back({ arr[i], arr[j], arr[k] });
				j++;
				k--;
			}
			else if (current_sum > sum) {
				k--;
			}
			else {
				j++;
			}
		}
	}
	return result;
}

int remain_candy(int candies_sum, int kids_num) {

	return candies_sum % kids_num;
}

int record_breaking(vector<int> v, int n) {
	int cnt = 0;
	int max_value = -1;
	if (n == 1) { // first day
		cnt=1;
	}
	else { // other (Vth) days
		for (int i = 0; i < n-1; i++) {
			if (v[i] > max_value) {
				max_value = v[i];
				if (v[i] > v[i + 1]) {
					cnt++;
				}
			}
		}

		// last day
		if (v[n - 1] > max_value)
			cnt++;
	}

	return cnt;
}

int countRecordBreakingDays(vector<int> visitors) {
	int recordBreakingCount = 0, previousRecord = 0;

	for (int i = 0; i < visitors.size(); i++)
	{
		bool greaterThanPreviousDays = i == 0 || visitors[i] > previousRecord;
		bool greaterThanNextDay = i == visitors.size() - 1 || visitors[i] > visitors[i + 1];

		if (greaterThanPreviousDays && greaterThanNextDay)
			recordBreakingCount++;

		previousRecord = max(previousRecord, visitors[i]);
	}

	return recordBreakingCount;
}

tuple<int, int> robot_walk(vector<vector<int>> grid, int row, int col, int pr, int pc, string pos) {

	int actual_pr = pr - 1, actual_pc = pc - 1;
	grid[actual_pr][actual_pc] = 1;
	for (int i = 0; i < pos.length(); i++) {
		if (pos[i] == 'N' && actual_pr >= 0) {
			while (grid[actual_pr][actual_pc] == 1) {
				actual_pr--;
			}
			grid[actual_pr][actual_pc] = 1;
		}
		else if (pos[i] == 'S' && actual_pr < row-1) {
			while (grid[actual_pr][actual_pc] == 1) {
				actual_pr++;
			}
			grid[actual_pr][actual_pc] = 1;
		}
		else if (pos[i] == 'E' && actual_pc < col - 1){
			while (grid[actual_pr][actual_pc] == 1) {
				actual_pc++;
			}
			grid[actual_pr][actual_pc] = 1;
		}
		else if (pos[i] == 'W' && actual_pc >= 0){
			while (grid[actual_pr][actual_pc] == 1) {
				actual_pc--;
			}
			grid[actual_pr][actual_pc] = 1;
		}
	}


	return make_tuple(actual_pr+1, actual_pc+1);
}

struct Node
{
	pair<int, int> N, S, E, W;

	Node() {
		N = S = E = W = { 0, 0 };
	}

	Node(int x, int y) {
		N = { x - 1, y };
		S = { x + 1, y };
		W = { x, y - 1 };
		E = { x, y + 1 };
	}
};

template<typename Map>

struct Direction {
	pair<int, int> N, S, E, W;

	Direction() {
		N = { -1, 0 };
		S = { 0, -1 };
		W = { 0, -1 };
		E = { -1, 0 };
	}
};

pair<int,int> wiggleWalk(int s_r, int s_c, string instructions) {
	int x = 0, y = 0;
	map<char, pair<int, int>> pos;
	pos['N'] = make_pair(-1, 0);
	pos['S'] = make_pair(1, 0);
	pos['W'] = make_pair(0, -1);
	pos['E'] = make_pair(0, 1);

	map<pair<int, int>, bool> grid;
	auto grid_pos = make_pair(s_r, s_c);
	grid[grid_pos] = true;
	int cur_r = s_r, cur_c = s_c;

	for (int i = 0; i < instructions.length(); i++) {
		char dir = instructions[i];
		int d_r = pos[dir].first, d_c = pos[dir].second;
		cur_r += d_r;
		cur_c += d_c;
		
		while (grid[make_pair(cur_r, cur_c)]) {
			cur_r += d_r;
			cur_c += d_c;
		}
		grid[make_pair(cur_r, cur_c)] = true;
	}

	for (auto& m : grid)
	{
		x = m.first.first;
		y = m.first.second;
		cout << x << ", " << y << endl;
	}
	return make_pair(x, y);
}

pair<int, int> wiggle_walk_approach(vector<vector<int>> grid, int row, int col, int sr, int sc, string pos) {
	map<pair<int, int>, Node> map_grid;
	Node curr = Node(sr, sc);
	map_grid[{sr, sc}] = curr;
	for (int i = 0; i < pos.length(); i++)
	{
		if (map_grid.find({ sr, sc }) == map_grid.end()) {
			map_grid[{sr, sc}] = Node(sr, sc);
		}

		auto nor = map_grid[{sr, sc}].N;
		auto sou = map_grid[{sr, sc}].S;
		auto eas = map_grid[{sr, sc}].E;
		auto wes = map_grid[{sr, sc}].W;

		if (map_grid.find(nor) == map_grid.end())
			map_grid[nor] = Node(nor.first, nor.second);
		if (map_grid.find(sou) == map_grid.end())
			map_grid[sou] = Node(sou.first, sou.second);
		if (map_grid.find(eas) == map_grid.end())
			map_grid[eas] = Node(eas.first, eas.second);
		if (map_grid.find(wes) == map_grid.end())
			map_grid[wes] = Node(wes.first, wes.second);

		map_grid[nor].S = sou;
		map_grid[sou].N = nor;
		map_grid[eas].W = wes;
		map_grid[wes].E = eas;

		if (pos[i] == 'E')
			sc = eas.second;
		else if (pos[i] == 'W')
			sc = wes.second;
		else if (pos[i] == 'S')
			sr = nor.first;
		else
			sr = nor.first;
	}

	return make_pair(sr, sc);
}

int highest_mountain(vector<int> arr) {
	int n = arr.size();
	int largest = 0;

	// first and last can't be peak 
	for (int i = 1; i <= n - 2;) {

		// (find the peak)
		if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {

			// for LHS
			int lhs = i, cnt = 0;
			while (lhs > 0 && arr[lhs] > arr[lhs - 1]) {
				lhs--;
				cnt++;
			}

			// for RHS
			while (i < n - 1 && arr[i] > arr[i + 1]) {
				i++;
				cnt++;
			}

			// longest mountain
			largest = max(largest, cnt);

		}
		else { // skip the Ith possition if not peak
			i++;
		}
	}

	// when no montian found
	if (largest == 0)
		return 0;

	// +1 for peak;
	return largest + 1;
}

bool Valid_mountain(vector<int> arr) {
	int n = arr.size();
	bool isValidMountain = false;

	if (n < 3) {
		return isValidMountain;
	}

	for (int i = 1; i <= n - 2;) {

		if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
			isValidMountain = true;
			int lhs = i;
			for (int lhs = i; lhs > 0;) {
				if (lhs > 0 && arr[lhs] > arr[lhs - 1]) {
					lhs--;
				}
				else {
					isValidMountain = false;
					return isValidMountain;
				}
			}

			for (; i < n - 1; ) {
				if (arr[i] > arr[i + 1]) {
					i++;
				}
				else {
					isValidMountain = false;
					return isValidMountain;
				}
			}
		}
		else {
			i++;
		}
	}

	return isValidMountain;
}

int main() {
	/*int test_case = 0;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++) {
		int n = 0, r = 0, c = 0, pr = 0, pc = 0;
		string pos;

		cin >> n >> r >> c >> pr >> pc >> pos;

		vector<vector<int>> grid(r, vector<int>(c, 0));*/
		auto res = wiggleWalk(3, 4, "NEESSWWNESE");
		cout << "Case #" << res.first << " " << res.second << endl;
		//cout << "Case #" << t << ": " << res. << " " << y << endl;
	//}
	return 0;
}
