/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS: Rayyan Mohammed, Muhammed Khalid, Daniyal Khan>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"


// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here
// Processes user input answer which must include what is or who is and retrieves the answer.
void tokenize(char *input, char **tokens){
    char *str; // Holds player answer
    if((str = strtok(input, "")) != NULL)
        if(strcmp(str, "who") != 0 && strcmp(str, "what") != 0)
            return;
    if((str = strtok(NULL, "")) != NULL)
        if(strcmp(str, "is") != 0)
            return;
    *tokens = strtok(NULL, "\n");
}

// Displays the results for each play and final score, ranked from first to last place
void show_results(player *players, int num_players){
    char name; // Player names
    int gameWinner = 0;  // Game winner variable
    int score;  // Keeps track of user score

    for(int x = 0; x < num_players; x++) {
        if((int) strlen(players[x].name) > name){
            name = strlen(players[x].name);
        }

        if(players[x].score > score) {
            score = players[x].score;
            gameWinner = x;
        }
    }

    printf("The scores are: \n"); // Prints all user scores
    for(int x = 0; x < num_players; x++)
        printf("%*s: %d\n", name + 1, players[x].name, players[x].score);

    printf("The winner is: %s", players[gameWinner].name); // Prints game winner
}


int main(void)
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();
    printf("WELCOME TO THE GAME OF JEOPARDY \n");
    
    // initialize each of the players in the array and prompts for player names
    for(int x = 0; x < 4; x++) {
        players[x].score = 0;
        printf("Please enter your player name: ");
        scanf("%s", (char *) &players[x].name);
    }
    int placeCounter = 0;
    
    // An infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        char player_name[MAX_LEN], game_category[MAX_LEN], correct_Answer[MAX_LEN];
        int score_value;
        
        // Call functions from the questions and players source files
        printf("Please enter which players turn it is: ");
        scanf("%s", player_name);

        while (!player_exists(players, NUM_PLAYERS, player_name)) {
        printf("You have entered an INVALID name!! Please try again: ");
        scanf("%s", player_name);
        }

        // Execute the game until all questions are answered
        display_categories();
        printf("\nPlease select a category and a value");
        scanf("%s %d", game_category, &score_value);
        while(already_answered(game_category, score_value)) {
        printf("Thw question you selected has been answered. Please select another question: ");
        scanf("%s %d", game_category, &score_value);
        }
        display_question(game_category, score_value);
        
        
        printf("Enter your answer: ");
        fgets (correct_Answer, MAX_LEN, stdin);
        scanf("%[^\n]%*c", correct_Answer);
        if(valid_answer(game_category, score_value, correct_Answer)){
        update_score(players, NUM_PLAYERS, player_name, score_value);
        }
        placeCounter++;
        if (placeCounter == 12) { // stop the game after its done
        show_results(players, NUM_PLAYERS);
        break; 
        }
        printf("If you want to continue, click enter\n");

        // Display the final results and exit
    }
    return EXIT_SUCCESS;
}


