#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;
int treeSum = 0;
int minDiff = INT_MAX;
int dfs(int root, vector<int>& file_size, unordered_map<int, vector<int>> childs) {
	int sum = 0;
	for(int child : childs[root]) {
		int subSum = dfs(child, file_size, childs);
		sum += subSum;
		minDiff = min(minDiff, abs(abs(treeSum - subSum) - subSum));
	}
	sum += file_size[root];
	return sum;

}

void helper(vector<int> parent, vector<int> file_size) {
	for(int i = 0; i < file_size.size(); i++) {
		treeSum += file_size[i];
	}
	// treeSum = accumulate(file_size.begin(), file_size.end(), 0);
	unordered_map<int, vector<int>> childs;
	for(int i = 0; i < parent.size(); i++) {
		childs[parent[i]].emplace_back(i);
	}
	/* 
	  [-1, 0]
	  [0, 1]
	  [0, 2]
	  [1, 3]
	  [1, 4]
	  [2, 5]
	*/
	
	dfs(0, file_size, childs);
}

int main(int argc, char const *argv[])
{
	vector<int> parent = {-1, 0, 1, 2};
	vector<int> file_size = {1, 4, 3, 4};
	helper(parent, file_size);
	cout << "minDiff = " << minDiff << "\n";

	return 0;
}