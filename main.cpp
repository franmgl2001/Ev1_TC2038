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



int main()
{
    // Initialize variables and arrays
    int findings_position[300];
    int findings_count = 0;
    int comparissons = 0;

    // Load mcode and transmission files
    string file = load_file("transmission.txt");
    string mcode1 =load_file("mcode1.txt");
    string mcode2 =load_file("mcode2.txt");
    string mcode3 =load_file("mcode3.txt");

    // Run pattern finding algorithms and right reports
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

// Load file function
string load_file(string file_name)
{
    // Initialize variables
    string line;
    ifstream myfile (file_name);
    //Open file and read dtring line
    if (myfile.is_open())
    {
        getline (myfile,line);
        myfile.close();
    }
    // Exception handling if the file couldn't be opened
    else cout << "Unable to open file";
    // Return string line
    return line;
}
//Brute force algorithm
void pattern_finding_algorithm_brute_force(string file, string mcode, int findings[], int *findings_count, int *comparissons)
{
    // Initialize variables
    *findings_count = 0;
    *comparissons = 0;

    // Initialize variables for the loop
    int i = 0;
    int j = 0;
    int m = mcode.length();
    int n = file.length();

    // Find pattern
    while (i < n)
    {
        //If the characters match, increment i and j
        if (file[i] == mcode[j])
        {
            (*comparissons)++;
            i++;
            j++;
        }
        //If the characters don't match, reset i to the next position before matching the pattern and reset j to 0
        else
        {
            (*comparissons)++;
            i = i - j + 1;
            j = 0;
        }
        //If j is equal to the length of the pattern, the pattern was found and the position is stored in the findings array
        if (j == m)
        {
            findings[*findings_count] = i - j;
            j = 0;
            (*findings_count)++;
        }
    }
    // Print small summary
    cout << "Number of times the pattern was found: " << *findings_count << endl;
    cout << "Number of comparisons: " << *comparissons << endl;
}

void kmp_algorithm(string file, string mcode, int findings[], int *findings_count, int *comparissons)
{
    // Initialize variables
    *findings_count = 0;
    *comparissons = 0;
    int mcode_index[mcode.length()];
    int n = file.length();
    int i = 0;
    int j = 0;

    // Run preRun function to create the mcode_index array used on algorithm
    preRun(mcode, mcode_index, comparissons);


    // Find pattern using the mcode_index array
    while (n > i)
    {
        // If the characters match, increment i and j and compare the next characters
        if (file[i] == mcode[j])
        {
            (*comparissons)++;
            i++;
            j++;
        }
        // If the characters don't match, and j is 0 go to the next character in the file
        else if (j == 0)
        {
            (*comparissons)++;
            i++;
        }
        // If the characters don't match, and j is not 0, compare character i with next character in the pattern index array
        else
        {
            (*comparissons)++;
            j = mcode_index[j - 1];
        }
        // Pattern found exception
        if (j == mcode.length())
        {
            findings[*findings_count] = i - j;
            (*findings_count)++;
            j = 0;
        }
    }
    // Print small summary
    cout << "Number of times the pattern was found: " << *findings_count << endl;
    cout << "Number of comparisons: " << *comparissons << endl;
}


void write_report(string file_name, string mcode, int *findings_position, int findings_count, int comparissons)
{
    // Initialize variables
    ofstream myfile;
    // Open file and write the report
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
    // Close file
    myfile.close();
}

void preRun(string mcode,int *array_index, int *comparissons)
{
    // Initialize variables
    int m = mcode.length();
    int i = 1;
    int j = 0;
    array_index[0] = 0;

    // Create the array_index array
    while (i < m)
    {
        // If the characters match, increment i and j and compare the next characters
        if(mcode[i] == mcode[j])
        {
            (*comparissons)++;
            array_index[i] = j + 1;
            i++;
            j++;
        }
        // If the characters don't match, and j is 0 go to the next character in the file
        else if (j == 0)
        {
            (*comparissons)++;

            array_index[i] = 0;
            i++;
        }
        // If the characters don't match, and j is not 0, compare character i with next character in the pattern index array
        else
        {
            j = array_index[j - 1];
        }
        
    
    }
}
