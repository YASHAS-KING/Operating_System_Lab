#include <stdio.h>

void firstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[10];
    int i, j;

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        for(j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFIRST FIT Allocation:\n");
    printf("Process No\tProcess Size\tBlock No\n");

    for(i = 0; i < processes; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[10];
    int i, j, bestIdx;

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        bestIdx = -1;

        for(j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if(bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBEST FIT Allocation:\n");
    printf("Process No\tProcess Size\tBlock No\n");

    for(i = 0; i < processes; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[10];
    int i, j, worstIdx;

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        worstIdx = -1;

        for(j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if(worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWORST FIT Allocation:\n");
    printf("Process No\tProcess Size\tBlock No\n");

    for(i = 0; i < processes; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int blocks, processes, i;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);

    int blockSize1[10], blockSize2[10], blockSize3[10];

    printf("Enter sizes of memory blocks:\n");
    for(i = 0; i < blocks; i++)
    {
        scanf("%d", &blockSize1[i]);
        blockSize2[i] = blockSize1[i];
        blockSize3[i] = blockSize1[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);

    int processSize[10];

    printf("Enter sizes of processes:\n");
    for(i = 0; i < processes; i++)
    {
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize1, blocks, processSize, processes);
    bestFit(blockSize2, blocks, processSize, processes);
    worstFit(blockSize3, blocks, processSize, processes);

    return 0;
}
