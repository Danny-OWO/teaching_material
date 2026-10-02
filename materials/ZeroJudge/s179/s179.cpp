// this approach only got 40% even we use prefix
#include <iostream>
#include <vector>

using namespace std;

// Using long long for prefix sums to avoid integer overflow during multiplication
vector<long long> prefix;

void seek() {
    int l, r;
    long long a, b;
    cin >> l >> r >> a >> b;

    for (int k = l; k <= r; ++k) {
        long long slk_1 = prefix[k - 1] - prefix[l - 1];
        long long s_lr = prefix[r] - prefix[l - 1];
        long long s_lk = prefix[k] - prefix[l - 1];

        if (s_lr * a > slk_1 * (a + b)) {
            if (s_lk * (a + b) >= a * s_lr) {
                cout << k << "\n";
                return;
            }
        }
    }
}

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> w(n);
    prefix.resize(n + 1, 0);

    long long temp = 0;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
        temp += w[i];
        prefix[i + 1] = temp;
    }

    for (int i = 0; i < m; ++i) {
        seek();
    }

    return 0;
}