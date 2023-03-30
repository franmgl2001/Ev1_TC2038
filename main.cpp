#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Function: prototypes
string load_file(string file_name);


int main()
{
    // Load the transmission file
    string file = load_file("transmission.txt");
    string mcode1 =load_file("mcode1.txt");
    string mcode2 =load_file("mcode2.txt");
    string mcode3 =load_file("mcode3.txt");


}

string load_file(string file_name)
{
    string line;
    ifstream myfile (file_name);
    if (myfile.is_open())
    {
        getline (myfile,line);
        myfile.close();
    }

    else cout << "Unable to open file";

    return line;
}