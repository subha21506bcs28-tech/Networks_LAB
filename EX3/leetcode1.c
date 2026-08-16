int hammingDistance(int x, int y) {
    int count = 0;
    x = x ^ y;
    while (x != 0) {
        count += x % 2;
        x = x / 2;
    }

    return count;
}
