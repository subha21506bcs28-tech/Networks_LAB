bool hasAlternatingBits(int n) {
    int binary[32];
    int i = 0;
    while (n > 0) {
        binary[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = 0; j < i - 1; j++) {
        if (binary[j] == binary[j + 1]) {
            return false;
        }
    }
    return true;
}
