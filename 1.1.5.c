#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SUBSETS 10000
#define MAX_ELEMENTS 100

// Structure to store a discovered subset
typedef struct {
    int data[MAX_ELEMENTS];
    int size;
} Subset;

Subset discovered_subsets[MAX_SUBSETS];
int subset_count = 0;

int arr[MAX_ELEMENTS];
int current_subset[MAX_ELEMENTS];
int n, target;

// Backtracking function to find all subsets
void findSubsets(int idx, int current_sum, int subset_size) {
    // If we have traversed all elements
    if (idx == n) {
        if (current_sum == target) {
            // Store the discovered subset
            for (int i = 0; i < subset_size; i++) {
                discovered_subsets[subset_count].data[i] = current_subset[i];
            }
            discovered_subsets[subset_count].size = subset_size;
            subset_count++;
        }
        return;
    }

    // Choice 1: Include the current element
    current_subset[subset_size] = arr[idx];
    findSubsets(idx + 1, current_sum + arr[idx], subset_size + 1);

    // Choice 2: Exclude the current element
    findSubsets(idx + 1, current_sum, subset_size);
}

int main() {
    // Read the number of elements
    if (scanf("%d", &n) != 1) return 0;

    // Read the elements of the set
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) return 0;
    }

    // Read the target sum
    if (scanf("%d", &target) != 1) return 0;

    // Start backtracking from index 0
    findSubsets(0, 0, 0);

    // If no subset matches the target sum
    if (subset_count == 0) {
        printf("-1\n");
    } else {
        // Print in reverse order of discovery
        for (int i = subset_count - 1; i >= 0; i--) {
            for (int j = 0; j < discovered_subsets[i].size; j++) {
                printf("%d ", discovered_subsets[i].data[j]);
            }
            printf("\n");
        }
    }

    return 0;
}
