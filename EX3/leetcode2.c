int totalHammingDistance(int* nums, int numsSize) {
    int total = 0;

    for (int bit = 0; bit < 31; bit++) {
        int count = 0;

        for (int i = 0; i < numsSize; i++) {
            if ((nums[i] >> bit) & 1)
                count++;
        }

        total += count * (numsSize - count);
    }

    return total;
}
