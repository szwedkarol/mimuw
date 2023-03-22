#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // liczba naszyjników
    int l; // długość każdego naszyjnika
    cin >> n >> l;

    set<pair<int, int>> bead; // koraliki naszyjników

    for ( int i = 0; i < n; i++ ) {
        for ( int column = 0; column < l; column++ ) {
            int value;
            cin >> value;

            bead.insert({value, column});
        }
    }

    auto prev = bead.begin();
    auto it = bead.begin();
    ++it;

    int price_max = 1;
    for ( ; it != bead.end(); ++it, prev++ ) {
        int value = prev->first;

        int temp_price = 1;
        while ( it != bead.end() && it->second == prev->second + 1 && it->first == value ) {
            temp_price++;
            it++;
            prev++;
        }

        if( it == bead.end() ) {
            price_max = max(price_max, temp_price );
            break;
        }

        price_max = max(price_max, temp_price);
    }

    cout << price_max << '\n';

    // debug
//    for ( pair<int, int> b : bead ) {
//        cout << "Koralik: " << b.first << ", " << b.second << '\n';
//    }

    return 0;
}