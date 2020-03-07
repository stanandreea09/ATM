#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"

int sumacif(long int n)
{ 
	if(n==0) return 0;
  	else return sumacif(n/10)+n%10;
}

void add_card(struct LC** card,long int card_number, char pin[4],char expirare[5],int CVV,int poz, FILE *output){
	if((*card)==NULL)
	{
		if(card_number!=0)
		{
		(*card)=(LC*)calloc(1, sizeof(LC));
		(*card)->card=(LSC*)calloc(1, sizeof(LSC));
		(*card)->card->card_number=card_number;
		strcpy((*card)->card->expirare,expirare);
		strcpy((*card)->card->status,"NEW");
		strcpy((*card)->card->pin, pin);
		(*card)->card->CVV=CVV;
		(*card)->poz=poz;
		(*card)->card->balance=0;
		(*card)->card->invalid_pin=0;
		(*card)->next=NULL;

		return;
		}
		
		return;
	}
	struct LC* iterator=(*card);
	int iesire=0;
		while(iterator!=NULL){
		if(poz==iterator->poz)
		{
			if(iterator->card->card_number != card_number){
			iesire=1;
			struct LSC* card_new=(LSC*)calloc(1, sizeof(LSC));
			card_new->card_number=card_number;
			strcpy(card_new->pin,pin);
			card_new->CVV=CVV;
			card_new->balance=0;
			card_new->invalid_pin=0;
			strcpy(card_new->expirare,expirare);
			strcpy(card_new->status,"NEW");
			card_new->next=iterator->card;
			iterator->card = card_new;
			printf("aajung aici\n");
			break;
			}else{ fprintf(output, "The card already exists\n"); iesire=1; break;}
			
		}
		if(iterator->next==NULL)
		{
			break;
		}
		iterator=iterator->next;

	}
	if(iesire==1)
		{
		return;
		}
	struct LC* next_card=NULL;
	next_card=(LC*)calloc(1, sizeof(LC));
	next_card->card=(LSC*)calloc(1, sizeof(LSC));
	strcpy(next_card->card->expirare,expirare);
	strcpy(next_card->card->status,"NEW");
	next_card->card->card_number=card_number;
	strcpy(next_card->card->pin,pin);
	next_card->poz=poz;
	next_card->card->CVV=CVV;
	next_card->card->invalid_pin=0;
	next_card->card->balance=0;
	next_card->next=NULL;
	iterator->next=next_card;
	printf("am adaugat\n");

}

void delete_card(struct LC** card, long int card_number, int poz)  
{
	
	struct LC *iterator = (*card);
	while(iterator !=NULL && iterator->poz != poz)
	{
		printf("%d\n", poz);
		iterator = iterator -> next;
	}
	if (iterator == NULL) return;
	else if(iterator->poz==poz)
	{
		int ok=0;
		if(iterator->card->card_number==card_number)
			iterator->card=iterator->card->next;
		else
		while(iterator->card->next!=NULL&& ok==0)
		{
			if(iterator->card->next->card_number==card_number)
				if(iterator->card->next->next==NULL)
					{iterator->card->next=NULL;ok=1;}
				else
				{
					iterator->card->next=iterator->card->next->next;
					ok=1;
				}
				if(ok==0)
				iterator->card=iterator->card->next;
		}
		if(ok==1){
			free(iterator->card);
		}
	}
}

void show(struct LC* card,int nr_max_card,FILE *output)
{
	struct LC *iterator;
	iterator=card;

	
	if(card==NULL)
	{
		return;
	}
	
	int i;
	int poz=-1;
	while(iterator != NULL){
		 		for(i=poz+1; i< iterator->poz; i++ ){
		 		 	printare_lista(i, card, output);
		 		 }
	 	 		printare_lista(iterator->poz, card, output);
	 			poz=iterator->poz;
	 			
	 		
	  		iterator = iterator->next;

	  	}

}
void printare_card(struct LC **card,long int nr_card, FILE *output)
{
	struct LC *iterator = (*card);
		while(iterator!=NULL)
		{
			while(iterator->card != NULL){


				if(iterator->card->card_number==nr_card)
				{
				struct LSC* iterator_LSC=iterator->card;
				fprintf(output,"(card number: %ld, PIN: %s, ", iterator_LSC->card_number,iterator_LSC->pin);
				fprintf(output,"expiry date: %s, CVV: %d, ",iterator_LSC->expirare,iterator_LSC->CVV);
				fprintf(output,"balance: %d, status: %s, history: [", iterator_LSC->balance, iterator_LSC->status);
					
				while(iterator_LSC->istoric != NULL){
					printf("%s\n",iterator_LSC->istoric->operatie );
					fprintf(output, "(%s, %s)",iterator_LSC->istoric->success, iterator_LSC->istoric->operatie);
					if (iterator_LSC->istoric->next != NULL){
						fprintf(output, ", ");
						break;
					}
					printf("de 2 ori\n");
				}
				fprintf(output,"])");
				}
				iterator->card=iterator->card->next;
			}
			iterator=iterator->next;	
		}	
	
}
void printare_lista(int poz, struct LC* card, FILE *output)
{
	int exista=0, ok=0;
	struct LC* iterator;
	iterator=card;

	while(iterator!=NULL)
	{
				if(iterator->poz==poz)
				{

					exista=1;

					break;
				}
				if(iterator->card->expirare==NULL)
				{
					return;
				}
				iterator=iterator->next;
				
	}
	if(exista==1)
	{
			if(ok==0){
			fprintf(output,"pos%d: [",poz);
			
			struct LSC* iterator_LSC=iterator->card;
			while(iterator_LSC!=NULL )
			{
				fprintf(output, "\n" );
				
				fprintf(output,"(card number: %ld, PIN: %s, ", iterator_LSC->card_number,iterator_LSC->pin);
				fprintf(output,"expiry date: %s, CVV: %d, ",iterator_LSC->expirare,iterator_LSC->CVV);
				fprintf(output,"balance: %d, status: %s, history: [", iterator_LSC->balance, iterator_LSC->status);
				while(iterator_LSC->istoric != NULL){
					printf("%s\n",iterator_LSC->istoric->operatie );
					fprintf(output, "(%s, %s)",iterator_LSC->istoric->success, iterator_LSC->istoric->operatie);
					if (iterator_LSC->istoric->next != NULL){
						fprintf(output, ", ");
					}
					iterator_LSC->istoric=iterator_LSC->istoric->next;
				}	
				fprintf(output,"])");
				iterator_LSC=iterator_LSC->next;
				ok=1;	
				

			}

			if(ok==1) fprintf(output, "\n");
			fprintf(output,"]\n");
			return;
			}
		
		fprintf(output,"pos%d: []\n",poz);

		
	}else {
		fprintf(output,"pos%d: []\n",poz);
	}
}


void unblock_card(struct LC** card, long int card_number, char* success)
{
	struct  LC *iterator= (*card);
		while (iterator != NULL){
			while(iterator->card != NULL){
				if(iterator->card->card_number == card_number){
					if(strcmp(iterator->card->status, "LOCKED") ==0){
						strcpy(iterator->card->status, "ACTIVE");
						iterator->card->invalid_pin=0;
						strcpy(success, "SUCCESS");
						return;
					}else {
						strcpy(iterator->card->status, "ACTIVE");
						iterator->card->invalid_pin=0;
						strcpy(success, "SUCCESS");
						return;
					}
				}
				iterator->card = iterator ->card->next;
			}
			iterator=iterator->next;
		}
		strcpy(success, "FAIL");
}




 void insert_card(struct LC** card, long int card_number, char* pin, char* success, FILE *output)
 {
 	struct LC *iterator = (*card);
 	struct LSC *itcard = (iterator->card);
 	int ok=0;
 	while(iterator!=NULL && ok==0 && iterator->inserted==0)
		{
			while(iterator->card != NULL && ok==0){


				if(iterator->card->card_number==card_number)
				{
					ok=1;

					if(strcmp(iterator->card->pin, pin) == 0){
						if (strcmp(iterator->card->status, "NEW" ) == 0)
						{
							fprintf(output,"You must change your PIN.\n");
							strcpy(success, "SUCCESS");
							iterator->inserted=1;
							return;
							
						}
					}else{
						fprintf(output, "Invalid PIN\n" );
						strcpy(success, "FAIL");
						if(iterator->card->invalid_pin<3){
							iterator->card->invalid_pin++;

						} 
						if(iterator->card->invalid_pin==3){
							strcpy(iterator->card->status, "LOCKED");
							fprintf(output, "The card is blocked. Please contact the administrator.\n");

						}
						if (iterator->card->invalid_pin >3)
						{
							fprintf(output, "The card is blocked. Please contact the administrator.\n");
						}
						return;
					}		
				}
				iterator->card=iterator->card->next;
			}
			iterator=iterator->next;	
		}	
	strcpy(success, "FAIL");
}


void add_history(struct LC **card, long int card_number, char* success, char* operatie)  
{
	struct LC *iterator = (*card);
	while(iterator!=NULL)
		{
			while( iterator->card != NULL){

				if(iterator->card->card_number == card_number)
				{	
					struct history *hist = calloc(1, sizeof(struct history));
					strcpy(hist->operatie, operatie);
					strcpy(hist->success, success);	
					hist->next = iterator->card->istoric;
					iterator->card->istoric = hist;
					break;
				}

				iterator->card=iterator->card->next;
			}
			iterator=iterator->next;	
		}
	return;
}		


	
	


void recharge (struct LC **card, long int card_number, int sum, char* success, FILE *output)  
{
	struct LC *iterator = (*card);

	if(sum%10 == 0){
		while(iterator!=NULL)
		{
			while(iterator->card != NULL){
				if(iterator->card->card_number==card_number)
				{
					iterator->card->balance += sum;
					fprintf(output, "%d\n", iterator->card->balance);
					strcpy(success, "SUCCESS");
					iterator->inserted=0;
					return;
				}
		
				iterator->card=iterator->card->next;
			}
			iterator=iterator->next;	
		}	
	}else 
		{
			fprintf(output, "The added amount must be multiple of 10\n");
			strcpy(success, "FAIL");
			return;
		}
}

void cash_withdrawal(struct LC **card, long int card_number, int sum, char* success, FILE* output)
{
	struct LC *iterator = (*card);

	if(sum%10 == 0){
		while(iterator!=NULL)
		{
			while( iterator->card != NULL){

				if(iterator->card->card_number==card_number)
				{
					if(iterator->card->balance < sum){
						fprintf(output, "Insufficient funds.\n");
					}else{
							
						iterator->card->balance -= sum;
						fprintf(output, "%d\n", iterator->card->balance);
						strcpy(success, "SUCCESS");
						iterator->inserted=0;
						return;
					}
				}
		
				iterator->card=iterator->card->next;
			}
			iterator=iterator->next;	
		}	
	}else 
		{
			fprintf(output, "The requestes amount must be multiple of 10\n");
			strcpy(success, "FAIL");
			iterator->inserted=0;
			return;
		}
}

void balance_inquiry (struct LC **card, long int card_number, char* success, FILE* output)
{	
	struct  LC *iterator= (*card);
	while (iterator != NULL && iterator->inserted==1){
		while(iterator->card != NULL){
			if(iterator->card->card_number == card_number){
				fprintf(output, "%d\n", iterator->card->balance);
				iterator->inserted = 0;
				strcpy(success, "SUCCESS");
				return;
				}
			iterator->card = iterator ->card->next;
		}
		iterator=iterator->next;
	}
	strcpy(success, "FAIL");
}

void pin_change(struct LC **card, long int card_number, char* new_pin, char* success, FILE* output) 
{
		struct  LC *iterator= (*card);
		while (iterator != NULL){
			while(iterator->card != NULL){
				if(iterator->card->card_number == card_number){
					if(strlen(new_pin) != 4){
						fprintf(output, "Invalid PIN\n" );
						strcpy(success, "FAIL");
						return;
					}else{
						strcpy(iterator->card->pin, new_pin);
						strcpy(success, "SUCCESS");
						return;
					}
				}
				iterator->card = iterator ->card->next;
			}
			iterator=iterator->next;
		}

}

void cancel(struct LC **card, long int card_number, char* success) 
{
	struct  LC *iterator= (*card);
	if(iterator->inserted==1){
		iterator->inserted = 0;
		strcpy(success, "SUCCESS");
		return;
	}else strcpy(success, "FAIL");
	
}



void transfer_funds(struct LC** card, long int card_source, long int card_dest, int sum, char* success, FILE *output)
{
	struct LC *iterator=(*card);

	if(sum%10 != 0){
		fprintf(output, "The transferred amount must be multiple of 10" );
		iterator->inserted = 0;
		return;
	}

	cash_withdrawal(card, card_source, sum, success, output);
	if(strcmp(success, "SUCCESS")==0){
		recharge (card, card_dest, sum, success, output);
		return;
	}
	return;

}



 

