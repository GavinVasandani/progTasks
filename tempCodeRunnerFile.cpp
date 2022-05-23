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