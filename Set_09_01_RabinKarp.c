#include <stdio.h>
#include <string.h>

#define d 256          // Number of characters in input alphabet
#define q 101          // A prime number for modulo

void rabinKarp(char pattern[], char text[]) {
    int m = strlen(pattern);
    int n = strlen(text);

    int p = 0;   // Hash value for pattern
    int t = 0;   // Hash value for text window
    int h = 1;

    // The value of h = pow(d, m-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate hash values for pattern and first window of text
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text
    for (int i = 0; i <= n - m; i++) {

        // If hash values match, check characters
        if (p == t) {
            int j = 0;
            while (j < m && text[i + j] == pattern[j])
                j++;

            if (j == m)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // Convert negative values to positive
            if (t < 0)
                t += q;
        }
    }
}

int main() {
    char text[200], pattern[50];

    printf("Enter text: ");
    gets(text);

    printf("Enter pattern: ");
    gets(pattern);

    rabinKarp(pattern, text);

    return 0;
}
