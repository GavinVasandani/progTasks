#include <iostream>
#include <vector>
#include <string>
 
// you can include other headers 
// you need for your code
 
// you can use only headers from the C++ standard library
 
// you can use any headers from the C++ standard library
// except for the algorithm header
 
// do not use "using namespace std;"
 
// do not alter this structured data type definition
struct BNode{
    std::string val;
    // this will contain
    // "xn" (e.g. x3 or x1 etc) in non-leaf nodes
    // "0" or "1" in leaf nodes
 
    BNode* left;
    // this will conventionally represent the 0 branch
    BNode* right;
    // this will conventionally represent the 1 branch
 
    // (as usual leaf nodes will have both left and right pointing to NULL)
};

// you can define here other functions to use in the code below
 
// you can also define here other 
// structured data types or classes 
// (including member data and member functions) 
// to use in the code below
 
// do not alter the following line that begins the function build_bt
BNode* build_bt(const std::vector<std::string>& fvalues){
    // complete this function
}
 
// do not alter the following function
// this function converts e.g. std::string "x3" to int 2
int label_to_idx(const std::string& label){
 
    std::string out;
 
    for(int i = 1; i < label.size(); i++){
        out.push_back(label[i]);
    }
 
    return std::stoi(out) - 1;
}
 
// do not alter the following function
std::string eval_bt(BNode* bt, const std::string& input){
 
    if( (bt->left == NULL) && (bt->right == NULL) ){
        return bt->val; //so if we reach leaf we output value in leaf
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

//^^^IMPLEMENTED

 
// do not alter the following function
int n_nodes_bt(BNode* t){
    if(t == NULL){
        return 0;
    }
    else{
        return 1 + n_nodes_bt(t->left) + n_nodes_bt(t->right);
    }
}

//^^IMPLEMENTED
 
class BoolTree{
public:
 
    BoolTree(const std::vector<std::string>& fvalues){
       t = build_bt(fvalues);
    }
 
    std::string eval(const std::string& s){
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
 
// the main provided below must work correctly
// with your implementation for the code above
// however you can change it as you wish for your own testing 
// and your changes won't be considered for the assessment
// (in your submission you can also have an empty main or no main at all)
 
int main(){
 
    std::vector<std::string> fv;
    std::string row;
 
    row = "00000";
    fv.push_back(row);
    row = "00001";
    fv.push_back(row);
    row = "00010";
    fv.push_back(row);
    row = "00011";
    fv.push_back(row);
    row = "00100";
    fv.push_back(row);
    row = "00101";
    fv.push_back(row);
    row = "00110";
    fv.push_back(row);
    row = "00111";
    fv.push_back(row);
    row = "01000";
    fv.push_back(row);
    row = "01001";
    fv.push_back(row);
    row = "01010";
    fv.push_back(row);
    row = "01011";
    fv.push_back(row);
    row = "01100";
    fv.push_back(row);
    row = "01101";
    fv.push_back(row);
    row = "01110";
    fv.push_back(row);
    row = "01111";
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
 
    std::cout << ft1.n_nodes() << std::endl;
    // we expect this to print 5
 
    std::cout << ft2.n_nodes() << std::endl;
    // if the algorithm is such that it builds the smallest possible corresponding tree
    // for the boolean function we are considering
    // then this will print 3 (see tree diagram in the example above)
 
    std::cout << ft1.eval("01000") << std::endl;
    // this should print "0" 
 
    std::cout << ft1.eval("11000") << std::endl;
    // this should print "1"
 
    std::cout << ft2.eval("001") << std::endl;
    // this should print "0"
 
    std::cout << ft2.eval("110") << std::endl;
    // this should print "1"
 
}