#ifndef __ATM_H__
#define __ATM_H__
#include <stdio.h>
#include <stdlib.h>
typedef struct history{
char success[8];
char operatie[100];
struct history* next;
}history;
typedef struct LSC{
	long int card_number;
	char pin[5];
	int invalid_pin; 
	char expirare[5];
	int CVV;
	int balance;
	char status[6]; 
	struct history *istoric;
	struct LSC *next;
}LSC;
typedef struct LC{
	int inserted; //este 0 daca nu a fost introdus un card si 1 daca a fost introdus;
	int poz; //pastreaza pozitia unde vom insera cardurile
struct LSC *card;
struct LC *next;
}LC;
void add_card(struct LC** card,long int card_number, char pin[4],char expirare[5],int CVV,int poz, FILE *output);
void show(struct LC* card,int nr_card, FILE *output);
int sumacif(long int n);
void printare_lista(int poz, struct LC* card, FILE *output);
void delete_card(struct LC** card, long int card_number, int poz);
void insert_card(struct LC** card, long int card_number, char* pin, char* success, FILE *output);
void recharge (struct LC **card, long int card_number, int sum, char* success, FILE *output);
void cash_withdrawal(struct LC **card, long int card_number, int sum, char* success, FILE* output); 
void balance_inquiry (struct LC **card, long int card_number,char* success, FILE* output);
void printare_card(struct LC **card,long int nr_card, FILE *output);
void add_history(struct LC **card, long int card_number,char* success, char* operatie);
void pin_change(struct LC **card, long int card_number, char* new_pin, char* success, FILE* output);
void cancel(struct LC **card, long int card_number, char* success);
void unblock_card(struct LC** card, long int card_number, char* success);
void transfer_funds(struct LC** card, long int card_source, long int card_dest, int sum, char* success, FILE *output);
#endif
