/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26] = {};
        for (int i = 0; i < s.size(); ++i) last[s[i] - 'a'] = i;   // 每个字母最后出现的位置
        vector<int> ans;
        int start = 0, end = 0;                     // 当前片段的起点、至少要延伸到的位置
        for (int i = 0; i < s.size(); ++i) {
            end = max(end, last[s[i] - 'a']);       // 片段必须包住这个字母的最后一次出现
            if (i == end) {                         // 片段里所有字母都不会再出现：切一刀
                ans.push_back(end - start + 1);
                start = i + 1;
            }
        }
        return ans;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
    cout << "]";
}

int main() {
    struct Case {
        string s;
        vector<int> expected;
    };
    vector<Case> cases = {
        {"ababcbacadefegdehijhklij", {9, 7, 8}},
        {"eccbbbbdec", {10}},
        {"a", {1}},
        {"abc", {1, 1, 1}},
        {"abca", {4}},
        {"caedbdedda", {1, 9}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.partitionLabels(c.s);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\"";
        cout << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
