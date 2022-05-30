#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono> //REMOVE BEFORE TAKING ON REPLIT

using namespace std; //REMOVE

struct BNode{
    string val;    
    BNode* left;
    BNode* right;
};

vector<string> find_direction(string word){
 //this needs to loop for every letter in the element
    string word_i;
    vector<string>direction; //list containing what direction to go in (1 = R, 0 = L)
 
    for(int i = 0; i < word.size(); i++){ //word.size() tells us the number of parameters 
 
        word_i = "";
        word_i.push_back(word[i]);
        direction.push_back(word_i);

    }
    return direction;
}

void updateVal (BNode* pntr, vector<string>direction, int i) { //so output of this gives the final tree that has all the 1s in the leaves which are given based on input combo

    if((pntr->right == nullptr) && (pntr->left == nullptr)) { 
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

string parser (BNode* pntr, vector<string>direction, int i) { //this checks whether the input combo of 0,1s gives 0 or 1
    //outputs the value of the bottom node

    if((pntr->left == nullptr) && (pntr->right == nullptr)) { //should both be nullptr or is 1 enough?
        return pntr->val; //so this means we're in leaf node, so pntr is pointing to a leaf node
       // if ((pntr->val //no we need to start at node right before leafs
    }
    else if (direction.at(i)=="0") { //if vector that contains this specific input has a 0 then we go left, if not then else go right and recur function
        return parser(pntr->left,direction,i+1);
    }
    else {
        return parser(pntr->right,direction,i+1); 
        //we only want to do this for the leaves not every node
      //  if ((pntr->right->val) == (pntr->left->val)) { 

        }
} //this will make sure we parse all the way to the bottom and output the value

//given function. tree node counter
int n_nodes_bt(BNode* t){
    if(t == NULL){
        return 0;
    }
    else{
        return 1 + n_nodes_bt(t->left) + n_nodes_bt(t->right);
    }
}

//Arranger Code. Rename this func name to something that better represents what it does
vector<int> commonTerm (vector<string>fvalues) {

   vector<int>numofComTerms;

    for (int k = 0; k<fvalues[0].size(); k++) { //fvalues.at(1).size() works
        
        //after every loop through fvalues elements we reset count1 and count0 values.
        int count1 = 0;
        int count0 = 0;

        for (int j = 0; j<fvalues.size(); j++) {
            
            string word = "";
            word.push_back(fvalues[j][k]);

            if(word == "1") { //fvalues.at(j)[k] works. Use stoi() as contents of fvalues are strings to must convert to int for comparison with 1
                count1 = count1+1;
            }
            else {
                count0 = count0+1;
            }
        }
        //when we exit it means we've seen all elements in fvalue at position k
        if (count1>=count0) { //if count1=count0 then doesnt matter if we input count1 or count0 values into numofComTerms. 
            numofComTerms.push_back(count1); 
        }
        else {
            numofComTerms.push_back(count0);//else we store number of 0s
        }

    }

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
    return arrangeParam;
}

BNode* below (int numofParam, int count, vector<string>fvalues) { //this builds the full tree and by default assigns value = 0 for each node
    BNode* b; //pointer b which holds address to a variable that is type BNode
    b = new BNode; //pointer holds address to a temporary variable (new) BNode
    vector<int>arrangeParam = commonTerm(fvalues); //maybe change to rearrageParam so more clear

    if (count==numofParam) { //so loop ends once count = number of parameters
        b->val = "0";
        b->left = nullptr;
        b->right = nullptr;
    }
    else { 
        string nodeVal = "x"+to_string(arrangeParam[count]+1); //we add +1 again as arrangeParam is 0-3 so to get it from 1 onwards then must add 1 so now 1-4.
        b->val = nodeVal;
        b->left = below(numofParam,count+1,fvalues);
        b->right = below(numofParam,count+1,fvalues);
    }
    return b; 
} 

vector<string> rearrangeInputs (vector<string>fvalues) {
    //rearrange fvalues to new order:
    vector<string>fvaluesNew; //new vector that will contain all the rearranged fvalues
    vector<int>arrangeParam = commonTerm(fvalues); //this gets arrangeParam into our function to use

    for(int n = 0; n<fvalues.size(); n++) {

        string elementNew = "";
        
        for(int m = 0; m<fvalues[0].size(); m++) {
            elementNew.push_back(fvalues[n][arrangeParam[m]]);
        }

        fvaluesNew.push_back(elementNew); //so new rearranged word is inputted into fvaluesNew;
    }
    return fvaluesNew; //rearranged fvalues

}

BNode* parserChecker (BNode* pntr) { 
    if(pntr->left==nullptr && pntr->right==nullptr) {
        return pntr;
    }
    
    else if((pntr->left->left == nullptr) && (pntr->left->right == nullptr) && (pntr->right->left == nullptr) && (pntr->right->right == nullptr)) { //why do we need this condition? because are only considering values in leaves not branch nodes
        if((pntr->left->val) == (pntr->right->val)) {

            pntr->val = pntr->left->val; //so we reassign value of parent
            //so we set the children nodes to nullptr
            pntr->left = nullptr;
            pntr->right = nullptr; 
            //execute function to simplify tree
        }
    }
    
    else {
        pntr->left = parserChecker(pntr->left);
        pntr->right = parserChecker(pntr->right); //fine no stack overflow
        //parserChecker(pntr->left);
    }
    return pntr;
}

BNode* repeatCheck (int numofParam, BNode* currentpntr) { 

    for (int i = 0; i<numofParam-1; i++) { 
        currentpntr = parserChecker(currentpntr); 
    }
    return currentpntr; //this is the address of the head of the simplified tree
}
int compareTree (BNode* a, BNode* b) {

    if (a == nullptr && b == nullptr) {
        return 1; 
    }
    else if (a->val==b->val) {
        return (compareTree(a->left, b->left) && compareTree(a->right, b->right)); //so bool func, if one of them is not equal then output is false
    }
    else {
        return 0;
    }
}

BNode* finalSimplify (BNode* pntr) {

    if (compareTree(pntr->left,pntr->right)) { 
    
        while (compareTree(pntr->left,pntr->right)==1 && (pntr->left!=nullptr) && (pntr->right!=nullptr)) { 
            pntr = pntr->left; 
        }
        return pntr; //pntr->left is going to be the new head of the tree
    }
    else { 
        pntr->left = finalSimplify(pntr->left);
        pntr->right = finalSimplify(pntr->right);
        return pntr; 
    }
}

void printBT(const string& prefix, const BNode* node, bool isLeft) {
    if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        cout << node->val << endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, false);
    }
}
void printBT2(const BNode* node) {
    printBT("", node, false);    
}

BNode* build_bt(const vector<string>& fvalues) { //remember its referenced so vector<string> &fvalues

    vector<string>fvaluesNew = rearrangeInputs(fvalues); 

    int numofParam = (fvalues.at(0)).size(); 

    BNode* topN = below(numofParam,0,fvalues); 
    BNode* currentpntr = checker(topN, fvaluesNew); //USES find_direction
    currentpntr = repeatCheck(numofParam, currentpntr); 
    return finalSimplify(currentpntr); //outputs fully simplified tree
    
}

//given function
int label_to_idx(const string& label){
 
    string out;
 
    for(int i = 1; i < label.size(); i++){
        out.push_back(label[i]);
    }
 
    return stoi(out) - 1;
}
//given function
string eval_bt(BNode* bt, const string& input){
 
    if( (bt->left == NULL) && (bt->right == NULL) ){
        return bt->val;
    }
    else{
        int idx = label_to_idx(bt->val);
        string input_idx;
        input_idx.push_back(input[idx]);
 
        if(input_idx == "0"){
            return eval_bt(bt->left, input); 
        }
        else{
            return eval_bt(bt->right, input); 
        }
    }
}

class BoolTree{
public:
 
    BoolTree(const vector<string>& fvalues){
       t = build_bt(fvalues);
       printBT2(t); //REMOVE 
    }
 
    std::string eval(const string& s){
        return eval_bt(t, s);
    }
 
    int n_nodes(){
        return n_nodes_bt(t);
    }
 
    ~BoolTree(){
        // complete this function 
        // (do not alter in any other way class BoolTree)
 
        // keep in mind that you can include in this function 
        // calls to functions defined outside class BoolTree
        // (as done in the member functions above)
        // and that you can define other functions
        // above and outside this class
 
    }
 
private:
    BNode* t;
};

int main(){
 
    vector<string> fv;
    string row;
 
    row = "11";
    fv.push_back(row);
 
    BoolTree ft1(fv);
    // as in the second assignment we give as input only the rows
    // of the truth table whose value is 1
    // (this is an example with the boolean "and" function)
 
    fv.clear();
 
    row = "010";
    fv.push_back(row);
    row = "011";
    fv.push_back(row);
    row = "110";
    fv.push_back(row);
    row = "111";
    fv.push_back(row);
 
    BoolTree ft2(fv);
    // this corresponds to the f(x1, x2, x3) example shown above
 
    cout << ft1.n_nodes() << endl;
    // we expect this to print 5
 
    cout << ft2.n_nodes() << endl;
    // if the algorithm is such that it builds the smallest possible corresponding tree
    // for the boolean function we are considering
    // then this will print 3 (see tree diagram in the example above)
 
    cout << ft1.eval("01") << endl;
    // this should print "0" 
 
    cout << ft1.eval("11") << endl;
    // this should print "1"
 
    cout << ft2.eval("000") << endl;
    // this should print "0"
 
    cout << ft2.eval("111") << endl;
    // this should print "1"
 
}