int findMaximumXOR(int* nums, int numsSize){
    static int trie[6500000][2];
    int nodeCount = 1;
    trie[0][0] = 0;
    trie[0][1] = 0;
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int currNode = 0;
        for (int bit = 30; bit >= 0; bit--) {
            int bitVal = (num >> bit) & 1;
            if (!trie[currNode][bitVal]) {
                trie[nodeCount][0] = 0;
                trie[nodeCount][1] = 0;
                trie[currNode][bitVal] = nodeCount++;
            }
            currNode = trie[currNode][bitVal];
        }
    }
    int maxXor = 0;
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int currNode = 0;
        int currentXor = 0;
        for (int bit = 30; bit >= 0; bit--) {
            int bitVal = (num >> bit) & 1;
            int toggledBit = 1 - bitVal; 
            if (trie[currNode][toggledBit]) {
                currentXor |= (1 << bit);
                currNode = trie[currNode][toggledBit];
            } else {
                currNode = trie[currNode][bitVal];
            }
        }
        if (currentXor > maxXor) {
            maxXor = currentXor;
        }
    }
    return maxXor;
}

    
