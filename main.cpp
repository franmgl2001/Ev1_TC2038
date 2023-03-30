#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Function: prototypes
string read_file(string file_name);


int main()
{

}

string read_file(string file_name)
{
    ifstream file;
    file.open(file_name);
    string line;
    string text;
    while (getline(file, line))
    {
        text += line + "