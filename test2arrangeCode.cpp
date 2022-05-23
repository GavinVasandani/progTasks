#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <typeinfo>

using namespace std;

int main() { //havent considered case where we have no identical subtrees in entire tree

    vector<string>fvalues;
    string row;

    row = "0001";
    fvalues.push_back(row);
    row = "0010";
    fvalues.push_back(row);
    row = "0101";
    fvalues.push_back(row);
    row = "0110";
    fvalues.push_back(row);
    row = "0111";
    fvalues.push_back(row);
    row = "1010";
    fvalues.push_back(row);
    row = "1101";
    fvalues.push_back(row);
    row = "1110";
    fvalues.push_back(row);
    row = "1111";
    fvalues.push_back(row);

    cout<<fvalues[5][0]<<endl;
    string word = "";
    word.push_back(fvalues[5][0]);

    if(word == "1"){
        cout<<"it works!";
    }

    cout<<fvalues[1]<<endl;


    
    //int sum = stoi((fvalues.at(5))[0]) + 1;
    //cout<<typeid(stoi(fvalues.at(5)[0])).name()<<endl;
    //cout<<sum<<endl;
}