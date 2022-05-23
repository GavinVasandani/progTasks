#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono> //REMOVE BEFORE TAKING ON REPLIT

using namespace std;
auto start = chrono::steady_clock::now();
    
vector<string> arranger (vector<string>fvalues) {

    vector<int>numofComTerms; //vector that contains the number of common terms for its respective index so index 1 contains number of common terms in x1

    //wrong we want to iterate element number and keep character position in element constant so: 
    //so in below logic we iterate through each element in fvalues first and keep character position we evaluate constant
    for (int k = 0; k<fvalues[0].size(); k++) { //fvalues.at(1).size() works
        
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
    for (int r = 0; r<numofComTerms.size(); r++) {
        cout<<"This is value before ordering: "<<numofComTerms[r]<<endl;
    }
    //return numofComTerms; //we output the vector

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
    for (int r = 0; r<arrangeParam.size(); r++) {
        cout<<"This is new parameter order: "<<arrangeParam[r]<<endl;
    }
    //return {numofComTerms,arrangeParam}; //do this process in a func and then the output of the func wont be 2 vec

    //vector<int>comTerm = arranger(fvalues);
    //for (int k=0; k<numofComTerms.size(); k++) {
    //    cout<<numofComTerms[k]<<endl;
    //}
    //for (int j=0; j<arrangeParam.size(); j++) {
    //    cout<<arrangeParam[j]<<endl;
    //}

    //rearrange fvalues to new order:

    vector<string>fvaluesNew; //new vector that will contain all the rearranged fvalues

    for(int n = 0; n<fvalues.size(); n++) {

        string elementNew = "";
        for (int t = 0; t<fvalues[0].size(); t++) {
            elementNew.push_back(0); //so this makes sure the string that will hold values and will change based on new arranged order is same size as inputs
        }
        //string elementNew = "0000"; //string that will hold values that we will change based on new rearranged order and then input into fvaluesNew
        
        for(int m = 0; m<fvalues[0].size(); m++) {
            elementNew[arrangeParam[m]] = fvalues[n][m];
        }

        fvaluesNew.push_back(elementNew); //so new rearranged word is inputted into fvaluesNew;
    }

    return fvaluesNew; //rearranged fvalues

}
    
int main() { //havent considered case where we have no identical subtrees in entire tree

    vector<string>fvalues;
    string row;

    row = "11";
    fvalues.push_back(row);

    vector<string>fvaluesNew = arranger(fvalues);

    for(int i = 0; i<fvaluesNew.size(); i++) {
        cout<<fvaluesNew[i]<<endl;
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout<<chrono::duration<double, milli>(diff).count()<<" ms"<<endl;

}