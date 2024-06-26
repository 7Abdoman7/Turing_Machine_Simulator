#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZERO            (0)
#define ACTION_NUM      (4)
#define TAPE_MAX_LENGTH (512)

typedef enum {
    RIGHT,
    LEFT,
    YES,
    NO,
    UNKNOWN
} action_t;

typedef struct {
    int input_State;
    int output_State;
    char input_Char;
    char output_Char;
    action_t action;
} transitionLine_t;

typedef struct {
    int num_Of_states;
    int num_Of_Alphabet;
    char alphabet[32];
    transitionLine_t lines[1024];
} transitionTable_t;

typedef struct {
    transitionTable_t *table;
    int table_Size;
    int initial_State;
    int head_Position;
    int tape_Max_Lengh;
} turingMachine_t;


const char* actionToString(action_t action) {
    switch (action) {
        case RIGHT:
            return "RIGHT";
        case LEFT:
            return "LEFT";
        case YES:
            return "YES";
        case NO:
            return "NO";
        default:
            return "UNKNOWN";
    }
}

void get_Alpha_Str(turingMachine_t *turing, char c, char *str) {
    int pos = ZERO;
    int counter = ZERO;

    for (counter = ZERO; counter < turing->table->num_Of_Alphabet; counter++) {
        if (turing->table->alphabet[counter] == c) {
            break;
        }
        pos++;
    }

    for (counter = ZERO; counter <= pos; counter++) {
        str[counter] = '1';
    }
    str[counter] = '\0';
}

action_t turing_Work(turingMachine_t *turing, char *tape) {
    int counter = 1;
    int currentState = turing->initial_State;
    int temp = ZERO;
    int tape_Counter = ZERO;

    while (1) {
        printf("\nConfiguration[%d]: \n", counter);
        printf("Current state: q%d\n", currentState);
        printf("Current head position: %d\n", turing->head_Position);

        printf("Tape: ");
        for (tape_Counter  = 0; tape_Counter < turing->tape_Max_Lengh; tape_Counter++) {
            if (tape_Counter == turing->head_Position) {
                printf("(%c)", tape[tape_Counter]);
            } 
            else {
                printf("%c", tape[tape_Counter]);
            }
        }
        printf("\n");

        for (temp = ZERO; temp < turing->table_Size; temp++) {
            transitionLine_t line = turing->table->lines[temp];
            if (line.input_State == currentState && line.input_Char == tape[turing->head_Position]) {
                tape[turing->head_Position] = line.output_Char;

                if (line.action == RIGHT) {
                    turing->head_Position++;
                    if (turing->head_Position > turing->tape_Max_Lengh) {
                        printf("\n\nError with tape size {overflow}\n\n");
                        exit(1);
                    }
                } 
                else if (line.action == LEFT) {
                    turing->head_Position--;
                    if (ZERO > turing->head_Position) {
                        printf("\n\nERROR with the head position {Less than 0}\n\n");
                        exit(1);
                    }
                }

                currentState = line.output_State;

                if (line.action == YES) {
                    return YES;
                } 
                else if (line.action == NO) {
                    return NO;
                }

                break; 
            }
        }
        counter++;
    }
}


void print_Encrypted_Turing(turingMachine_t *turing) {
    int counter = ZERO;
    int temp_Counter = ZERO;

    char state_Str[turing->table->num_Of_states][64];
    char alpha_Str[128];

    char action_Str[4][8] = {"1", "11", "111", "1111"};

    printf("\nSteps for encryption: \n");

    printf("States: \n");
    for (counter = ZERO; counter < turing->table->num_Of_states; counter++) {
        for (temp_Counter = ZERO; temp_Counter <= counter; temp_Counter++) {
            state_Str[counter][temp_Counter] = '1';
        }
        state_Str[counter][temp_Counter] = '\0';
    }

    for (counter = ZERO; counter < turing->table->num_Of_states; counter++) {
        printf("q%d => %s\n", (counter + 1), state_Str[counter]);
    }

    printf("Alphabet: \n"); 
    for (counter = ZERO; counter < turing->table->num_Of_Alphabet; counter++) {
        get_Alpha_Str(turing, turing->table->alphabet[counter], alpha_Str);
        printf("%c => %s\n", turing->table->alphabet[counter], alpha_Str);
    }

    printf("Actions: \n");
    printf("R => 1\n");
    printf("L => 11\n");
    printf("Y => 111\n");
    printf("N => 1111\n");
    printf("SPACE => 0\n");
    printf("New transition line => 00\n");

    printf("\nThe encrpted turing machine:\n");

    for (counter = ZERO; counter < turing->table_Size; counter++) {
        printf("%s", state_Str[turing->table->lines[counter].input_State - 1]);
        printf("0");

        get_Alpha_Str(turing, turing->table->lines[counter].input_Char, alpha_Str);
        printf("%s", alpha_Str);
        printf("0");

        printf("%s", state_Str[turing->table->lines[counter].output_State - 1]);
        printf("0");

        get_Alpha_Str(turing, turing->table->lines[counter].output_Char, alpha_Str);
        printf("%s", alpha_Str);
        printf("0");

        printf("%s", action_Str[turing->table->lines[counter].action]);
        printf("00");
    }
    printf("\n");
}

int main() {
    int counter = ZERO;
    int tape_Counter = ZERO;

    int table_Size = ZERO;
    int number_Of_States = ZERO;
    int alphabet_Counter = ZERO;
    int initial_State = ZERO;
    int head_Position = ZERO;

    action_t temp_Action = UNKNOWN;

    char str[1024][16];
    char temp = '0';

    char tape_Temp[TAPE_MAX_LENGTH];
    char tape[TAPE_MAX_LENGTH];

    transitionTable_t *table = (transitionTable_t*)malloc(sizeof(transitionTable_t));
    turingMachine_t *turing = (turingMachine_t*)malloc(sizeof(turingMachine_t));
    turing->table = table;
    turing->tape_Max_Lengh = TAPE_MAX_LENGTH;

    printf("Enter the transition table:\n");
    printf("The format is (state{starting from 1},input,newState,output,action{R,L,Y,N}) e.g. (1,a,2,b,R)\n");
    printf("When you are finished enter # on a new line.\n");
    printf("Examples at the end of the code\n\n");

    while (1) {
        fgets(str[table_Size], sizeof(str[table_Size]), stdin);
        str[table_Size][strcspn(str[table_Size], "\n")] = 0; 
        if (str[table_Size][0] == '#') {
            break;
        }
        table_Size++;
    }

    printf("\nEnter the tape (put () around the head position): ");
    scanf("%s", tape_Temp);

    printf("\nEnter initial state{starting from 1}: ");
    scanf("%d", &initial_State);

    for (counter = ZERO; counter < table_Size; counter++) {
        table->lines[counter].input_State = str[counter][0] - '0';
        table->lines[counter].input_Char = str[counter][2];
        table->lines[counter].output_State = str[counter][4] - '0';
        table->lines[counter].output_Char = str[counter][6];
        switch (str[counter][8]) {
            case 'R':
            case 'r':
                table->lines[counter].action = RIGHT;
            break;
            case 'L':
            case 'l':
                table->lines[counter].action = LEFT;
            break;
            case 'Y':
            case 'y':
                table->lines[counter].action = YES;
            break;
            case 'N':
            case 'n':
                table->lines[counter].action = NO;
            break;
        }    
    }

    turing->initial_State = initial_State;
    turing->table_Size = table_Size;

    for (counter = ZERO; counter < strlen(tape_Temp); counter++) {
        if ('(' == tape_Temp[counter]) {
            head_Position = counter;
        } else if (')' == tape_Temp[counter]) {
            // Do nothing
        } else {
            tape[tape_Counter] = tape_Temp[counter];
            tape_Counter++;
        }
    }

    for (counter = tape_Counter; counter < turing->tape_Max_Lengh; counter++) {
        tape[counter] = '#';
        tape_Counter++;
    }
    tape[tape_Counter] = '\0';

    turing->head_Position = head_Position;

    for (counter = ZERO; counter < table_Size; counter++) {
        if (temp != str[counter][0]) {
            temp = str[counter][0];
            number_Of_States++;
        }
    }

    alphabet_Counter = table_Size / number_Of_States;

    for (counter = ZERO; counter < alphabet_Counter; counter++) {
        table->alphabet[counter] = str[counter][2];
    }

    table->num_Of_states = number_Of_States;
    table->num_Of_Alphabet = alphabet_Counter;

    printf("\nnum of states: %d", table->num_Of_states);
    printf("\nThe alphabet: ");

    for (counter = ZERO; counter < alphabet_Counter; counter++) {
        printf("%c ", table->alphabet[counter]);
    }

    for (counter = ZERO; counter < turing->tape_Max_Lengh; counter++) {
        tape_Temp[counter] = tape[counter];
    }

    printf("\nThe Tape: %s\n", tape);
    
    printf("\nTape length: %d", tape_Counter);
    printf("\nInitial state: %d", turing->initial_State);
    printf("\nHead position: %d", turing->head_Position);

    printf("\n\nTransition table:\n");
    printf("state   read    state   write   action\n");

    for (counter = ZERO; counter < table_Size; counter++) {
        printf("  q%d      %c      q%d       %c     %s\n", 
            turing->table->lines[counter].input_State, 
            turing->table->lines[counter].input_Char,
            turing->table->lines[counter].output_State, 
            turing->table->lines[counter].output_Char, 
            actionToString(turing->table->lines[counter].action));
    }

    temp_Action = turing_Work(turing, tape);

    if (YES == temp_Action) {
        printf("\nTuring machine is done with yes\n");
    } 
    else {
        printf("\nTuring machine is done with no or error\n");
    }

    tape[turing->tape_Max_Lengh] = '\0';

    printf("\nFinal Tape: %s\n", tape);

    print_Encrypted_Turing(turing);

    free(table);
    free(turing);

    return 0;
}


/*Examples you can take copy and paste it:*/

//Add one to the number
/*
1,<,1,<,R
1,0,1,0,R
1,1,1,1,R
1,#,2,#,L
2,<,2,<,N
2,0,2,1,Y
2,1,2,0,L
2,#,2,#,N
#

tape: (<)00001111
*/

//Check if even it prints 1 on the tape or if odd it prints 0 on the tape
/*
1,<,1,<,R
1,0,1,0,R
1,1,1,1,R
1,#,2,#,L
2,<,2,<,N
2,0,3,#,L
2,1,4,#,L
2,#,2,#,N
3,<,5,<,R
3,0,3,#,L
3,1,3,#,L
3,#,3,#,N
4,<,6,<,R
4,0,4,#,L
4,1,4,#,L
4,#,4,#,N
5,<,5,<,N
5,0,5,#,N
5,1,5,#,N
5,#,5,1,Y
6,<,6,<,N
6,0,6,#,N
6,1,6,#,N
6,#,6,0,Y
#

tape: (<)10101

*/