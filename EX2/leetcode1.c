#include <string.h>
#include <stdlib.h>
char* addBinary(char* a, char* b) {
    int i = strlen(a) - 1;
    int j = strlen(b) - 1;
    char *ans = (char *)malloc(strlen(a) + strlen(b) + 2);
    int k = 0;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0)
            sum += a[i--] - '0';
        if (j >= 0)
            sum += b[j--] - '0';
        ans[k++] = (sum % 2) + '0';
        carry = sum / 2;
    }
    ans[k] = '\0';
    int left = 0, right = k - 1;
    while (left < right) {
        char temp = ans[left];
        ans[left] = ans[right];
        ans[right] = temp;
        left++;
        right--;
    }
    return ans;
}
