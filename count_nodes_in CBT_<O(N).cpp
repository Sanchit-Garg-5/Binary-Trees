/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
// we have to compute in <o(n) tc. the current tc is o(log base 2 of n)^2. sc is o(log base2 n) for recursive call stack.
/* nodes contributed by curr(if its null is 0) else: 1+ nodes by its left,nodes by its right.
now check that left height and right height of curr->left, is same: then we can directly say the number of noded by curr->left is 2^(h) -1.
but if left H!=right H of curr->left, then for its contribution to nodes, we have to recuse as usual.
since its a complete BT, it is guranteed that the subtrees/nodes actually recursed are log base 2 of total. 
view tree at 7th min of striver's video: contribution at root=1+ count(2)+count(3). for count2, since leftH=rightH=3, count2 is hence 7. similarly count3.
*/
public:
    int Llevel(TreeNode* curr){
        if(!curr){return 0;}    
        return 1+Llevel(curr->left);
    }
    int Rlevel(TreeNode* curr){
        if(!curr){return 0;}    
        return 1+Rlevel(curr->right);
    }
    int count(TreeNode* curr){
        if(!curr){return 0;}
        int left1=Llevel(curr->left);
        int right1=Rlevel(curr->left);
        int cleft=0,cright=0;
        if(left1==right1){cleft=(1LL<<left1)-1;}
        else{cleft=count(curr->left);}
        int left2=Llevel(curr->right);
        int right2=Rlevel(curr->right);
        if(left2==right2){cright=(1LL<<left2)-1;}
        else{cright=count(curr->right);}
        return 1+cleft+cright;
    }
    int countNodes(TreeNode* root) {
        return count(root);
    }
};
