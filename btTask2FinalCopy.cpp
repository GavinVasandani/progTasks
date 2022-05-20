#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

struct BNode{
    string val;    
    BNode* left;
    BNode* right;
};

vector<string> find_direction(string word){
 //this needs to loop for every letter in the element
    string word_i;
    vector<string>direction; //list containing what direction to go in (1 = R, 0 = L)
 
    for(int i = 0; i < word.size(); i++){
 
        word_i = "";
        word_i.push_back(word[i]);
        direction.push_back(word_i);

    }
    return direction;
}

void updateVal (BNode* pntr, vector<string>direction, int i) {

    if((pntr->right == nullptr) && (pntr->left == nullptr)) { //any combo of 0,1s we input must give 1 at the end because we only input combos that give 1, so base case is 1 is given to value of the leaf node (node which has nullptr next)
        pntr->val = "1";
        //return pntr;
    }
    else if (direction.at(i)=="0") { //direction.at(i) gives the value at index i in the vector direction
        updateVal(pntr->left,direction,i+1);
    }
    else {
        updateVal(pntr->right,direction,i+1);
    } //this will make sure we assign the correct leaf node the correct answer value

}

BNode* checker (BNode* t, vector<string> fvalues) { //will be necessary to see whether 1 so we go R or 0 we go left

  for (int i = 0; i<fvalues.size(); i++) { //iterates through vector of values that give ouput 1

    vector<string>direction = find_direction(fvalues.at(i)); //makes individual vector for each answer and splits into 2 so '01' becomes '0','1' and this is stored in 1 vector
    updateVal(t,direction,0);
    
    }
    return t; //outputs the pointer holding address of the top node of the tree
}

BNode* below (int numofParam, int count) { //this builds the full tree and by default assigns value = 0 for each node
    BNode* b; //pointer b which holds address to a variable that is type BNode
    b = new BNode; //pointer holds address to a temporary variable (new) BNode
    if (count==numofParam) { //so loop ends once count = number of parameters
        b->val = "0";
        b->left = nullptr;
        b->right = nullptr;
    }
    else { //this names each node aka the val is assigned to a string being x(number)
        string nodeVal = "x"+to_string(count+1);
        b->val = nodeVal;
        b->left = below(numofParam,count+1);
        b->right = below(numofParam,count+1);
    }
    return b; 
} //this recursion makes the entire tree of n parameters

string parser (BNode* pntr, vector<string>direction, int i) { //this checks whether the input combo of 0,1s gives 0 or 1
    //outputs the value of the bottom node

    if((pntr->right == nullptr) && (pntr->left == nullptr)) {
        return pntr->val;
    }
    else if (direction.at(i)=="0") { //if vector that contains this specific input has a 0 then we go left, if not then else go right and recur function
        return parser(pntr->left,direction,i+1);
    }
    else {
        return parser(pntr->right,direction,i+1);
    } //this will make sure we parse all the way to the bottom and output the value

}

BNode* build_bt(const vector<string>& fvalues) { //remember its referenced so vector<string> &fvalues
    
    //Inserting tree nodes
    //checking for a 1
    //create the tree root aka top node

    int numofParam = (fvalues.at(0)).size(); //number of parameters, so this checks the size of the first input combo of 0,1s

    BNode* topN = below(numofParam,0); //creates initial tree with 0s in all leaf nodes and x(number) as val in the other branch nodes
    return checker (topN, fvalues); //changes leaf nodes to have 1 if necessary based on what input was and outputs pointer holding address to top node of modified tree

}

string eval_bt(BNode* bt, const string& input) {
    //bt is address of top node pointer
    //input is the configuration we want to check to see what output is by parsing through tree
    vector<string>direction = find_direction(input); //so we make each input into its own vector and parse through tree to check if its 0 or 1 at specific leaf node

    //parse through
    return parser(bt,direction,0);

}

int main() {

    vector<string>fvalues;
    string row;

    row = "010";
    fvalues.push_back(row);
    row = "011";
    fvalues.push_back(row);
    row = "110";
    fvalues.push_back(row);
    row = "111";
    fvalues.push_back(row);
  
    BNode* bt;
    bt = build_bt(fvalues);

    cout<<"Please work"<<endl;
    cout<<(bt->right->right)<<endl;

    cout << eval_bt(bt, "010") << endl; //should output 1
    cout << eval_bt(bt, "000") << endl; //should output 0
    
}