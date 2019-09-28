#include <iostream>

using namespace std;



    // Write your code here
float toFahrenheit(float deg) {
    return deg * 1.8f + 32.0f;
}

float toDegrees(float f) {
    return f/1.8f - 32.0f/1.8f;

}
int main()
{
    cout << "Enter a temperature: ";
    float temp;

    cin >> temp;

    float fa = toFahrenheit(temp);
    float deg = toDegrees(temp);

    cout << temp << " degrees Celsius is " << fa << " degrees Fahrenheit" << endl;

    cout << temp << " degrees Fahrenheit is " << deg << " degrees Celsius" << endl;


    return 0;
}
