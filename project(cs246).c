
#include <stdio.h>
#include <string.h>


void difficultyLabel(int diff) {
    if(diff <= 3)
        printf(" (Easy)");
    else if(diff <= 6)
        printf(" (Medium)");
    else
        printf(" (Hard)");
}


int LIS(char topics[][50], int diff[], int n)
{
    int length[n], prev[n];

    for (int i = 0; i < n; i++)
    {
        length[i] = 1;
        prev[i] = -1;
    }


    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (diff[j] < diff[i] && length[j] + 1 > length[i])
            {
                length[i] = length[j] + 1;
                prev[i] = j;
            }
        }
    }


    int max_len = 0;
    for (int i = 0; i < n; i++)
        if (length[i] > max_len)
            max_len = length[i];



   int maximum_length = 99999;
    int max_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (length[i] == max_len)
        {
            int idx = i;
            while (prev[idx] != -1)
                idx = prev[idx];

            if (diff[idx] < maximum_length)
            {
                maximum_length= diff[idx];
                 max_index= i;
            }
        }
    }


    char result[max_len][50];
    int k = 0, index = max_index;

    while (index != -1)
    {
        strcpy(result[k++], topics[index]);
        index = prev[index];
    }


    printf("\nOptimal Study Order (Increasing Difficulty):\n");
    for (int i = max_len - 1; i >= 0; i--)
    {

        int idx;
        for(idx=0; idx<n; idx++)
            if(strcmp(result[i], topics[idx])==0) break;

        printf("%s", result[i]);
        difficultyLabel(diff[idx]);
        printf("\n");
    }

    return max_len;
}

int main()
{
    int n;

    printf("Personalized Study Planner \n");

    printf("Enter number of topics: ");
    scanf("%d", &n);

    char topics[n][50];
    int difficulty[n];

    printf("\nEnter topic name and difficulty:\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nTopic %d name: ", i + 1);
        scanf("%s", topics[i]);

        printf("Difficulty of %s: ", topics[i]);
        scanf("%d", &difficulty[i]);
    }
       printf("\nYou entered:\n");
    for (int i = 0; i < n; i++)
        printf("%s (Difficulty %d)\n", topics[i], difficulty[i]);

    int len = LIS(topics, difficulty, n);

    printf("\nLength of optimal study sequence: %d\n", len);
   return 0;
}
