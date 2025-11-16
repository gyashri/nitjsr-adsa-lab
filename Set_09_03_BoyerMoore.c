#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

// Function to create the bad character table
void badCharTable(char pattern[], int m, int badchar[]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;   // initialize all as -1

    for (int i = 0; i < m; i++)
        badchar[(unsigned char)pattern[i]] = i;
}

// Boyer-Moore search using Bad Character Heuristic
void boyerMoore(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int badchar[NO_OF_CHARS];

    // Fill the bad character table
    badCharTable(pattern, m, badchar);

    int shift = 0;  // shift of the pattern with respect to text

    while (shift <= (n - m)) {
        int j = m - 1;

        // Move from rightmost character of pattern
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        // If pattern found
        if (j < 0) {
            printf("Pattern found at index %d\n", shift);

            // Shift pattern based on next character in text
            shift += (shift + m < n) ? m - badchar[(unsigned char)text[shift + m]] : 1;
        }
        else {
            // Bad character mismatch rule
            int bcShift = j - badchar[(unsigned char)text[shift + j]];
            if (bcShift < 1) bcShift = 1;

            shift += bcShift;
        }
    }
}

int main() {
    char text[200], pattern[50];

    printf("Enter text: ");
    gets(text);

    printf("Enter pattern: ");
    gets(pattern);

    boyerMoore(text, pattern);

    return 0;
}
