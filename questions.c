/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    for(int x = 0; x < 12; x++ ) {
        strcpy(questions[x].category, categories[x % 3]);
    	questions[x].answered = false;
    	strcpy(questions[x].question, "Question");
    	strcpy(questions[x].answer, "Answer");
    }

    // Programming Category Questions
    
    questions[0].value = 200;
    strcpy(questions[0].category, "Programming");
    strcpy(questions[0].question, "What is the most used operating system in the world?");
    strcpy(questions[0].answer, "Windows");

    questions[1].value = 400;
    strcpy(questions[1].category, "Programming");
    strcpy(questions[1].question, "What is the most used programming language in the world?");
    strcpy(questions[1].answer, "JavaScript");

    questions[2].value = 800;
    strcpy(questions[2].category, "Programming");
    strcpy(questions[2].question, "How many types of windows does Python use?");
    strcpy(questions[2].answer, "Two");

    questions[3].value = 1000;
    strcpy(questions[3].category, "Programming");
    strcpy(questions[3].question, "In C programming, what does i equal at the end of the following piece (snippet) of code? \n i = 1; \n i *= 5 \n i += 3; ");
    strcpy(questions[3].answer, "Five");

    // Algorithms Category Questions

    questions[4].value = 200;
    strcpy(questions[4].category, "Algorithms");
    strcpy(questions[4].question, "In a flowchart, an input or output is represented by a?");
    strcpy(questions[4].answer, "Parallelogram");

    questions[5].value = 400;
    strcpy(questions[5].category, "Algorithms");
    strcpy(questions[5].question, "In a flowchart, a calculation process is represented by a?");
    strcpy(questions[5].answer, "Rectangle");

    questions[6].value = 800;
    strcpy(questions[6].category, "Algorithms");
    strcpy(questions[6].question, "True of False? The first thing that happens in a while loop is that it executes the entire code block located inside the while loop at least once?");
    strcpy(questions[6].answer, "True");

    questions[7].value = 1000;
    strcpy(questions[7].category, "Algorithms");
    strcpy(questions[7].question, "How many times will this loop iterate? \n a = 0 \n while a < 5: \n a = a + 1");
    strcpy(questions[7].answer, "Five");

    // Databases Category Questions

    questions[8].value = 200;
    strcpy(questions[8].category, "Databases");
    strcpy(questions[8].question, "What database management system did we use last semester?");
    strcpy(questions[8].answer, "MySQL");

    questions[9].value = 400;
    strcpy(questions[9].category, "Databases");
    strcpy(questions[9].question, "True or False? What database management system did we use last semester?");
    strcpy(questions[9].answer, "MySQL");

    questions[10].value = 800;
    strcpy(questions[10].category, "Databases");
    strcpy(questions[10].question, "_________ is a property that describes various characteristics of an entity");
    strcpy(questions[10].answer, "Attribute");

    questions[11].value = 1000;
    strcpy(questions[11].category, "Databases");
    strcpy(questions[11].question, "What type of field would be used in a database structure for an email address?");
    strcpy(questions[11].answer, "Text");

}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    int place_Count = 0;
    printf("Programming | Algorithms | Databases |\n");
    for(int i = 0; i < 4; i++){
    	for (int j = 0; j < 3; j++) {
	    	int index = i + place_Count;
	    	if(questions[index].answered){
	    		printf("x|");
	    	}else{
	    		printf("%d|", questions[index].value);
	    	}
	    	place_Count += 4;
	    	place_Count %= 12;
    	}
    	printf("\n");
    }	
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    printf("Question: ");
    // lookup the question and see if it's already been marked as answered
    for(int i = 0; i < NUM_QUESTIONS; ++i)
    {
        if(!strcmp(questions[i].category, category) && questions[i].value == value)
        {
        printf("%s\n", questions[i].question);
        }
    }

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    for(int i = 0; i < NUM_QUESTIONS; ++i)
    {
        if(!strcmp(questions[i].category, category) && questions[i].value == value)
        {
            if (!strcmp(questions[i].answer, answer)) {
            printf("Correct! Player awarded with $%d\n", questions[i].value);
                questions[i].answered = true;
            return true;
            } else {
                printf("Incorrect! The correct answer is %s\n", questions[i].answer);
                questions[i].answered = true;
                return false;
            }
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for(int i = 0; i < NUM_QUESTIONS; ++i)
    {
        if(!strcmp(questions[i].category, category) && questions[i].value == value && questions[i].answered)
        {
        return true;
        }
    }
    return false;
}
