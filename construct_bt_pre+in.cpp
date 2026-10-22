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
/*   In preoder-the jth guy is either the left child of j-1th or it is a right child of either j-1th or right child of(some ancestor of j-1 th guy).
we use a map to save given indexes of inorder. clearly inorder:1,2,3. so 1 belongs to left subtree of 2 and 3 belongs to right subtree of 2.
so if index of jth guy(in preorder) is to the left of the index of j-1th guy, then j is left child of j-1 th guy. else it must be right child of some ancestor of j-1 th guy, including 
the j-1 th guy too. Which ancestor? Let 10 be root, 20 lchild of 10,30rchild of 10. 40 lchild of 20,50 lchild of 20. 
clearly right child of 20 would appear before the right child of 10 in preoder. or think opposite. if we currently at 30 in preorder array. then its parent would first be 40,20 and then 10.
UNLESS 40,20 NOT GET ELIMINATED AS POTENTIAL PARENTS TO 30: 10 CAN'T BE THE PARENT TO 30 THEN. So we use a stack.
The last ancestor of j-1 (inlcuding j-1 itself) to whose right subtree does jth guy is part of-has to be the parent of jth guy. so 50 appears right to both 40,20,but not 10. and the last ancestor
to whose right it was part of is 20, hence 20 is the parent.
*/
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        map<int,int>mp;
        int n=preorder.size();
        for(int i=0;i<n;i++){
            mp[inorder[i]]=i;
        }
        stack<TreeNode*>me;
        TreeNode* root=new TreeNode(preorder[0]);
        TreeNode* curr=root;
        me.push(root);//push 0th element(actual root) of preorder to stack.
        for(int j=1;j<n;j++){
            TreeNode* temp=new TreeNode(preorder[j]);
            if(mp[preorder[j-1]]>mp[preorder[j]]){// case if j appears to left of j-1.
                curr->left=temp; curr=temp; 
            }
            else{ 
                TreeNode* last;
                if(!me.empty()){last=me.top();}
                while(!me.empty() && mp[me.top()->val]<mp[preorder[j]]){
                  //pop those -if j guy appears to their right.
                    last=me.top(); me.pop(); //last keeps track of the just now popped guy
                }
                last->right=temp; curr=temp; //finally join last with temp(j) and curr=temp.
            }
            me.push(curr); //finally push this currently processed guy to stack
        }
        return root;
    }
};
