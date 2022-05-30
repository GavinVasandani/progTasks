#include <iostream> //FINAL
#include <string>
#include <vector>

struct BNode{

    std::string val;    
    BNode* left;
    BNode* right;

};
//Function to split input into separate strings
std::vector<std::string> findDirection(std::string word){

    std::string word_i;
    std::vector<std::string>direction;
 
    for(int i = 0; i < word.size(); i++){
 
        word_i = "";
        word_i.push_back(word[i]);
        direction.push_back(word_i);

    }
    return direction;
}
//Function to reassign leaf value based on input combination
void updateVal (BNode* pntr, std::vector<std::string>direction, int i) {

    if((pntr->right == nullptr) && (pntr->left == nullptr)) { 
        pntr->val = "1";
    }
    else if (direction[i]=="0") {
        updateVal(pntr->left,direction,i+1);
    }
    else {
        updateVal(pntr->right,direction,i+1);
    }

}
//Function used to connect the 2 functions: findDirection and UpdateVal
BNode* assignLeaf (BNode* t, std::vector<std::string> fvalues) {

    for (int i = 0; i<fvalues.size(); i++) {
        std::vector<std::string>direction = findDirection(fvalues[i]);
        updateVal(t,direction,0);
    }
    return t;
}
//Function takes in input and traverses through tree to check if output is 0 or 1
std::string checker (BNode* pntr, std::vector<std::string>direction, int i) {

    if((pntr->left == nullptr) && (pntr->right == nullptr)) {
        return pntr->val;
    }
    else if (direction[i]=="0") {
        return checker(pntr->left,direction,i+1);
    }
    else {
        return checker(pntr->right,direction,i+1); 
    }

} 
//Rearranging Algorithm Start
std::vector<int> rearrangeOrder (int NumOfVar, std::vector<std::string>fvalues) {

   std::vector<int>CommonTerms;

    for (int k = 0; k<NumOfVar; k++) {
        
        int count1 = 0;
        int count0 = 0;

        for (int j = 0; j<fvalues.size(); j++) {
            
            std::string word = "";
            word.push_back(fvalues[j][k]);

            if(word == "1") {
                count1 = count1+1;
            }
            else {
                count0 = count0+1;
            }
        }

        if (count1>=count0) {
            CommonTerms.push_back(count1); 
        }
        else {
            CommonTerms.push_back(count0);
        }

    }

    std::vector<int>varOrder;
    int temp0 = 0;
    int temp1 = 0;

    for(int i = 0; i<NumOfVar; i++) {
        varOrder.push_back(i);
    }

    for (int p = 0; p<NumOfVar; p++) {

        for(int q = p+1; q<NumOfVar; q++) {

            if(CommonTerms[p]>CommonTerms[q]) {

                temp0 = CommonTerms[p];
                CommonTerms[p] = CommonTerms[q];
                CommonTerms[q] = temp0;

                temp1 = varOrder[p];
                varOrder[p] = varOrder[q];
                varOrder[q] = temp1;
            }
        }
    }
    return varOrder;
}

std::vector<std::string> rearrangeInputs (int NumOfVar, std::vector<std::string>fvalues) {

    std::vector<std::string>fvaluesNew; 

    std::vector<int>varOrder = rearrangeOrder(NumOfVar, fvalues); 

    for(int n = 0; n<fvalues.size(); n++) {

        std::string elementNew = "";

        for(int m = 0; m<NumOfVar; m++) {
            elementNew.push_back(fvalues[n][varOrder[m]]);
        }
        
        fvaluesNew.push_back(elementNew); 
    }
    return fvaluesNew; 
}
//Rearranging Algorithm End
//Function used to construct tree and assign variables (x1,x2,x3...) to nodes
BNode* construct (int NumOfVar, int count, std::vector<std::string>fvalues) {
    BNode* b; 
    b = new BNode; 
    std::vector<int>varOrder = rearrangeOrder(NumOfVar, fvalues); 

    if (count==NumOfVar) { 
        b->val = "0";
        b->left = nullptr;
        b->right = nullptr;
    }

    else { 
        std::string nodeVal = "x"+std::to_string(varOrder[count]+1);
        b->val = nodeVal;
        b->left = construct(NumOfVar,count+1,fvalues);
        b->right = construct(NumOfVar,count+1,fvalues);
    }
    return b; 
} 
//Identical Leaf Algorithm Start
BNode* compareLeaf (BNode* pntr) { 
    if(pntr->left==nullptr && pntr->right==nullptr) {
        return pntr;
    }
    
    else if((pntr->left->left == nullptr) && (pntr->left->right == nullptr) && (pntr->right->left == nullptr) && (pntr->right->right == nullptr)) { //why do we need this condition? because are only considering values in leaves not branch nodes
        
        if((pntr->left->val) == (pntr->right->val)) {
            pntr->val = pntr->left->val;
            pntr->left = nullptr;
            pntr->right = nullptr; 
        }

    }
    
    else {
        pntr->left = compareLeaf(pntr->left);
        pntr->right = compareLeaf(pntr->right);
    }
    return pntr;
}

BNode* identicalLeaf (int NumOfVar, BNode* currentpntr) { 

    for (int i = 0; i<NumOfVar; i++) { 
        currentpntr = compareLeaf(currentpntr); 
    }
    return currentpntr;
}
//Identical Leaf Algorithm End

//Identical Tree Algorithm Start
int compareTree (BNode* a, BNode* b) {

    if (a == nullptr && b == nullptr) {
        return 1; 
    }
    else if (a->val==b->val) {
        return (compareTree(a->left, b->left) && compareTree(a->right, b->right));
    }
    else {
        return 0;
    }
}

BNode* identicalTree (BNode* pntr) {

    if (compareTree(pntr->left,pntr->right)) { 

        while (compareTree(pntr->left,pntr->right)==1 && (pntr->left!=nullptr) && (pntr->right!=nullptr)) {
            pntr = pntr->left; 
        }
        return pntr;
    }

    else { 
        pntr->left = identicalTree(pntr->left);
        pntr->right = identicalTree(pntr->right);
        return pntr; 
    }
}
//Identical Tree Algorithm End

void printBT(const std::string& prefix, const BNode* node, bool isLeft) {
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->val << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, false);
    }
}
void printBT2(const BNode* node) {
    printBT("", node, false);    
}

BNode* build_bt(const std::vector<std::string>& fvalues) {

    int NumOfVar = (fvalues[0]).size();

    std::vector<std::string>fvaluesNew = rearrangeInputs(NumOfVar, fvalues); 

    BNode* topN = construct(NumOfVar,0,fvalues); 

    BNode* currentpntr = assignLeaf(topN, fvaluesNew);
    
    currentpntr = identicalLeaf(NumOfVar, currentpntr); 

    return identicalTree(currentpntr); 
}

int label_to_idx(const std::string& label){
 
    std::string out;
 
    for(int i = 1; i < label.size(); i++){
        out.push_back(label[i]);
    }
 
    return std::stoi(out) - 1;
}

std::string eval_bt(BNode* bt, const std::string& input){
 
    if( (bt->left == NULL) && (bt->right == NULL) ){
        return bt->val;
    }
    else{
        int idx = label_to_idx(bt->val);
        std::string input_idx;
        input_idx.push_back(input[idx]);
 
        if(input_idx == "0"){
            return eval_bt(bt->left, input); 
        }
        else{
            return eval_bt(bt->right, input); 
        }
    }
}

void deallocate_tree(BNode* t) {
        if(t != NULL){
          deallocate_tree(t->left);
          deallocate_tree(t->right);
          delete t;
    }
}

int n_nodes_bt(BNode* t){
    if(t == NULL){
        return 0;
    }
    else{
        return 1 + n_nodes_bt(t->left) + n_nodes_bt(t->right);
    }
}

class BoolTree{
public:
 
    BoolTree(const std::vector<std::string>& fvalues){
       t = build_bt(fvalues);
       printBT2(t); //REMOVE 
    }
 
    std::string eval(const std::string& s){
        return eval_bt(t, s);
    }
 
    int n_nodes(){
        return n_nodes_bt(t);
    }
 
    ~BoolTree(){
        deallocate_tree(t);
 }
 
private:
    BNode* t;
};

int main(){
 
    std::vector<std::string> fv;
    std::string row;
 
    row = "11";
    fv.push_back(row);
 
    BoolTree ft1(fv);
    // as in the second assignment we give as input only the rows
    // of the truth table whose value is 1
    // (this is an example with the boolean "and" function)
 
    fv.clear();
 
    row = "0001";
    fv.push_back("0001");
    row = "1111";
	fv.push_back("1111");
    row = "1110";
	fv.push_back("1110");
    row = "0111";
	fv.push_back("0111");
    row = "0110";
	fv.push_back("0110");
    row = "0010";
	fv.push_back("0010");
    row = "1101";
	fv.push_back("1101");
    row = "1010";
	fv.push_back("1010");
    row = "0101";
	fv.push_back("0101");

    BoolTree ft2(fv);
    // this corresponds to the f(x1, x2, x3) example shown above
 
    std::cout << ft1.n_nodes() << std::endl;
    // we expect this to print 5
 
    std::cout << ft2.n_nodes() << std::endl;
    // if the algorithm is such that it builds the smallest possible corresponding tree
    // for the boolean function we are considering
    // then this will print 3 (see tree diagram in the example above)
 
    std::cout <<ft1.eval("01") << std::endl;
    // this should print "0" 

    std::cout << ft1.eval("11") << std::endl;
    // this should print "1"
 
    std::cout << ft2.eval("0000") << std::endl;
    // this should print "0"

    std::cout << ft2.eval("1111") << std::endl;
    // this should print "1"
 
}