#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max_demand[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

int num_processes, num_resources;

bool is_safe() {
    int work[num_resources];
    bool finish[num_processes];
    
    // Initialize work and finish arrays
    for (int i = 0; i < num_resources; ++i)
        work[i] = available[i];
    for (int i = 0; i < num_processes; ++i)
        finish[i] = false;

    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; ++i) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_resources; ++j) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == num_resources) {
                    for (int k = 0; k < num_resources; ++k)
                        work[k] += allocation[i][k];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            return false; // No process found, it's unsafe
    }
    return true; // Safe sequence found
}

void print_safe_sequence(int safe_sequence[]) {
    printf("Safe sequence: ");
    for (int i = 0; i < num_processes; ++i)
        printf("%d ", safe_sequence[i]);
    printf("\n");
}

void input_data() {
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter available resources:\n");
    for (int i = 0; i < num_resources; ++i)
        scanf("%d", &available[i]);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j)
            scanf("%d", &allocation[i][j]);

    printf("Enter maximum demand matrix:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j) {
            scanf("%d", &max_demand[i][j]);
            need[i][j] = max_demand[i][j] - allocation[i][j];
        }
}

int main() {
    input_data();

    if (is_safe()) {
        printf("The system is safe.\n");
    } else {
        printf("The system is unsafe.\n");
        return 0;
    }

    int safe_sequence[MAX_PROCESSES];
    int seq_count = 0;
    while (seq_count < num_processes) {
        for (int i = 0; i < num_processes; ++i) {
            if (!finished[i]) {
                bool can_run = true;
                for (int j = 0; j < num_resources; ++j) {
                    if (need[i][j] > available[j]) {
                        can_run = false;
                        break;
                    }
                }
                if (can_run) {
                    for (int j = 0; j < num_resources; ++j)
                        available[j] += allocation[i][j];
                    finished[i] = true;
                    safe_sequence[seq_count++] = i;
                }
            }
        }
    }

    print_safe_sequence(safe_sequence);

    return 0;
}
