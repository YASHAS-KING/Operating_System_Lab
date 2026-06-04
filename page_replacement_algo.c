#include <stdio.h>
void fifo(int pages[], int n, int frames_count) {
    int frames[frames_count];
    int fault = 0, index = 0;
    for(int i = 0; i < frames_count; i++) frames[i] = -1; 
    for(int i = 0; i < n; i++) {
        int found = 0;
        for(int j = 0; j < frames_count; j++) {
            if(frames[j] == pages[i]) {
                found = 1; 
                break;
            }
        }
        if(!found) {
            frames[index] = pages[i];
            index = (index + 1) % frames_count; 
            fault++;
        }
    }
    printf("FIFO Total Page Faults: %d\n", fault);
}
void lru(int pages[], int n, int frames_count) {
    int frames[frames_count], time[frames_count];
    int fault = 0, counter = 0;
    for(int i = 0; i < frames_count; i++) frames[i] = -1;
    for(int i = 0; i < n; i++) {
        int found = 0, min_time = counter, lru_index = 0;
        for(int j = 0; j < frames_count; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                time[j] = ++counter; 
                break;
            }
        }
        if(!found) {
            for(int j = 0; j < frames_count; j++) {
                if(frames[j] == -1) { 
                    lru_index = j;
                    break; 
                }
                if(time[j] < min_time) { 
                    min_time = time[j]; 
                    lru_index = j; 
                }
            }
            frames[lru_index] = pages[i];
            time[lru_index] = ++counter;
            fault++;
        }
    }
    printf("LRU Total Page Faults: %d\n", fault);
}
void optimal(int pages[], int n, int frames_count) {
    int frames[frames_count];
    int fault = 0;
    for(int i = 0; i < frames_count; i++) frames[i] = -1;
    for(int i = 0; i < n; i++) {
        int found = 0;
        for(int j = 0; j < frames_count; j++) {
            if(frames[j] == pages[i]) { found = 1; break; }
        }
        if(!found) {
            int replace_index = -1, farthest = i;
            
            for(int j = 0; j < frames_count; j++) {
                if(frames[j] == -1) { replace_index = j; break; } 
                int next_use = -1;
                for(int k = i + 1; k < n; k++) {
                    if(frames[j] == pages[k]) { next_use = k; break; }
                }
                if(next_use == -1) { replace_index = j; break; } 
                if(next_use > farthest) { 
                    farthest = next_use; 
                    replace_index = j; 
                }
            }
            frames[replace_index] = pages[i];
            fault++;
        }
    }
    printf("Optimal Total Page Faults: %d\n", fault);
}
int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames_count = 4; 
    fifo(pages, n, frames_count);
    lru(pages, n, frames_count);
    optimal(pages, n, frames_count);
    return 0;
}