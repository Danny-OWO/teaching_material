#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        const unordered_map<char, char> openingOf{
            {')', '('}, {']', '['}, {'}', '{'}
        };
        stack<char> unmatched;

        for (char token : s) {
            if (token == '(' || token == '[' || token == '{') {
                unmatched.push(token);
                continue;
            }

            if (unmatched.empty() || unmatched.top() != openingOf.at(token)) {
                return false;
            }
            unmatched.pop();
        }

        return unmatched.empty();
    }
};
