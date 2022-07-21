/*
 *Hope Zobinou 3/30/22
 *
 *This program displays values in binary, hex, octal, and decimal based on the
 *the current value of the program's accumulator.
 */
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "calc.h" //Header file that defines the bin_str array type that holds size 20

char print_menu(void);
void print_acc(short acc, char mode);
short get_operand(char mode);

unsigned short get_binary_op(char *bin);
void convert_to_binary(short acc, char *bin);
void add(short *acc, char mode);
void subtract(short *acc, char mode);

int main(void)
{
  char Mode = 'D'; //Default initilizations
  short acc = 0;
  char UserOption;
  int ShiftNum = 0;
  int OtherAcc = 0;
  
  print_acc(acc, Mode);
  UserOption = print_menu();

  while(UserOption != 'Q') //Loop that tracks the users choice in the menu
  {                        //Stops when the user clicks 'Q'
    
    if(UserOption == 'O')
    {
      Mode = UserOption;
      printf("Mode is Octal\n");
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == 'H')
    {  
      Mode = UserOption;
      printf("Mode is Hexadecimal\n");
      printf("\n");
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == 'D')
    {  
      Mode = UserOption;
      printf("Mode is Decimal\n");
      printf("\n");
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == 'C')
    {
      acc = 0;
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == 'B')
    {
      Mode = UserOption;
      printf("Mode is Binary");
      printf("\n");
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == '~')
    {
      acc = ~acc;
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == 'N')
    {
      acc = ~(~acc);
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == '<')
    {
      printf("Enter number of positions to left shift accumulator: ");
      scanf("%d", &ShiftNum);
      acc = acc << ShiftNum;
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == '>')
    {
      printf("Enter number of positions to right shift accumulator: ");
      scanf("%d", &ShiftNum);
      acc = acc >> ShiftNum;
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == '&')
    {
      OtherAcc = get_operand(Mode);
      acc &= OtherAcc;
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == '|')
    {
      OtherAcc = get_operand(Mode);
      acc |= OtherAcc;
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == '^')
    {
      OtherAcc = get_operand(Mode);
      acc ^= OtherAcc;
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == '+')
    {
      add(&acc, Mode);
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == '-')
    {
      subtract(&acc, Mode);
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
    else if(UserOption == 'S')
    {
      acc = get_operand(Mode);
      print_acc(acc, Mode);
      UserOption = print_menu();
    }
  }

}

void print_acc(short acc, char mode) //Prints out the accumulator tab
{
  bin_str bin = "0000 0000 0000 0000";

  convert_to_binary(acc, bin);
  
  printf("*****************************************\n");
  printf("* Accumulator:          Input Mode: ");
  printf("%c   *\n", mode);
  printf("*   Binary  :  %-20s     *\n", bin); 
  printf("*   Hex     :  %04hX                     *\n", acc);
  printf("*   Octal   :  %06ho                   *\n", acc);
  printf("*   Decimal :  %-10d               *\n", acc);
  printf("*****************************************\n");
  printf("\n");
}

char print_menu(void) //Prints the menu
{
  char ValidOptions [17] ="BOHDCSQ&|^~<>+-N";
  short IsValidOption = 0;
  char UserOption;
  char UserString[20]; 
  
  while(IsValidOption == 0) //Loop tracks whether the user chooses a valid option
  {
    printf("Please select one of the following options: \n");
    printf("\n");
    printf("B Binary Mode");
    printf("           & AND with Accumulator      + Add to Accumulator\n");
    printf("O Octal Mode");
    printf("            | OR with Accumulator       - Subtract from Accumulator\n");
    printf("H Hexadecimal Mode");
    printf("      ^ XOR with Accumulator      N Negate Accumulator\n");
    printf("D Decimal Mode\n");
    printf("\n");
    printf("C Clear Accumulator");
    printf("     < Shift Accumulator left\n"); 
    printf("S Set Accumulator");
    printf("       > Shift Accumulator Right\n");
    printf("\n");
    printf("Q Quit\n");
    printf("\n");
    printf("Option: ");
    scanf("%s", UserString);
    printf("\n");
    
    if(strlen(UserString) == 1)
    {
      UserOption = UserString[0];
      UserOption = toupper(UserOption);
    }
    if(!strchr(ValidOptions, UserOption) || strlen(UserString) != 1)
    {
      printf("Invald option: %s\n", UserString);
      printf("\n");
    }
    else
    {
      IsValidOption = 1;
    }
  }
  
  return UserOption; 
}

short get_operand(char mode) //Gets additional user info when in these 4 modes
{
  short int UserValue;

  bin_str bit;

  switch(mode)
  {
  case 'D':
    printf("Enter decimal value: ");
    scanf("%hd", &UserValue);
    break;
  case 'O':
    printf("Enter octal value: ");
    scanf("%ho", &UserValue);
    break;
  case 'H':
    printf("Enter hex value: ");
    scanf("%hx", &UserValue);
    break;
  case 'B':
    printf("Enter binary value: ");
    scanf("%s", bit);
    UserValue = get_binary_op(bit);  
    break;
  }

  return UserValue; //Returns the additional info the user gave
  
}

unsigned short get_binary_op(char *bin) //Makes the user binary input into a proper binary format
{
  unsigned short TheValue;
  int counter = strlen(bin);
  int exponent = 0;

  while(counter != 0)
  {
    if(bin[counter - 1] == '1')
    {
      TheValue += 1 << exponent;
    }
    counter--;
    exponent++;
  }

  return TheValue;
}

void convert_to_binary(short acc, char *bin) //Converts acc to binary for the accumulator and account
{                                            //For spaces
  int BitIndex = 18; //Starts at the end of array
  int counter = 0; //Starts at the beginning of array
  unsigned short NewAcc = acc;

  while((NewAcc != 0) || (BitIndex < 0))
  {
    if(counter != 4)
    {
      int TempBit = 0;
      TempBit = NewAcc % 2;
      NewAcc = NewAcc / 2;
      if((TempBit == 1) || (TempBit == -1))
      {
	bin[BitIndex] = '1';
      }
      counter++;
      BitIndex--;
    }
    else
    {
      counter = 0;
      BitIndex--;
    }
  }
}

void add(short *acc, char mode) //Adds to accumulator and checks for overflow
{
  short OtherAcc = get_operand(mode);
  short sum = *acc + OtherAcc;

  if((OtherAcc && *acc) > 0 && sum < 0)
  {
    printf("Positive Overflow");
  }
  if((OtherAcc && *acc) < 0 && sum > 0)
  {
    printf("Negative Overflow");
  }
  
  printf("\n");
  *acc = sum;
}

void subtract(short *acc, char mode) //Subtracts from accumulator and checks for overflow
{
  short OtherAcc = get_operand(mode);
  short diff = *acc - OtherAcc;

  if((OtherAcc && *acc) > 0 && diff < 0)
  {
    printf("Positive Overflow"); 
  }
  if((OtherAcc && *acc) < 0 && diff > 0)
  {
    printf("Negative Overflow");
  }

  printf("\n");
  *acc = diff;
}
