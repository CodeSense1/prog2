#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    for (int i = 0; i < 4; i++) {
        int spaceBetween = i*4;
        if (i == 0) {
            cout << setw(7-i*2);
            cout << "*" << endl;
        } else {
            cout << setw(7-i*2);
            cout << "*";
            cout << setw(spaceBetween);
            cout << "*" << endl;
        }
    }
    for (int i = 2; i > -1; i--) {
        int spaceBetween = i*4;
        if (i == 0) {
            cout << setw(7-i*2);
            cout << "*" << endl;
        } else {
            cout << setw(7-i*2);
            cout << "*";
            cout << setw(spaceBetween);
            cout << "*" << endl;
        }
    }
    return 0;
}
