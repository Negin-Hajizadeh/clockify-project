/*
This program was created by (Negin Hajizadeh) and delivered as a university project

For compiling : g++ .\main.cpp -std=c++11
*/

#include "header.hpp"
#include "header.cpp"


int main() // main function
{
    system("Color E0");
    int n;
    cout << "\n---------------------------- Bitok App ----------------------------\n";
    cout << "Welcome to the bitok accounting app :D" << endl
         << "Please sign up for more or login to your account." << endl
         << ">> Enter the number to continue:" << endl;

    n = start_menu();
    //The rest of the steps are done in the "header.cpp" file

    return 0;
}