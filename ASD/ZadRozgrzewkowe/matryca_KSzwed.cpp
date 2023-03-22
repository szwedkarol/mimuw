#include <iostream>
#include <climits>
#include <string>

using namespace std;

int main() {
    // Magiczne linijki do przyspieszania wejœcia/wyjœcia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    string s; // ca³e wejœcie
    int c = 0; // indeks aktualnie sprawdzanego znak
    int last_letter = 0; // indeks ostatniej litery
    int t; // d³ugoœæ ca³ego tekstu
    int curr_l = 0; // obecna odleg³oœæ miêdzy -//-

    cin >> s;
    t = s.length();
    int min_l = t; // minimalna odleg³oœæ miêdzy dwiema ró¿nymi literami w napisie

    while ( c < t && !(s[c] >= 'A' && s[c] <= 'Z') ) {
        c++; // Pomijamy gwiazdki na pocz¹tku
    }
    last_letter = c;
    c++;

    for ( ; c < t; c++ ) {
        if ( s[c] == '*' ) {
            curr_l++;
        } else {
            if ( s[c] != s[last_letter] ) {
                min_l = min(min_l, curr_l);
            }
            curr_l = 0;
            last_letter = c;
        }
    }

    int res = max(t - min_l, 1); // wynik

    //cout << "\nWynik: " << res << "\n|T| = " << t << "\nmin_l: " << min_l << "\n"; // debug

    cout << res << "\n";

    return 0;
}
