#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono> //REMOVE BEFORE TAKING ON REPLIT

using namespace std;
auto start = chrono::steady_clock::now(); //USED TO CHECK PROCESSING TIME. MAKE SURE TO REMOVE

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

string parser (BNode* pntr, vector<string>direction, int i) { //this checks whether the input combo of 0,1s gives 0 or 1
    //outputs the value of the bottom node

    if((pntr->right == nullptr) && (pntr->left == nullptr)) { //should both be nullptr or is 1 enough?
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

//tree node counter
int counterN(BNode* t) {
    if (t==nullptr) { //checks if pointer which holds address to a node is null. Leaf node has an address but child of leaf node doesn't exist so it will be null so 0 count for that
        return 0; 
    }

    else {
        return 1+counterN(t->left)+counterN(t->right); //so we go left node and we add 1 for that node and then we check the children of the left node, if doesnt exist then only 1+0+0 is outputted for this stack.
    }
}

//Arranger Code
vector<int> commonTerm (vector<string>fvalues) { //part 1 of arrange functionality. Finds the number of common terms in each input parameter.

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
    //return numofComTerms; //we output the vector

    //used to check outputs of the vectors
    //for (int r = 0; r<numofComTerms.size(); r++) {
    //    cout<<"This is value before ordering: "<<numofComTerms[r]<<endl;
   // }

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
    else { //this names each node aka the val is assigned to a string being x(number)
        //string nodeVal = "x"+to_string(count+1); //change this so that it takes parameter based on rearranged order
        //maybe make vector so arrangeParam + 1; then to_string(arrangeParamNew[count+1]);
        string nodeVal = "x"+to_string(arrangeParam[count]+1); //we add +1 again as arrangeParam is 0-3 so to get it from 1 onwards then must add 1 so now 1-4.
        b->val = nodeVal;
        b->left = below(numofParam,count+1,fvalues);
        b->right = below(numofParam,count+1,fvalues);
    }
    return b; 
} //this recursion makes the entire tree of n parameters
//function order matters if we're calling a function in another function, so as we're calling commonTerm in func below then func below must be declared after commonTerm func

//make new function and call arrange so we can use arrangeParam
vector<string> rearrangeInputs (vector<string>fvalues) {
    //rearrange fvalues to new order:
    vector<string>fvaluesNew; //new vector that will contain all the rearranged fvalues
    vector<int>arrangeParam = commonTerm(fvalues); //this gets arrangeParam into our function to use

    for(int n = 0; n<fvalues.size(); n++) {

        string elementNew = "";
        //for (int t = 0; t<fvalues[0].size(); t++) {
        //    elementNew.push_back(0); //so this makes sure the string that will hold values and will change based on new arranged order is same size as inputs
        //}
        //string elementNew = "00000"; //string that will hold values that we will change based on new rearranged order and then input into fvaluesNew
        
        for(int m = 0; m<fvalues[0].size(); m++) {
            //elementNew[arrangeParam[m]] = fvalues[n][m];
            //elementNew[m] = fvalues[n][arrangeParam[m]];
            elementNew.push_back(fvalues[n][arrangeParam[m]]);
        }

        fvaluesNew.push_back(elementNew); //so new rearranged word is inputted into fvaluesNew;
    }
    return fvaluesNew; //rearranged fvalues

}

BNode* parserChecker (BNode* pntr) { //as long as pntr is head of tree, the modifications to pntr should be displayed in pntr by itself so we can keep as void func

    //we havent considered case where we have 1 leaf node alone so parent has 2 children, 1 is leaf, 1 is another parent node and we still run program for leaf node even though it doesnt have any children so it shouldn't run as the if condition will not apply so we get segmentation fault.
    //As if node is leaf node with val = 1, pntr->left->left = nullptr isnt possible, only pntr->left exists.
    //This should be solved by:
    //so we reordered so that leaf would not have to deal or check with condition where pntr->left->left == nullptr first.
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

    for (int i = 0; i<numofParam-1; i++) { //so if we have 3 input then this will loop twice, also string word argument is given by number of param in build_bt func
        currentpntr = parserChecker(currentpntr); //so we sent in the pointer to the head of the tree, we simplify one time and then resend in the simplified tree back into to further simplify if possible. 
    }
    return currentpntr; //this is the address of the head of the simplified tree
}
int compareTree (BNode* a, BNode* b) {

    if (a == nullptr && b == nullptr) {
        return 1; //default output is true because too reach nullptr we must've parsed down the trees such that we get nullptr
    }
    else if (a->val==b->val) {
        return (compareTree(a->left, b->left) && compareTree(a->right, b->right)); //so bool func, if one of them is not equal then output is false
    }
    else {
        return 0;
    }
}
BNode* finalSimplify (BNode* pntr) {

    if (compareTree(pntr->left,pntr->right)) { //so if we have first initial equivalence we run for loop
    
        while (compareTree(pntr->left,pntr->right)==1 && (pntr->left!=nullptr) && (pntr->right!=nullptr)) { //so while loop should repeat as long as subtrees are identical and pntr left, right isnt nullptr as that point we're most simplified possible and cant simplify further
            pntr = pntr->left; //if all these conditions occur then we have identical so pntr is pntr left and we repeat while loop condition
        }
        return pntr; //pntr->left is going to be the new head of the tree
    }
    else { //if we dont have equivalence we output tree as it is, so we only use the if statement so that we can have the else output the tree if we have no equivalence so we can differentiate between pntr outputted from while loop and pntr from else statement which was the original pntr.

        pntr->left = finalSimplify(pntr->left); //so if output is same as input then pntr->left = pntr->left (no change) if there is change we output fully simplified left and then we assign that to pntr->left;
        pntr->right = finalSimplify(pntr->right);
        return pntr; //so if nothing is identical, so we'll have nullptr at bottom so while will not execute and we'll output pntr so no change and if not nullptr but its leaves with values 0,1 then not equal so while will not execute so output will be same as input so no change.
    }
}

void printBT(const string& prefix, const BNode* node, bool isLeft)
{
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
void printBT2(const BNode* node)
{
    printBT("", node, false);    
}

BNode* build_bt(const vector<string>& fvalues) { //remember its referenced so vector<string> &fvalues

    vector<string>fvaluesNew = rearrangeInputs(fvalues); //this is reordered fvalues aka fvaluesNew

    int numofParam = (fvalues.at(0)).size(); //number of parameters, so this checks the size of the first input combo of 0,1s

    BNode* topN = below(numofParam,0,fvalues); //creates initial tree with 0s in all leaf nodes and x(number) as val in the other branch nodes

    //this function gets the pointer to head of tree and sends it to the simplification function to check for common children
    BNode* currentpntr = checker(topN, fvaluesNew);
    currentpntr = repeatCheck(numofParam, currentpntr);
    return finalSimplify(currentpntr); //outputs fully simplified tree
    
}

string eval_bt(BNode* bt, const string& input) {
    //bt is address of top node pointer
    //input is the configuration we want to check to see what output is by parsing through tree
    vector<string>direction = find_direction(input); //so we make each input into its own vector and parse through tree to check if its 0 or 1 at specific leaf node

    //parse through
    return parser(bt,direction,0);

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
  
    BNode* bt;
    bt = build_bt(fvalues);

    cout<<"Please work"<<endl;
    cout<<(bt->val)<<endl;

    cout << eval_bt(bt, "0") << endl; //should output 0
    cout << eval_bt(bt, "1") << endl; //should output 1
    cout << "Number of nodes in tree is: " << counterN(bt)<<endl;

    printBT2(bt); //outputs tree
    
    //USED TO CHECK PROCESSING TIME. MAKE SURE TO REMOVE
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout<<chrono::duration<double, milli>(diff).count()<<" s"<<endl;

}
