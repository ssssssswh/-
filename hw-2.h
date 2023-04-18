    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        //用来存储左右边界位置
        vector<int> left(n), right(n);
        stack<int> stack1;
        for(int i=0;i<n;i++){
           // 如果栈顶的位置柱子高度大于该柱子，就出栈直到小于，这个时候栈顶的小于该柱子的柱子高度就是最左的边界
            while(!stack1.empty() && heights[stack1.top()]>=heights[i]){
                stack1.pop();
            }
            left[i] = (stack1.empty() ? -1 : stack1.top());
            stack1.push(i);
        }

        stack1=stack<int>();
        for(int i=n-1;i>=0;i--){
            while(!stack1.empty() && heights[stack1.top()]>=heights[i]){
                stack1.pop();
            }
            right[i] = (stack1.empty() ? n : stack1.top());
            stack1.push(i);
        }

        //遍历left和right，分别得到每个柱子的左右边界，然后计算最大面积
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
