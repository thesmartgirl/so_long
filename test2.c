#include <stdio.h>

// Function to perform DFS
void dfs(int img[3][3], int x, int y, int prevClr, int newClr) {
    if (img[x][y] != prevClr)
        return;

    // Marking it as the new color
    img[x][y] = newClr;

    // Moving up, right, down and left one by one.
    if (x - 1 >= 0)
        dfs(img, x - 1, y, prevClr, newClr);
    if (y + 1 < 3)
        dfs(img, x, y + 1, prevClr, newClr);
    if (x + 1 < 3)
        dfs(img, x + 1, y, prevClr, newClr);
    if (y - 1 >= 0)
        dfs(img, x, y - 1, prevClr, newClr);
}

// FloodFill Function
void floodFill(int img[3][3], int x, int y, int newClr) {
    int prevClr = img[x][y];
    if (prevClr == newClr)
        return;
    dfs(img, x, y, prevClr, newClr);
}

// Driver code
int main() {
    int img[3][3] = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    // Co-ordinate provided by the user
    int x = 1, y = 1;
    // New color that has to be filled
    int newClr = 3;
    floodFill(img, x, y, newClr);

    // Printing the updated img
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", img[i][j]);
        }
        printf("\n");
    }
    return 0;
}