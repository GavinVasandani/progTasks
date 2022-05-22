#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;
    
vector<int> arranger (vector<string>fvalues) {

    vector<int>numofComTerms; //vector that contains the number of common terms for its respective index so index 1 contains number of common terms in x1

    //wrong we want to iterate element number and keep character position in element constant so: 
    //so in below logic we iterate through each element in fvalues first and keep character position we evaluate constant
    for (int k = 0; k<fvalues.at(1).size(); k++) { //fvalues.at(1).size() works
        
        //after every loop through fvalues elements we reset count1 and count0 values.
        int count1 = 0;
        int count0 = 0;

        for (int j = 0; j<fvalues.size(); j++) {
            
            string word = "";
            word.push_back(fvalues.at(j)[k]);
            //so word is used here to create a string with only 1 char input so we can easily compare string to string in if statement condition

            if(word == "1") { //fvalues.at(j)[k] works. Use stoi() as contents of fvalues are strings to must convert to int for comparison with 1
                count1 = count1+1;
            }
            else {
                count0 = count0+1;
            }
        }
        //when we exit it means we've seen all elements in fvalue at position k
        if (count1>=count0) { //if count1=count0 then doesnt matter if we input count1 or count0 values into numofComTerms. 
            numofComTerms.push_back(count1); //so we store the 1st value in numofComTerms, doesnt matter if most common term was 0s or 1s, we just evaluate which is the highest
        }
        else {
            numofComTerms.push_back(count0);//else we store number of 0s
        }
        //so this will repeat for all terms in fvalues to give us vector with number of common terms for each parameter in its respective index.

    }
    return numofComTerms; //we output the vector
}
    
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

    vector<int>comTerm = arranger(fvalues);
    for (int i=0; i<comTerm.size(); i++) {
        cout<<comTerm.at(i)<<endl;
    }
}