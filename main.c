
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"

int main(){
	long int card_number, card_dest, card_source;
	int pin,CVV,nr_max_card,i,poz, sum, sum2;
		struct LC* card=NULL;
		char expirare[5],comanda[10];
	FILE* input=fopen("input.in","r");
	FILE* output=fopen("output.out","w");
	fscanf(input,"%d",&nr_max_card);
	fgetc(input);
	char success[7];
	char buffer[100];
	memset(buffer, 0, 100);
	char operatie[100];
while(fgets(buffer,100,input)!=0)
	{
		char *op=strtok(buffer," ");
		char *card_no=strtok(NULL,"\n ");
		if(card_no!=NULL && strstr(op,"show")!=NULL)
		{
			card_number=atol(card_no);
			printare_card(&card, card_number,output);

		}
		else if(strstr(op,"show")!=0)
		{
			show(card, nr_max_card, output);
		}
		if(strstr(op,"add_card")!=NULL)
		{	char * pin=strtok(NULL," ");
			char* expiry=strtok(NULL," ");
			char* sCVV=strtok(NULL," ");

			card_number=atol(card_no);
			CVV=atoi(sCVV);
			poz=sumacif(card_number)%(nr_max_card);
			add_card(&card,card_number, pin, expiry, CVV, poz, output);
			}
		if(strstr(op, "delete")!=0)
		{
			card_number=atol(card_no);
			poz=sumacif(card_number)%(nr_max_card);
			delete_card(&card, card_number, poz);
		}
		if(strstr(op, "insert_card")!=0){
			card_number=atol(card_no);
			char*pin=strtok(NULL,"\n ");

			strcpy(operatie, "insert_card");
			strcat(operatie, " ");
			strcat(operatie, card_no);
			strcat(operatie, " ");
			strcat(operatie, pin);
			insert_card(&card, card_number, pin, success, output);
			add_history(&card, card_number, success, operatie);

			

		}
		if(strstr(op, "recharge") != 0){
			card_number=atol(card_no);
			char* string_sum=strtok(NULL, "\n ");
			strcpy(operatie, op);
			strcat(operatie, " ");
			strcat(operatie, card_no);
			strcat(operatie, " ");
			strcat(operatie, string_sum);
			sum=atoi(string_sum);
			recharge(&card, card_number, sum, success, output);
			add_history(&card, card_number, success, operatie);

		}

		if(strstr(op, "cash_withdrawal")!=0){
			card_number=atol(card_no);
			char* string_sum=strtok(NULL, "\n ");
			strcpy(operatie, op);
			strcat(operatie, " ");
			strcat(operatie, card_no);
			strcat(operatie, " ");
			strcat(operatie, string_sum);
			sum=atoi(string_sum);
			cash_withdrawal(&card, card_number, sum, success, output);
			add_history(&card, card_number, success, operatie); 
		}

		if (strstr(op, "cancel")!=0){
			card_number=atol(card_no);
			strcpy(operatie, op);
			strcat(operatie, " ");
			strcat(operatie, card_no);
			cancel(&card, card_number, success);
			add_history(&card, card_number, success, operatie);
		}

		if(strstr(op, "balance_inquiry")!=0){
			card_number=atol(card_no);
			strcpy(operatie, "balance_inquiry");
			strcat(operatie, " ");
			strcat(operatie, card_no);
			balance_inquiry(&card, card_number, success, output);
			add_history(&card, card_number, success, operatie);
		}

		if(strstr(op, "pin_change")!=0){
			card_number=atol(card_no);
			char* pin= strtok(NULL, "\n ");
			strcpy(operatie, "pin_change");
			strcat(operatie, " ");
			strcat(operatie, card_no);
			strcat(operatie, " ");
			strcat(operatie, pin);
			pin_change(&card, card_number, pin, success, output);
			add_history(&card, card_number, success, operatie);
		}

		if(strstr(op, "unblock_card")!=0){
			card_number=atol(card_no);
			strcpy(operatie, "unblock_card");
			strcat(operatie, " ");
			strcat(operatie, card_no);
			unblock_card(&card, card_number, success);
			add_history(&card, card_number, success, operatie);
		}

		if(strstr(op, "transfer_funds")!=0){
			char* aux1=strtok(NULL, " ");
			char* aux2=strtok(NULL, "\n ");
			card_source = atol(card_no);
			card_dest = atol(aux1);
			sum=atoi(aux2);
			strcpy(operatie, "transfer_funds");
			strcat(operatie, " ");
			strcat(operatie, card_no);
			strcat(operatie, " ");
			strcat(operatie, aux1);
			strcat(operatie, " ");
			strcat(operatie, aux2);
			transfer_funds(&card, card_source,card_dest, sum, success, output);
			add_history(&card, card_dest, success, operatie);
			if(strcmp(success, "SUCCESS")==0){
				add_history(&card, card_source, success, operatie);
			}
		}


	}


	free(card);	
	fclose(input);
	fclose(output);


	return 0;
}
