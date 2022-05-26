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

//checks if children are common and if so replaces the parent with child

BNode* parserChecker (BNode* pntr) { //as long as pntr is head of tree, the modifications to pntr should be displayed in pntr by itself so we can keep as void func

    if((pntr->left->left == nullptr) && (pntr->left->right == nullptr) && (pntr->right->left == nullptr) && (pntr->right->right == nullptr)) {
        if((pntr->left->val) == (pntr->right->val)) {
            pntr->val = pntr->left->val; //so we reassign value of parent
            //so we set the children nodes to nullptr
            pntr->left = nullptr;
            pntr->right = nullptr; 
            //execute function to simplify tree
        }
    }
    else {
        parserChecker(pntr->left);
        parserChecker(pntr->right); //fine no stack overflow
        //parserChecker(pntr->left);
    }
    return pntr;
}

//function to repeat parserChecker x-1 times where x is number of parameters

BNode* repeatCheck (int numofParam, BNode* currentpntr) { 

    for (int i = 0; i<numofParam-1; i++) { //so if we have 3 input then this will loop twice, also string word argument is given by number of param in build_bt func
        currentpntr = parserChecker(currentpntr); //so we sent in the pointer to the head of the tree, we simplify one time and then resend in the simplified tree back into to further simplify if possible. 
    }
    return currentpntr; //this is the address of the head of the simplified tree
}

//function to compare 2 subtrees
//so we get 2 trees given by the pointers a, b

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

//to get pointers to the head of the subtrees for now we'll just take what's below head of current tree but technically this code should work anywhere in the tree not only for x2 which is children of head of tree
BNode* finalSimplify (BNode* pntr) {

    if (compareTree(pntr->left,pntr->right)) { //so if we have first initial equivalence we run for loop
    
        while (compareTree(pntr->left,pntr->right)==1 && (pntr->left!=nullptr) && (pntr->right!=nullptr)) { //so while loop should repeat as long as subtrees are identical and pntr left, right isnt nullptr as that point we're most simplified possible and cant simplify further
            pntr = pntr->left; //if all these conditions occur then we have identical so pntr is pntr left and we repeat while loop condition
        }
        return pntr; //pntr->left is going to be the new head of the tree
    }
        //then we must also repeat compareTree for remainder of this tree
        //or should we continue comparison and take the parent node that is the closest to leaf as long as they're completely identical
        //so taking x3 parent directly instead of getting x2 as head of tree and then comparing its children to get x3 as head.
        //nvm repeating makes most sense so that compareTree just has to output either 1, 0
    //else if (pntr->left==nullptr && pntr->right==nullptr) { //check for leaf node condition, also put this as the first if statement
    //    return pntr;
    //}
    else { //if we dont have equivalence we output tree as it is, so we only use the if statement so that we can have the else output the tree if we have no equivalence so we can differentiate between pntr outputted from while loop and pntr from else statement which was the original pntr.

        pntr->left = finalSimplify(pntr->left); //so if output is same as input then pntr->left = pntr->left (no change) if there is change we output fully simplified left and then we assign that to pntr->left;
        pntr->right = finalSimplify(pntr->right);
        return pntr; //so if nothing is identical, so we'll have nullptr at bottom so while will not execute and we'll output pntr so no change and if not nullptr but its leaves with values 0,1 then not equal so while will not execute so output will be same as input so no change.
    }
}

BNode* build_bt(const vector<string>& fvalues) { //remember its referenced so vector<string> &fvalues
    
    //Inserting tree nodes
    //checking for a 1
    //create the tree root aka top node

    int numofParam = (fvalues.at(0)).size(); //number of parameters, so this checks the size of the first input combo of 0,1s

    BNode* topN = below(numofParam,0); //creates initial tree with 0s in all leaf nodes and x(number) as val in the other branch nodes
    //return checker (topN, fvalues); //changes leaf nodes to have 1 if necessary based on what input was and outputs pointer holding address to top node of modified tree
    //send output of checker into commonChecker
    //output of checker func is a pointer so: 
    //return parserChecker(checker(topN, fvalues));

    //this function gets the pointer to head of tree and sends it to the simplification function to check for common children
    BNode* currentpntr = checker(topN, fvalues);
    currentpntr = repeatCheck(numofParam, currentpntr);
    return finalSimplify(currentpntr); //outputs fully simplified tree

    //for tree without final simplification by comparing subtrees uncomment:
    //return repeatCheck(numofParam,currentpntr);
    
    //currentpntr = parserChecker(currentpntr);
    //return currentpntr;
    //return parserChecker(currentpntr);
    
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

    row = "0001";
    fvalues.push_back(row);
    row = "0011";
    fvalues.push_back(row);
    row = "0101";
    fvalues.push_back(row);
    row = "0111";
    fvalues.push_back(row);
    row = "1010";
    fvalues.push_back(row);
    row = "1011";
    fvalues.push_back(row);
    row = "1110";
    fvalues.push_back(row);
    row = "1111";
    fvalues.push_back(row);
  
    BNode* bt;
    bt = build_bt(fvalues);

    cout<<"Please work"<<endl;
    cout<<(bt->right->right->val)<<endl;

    cout << eval_bt(bt, "0000") << endl; //should output 0
    cout << eval_bt(bt, "0011") << endl; //should output 1
    cout << "Number of nodes in tree is: " << counterN(bt);
    //current works for all tests but we need the compare tree function to work not only for children of head of tree but for anywhere in the tree
}