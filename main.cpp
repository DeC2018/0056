#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        sort(intervals.begin(), intervals.end()); // Sort intervals by start time
        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            if (merged.back()[1] >= intervals[i][0]) { // Overlap detected
                merged.back()[1] = max(merged.back()[1], intervals[i][1]); // Merge
            } else {
                merged.push_back(intervals[i]); // No overlap, add to result
            }
        }

        return merged;
    }
};

int main() {
    Solution solution;

    vector<vector<int>> intervals1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    cout << "Input: intervals = [[1,3],[2,6],[8,10],[15,18]]" << endl;
    vector<vector<int>> result1 = solution.merge(intervals1);
    cout << "Output: [";
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    vector<vector<int>> intervals2 = {{1, 4}, {4, 5}};
    cout << "Input: intervals = [[1,4],[4,5]]" << endl;
    vector<vector<int>> result2 = solution.merge(intervals2);
    cout << "Output: [";
    for (size_t i = 0; i < result2.size(); ++i) {
        cout << "[" << result2[i][0] << "," << result2[i][1] << "]";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}
