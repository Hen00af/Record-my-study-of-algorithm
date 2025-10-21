#include <bits/stdc++.h>
using namespace std;

void processTransactions(vector<string> operations)
{
	unordered_map<long, long> mp;
	for (string line : operations) {
		stringstream ss(line);
		string op;
		long id;
		long qty;
		ss >> op >> id >> qty;
	}
}

int main() {
    vector<string> ops = {
        "add 1 5", "add 2 3", "sell 1 2", "sell 3 1", "add 2 4", "sell 2 6"
    };
    processTransactions(ops);
}
