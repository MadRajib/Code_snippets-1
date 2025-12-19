# String Problems

1. [KMP ALGO](#kmp-algo)

### KMP Algo
```cpp
void generate_lps(vector<int> &pattern, vector<int> &lps) {
    int prev_lps = 0;
    int i = 1;

    while (i < pattern.size()) {
        if (pattern[i] == lps[prev_lps]) {
            lps[i] = prev_lps + 1;
            prev_lps++;
            i++;
        } else {
            if (prev_lps == 0) {
                lps[i] = 0;
                i++;
            } else {
                prev_lps = lps[prev_lps - 1];
            }
        }
    }
}

void kmp(vector<int> &haystack, vector<int> &pattern) {

    int i = 0;  // ptr for hatystack
    int j = 0;  // ptr for needle

    vector<int> lps(pattern.size(), 0);
    generate_lps(pattern, lps);

    while (i < len(haystack)) {
        if (haystack[i] == pattern[i]) {
            i++;
            j++;
        } else {
            if (j == 0)
                i++;
            else
                j = lps[j - 1];
        }

        if (j == pattern.size())
            return i - patter.size();
    }

    return -1;
}
```