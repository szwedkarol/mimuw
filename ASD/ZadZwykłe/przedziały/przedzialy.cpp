#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int ileS( set<int, greater<>> & EndsOfLeft, set<int> & BegsOfRight, int n ) {
    int biggestFromLeft = 0;
    int smallestFromRight = n + 1;

    if ( !EndsOfLeft.empty() ) {
        biggestFromLeft = *EndsOfLeft.begin();
    }

    if ( !BegsOfRight.empty() ) {
        smallestFromRight = *BegsOfRight.begin();
    }

    return max( 0, smallestFromRight - biggestFromLeft - 1 );
}

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // Maksymalna długość przedziału (tj. U = [1, n])
    int m; // liczba zapytań

    cin >> n >> m;

    set<int, greater<>> EndsOfLeft; // końce przedziałów [1, a]
    set<int> BegsOfRight; // Początki przedziałów [a, n]

    for ( int i = 0; i < m; i++ ) {
        char c;
        cin >> c;
        int left;
        cin >> left;
        int right;
        cin >> right;
        if ( c == '+' ) {
            if ( left == 1 ) {
                EndsOfLeft.emplace(right);
            } else {
                BegsOfRight.emplace(left);
            }
        } else {
            if ( left == 1 ) {
                auto indexRight = EndsOfLeft.find(right);

                if (indexRight != EndsOfLeft.end() ) {
                    EndsOfLeft.erase(indexRight);
                }
            } else {
                auto indexLeft = BegsOfRight.find(left);

                if ( indexLeft != BegsOfRight.end() ) {
                    BegsOfRight.erase(indexLeft);
                }
            }
        }

        cout << ileS(EndsOfLeft, BegsOfRight, n) << '\n';
    }

    return 0;
}
