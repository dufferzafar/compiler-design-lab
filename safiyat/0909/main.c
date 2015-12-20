#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUG

int main()
{
    FILE *fp;
    int init, *FS, i, j, col, row, fs, r, c;
    char *str, temp[50], ***FA;
    
    fp = FA = FS = str = NULL;
    
    if(!(fp = fopen("input", "r")))
    {
        printf("Error opening file!!!\n");
        return -1;
    }
    
    fscanf(fp, "%d", &init);
    fgets(temp, sizeof(char)*50, fp);
    fgets(temp, sizeof(char)*50, fp);
#ifdef DEBUG
    printf("FS String: %s", temp);
#endif
    str = temp;
    i = 0;
    while(*str != '\0')
    {
        FS = (int *) realloc(FS, sizeof(int)*(i+1));
        sscanf(str, "%d", &FS[i++]);
#ifdef DEBUG
        printf("Here, i = %d, *str = %c\n", i, *str);
#endif
        str++;
        while(isdigit(*str))
        {
#ifdef DEBUG
            printf("He1");
#endif            
            str++;
        }
        while(isspace(*str))
            str++;
    }
    fs = i;
    
    fgets(temp, sizeof(char)*50, fp);
    str = temp;
    i= 0;
#ifdef DEBUG
    printf("0FA scanned: %s\n", temp);
#endif
    FA = (char ***) malloc(sizeof(char **)*1);
    FA[0] = NULL;
    i = 0;
    while(*str != '\0')
    {
    	FA[0] = (char **)realloc(FA[0], sizeof(char *)*(i+1));
        FA[0][i] = (char *)malloc(sizeof(char)*5);
        sscanf(str, "%s", FA[0][i++]);
#ifdef DEBUG
        printf("Here1, i = %d, *str = %c, FA[0][%d] = %s\n", i, *str, i-1, FA[0][i-1]);
#endif
        str++;
        while(isdigit(*str))
            str++;
        while(isspace(*str))
            str++;
    }
    row = 1;
    col = i;
    while(!feof(fp))
    {
    	FA = (char ***) malloc(sizeof(char **)*(row+1));
    	FA[row] = NULL;
        fgets(temp, sizeof(char)*50, fp);
#ifdef DEBUG        
        printf("1FA scanned: %s\n", temp);
#endif        
        str = temp;
        i= 0;
        while(*str != '\0')
        {
        	FA[row] = (char **)malloc(sizeof(char *)*(i+1));
            FA[row][i] = (char *)malloc(sizeof(char)*5);
            sscanf(str, "%s", FA[row][i++]);
#ifdef DEBUG
            printf("Here1, i = %d, *str = %c, FA[%d][%d] = %s\n", i, *str, row,  i-1, FA[row][i-1]);
#endif
            str++;
            while(isdigit(*str))
                str++;
            while(isspace(*str))
                str++;
        }
        row++;
    }
    
    
    
    printf("Initial State: %d\n", init);
    printf("Final states: ");
    for(i = 0; i < fs; i++)
        printf("%d ", FS[i]);
    printf("\nInput Table:\n");
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%s	\t", FA[i][j]);
        }
        printf("\n");
    }
    /*
    while(1)
    {
    	printf("Enter the string to be validated using the Finite Automata (\"!end\" to quit): ");
    	scanf("%s", temp);
    	if(strcmp(temp, "!end") == 0)
    		break;
    	str = temp;
    	r = 0;
    	while(*str != '\0')
    	{
    		c = tolower(*str) - 97;		//Column of FA to be matched for the current input symbol
    		if((c >= col) || (c < 0))
    		{
    			printf("Error! Invalid input symbol!\n");
    			c = -1;
    			break;
    		}
    		if(FA[r][c] != -1)
    		{
    			r = FA[r][c];
    			str++;
    		}
    		else
    		{
    			printf("Error! Input symbol unexpected!\n");
    			c = -1;
    			break;
    		}
    	}
    	if(c == -1)
    		continue;
    	for(i = 0; i < fs; i++)
    		if(r == FS[i])
    		{
    			printf("String validated.\n");
    			break;
    		}
    	if(i == fs)
    		printf("String ending at a non-final state.\n");
    };
    */
    return 0;
}