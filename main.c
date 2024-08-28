#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIDES 4
#define MAX_ROWS 100
#define MAX_COLS 100

// Edge enum
typedef enum {
    INDENTATION,
    EXTRUSION,
    FLAT
} Edge;

// Side structure
typedef struct {
    Edge edge;
} Side;

// Piece structure
typedef struct {
    Side sides[MAX_SIDES];
} Piece;

// Puzzle structure (Singleton)
typedef struct {
    Piece* board[MAX_ROWS][MAX_COLS];
    Piece* free;
    int free_count;
    int rows;
    int cols;
} Puzzle;

// Global puzzle instance
Puzzle* puzzle = NULL;

// Function prototypes
bool check_corner(Piece* piece);
bool check_edge(Piece* piece);
bool check_middle(Piece* piece);
void insert_piece(Puzzle* puzzle, Piece* piece, int row, int column);
Puzzle* get_puzzle_instance(int rows, int cols);
bool match_pieces(Puzzle* puzzle);

// Implementation of check functions
bool check_corner(Piece* piece) {
    int flat_count = 0;
    for (int i = 0; i < MAX_SIDES; i++) {
        if (piece->sides[i].edge == FLAT) {
            flat_count++;
        }
    }
    return flat_count == 2;
}

bool check_edge(Piece* piece) {
    int flat_count = 0;
    for (int i = 0; i < MAX_SIDES; i++) {
        if (piece->sides[i].edge == FLAT) {
            flat_count++;
        }
    }
    return flat_count == 1;
}

bool check_middle(Piece* piece) {
    for (int i = 0; i < MAX_SIDES; i++) {
        if (piece->sides[i].edge == FLAT) {
            return false;
        }
    }
    return true;
}

// Implementation of insert_piece function
void insert_piece(Puzzle* puzzle, Piece* piece, int row, int column) {
    if (row < 0 || row >= puzzle->rows || column < 0 || column >= puzzle->cols) {
        printf("Invalid position\n");
        return;
    }

    if (puzzle->board[row][column] != NULL) {
        printf("Position already occupied\n");
        return;
    }

    puzzle->board[row][column] = piece;

    // Remove the piece from free pieces
    for (int i = 0; i < puzzle->free_count; i++) {
        if (&puzzle->free[i] == piece) {
            for (int j = i; j < puzzle->free_count - 1; j++) {
                puzzle->free[j] = puzzle->free[j + 1];
            }
            puzzle->free_count--;
            break;
        }
    }
}

// Implementation of get_puzzle_instance function (Singleton pattern)
Puzzle* get_puzzle_instance(int rows, int cols) {
    if (puzzle == NULL) {
        puzzle = (Puzzle*)malloc(sizeof(Puzzle));
        puzzle->rows = rows;
        puzzle->cols = cols;
        puzzle->free_count = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                puzzle->board[i][j] = NULL;
            }
        }
    }
    return puzzle;
}

// Implementation of match_pieces function (PuzzleSolver functionality)
bool match_pieces(Puzzle* puzzle) {
    // This is a simplified implementation. A real solver would be more complex.
    for (int i = 0; i < puzzle->rows; i++) {
        for (int j = 0; j < puzzle->cols; j++) {
            if (puzzle->board[i][j] == NULL) {
                for (int k = 0; k < puzzle->free_count; k++) {
                    Piece* piece = &puzzle->free[k];
                    bool fits = true;

                    // Check top
                    if (i > 0 && puzzle->board[i-1][j] != NULL) {
                        if (piece->sides[0].edge == puzzle->board[i-1][j]->sides[2].edge) {
                            fits = false;
                        }
                    }

                    // Check left
                    if (j > 0 && puzzle->board[i][j-1] != NULL) {
                        if (piece->sides[3].edge == puzzle->board[i][j-1]->sides[1].edge) {
                            fits = false;
                        }
                    }

                    if (fits) {
                        insert_piece(puzzle, piece, i, j);
                        if (match_pieces(puzzle)) {
                            return true;
                        }
                        // If it doesn't lead to a solution, remove the piece and try the next one
                        puzzle->board[i][j] = NULL;
                        puzzle->free[puzzle->free_count++] = *piece;
                    }
                }
                // If we've tried all pieces and none fit, backtrack
                return false;
            }
        }
    }
    // If we've filled all positions, we've solved the puzzle
    return true;
}

// Main function for testing
int main() {
    Puzzle* puzzle = get_puzzle_instance(3, 3);


    // Create some pieces for testing
    Piece pieces[] = {
        {{{FLAT}, {EXTRUSION}, {INDENTATION}, {FLAT}}},
        {{{INDENTATION}, {EXTRUSION}, {INDENTATION}, {EXTRUSION}}},
        {{{EXTRUSION}, {FLAT}, {INDENTATION}, {EXTRUSION}}},
        {{{INDENTATION}, {FLAT}, {EXTRUSION}, {INDENTATION}}},
        {{{EXTRUSION}, {INDENTATION}, {FLAT}, {EXTRUSION}}},
        {{{INDENTATION}, {EXTRUSION}, {FLAT}, {INDENTATION}}},
        {{{FLAT}, {INDENTATION}, {EXTRUSION}, {FLAT}}},
        {{{FLAT}, {EXTRUSION}, {INDENTATION}, {FLAT}}},
        {{{EXTRUSION}, {INDENTATION}, {EXTRUSION}, {INDENTATION}}}
    };

    puzzle->free = pieces;
    puzzle->free_count = 9;

    printf("Attempting to solve the puzzle...\n");
    if (match_pieces(puzzle)) {
        printf("Puzzle solved successfully!\n");
        printf("Final puzzle board:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (puzzle->board[i][j] != NULL) {
                    printf("P ");
                } else {
                    printf(". ");
                }
            }
            printf("\n");
        }
    } else {
        printf("Unable to solve the puzzle.\n");
    }

    free(puzzle);
    return 0;
}