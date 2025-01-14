#include<stdio.h>


int main() {

	char testSubject, Answer;
	int PlayerScore = 0;

	printf("Which of the two quizes would you like to take?");
	printf("\nFor a German quiz, please enter the character 'G'");
	printf("\nFor a Geography quiz please enter the character 'E'");
	printf("\nPlease enter your desired character: ");
	scanf_s("\n%c", &testSubject);
	printf("\n*Every question has ONLY 1 correct answer, please choose ONLY 1 of the options given to you.*\n");

	if (testSubject == 'G' || testSubject == 'g')
	{
		printf("\nAnna und Paula wollten/wollte/musste/solltet ihren Urlaub planen.");
		printf("\n1. wollten \n2. wollte \n3. musste \n4. solltet");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '1') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '2' | Answer == '3' | Answer == '4')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nWir haben draussen uebernachtet, obwohl/ da es geregnet hat.");
		printf("\n1. obwohl 2. da");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '1') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '2')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nLouis aergert sich, obwohl / weil er den Insektenschutz vergessen hat. ");
		printf("\n1. obwohl 2. weil");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '2') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '1')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nJannis hat ein Feuer gemacht, obwohl / weil das im Gebirge verboten ist.");
		printf("\n1. obwohl 2. weil");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '1') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '2')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nIch darf/durfte/konnte/soll heute nicht zu spät nach Hause kommen.");
		printf("\n1. darf \n2. durfte \n3. konnte \n4. soll");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '2') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '1' | Answer == '3' | Answer == '4')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}
	}
	else if (testSubject == 'E' || testSubject == 'e')
	{
		printf("\nWhich African country is the largest by area?");
		printf("\n1. Sudan \n2. Algeria \n3. Democratic Republic of Congo \n4. Libya");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '2') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '1' | Answer == '3' | Answer == '4')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nWhich country is famous for its tulips and windmills?");
		printf("\n1. Belgium \n2. Denmark \n3. Netherlands \n4. Germany");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '3') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '1' | Answer == '4' | Answer == '2')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nWhat is the capital of South Korea?");
		printf("\n1. Seoul \n2. Beijing \n3. Soul \n4. Daejeon");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '1') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '4' | Answer == '3' | Answer == '2')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nWhat is the capital of Canada?");
		printf("\n1. Toronto \n2. Ottawa \n3. Munich \n4. Lahore");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '2') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '1' | Answer == '3' | Answer == '4')
		{
			printf("Your answer is incorrect");
		}
		else
		{
			printf("Invalid Data, please try again.");
		}

		printf("\nWhat country is not a part of Europe");
		printf("\n1. Brazil \n2. Portugal \n3. France \n4. Hungary");
		printf("\nYour Answer: ");
		scanf_s("\n%c", &Answer);

		if (Answer == '1') {
			printf("Your answer is correct");
			PlayerScore += 1;
		}
		else if (Answer == '2' | Answer == '3' | Answer == '4')
		{
			printf("Your answer is incorrect");
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

	printf("\nYour final score is, %i/5", PlayerScore);
	//return PlayerScore;
}
