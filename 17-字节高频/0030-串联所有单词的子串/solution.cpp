/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        int n = s.size(), m = words.size(), w = words[0].size();
        unordered_map<string, int> need;
        for (auto& x : words) ++need[x];

        for (int offset = 0; offset < w; ++offset) {         // w 种切法
            unordered_map<string, int> win;
            int left = offset, cnt = 0;
            for (int right = offset; right + w <= n; right += w) {
                string word = s.substr(right, w);
                if (!need.count(word)) {                     // 不在 words 里，窗口作废
                    win.clear();
                    cnt = 0;
                    left = right + w;
                    continue;
                }
                ++win[word];
                ++cnt;
                while (win[word] > need[word]) {             // 这个词多了，从左边吐
                    --win[s.substr(left, w)];
                    left += w;
                    --cnt;
                }
                if (cnt == m) {                              // 刚好凑齐
                    ans.push_back(left);
                    --win[s.substr(left, w)];
                    left += w;
                    --cnt;
                }
            }
        }
        sort(ans.begin(), ans.end());
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

// 暴力：每个起点切出 m 个词，排序后和 words 比
static vector<int> brute(const string& s, vector<string> words) {
    vector<int> ans;
    int m = words.size(), w = words[0].size();
    sort(words.begin(), words.end());
    for (int i = 0; i + m * w <= (int)s.size(); ++i) {
        vector<string> cut;
        for (int k = 0; k < m; ++k) cut.push_back(s.substr(i + k * w, w));
        sort(cut.begin(), cut.end());
        if (cut == words) ans.push_back(i);
    }
    return ans;
}

int main() {
    struct Case { string s; vector<string> words; vector<int> expected; };
    vector<Case> cases = {
        {"barfoothefoobarman", {"foo", "bar"}, {0, 9}},
        {"wordgoodgoodgoodbestword", {"word", "good", "best", "word"}, {}},
        {"barfoofoobarthefoobarman", {"bar", "foo", "the"}, {6, 9, 12}},
        {"aaaaaa", {"aa", "aa"}, {0, 1, 2}},
        {"wordgoodgoodgoodbestword", {"word", "good", "best", "good"}, {8}},
        {"a", {"a"}, {0}},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.findSubstring(c.s, c.words);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\", words = [";
        for (size_t t = 0; t < c.words.size(); ++t) cout << (t ? "," : "") << c.words[t];
        cout << "]\n  输出: "; printVec(got);
        cout << "   期望: "; printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    // 随机对拍：字母只有 a/b，单词长 1~3，重复和重叠很多
    mt19937 g(30);
    bool ok = true;
    for (int it = 0; it < 5000 && ok; ++it) {
        int w = g() % 3 + 1, m = g() % 3 + 1, n = g() % 20 + 1;
        string s;
        for (int i = 0; i < n; ++i) s += char('a' + g() % 2);
        vector<string> words(m);
        for (auto& x : words) for (int i = 0; i < w; ++i) x += char('a' + g() % 2);
        if (sol.findSubstring(s, words) != brute(s, words)) ok = false;
    }
    passed += ok;
    cout << "用例 " << cases.size() + 1 << ": 和暴力对拍 5000 组" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";

    int total = cases.size() + 1;
    cout << passed << "/" << total << " 通过\n";
    return passed == total ? 0 : 1;
}
