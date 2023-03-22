#include <iostream>

using namespace std;

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int number[n+1];

    for ( int i = 1; i <= n; i++ ) {
        cin >> number[i];
    }

    long long ilePrzed[n+1][11]; // ilePrzed[i][k] -> ile przed liczbą a_i występuje liczba k \in {1, ..., 10}

    for ( int i = 1; i <= 10; i++ ) {
        ilePrzed[1][i] = 0;
    }

    for ( int i = 2; i <= n; i++ ) {
        for ( int k = 1; k <= 10; k++ ) {
            ilePrzed[i][k] = ilePrzed[i-1][k];
        }

        int prev = number[i-1];
        ilePrzed[i][prev]++;
    }

    long long result = 0;
    for ( int i = 3; i <= n; i++ ) {
        if ( number[i] < 2 ) continue;
        int sumTwoEarlier = number[i];

        int low = 1;
        int high = sumTwoEarlier - low;

        while ( low < high ) {
            result += ilePrzed[i][low] * ilePrzed[i][high];
            low++;
            high--;
        }

        if ( low == high ) {
            result += (ilePrzed[i][low] * (ilePrzed[i][high] - 1)) / 2;
        }
    }

    std::cout << result << std::endl;

    return 0;
}
