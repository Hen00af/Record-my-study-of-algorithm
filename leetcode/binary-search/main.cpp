#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int search(vector<int>& num, int target)
{
	int left = 0;
	int right = num.size() - 1;

       while (left < right) {
		int mid = left + (right - left) / 2;
		if (num[mid] <= target) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}

	if (left > 0 && num[left - 1] == target) 
		return left - 1; 
	else 
		return -1;
	
}

int main()
{
	vector<int> nums = {-1,0,3,5,9,12};
	int target =3;

	int srh = search(nums,target);
	cout << srh << endl;
}
