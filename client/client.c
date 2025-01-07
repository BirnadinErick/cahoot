#include<stdio.h>


int main() {

	char testSubject, Answer;
	int PlayerScore=0;

	printf("Which of the two quizes would you like to take?");
	printf("\nFor a German quiz, please enter the character 'G'");
	printf("\nFor an English quiz please enter the character 'E'");
	printf("\nPlease enter your desired character: ");
	scanf_s("\n%c", &testSubject);
	printf("\n*Every question has ONLY 1 correct answer, please choose ONLY 1 of the four options given to you.*\n");

	if (testSubject == 'G' || testSubject == 'g')
	{
		printf("\nGerman Question 1");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '1') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '2' | Answer == '3' | Answer == '4')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nGerman Question 2");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '3') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '1' | Answer == '4' | Answer == '2')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nGerman Question 3");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '3') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '1' | Answer == '4' | Answer == '2')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nGerman Question 4");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '2') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '1' | Answer == '3' | Answer == '4')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nGerman Question 5");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '1') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '2' | Answer == '3' | Answer == '4')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}
	}
	else if (testSubject == 'E' || testSubject == 'e')
	{
		printf("\nEnglish Question 1");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '4') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '2' | Answer == '3' | Answer == '1')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nEnglish Question 2");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '3') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '1' | Answer == '4' | Answer == '2')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nEnglish Question 3");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '4') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '1' | Answer == '3' | Answer == '2')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nEnglish Question 4");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '2') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '1' | Answer == '3' | Answer == '4')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nEnglish Question 5");
		printf("\n1. Answer 1 2. Answer 2 3. Answer 3 4. Answer 4");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '1') {
			printf("Your answer is correct");
			PlayerScore += PlayerScore;
		}
		else if (Answer == '2' | Answer == '3' | Answer == '4')
		{
			printf("Your asnwer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}
	}
	else
	{
		printf("Invalid Data");
	}
	
	printf("%i", PlayerScore);
	return PlayerScore;
}
