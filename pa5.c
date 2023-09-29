#include "pa5.h"

int run_menu(void)
{
	int num = 0;

	printf("Y A H T Z E E\n");

	printf("\n--------------------");
	printf("\n1. Print Rules");
	printf("\n2. Start Game");
	printf("\n3. Exit");
	printf("\n--------------------\n");

	scanf("%d", &num);

	return num;
}

void print_rules(void)
{
	printf("The scorecard used for Yahtzee is composed of two sections. An upper section and a lower section.\n");
	printf("A total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\n");
	printf("The upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\n");
	printf("If a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\n"); 
	printf("Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\n");
	printf("If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the players overall score as a bonus.\n");
	printf("The lower section contains a number of poker like combinations.\n"); 
	
	printf("\nThree-of-a-kind: 3 dice with the same face and is worth the sum of all face values.\n");
	printf("Four-of-a-kind: 4 dice with the same face and is worth the sum of all face values.\n");
	printf("Full house: One pair and a three-of-a-kind and is worth 25.\n");
	printf("Small straight: a sequence of four dice and is worth 30.\n");
	printf("Large straight: a sequence of five dice and is worth 40.\n");
	printf("Yahtzee: five dice with the same face and is worth 50.\n");
	printf("Chance: may be used for any sequence of dice and is worth the sum of all face values.\n\n");

	system("pause");
	system("cls");
}

int roll_die(int* dice, int dice_num)
{
	if (dice_num == 6)
	{
		int i = 0;
		for (i = 0; i < 5; i++)
		{
			int result = rand();
			result = (result % 6) + 1;
			dice[i] = result;
		}
	}
	else
	{
		int result = rand();
		result = (result % 6) + 1;
		dice[dice_num] = result;
	}
	return 0;
}

int combo_selection(int *plr_score)
{
	int num = 0, combo = 0;

	printf("\n1. Sum of 1's");
	printf("\n2. Sum of 2's");
	printf("\n3. Sum of 3's");
	printf("\n4. Sum of 4's");
	printf("\n5. Sum of 5's");
	printf("\n6. Sum of 6's");
	printf("\n7. Three-of-a-kind");
	printf("\n8. Four-of-a-kind");
	printf("\n9. Full house");
	printf("\n10. Small straight");
	printf("\n11. Large straight");
	printf("\n12. Yahtzee");
	printf("\n13. Chance");

	while (combo == 0)
	{
		printf("\n\nEnter your selection: \n");
		scanf("%d", &num);
		if (num > 0 && num < 14 && plr_score[num - 1] == -1)
		{
			combo = 1;
		}
		else
		{
			printf("\nThis combination can't be used!");
		}
	}

	return num;
}

void verify_selection(int num, int* dice, int* plr1_score, int* plr2_score, int cur_plr)
{
	int check[6];
	int i = 1, j = 0, counting = 0, points = 0;

	for (i = 1; i <= 6; i++)
	{
		int counter = 0;
		for (j = 0; j < 5; j++)
		{
			if (dice[j] == i)
			{
				counter += 1;
			}
			check[i - 1] = counter;
		}
	}

	if (num > 0 && num < 7)
	{
		if (check[num - 1] != 0)
		{
			points = check[num - 1] * num;
			
		}
		
	}
	else if (num == 7 || num == 8)
	{
		for (i = 1; i <= 6; i++)
		{
			if (check[i] == num - 4)
			{
				for (j = 0; j < 5; j++)
				{
					points = dice[j] * (num - 4);
				}
			}
		}
	}
	else if (num == 9)
	{
		int three = 0;
		for (i = 1; i <= 6; i++)
		{
			if (check[i] == 3)
			{
				three = 1;
			}
		}
		if (three == 1)
		{
			for (i = 1; i <= 6; i++)
			{
				if (check[i] == 2)
				{
					points = 25;
				}
			}
		}
	}
	else if (num == 10 || num == 11)
	{
		for (i = 1; i < 5; i++)
		{
			if (dice[i - 1] == dice[i] - 1)
			{
				counting += 1;
			}
		}
		if (counting == 4 && num == 10)
		{
			points = 30;
		}
		else if (counting == 5 && num == 11)
		{
			points = 40;
		}
	}
	else if (num == 12)
	{
		for (i = 1; i <= 6; i++)
		{
			if (check[i] == 5)
			{
				points = 50;
			}
		}
	}
	else if (num == 13)
	{
		for (i = 1; i < 5; i++)
		{
			counting += dice[i];
		}
		points = counting;
	}

	if (cur_plr == 1)
	{
		plr1_score[num - 1] = points;
	}
	else if (cur_plr == 2)
	{
		plr2_score[num - 1] = points;
	}
}

void display_dice(int* dice)
{
	printf("You rolled: \n");
	int i = 0;
	printf(" _   _   _   _   _\n");
	for (i = 0; i < 5; i++)
	{
		int num = dice[i];
		printf("|%d| ", num);
	}
	int ascii = 196;
	char upper = ascii;
	printf("\n %c   %c   %c   %c   %c \n", upper, upper, upper, upper, upper);
}

void print_scores(int* plr1_score, int* plr2_score)
{
	int i = 0, plr1_up_total = 0, plr1_low_total = 0, plr2_up_total = 0, plr2_low_total = 0;

	for (i = 0; i < 13; i++)
	{
		if (plr1_score[i] == -1)
		{
			plr1_score[i] = 0;
		}
		if (plr2_score[i] == -1)
		{
			plr2_score[i] = 0;
		}
	}

	for (i = 0; i < 6; i++)
	{
		plr1_up_total += plr1_score[i];
		plr2_up_total += plr2_score[i];
	}

	for (i = 6; i < 13; i++)
	{
		plr1_low_total += plr1_score[i];
		plr2_low_total += plr2_score[i];
	}

	printf("----------PLAYER 1----------\n");
	printf("  -----UPPER SECTION------\n");
	for (i = 0; i < 6; i++)
	{
		printf("Sum of %d's: %d\n", i+1, plr1_score[i]);
	}
	printf("Total Score: %d\n", plr1_up_total);
	if (plr1_up_total >= 63)
	{
		printf("Bonus: 35\n");
		plr1_up_total += 35;
	}
	else
	{
		printf("Bonus: 0\n");
	}
	printf("Total: %d\n", plr1_up_total);
	printf("  -----LOWER SECTION------\n");
	printf("Three-of-a-kind: %d\n", plr1_score[6]);
	printf("Four-of-a-kind: %d\n", plr1_score[7]);
	printf("Full house: %d\n", plr1_score[8]);
	printf("Small straight: %d\n", plr1_score[9]);
	printf("Large straight: %d\n", plr1_score[10]);
	printf("Yahtzee: %d\n", plr1_score[11]);
	printf("Chance: %d\n", plr1_score[12]);
	printf("Total: %d\n", plr1_low_total);
	printf("\nGrand Total: %d", plr1_up_total + plr1_low_total);


	printf("\n\n\n----------PLAYER 2----------\n");
	printf("  -----UPPER SECTION------\n");
	for (i = 0; i < 6; i++)
	{
		printf("Sum of %d's: %d\n", i+1, plr2_score[i]);
	}
	printf("Total Score: %d\n", plr2_up_total);
	if (plr2_up_total >= 63)
	{
		printf("Bonus: 35\n");
		plr2_up_total += 35;
	}
	else
	{
		printf("Bonus: 0\n");
	}
	printf("Total: %d\n", plr2_up_total);
	printf("  -----LOWER SECTION------\n");
	printf("Three-of-a-kind: %d\n", plr2_score[6]);
	printf("Four-of-a-kind: %d\n", plr2_score[7]);
	printf("Full house: %d\n", plr2_score[8]);
	printf("Small straight: %d\n", plr2_score[9]);
	printf("Large straight: %d\n", plr2_score[10]);
	printf("Yahtzee: %d\n", plr2_score[11]);
	printf("Chance: %d\n", plr2_score[12]);
	printf("Total: %d\n", plr2_low_total);
	printf("\nGrand Total: %d", plr2_up_total + plr2_low_total);

	if ((plr1_up_total + plr1_low_total) > (plr2_up_total + plr2_low_total))
	{
		printf("\n\n\n**Player 1 won!**\n");
	}
	else if ((plr1_up_total + plr1_low_total) < (plr2_up_total + plr2_low_total))
	{
		printf("\n\n\n**Player 2 won!**\n");
	}
	else
	{
		printf("\n\n\n**There was a tie!**\n");
	}
	system("pause");
	system("cls");
	start_menu();
}

void play_game()
{
	int round_rolls = 0, cur_plr = 1, round_num = 1, selection_num = 0, keep_playing = 0;
	int* plr1_score[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int* plr2_score[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int* dice[5] = { 0, 0, 0, 0, 0 };

	printf("Player %d || Roll: %d | Round: %d\n", cur_plr, round_rolls, round_num);
	roll_die(&dice, 6);
	display_dice(&dice);

	while (keep_playing == 0)
	{
		if (round_num < 14)
		{
			if (round_rolls < 2)
			{
				char response = 'a';
				int sel_good = 0;
				while (sel_good == 0)
				{
					printf("\nDo you want to use the roll for one of the combinations? (y/n):\n");
					scanf(" %c", &response);
					if (response == 'y' || response == 'n')
					{
						sel_good = 1;
					}
				}

				if (round_rolls == 3 || response == 'y')
				{
					int selection_num = 0;
					if (cur_plr == 1)
					{
						selection_num = combo_selection(&plr1_score);
						verify_selection(selection_num, &dice, &plr1_score, &plr2_score, cur_plr);
						system("cls");
						cur_plr = 2;
					}
					else if (cur_plr == 2)
					{
						selection_num = combo_selection(&plr2_score);
						verify_selection(selection_num, &dice, &plr1_score, &plr2_score, cur_plr);
						system("cls");
						cur_plr = 1;
						round_num++;
					}
					round_rolls = 0;
					system("pause");
					system("cls");
					printf("Player %d || Roll: %d | Round: %d\n", cur_plr, round_rolls, round_num);
					roll_die(&dice, 6);
					display_dice(&dice);
				}
				else if (response == 'n')
				{
					int dice_selection = -1;
					while (dice_selection != 0)
					{
						printf("\nPlease enter which dice you would like to re-roll (1-5, enter 0 to quit): \n");
						scanf("%d", &dice_selection);
						if (1 <= dice_selection && dice_selection <= 5) {

							roll_die(&dice, dice_selection - 1);
						}
						else if (dice_selection == 0)
						{
							break;
						}
					}
					system("pause");
					system("cls");
					round_rolls++;
					printf("Player %d || Roll: %d | Round: %d\n", cur_plr, round_rolls, round_num);
					display_dice(&dice);
				}
			}
			else
			{
				int selection_num = 0;
				if (cur_plr == 1)
				{
					selection_num = combo_selection(&plr1_score);
					verify_selection(selection_num, &dice, &plr1_score, &plr2_score, cur_plr);
					system("cls");
					cur_plr = 2;
				}
				else if (cur_plr == 2)
				{
					selection_num = combo_selection(&plr2_score);
					verify_selection(selection_num, &dice, &plr1_score, &plr2_score, cur_plr);
					system("cls");
					cur_plr = 1;
					round_num++;
				}
				round_rolls = 0;
				system("pause");
				system("cls");
				printf("Player %d || Roll: %d | Round: %d\n", cur_plr, round_rolls, round_num);
				roll_die(&dice, 6);
				display_dice(&dice);
			}
		}
		else if (round_num == 14)
		{
			keep_playing = 1;
			system("cls");
			print_scores(&plr1_score, &plr2_score);
		}
	}
}

void start_menu()
{
	int menu_result = 0, menu_num = 0;
	while (menu_num == 0)
	{
		menu_result = run_menu();

		switch (menu_result)
		{
		case 1:
			system("cls");
			print_rules();
			break;
		case 2:
			system("cls");
			play_game();
			menu_num = 1;
			break;
		case 3:
			system("cls");
			menu_num = 1;
			printf("Thank you for playing, goodbye!");
			break;
		default:
			system("cls");
			break;
		}
	}
}
