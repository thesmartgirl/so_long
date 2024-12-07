#include <stdio.h>

// Function to perform DFS
void dfs( char img[7][16], int x, int y, int prevClr, int newClr, int *exits, int *coins) {

    // printf("starting pos %d %d\n", x, y);
    // printf("starting value %c\n", img[x][y]);
    if (img[x][y] == 'F' || x == 6 || y == 15 || x == 0 || y == 0 || img[x][y] == '1')
        return;

    if(img[x][y] == 'E')
    {
        printf("found e\n");
        *(exits) +=1;
    }
    if(img[x][y] == 'C')
        *(coins) += 1;
    // Marking it as the new color
    img[x][y] = newClr;

    // Moving up, right, down and left one by one.
        dfs(img, x - 1, y, prevClr, newClr, exits, coins);
        dfs(img, x, y + 1, prevClr, newClr, exits, coins);
        dfs(img, x + 1, y, prevClr, newClr, exits, coins);
        dfs(img, x, y - 1, prevClr, newClr, exits, coins);
}

// FloodFill Function
void floodFill( char img[7][16], int x, int y, int newClr) {
    int prevClr = img[x][y];
    int exits=0;
    int coins=0;
    printf("prevClr %c \n", prevClr);
    if (prevClr == newClr)
        return;
    dfs(img, x, y, prevClr, newClr, &exits, &coins);
    printf("exits %d, coins %d\n", exits, coins);
}

// Driver code
int main() {
    // int img[3][3] = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    char img[7][16] = {"1111111111111111", "1010010000100001", "1000C010C0010101", "1C0000E000010101", "10001000P0000101", "1000001000010101", "1111111111111111"};

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%c ", img[i][j]);
        }
        printf("\n");
    }
     printf("\n");
      printf("\n");
       printf("\n");
    // Co-ordinate provided by the user
    int x = 4, y = 8;
    // New color that has to be filled
    char newClr = 'F';
    floodFill(img, x, y, newClr);

    // Printing the updated img
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%c ", img[i][j]);
        }
        printf("\n");
    }
    return 0;
}