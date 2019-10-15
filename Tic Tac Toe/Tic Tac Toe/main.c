//
//  main.c
//  Tic Tac Toe
//
//  Created by Tommy Cao on 9/2/19.
//  Copyright © 2019 Tommy Cao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void instructions(){
    printf("To play Tic Tac Toe Agaisnt a bot, please type '0'. Else Type '1' play against a player \n");
    
    printf("To choose where to place X or O, please type a number corresponding to the placement on the map \n");
    printf(" 1 | 2 | 3 \n");
    printf("-----------\n");
    printf(" 4 | 5 | 6 \n");
    printf("-----------\n");
    printf(" 7 | 8 | 9 \n");
    return;
}
void reset_board(int board[9]){
    for(int i = 0; i < 9; i++){
        board[i]= 0;
    }
    return;
}
char readBoard(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
    return 'a';
}
void display_board(int board[9]){
    for(int i = 0; i<3;i++){
        printf(" %c | %c | %c \n",readBoard(board[i*3]),readBoard(board[3*i+1]),readBoard(board[3*i+2]));
        if(i<2){
            printf("-----------\n");
        }
    }
    return;
}

int win_check(int board[9]){
    //row check
    for (int i = 0 ; i < 3 ; i++){
        if ((board[3*i] == 1 | board[3*i] == 2) &&
            board[3*i] == board [1+3*i] && board[3*i] == board[2+3*i]){
            if(board[i] ==1){
                return 1;
            }else
                return 2;
        }
    }
    //col check
    for (int i = 0 ; i < 3 ; i++){
        if ((board[i] == 1 | board[i] == 2) && board[i] == board[3+i] && board[i] == board[6+i]){
            if(board[i] ==1){
                return 1;
            }else
                return 2;
        }
    }
    //     diagonal check
    if (((board[0] == board[4] && board[0] == board[8])|
         (board[2]== board[4] && board[2] == board[6])) &&
        (board[2] == 1 | board[2] == -1)){
        if(board[0] ==1){
            return 1;
        }else
            return 2;
    }
    return 0;
    
}
void playerMove(int board[9],int player) {
    int move = 0;
    int invalid = 0;
    do {
        display_board(board);
        if (invalid == 1){
            printf("Invalid move, please try again\n");
        }
        printf("It is player %d's turn. Please choose a location\n",player);
        scanf("%d", &move);
        printf("\n");
        if((board[move-1] == 1 || board[move-1] == 2) && (move<10 & move >0)){
            invalid = 1;
        }else{
            invalid = 0;
        }
    } while (invalid == 1);
    if (player == 1){
        board[move-1] = 1;
    }if (player == 2){
        board[move-1] = 2;
    }
    return;
}

void player_battle(int board[9]){
    int game_over = 0;
    int moves = 0;
    printf("You will now play agaisnt a player.\n");
    while (game_over == 0 && moves != 9){
        playerMove(board, 1);
        moves++;
        game_over = win_check(board);
        if(game_over != 1 && moves != 9){
            playerMove(board, 2);
            moves++;
            game_over = win_check(board);
        }
    }
  
    if (game_over == 1 || game_over == 2){
        display_board(board);
        printf("Player %d Won!\n",game_over);
    }
    if(game_over != 1){
        display_board(board);
        printf("That was a Tie. Would you like to play again?\n");
        game_over = 2;
    }
    return;
}
int getSize(int board[9]){
    int size = 0;
    for(int i = 0; i<9; i++){
        if (board[i] == 0){
            size++;
        }
    }
    return size;
}
int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}
int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;
    
    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
}
void player_Move(int board[9]) {
    int move = 0;
    do {
    start:
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        if(board[move-1] != 0) {
            printf("Its Already Occupied !");
            goto start;
        }
        printf("\n");
    } while (move > 9 || move < 0 && board[move-1] == 0);
    board[move-1] = -1;
}
void bot_battle(int board[9]){
    printf("Computer: O, You: X\nPlay (1)st or (2)nd? ");
    int player=0;
    scanf("%d",&player);
    printf("\n");
    for(int turn = 0; turn < 9 && win_check(board) == 0; ++turn) {
        if((turn+player) % 2 == 0)
            computerMove(board);
        else {
            display_board(board);
            player_Move(board);
        }
    }
    display_board(board);
}
int main(int argc, const char * argv[]) {
    // insert code here...
    int board[9];
    int mode;
    int play = 1;
    while (play == 1){
        instructions();
        reset_board(board);
        scanf("%d",&mode);
        while (!(mode == 1 || mode == 0)){
            printf("try again\n");
            scanf("%d",&mode);
        }
        if (mode == 0){
            printf("You are now playing a bot.\n");
            bot_battle(board);
        }
        else{
            printf("You are now playing a player.\n");
            player_battle(board);
        }
        printf("Would you like to play again? Type 1 for yes and 0 for no\n");
        scanf("%d",&play);
    }
    
    return 0;
}

