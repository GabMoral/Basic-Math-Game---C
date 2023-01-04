#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Checks for valid operator input
void opMatch(int opNum, char* op) {
	switch (opNum) {
	case 0:
		*op = '+';
		break;
	case 1:
		*op = '-';
		break;
	case 2:
		*op = '*';
		break;
	case 3:
		*op = '/';
		break;
	case 4:
		*op = '%';
		break;
	}
}
//Generates 2 random numbers
void generateNums(char* op, int* num1, int* num2, int* result) {
	int upper;
	int lower;
	switch (*op) {
		//+: 2 random ints between 0 and 99
	case '+':
		*num1 = rand() % 99;
		*num2 = rand() % 99;
		*result = *num1 + *num2;
		break;
		//-: 2 random ints between 0 and 99
	case '-':
		*num1 = rand() % 99;
		*num2 = rand() % 99;
		*result = *num1 - *num2;
		break;
		//*: 2 random ints between 0 and 99
	case '*':
		*num1 = rand() % 99;
		*num2 = rand() % 9;
		*result = *num1 * *num2;
		break;
		///: random numerator and random denominator less than the numerator that results in a whole number(no decimals)
	case '/':
		*num1 = rand() % 99;
		if (*num1 == 0) {
			*num2 = (rand() % 99) + 1;
		}
		else {
			upper = *num1;
			lower = 1;
			int temp = (rand() % (upper - lower + 1)) + lower;	//Random int within a range.
			while ((*num1 % temp) != 0) {
				temp--;
			}
			*num2 = temp;
		}
		*result = *num1 / *num2;
		break;
		//%: 2 random ints between 0 and 99
	case '%':
		*num1 = rand() % 99;
		*num2 = rand() % 99;
		*result = *num1 % *num2;
		break;
	}
}
//Displays score
void display(int* longestStreak, int* streak,  int* score, int* highscore, char* op, int* num1, int* num2) {
	printf("Highscore: %d\n", *highscore);
	printf("Current Score: %d\n", *score);
	printf("Longest Streak: %d\n", *longestStreak);
	printf("Current Streak: %d\n", *streak);
	printf("\t %3d\n", *num1);
	printf("\t%c%3d\n", *op, *num2);
	printf("\t====\n");
	printf("\t   ?\n");
}
//Gets input from user
void getInput(int* input) {
	int numCheck;
	do {
		printf("Enter number: ");
		numCheck = scanf("%d", input);
		if (numCheck != 1)
			printf("Invalid entry!!!\n");
		scanf("%*[^\n]");	//read past invalid input
	} while (numCheck != 1);
}
//Checks answer and updates score
void answerCheck(int* streak, char* op, int* score, int result, int input) {
	if (result == input) {
		switch (*op) {
		case '+':
			*score += 10;
			break;
		case '-':
			*score += 10;
			break;
		case '*':
			*score += 20;
			break;
		case '/':
			*score += 20;
			break;
		case '%':
			*score += 15;
			break;
		}
		printf("Correct!\n");
		*streak+=1;
	}
	else {
		*streak = 0;
		printf("Incorrect!\n");
	}
}
//Checks and updates highscore and longest streak
void updateScore(int* currentStreak, int* longestStreak, int* currentScore, int* highscore, FILE** fscore, FILE** fstreak) {
	if (*highscore < *currentScore) {
		*highscore = *currentScore;
		if ((*fscore = fopen("highscore.txt", "w")) == NULL) {
			printf("Error\n");
			return;
		}
		else {
			//printf("No error\n");
		}
		fprintf(*fscore, "%d", *highscore);
		fclose(*fscore);
	}
	if (*longestStreak < *currentStreak) {
		*longestStreak = *currentStreak;
		if ((*fstreak = fopen("longestStreak.txt", "w")) == NULL) {
			printf("Error\n");
			return;
		}
		else {
			//printf("No error\n");
		}
		fprintf(*fstreak, "%d", *longestStreak);
		fclose(*fstreak);
	}
}

int main() {
	int num1, num2, result, input, opNum, highscore, currentScore = 0, currentStreak = 0, longestStreak;
	char op;

	FILE* fhighscore = fopen("highscore.txt", "r");
	fscanf(fhighscore, "%d", &highscore);
	fclose(fhighscore);
	FILE* flongestStreak = fopen("longestStreak.txt", "r");
	fscanf(flongestStreak, "%d", &longestStreak);
	fclose(flongestStreak);

	srand(time(NULL));
	while (1) {
		opNum = rand() % 5;
		opMatch(opNum, &op);
		generateNums(&op, &num1, &num2, &result);
		display(&longestStreak, &currentStreak, &currentScore, &highscore, &op, &num1, &num2);
		getInput(&input);
		answerCheck(&currentStreak, &op, &currentScore, result, input);
		updateScore(&currentStreak, &longestStreak, &currentScore, &highscore, &fhighscore, &flongestStreak);
	}
	system("pause");
	return 0;
}