/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;  // 字母计数 -> 同组单词
        groups.reserve(strs.size());                   // 最多 n 组，提前分配桶
        for (string& s : strs) {
            string key(26, 0);                         // 26 个字母各出现几次
            for (char c : s) key[c - 'a']++;           // 异位词的计数完全相同
            groups[key].push_back(std::move(s));       // 移走字符串内存，不拷贝；之后 s 不再使用
        }
        vector<vector<string>> ans;
        ans.reserve(groups.size());
        for (auto& [k, g] : groups) ans.push_back(std::move(g));  // 整组移走，同理
        return ans;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
// 题目允许任意顺序，比较前先排序
static vector<vector<string>> normalize(vector<vector<string>> v) {
    for (auto& g : v) sort(g.begin(), g.end());
    sort(v.begin(), v.end());
    return v;
}

static void printStrs(const vector<string>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << '"' << v[i] << '"';
    cout << "]";
}

static void printGroups(const vector<vector<string>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ",";
        printStrs(v[i]);
    }
    cout << "]";
}

int main() {
    struct Case {
        vector<string> strs;
        vector<vector<string>> expected;
    };
    vector<Case> cases = {
        {{"eat", "tea", "tan", "ate", "nat", "bat"}, {{"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}}},
        {{""}, {{""}}},
        {{"a"}, {{"a"}}},
        {{"abc", "bca", "xyz", "cab", "zyx"}, {{"abc", "bca", "cab"}, {"xyz", "zyx"}}},
        {{"ab", "ba", "abb"}, {{"ab", "ba"}, {"abb"}}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        vector<string> input = c.strs;  // groupAnagrams 会 move 走字符串，留一份用来打印
        auto got = normalize(sol.groupAnagrams(c.strs));
        auto exp = normalize(c.expected);
        bool ok = got == exp;
        passed += ok;
        cout << "用例 " << k + 1 << ": strs = ";
        printStrs(input);
        cout << "\n  输出: ";
        printGroups(got);
        cout << "\n  期望: ";
        printGroups(exp);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
