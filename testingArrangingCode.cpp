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
    for (int k = 0; k<fvalues[1].size(); k++) { //fvalues.at(1).size() works
        
        //after every loop through fvalues elements we reset count1 and count0 values.
        int count1 = 0;
        int count0 = 0;

        for (int j = 0; j<fvalues.size(); j++) {
            
            string word = "";
            word.push_back(fvalues[j][k]);
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

    row = "00000";
    fvalues.push_back(row);
    row = "00001";
    fvalues.push_back(row);
    row = "00010";
    fvalues.push_back(row);
    row = "00011";
    fvalues.push_back(row);
    row = "00100";
    fvalues.push_back(row);
    row = "00101";
    fvalues.push_back(row);
    row = "00110";
    fvalues.push_back(row);
    row = "00111";
    fvalues.push_back(row);
    row = "01000";
    fvalues.push_back(row);
    row = "01001";
    fvalues.push_back(row);
    row = "01010";
    fvalues.push_back(row);
    row = "01011";
    fvalues.push_back(row);
    row = "01100";
    fvalues.push_back(row);
    row = "01101";
    fvalues.push_back(row);
    row = "01110";
    fvalues.push_back(row);
    row = "01111";
    fvalues.push_back(row);

    vector<int>numofComTerms = arranger(fvalues);
    for (int r = 0; r<numofComTerms.size(); r++) {
        cout<<"This is value before ordering: "<<numofComTerms[r]<<endl;
    }

    //Determining the parameter with most common terms and least: Rearranging vector to get parameter on top and bottom
    vector<int>arrangeParam;
    int temp0 = 0;
    int temp1 = 0;

    for(int i = 0; i<numofComTerms.size(); i++) {
        arrangeParam.push_back(i);
    }

    for (int p = 0; p<numofComTerms.size(); p++) {

        for(int q = p+1; q<numofComTerms.size(); q++) {

            if(numofComTerms[p]>numofComTerms[q]) {

                //ordering values in vector containing number of common terms
                temp0 = numofComTerms[p];
                numofComTerms[p] = numofComTerms[q];
                numofComTerms[q] = temp0;

                //ordering values in vector containing indexes aka parameters
                temp1 = arrangeParam[p];
                arrangeParam[p] = arrangeParam[q];
                arrangeParam[q] = temp1;
            } //we can call elements of vectors like vecname[index], so stop using .at()
        }   //else no change in any vector
    }
    //return {numofComTerms,arrangeParam}; //do this process in a func and then the output of the func wont be 2 vec

    //vector<int>comTerm = arranger(fvalues);
    for (int k=0; k<numofComTerms.size(); k++) {
        cout<<numofComTerms[k]<<endl;
    }
    for (int j=0; j<arrangeParam.size(); j++) {
        cout<<arrangeParam[j]<<endl;
    }
}