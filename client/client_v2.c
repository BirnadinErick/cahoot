#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXUSERNAME 50
#define maxPLayers 100

typedef struct {
    char* name;
    uint8_t score;
} Player;

int checkAnswer(char answer, char ref_answer, uint8_t playerCurrScore) {
    if (answer != ref_answer) {
        printf("Wrong answer dummy");
        return playerCurrScore;
    }

    printf("correct answer!");
    return playerCurrScore + 1;
}

uint8_t geographyQuiz(uint8_t playerScore) {
    char Answer = 'x';

    printf("\nWhich African country is the largest by area?");
    printf(
        "\n1. Sudan \n2. Algeria \n3. Democratic Republic of Congo "
        "\n4. Libya");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '2', playerScore);

    printf("\nWhich country is famous for its tulips and windmills?");
    printf("\n1. Belgium \n2. Denmark \n3. Netherlands \n4. Germany");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '3', playerScore);

    printf("\nWhat is the capital of South Korea?");
    printf("\n1. Seoul \n2. Beijing \n3. Soul \n4. Daejeon");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '1', playerScore);

    printf("\nWhat is the capital of Canada?");
    printf("\n1. Toronto \n2. Ottawa \n3. Munich \n4. Lahore");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '2', playerScore);

    printf("\nWhat country is not a part of Europe");
    printf("\n1. Brazil \n2. Portugal \n3. France \n4. Hungary");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '1', playerScore);

    return playerScore;
}

uint8_t germanQuiz(uint8_t playerScore) {
    char Answer = 'x';

    printf(
        "\nAnna und Paula wollten/wollte/musste/solltet ihren Urlaub "
        "planen.");
    printf("\n1. wollten \n2. wollte \n3. musste \n4. solltet");
    printf("\nYour Answer: ");
    scanf_s(" %c", &Answer);
    playerScore = checkAnswer(Answer, '1', playerScore);

    printf(
        "\nWir haben draussen uebernachtet, obwohl/ da es geregnet "
        "hat.");
    printf("\n1. obwohl 2. da");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '1', playerScore);

    printf(
        "\nLouis aergert sich, obwohl / weil er den Insektenschutz "
        "vergessen hat. ");
    printf("\n1. obwohl 2. weil");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '2', playerScore);

    printf(
        "\nJannis hat ein Feuer gemacht, obwohl / weil das im Gebirge "
        "verboten ist.");
    printf("\n1. obwohl 2. weil");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '1', playerScore);

    printf(
        "\nIch darf/durfte/konnte/soll heute nicht zu spaet nach Hause "
        "kommen.");
    printf("\n1. darf \n2. durfte \n3. konnte \n4. soll");
    printf("\nYour Answer: ");
    scanf_s("\n%c", &Answer);
    playerScore = checkAnswer(Answer, '2', playerScore);

    return playerScore;
}

int main() {
    char testSubject, Answer;
    uint8_t PlayerScore;
    int Quizover = 1;
    char playerName[MAXUSERNAME];
    char playerNames[maxPLayers][MAXUSERNAME];
    int playerScores[maxPLayers];
    int playerCount = 0;
    Player players[32];

    while (Quizover) {
        uint8_t playerScore = 0;

        printf("\nPlease enter your name: ");
        scanf_s("%s", playerName, MAXUSERNAME);

        printf("Hello %s, which of the two quizzes would you like to take?",
               playerName);
    quiz_start:
        puts("For a German quiz, please enter the character 'G'");
        puts("For a Geography quiz please enter the character 'E'");
        puts("Please enter your desired character: ");
        scanf_s(" %c", &testSubject);

        puts(
            "Every question has ONLY 1 correct answer, please choose ONLY 1 "
            "of the options given to you.*");

        if (testSubject == 'G' || testSubject == 'g') {
            playerScore = germanQuiz(playerScore);
        } else if (testSubject == 'E' || testSubject == 'e') {
            playerScore = geographyQuiz(playerScore);
        } else {
            puts(" **You have entered invalid data**, reenter!.");
            goto quiz_start;
        }

        char* name = (char*)malloc(sizeof(char) * MAXUSERNAME);
        strcpy_s(name, MAXUSERNAME, playerName);
        Player _player = {.name = name, .score = playerScore};
        players[playerCount] = _player;

        strcpy_s(playerNames[playerCount], MAXUSERNAME, playerName);
        playerScores[playerCount] = playerScore;
        playerCount++;

        printf("\nDo you want to end the quiz? (1 for Yes, 0 for No): ");
        scanf_s("%d", &Quizover);
    }

    printf("\nFinal Results:\n");
    for (int i = 0; i < playerCount; i++) {
        printf("Player: %s, Score: %d/5\n", players[i].name, players[i].score);
    }

    for (int i = 0; i < playerCount; i++) {
        printf("Player: %s, Score: %d/5\n", playerNames[i], playerScores[i]);
    }

    return 0;
}
