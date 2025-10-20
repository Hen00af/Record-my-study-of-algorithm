#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> two_sum(vector<int>& nums, int target)
{
	unordered_map<int, int> mp;

	for(int i = 0; i < nums.size(); i++)
	{
		int ans = target - nums[i];
		if(mp.count(ans))
			return{mp[ans], i};
		mp[nums[i]] = i;
		cout << "mp[" << nums[i] << "] = " <<mp[nums[i]] << "\n";
	}
	return{};
}

int main()
{
	vector<int> nums = {2, 5, 11, 16};
	int target = 9;
	two_sum(nums,target);
}
