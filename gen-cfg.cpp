#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
int main(int argc, char** argv)
{
    if(argc < 4) return -1;
    cout << "filename : " << argv[1] << endl;
    cout << "range : " << argv[2] << " - " << argv[3] << endl;
    cout << "-------------------------------------------" << endl;
    ofstream out("config.txt");
    int left = atoi(argv[2]), right = atoi(argv[3]);
    cout << "cpp=main.cpp" << endl;
    out << "cpp=main.cpp" << endl;
    cout << "count=" << right - left + 1 << endl;
    out << "count=" << right - left + 1 << endl;
    cout << "time=1000" << endl;
    out << "time=1000" << endl;
    for(int i = left; i <= right; i++) {
        cout << argv[1] << i << ".in " << argv[1] << i << ".ans" << endl;
        out << argv[1] << i << ".in " << argv[1] << i << ".ans" << endl;
    }
}