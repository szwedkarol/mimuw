#include <iostream>

#define BIT_SIZE 1000000

using namespace std;

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // liczba elementów ciągu

    cin >> n;
    int power[n]; // ciąg liczbowy (kolejne wykładniki 2)
    bool binary[BIT_SIZE]; // liczba bitowa o 10^6 bitów;

    for ( int i = 0; i < n; i++ ) {
        cin >> power[i];
    }

    for (bool & i : binary) {
        i = false;
    }

    int ileJedynek = 0;
    for ( int i = 0; i < n; i++ ) {
        if ( binary[power[i]] ) {
            int temp = power[i];
            while ( binary[temp] ) {
                binary[temp] = false;
                ileJedynek--;
                temp++;
            }
            binary[temp] = true;
            ileJedynek++;
        } else {
            ileJedynek++;
            binary[power[i]] = true;
        }

        cout << ileJedynek << '\n';
    }

    return 0;
}
