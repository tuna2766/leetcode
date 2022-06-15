# Work Schedule

An employee has to work exactly as many hours as they are told to each week, scheduling no more than a given daily maximum number of hours. On some days, the number of hours worked will be given. The employee gets to choose the remainder of their schedule, within the given limits. 

A completed schedule consists of exactly 7 digits in the range 0 to 8 that represent each day's hours to be worked. A pattern string similar to the schedule will be given, but with some of the digits replaced by a question mark, ?, (ascii 63 decimal). Given a maximum number of hours that can be worked in a day, replace the question marks with digits so that the sum of the scheduled hours is exactly the hours that must be worked in a week.

**Example**
pattern = "08??840"
workHours = 24
dayHours = 4
There are two days on which they must work 24 - 20 = 4 more hours for the week. All of the possible schedules are listed below:
0804840
0813840
0822840
0831840
0840840

```cpp
#include <iostream>
#include <vector>
std::vector<std::string> parse(std::string pattern, std::vector<std::vector<int>>& digits) {
	std::vector<std::string> res;
	for(auto digit : digits) {
		std::string s = pattern;
		int idx = 0;
		for(int i = 0; i < 8; i++) {
			if(s[i] == '?')
				s[i] = (digit[idx++] + '0');
		}
		res.push_back(s);
	}
	return res;
}

void backtrack(int require, int target, std::vector<int>& cur, std::vector<std::vector<int>>& digits) {
	if(require < 0 || target < 0)
		return;
	if(require == 0 && target == 0) {
		digits.push_back(cur);
		return;
	}
	for(int i = 0; i <= 8; i++) {
		cur.push_back(i);
		backtrack(require - 1, target - i, cur, digits);
		cur.pop_back();
	}
}

std::vector<std::string> findSchedules(int workHours, int dayHours, std::string pattern) {
	int require = 0;
	int target = workHours;
	for(auto c : pattern) {
		require += (c == '?');
		if(isdigit(c)) {
			target -= (c - '0');
		}
	}

	std::vector<int> cur;
	std::vector<std::vector<int>> digits;
	backtrack(require, target, cur, digits);
	return parse(pattern, digits);

}

int main(int argc, char const *argv[])
{
	std::string pattern = "08??840";
	int workHours = 24;
	int dayHours = 4;

	std::vector<std::string> ans = findSchedules(workHours, dayHours, pattern);
	for(const auto& s : ans) {
		std::cout << s << std::endl;
	}
	return 0;
}
```

```cpp
pattern = "08??840"
workHours = 24
dayHours = 4
output : 
	0804840
	0813840
	0822840
	0831840
	0840840

pattern = "??2??00";
workHours = 3
dayHours = 2
output : 
	0020100
	0021000
	0120000
	1020000

```