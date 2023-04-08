#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Function: prototypes
string load_file(string file_name);
void write_report(string file_name, string mcode, int *findings_position, int findings_count, int comparissons);
void pattern_finding_algorithm_brute_force(string file, string mcode, int *findings_position, int *findings_count, int *comparissons);
void kmp_algorithm(string file, string mcode, int *findings_position, int *findings_count, int *comparissons);
void preRun(string mcode, int *array_index, int *comparissons);
void printArray(int *array_index, int l);


int main()
{
    // Load the transmission file
    int findings_position[300];
    int findings_count = 0;
    int comparissons = 0;


    string file = load_file("transmission.txt");
    string mcode1 =load_file("mcode1.txt");
    string mcode2 =load_file("mcode2.txt");
    string mcode3 =load_file("mcode3.txt");

    // Run the naive algorithm
    pattern_finding_algorithm_brute_force(file, mcode1, findings_position, &findings_count, &comparissons);
    write_report("report_mcode1_brute_force.txt", mcode1, findings_position, findings_count, comparissons);
    kmp_algorithm(file, mcode1, findings_position, &findings_count, &comparissons);
    write_report("report_mcode1_kmp_algorithm.txt", mcode1, findings_position, findings_count, comparissons);
    pattern_finding_algorithm_brute_force(file, mcode2, findings_position, &findings_count, &comparissons);   
    write_report("report_mcode2_brute_force.txt", mcode2, findings_position, findings_count, comparissons);
    kmp_algorithm(file, mcode2, findings_position, &findings_count, &comparissons);
    write_report("report_mcode2_kmp_algorithm.txt", mcode2, findings_position, findings_count, comparissons);
    pattern_finding_algorithm_brute_force(file, mcode3, findings_position, &findings_count, &comparissons);
    write_report("report_mcode3_brute_force.txt", mcode3, findings_position, findings_count, comparissons);
    kmp_algorithm(file, mcode3, findings_position, &findings_count, &comparissons);
    write_report("report_mcode3_kmp_algorithm.txt", mcode3, findings_position, findings_count, comparissons);


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

void pattern_finding_algorithm_brute_force(string file, string mcode, int findings[], int *findings_count, int *comparissons)
{
    *findings_count = 0;
    *comparissons = 0;

    int i = 0;
    int j = 0;
    int m = mcode.length();
    int n = file.length();

    while (i < n)
    {
        if (file[i] == mcode[j])
        {
            (*comparissons)++;
            i++;
            j++;
        }
        else
        {
            (*comparissons)++;
            i = i - j + 1;
            j = 0;
        }
        if (j == m)
        {
            findings[*findings_count] = i - j;
            j = 0;
            (*findings_count)++;
        }
    }

    cout << "Number of times the pattern was found: " << *findings_count << endl;
    cout << "Number of comparisons: " << *comparissons << endl;
}

void kmp_algorithm(string file, string mcode, int findings[], int *findings_count, int *comparissons)
{
    *findings_count = 0;
    *comparissons = 0;
    int mcode_index[mcode.length()];
    preRun(mcode, mcode_index, comparissons);
    printArray(mcode_index, mcode.length());
    int n = file.length();
    int i = 0;
    int j = 0;

    while (n > i)
    {
        if (file[i] == mcode[j])
        {
            (*comparissons)++;
            i++;
            j++;
        }
        else
        {
            if (j == 0)
            {
                (*comparissons)++;
                i++;
            }
            else
            {
                (*comparissons)++;
                j = mcode_index[j - 1];
            }
        }
        if (j == mcode.length())
        {
            findings[*findings_count] = i - j;
            (*findings_count)++;
            j = 0;
        }
    }

    cout << "Number of times the pattern was found: " << *findings_count << endl;
    cout << "Number of comparisons: " << *comparissons << endl;
}


void write_report(string file_name, string mcode, int *findings_position, int findings_count, int comparissons)
{
    ofstream myfile;
    myfile.open (file_name);
    myfile  << "REPORT PATTERN 1" << endl;
    myfile  << mcode << endl;
    myfile  << "Number of times the pattern was found: " << findings_count << endl;
    myfile  << "Number of comparisons: " << comparissons << endl;
    myfile << "Positions: " << endl;
    for (int i = 0; i < findings_count; i++)
    {
        myfile << findings_position[i] << endl;
    }

    myfile.close();
}

void preRun(string mcode,int *array_index, int *comparissons)
{
    int m = mcode.length();
    int i = 1;
    int j = 0;

    array_index[0] = 0;

    while (i < m)
    {
        if(mcode[i] == mcode[j])
        {
            (*comparissons)++;
            array_index[i] = j + 1;
            i++;
            j++;
        }
        else
        {
            (*comparissons)++;
            if (j == 0)
            {
                array_index[i] = 0;
                i++;
            }
            else
            {
                j = array_index[j - 1];
            }
        }
    
    }
}

void printArray(int *array_index, int l)
{
    for (int i = 0; i < l; i++)
    {
        cout << array_index[i] << endl;
    }
}