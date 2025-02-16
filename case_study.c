#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// macros for FIBO function
#define MONTHS 12

// macros for MILITARY_TIME function
#define MAX 2400
#define MIN 0
#define MINUTE_MAX 59

void clear_screen(void);
int is_invalid(char* input);
void clear_input_buffer(void);
void FIBO(void);
int fib(int n);
void MILITARY_TIME(void);
char* convert_time(int time);

int main(void)
{
  char choice[3];

  while (1)
  {
    clear_screen();
    printf("=========================================\n");
    printf("|\t\tMAIN MENU\t\t|\n");
    printf("|\t\t\t\t\t|\n");
    printf("|\tA. FIBONACCI SERIES\t\t|\n");
    printf("|\tB. MILITARY TIME\t\t|\n");
    printf("|\tC. EXIT\t\t\t\t|\n");
    printf("=========================================\n");

    printf("CHOOSE LETTER TO EXECUTE: ");

    if (scanf(" %2s", choice) != 1 || is_invalid(choice)) {
      printf("Invalid Input. Allowed: A, B, C\n");
      printf("\nPress enter to continue...");
      clear_input_buffer();
      getchar();
      continue;
    }

    clear_input_buffer();

    switch (toupper(choice[0]))
    {
      case 'A':
        FIBO();
        break;
      case 'B':
        MILITARY_TIME();
        break;
      case 'C':
        return 0;
    }
  }
}

void clear_screen(void)
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

int is_invalid(char* input)
{
  return (strcasecmp(input, "A") && strcasecmp(input, "B") && strcasecmp(input, "C"));
}

void clear_input_buffer(void)
{
  while (getchar() != '\n');
}

void FIBO(void)
{
  int rabbit[MONTHS], pair_sum = 0;

  clear_screen();

  // make rabbit array
  for (int i = 0; i < MONTHS; i++) {
    rabbit[i] = fib(i + 1);
    pair_sum += rabbit[i];
  }

  // print rabbits per month
  printf("=========================================\n");
  printf("|\tRabbit pairs per month:\t\t|\n");
  printf("=========================================\n");

  for (int i = 0; i < MONTHS; i++) {
    if (rabbit[i] == 1) {
      printf("|  Month %d: %d pair\t\t\t|\n", i + 1, rabbit[i]);
    } else {
      printf("|  Month %d: %d pairs\t\t\t|\n", i + 1, rabbit[i]);
    }
  }

  // print sum
  printf("-----------------------------------------\n");
  printf("|  Sum of rabbits in a year: %d\t|\n", pair_sum * 2);
  printf("=========================================\n");

  printf("\nPress enter to continue...");
  clear_input_buffer();
}

int fib(int n)
{
  if (n <= 1)
    return n;

  return fib(n - 1) + fib(n - 2);
}

void MILITARY_TIME(void)
{
  int invalid = 0, military_time = 0;

  clear_screen();

  // input error check
  do {
    printf("Input time in military format: ");
    if (scanf("%d", &military_time) != 1 || military_time > MAX ||
      military_time < MIN || military_time % 100 > MINUTE_MAX) {

      clear_input_buffer();
      printf("Invalid time!\n");
      invalid = 1;
      continue;
    }
    clear_input_buffer();
    invalid = 0;
  } while (invalid);

  // print converted time
  printf("\n=========================\n");
  printf("|  Output: %s\t|\n", convert_time(military_time));
  printf("=========================\n");

  printf("\nPress enter to continue...");
  clear_input_buffer();
}

char* convert_time(int time)
{
  int hours = time / 100;
  int minutes = time % 100;
  static char standard_time_str[9];

  if (hours == 0) {
    sprintf(standard_time_str, "12:%02dAM", minutes);
  } else if (hours == 24) {
    sprintf(standard_time_str, "%02d:%02dAM", hours - 12, minutes);
  } else if (hours == 12) {
    sprintf(standard_time_str, "%02d:%02dPM", hours, minutes);
  } else if (hours > 12) {
    sprintf(standard_time_str, "%02d:%02dPM", hours - 12, minutes);
  } else {
    sprintf(standard_time_str, "%02d:%02dAM", hours, minutes);
  }

  return standard_time_str;
}

