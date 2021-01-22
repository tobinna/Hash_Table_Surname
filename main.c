#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 200
#define TABLE_SIZE 30001

struct record {
  int id, age;
	
	char deposition[MAX_BUFFER];
  char surname[MAX_BUFFER]; 
  char forename[MAX_BUFFER];
  char type[MAX_BUFFER];
  char gender[MAX_BUFFER];
  char nationality[MAX_BUFFER];
  char religion[MAX_BUFFER];
  char occupation[MAX_BUFFER];
};

typedef struct Node Node;

struct Node{
    struct  record after;
    Node* next;
};

void add_node(Node** list, struct record d){
    Node* newNode = (Node*)malloc( sizeof( Node ) ); 
    newNode->after = d;
    newNode->next = *list;
    *list=newNode;
    free(newNode);
}

struct Node htable[TABLE_SIZE];

void inittable(){
  struct Node * h = (struct Node *)malloc(sizeof(struct Node *));
}

int hash(char* s){
  int hash = 0;
  while(*s){
    hash = (hash + *s);
    
    s++;
    }
  return (hash % TABLE_SIZE);
}

int
next_field( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	
	for(;;) {
		
		buf[i] = fgetc(f);

		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }

		if(buf[i]==',' && !quoted) { break; }

		if(feof(f) || buf[i]=='\n') { end=1; break; } 

		if( i<max-1 ) { ++i; } 
	}

	buf[i] = 0;
	return end;
}

void insertKey(struct record  n){
    
    char * yup = (char*)malloc( sizeof( char ) );
    yup = n.surname;
    Node * temp = (Node*)malloc( sizeof( Node ) );
    Node * next = (Node*)malloc( sizeof( Node ) );
        
    int index,i=0,hkey;
    hkey=hash(yup);
    
    index=hkey%TABLE_SIZE;

    if(htable[index].next == NULL){
      
      add_node(&htable[index].next, n);      
 
      return;
       
       }
     else if (htable[index].next != NULL){
       
       temp->next = NULL;
       temp = htable[index].next;
       char * yeow = (char*)malloc( sizeof( char ) );
       struct record * now = (struct record *)malloc( sizeof( struct record * ) );
       now = &temp->after;
       yeow = now->surname;
      
        while (strcmp(yup, yeow) != 0){
           
          temp = htable[index+i].next;
            if(htable[index+i].next == NULL){      
             add_node(&htable[index+i].next, n);  
             free(temp);    
             return;
       
            }
                     
           now = &temp->after;
           yeow = now->surname;
           i++;
    
       }
        
         while(temp->next != NULL){
          
          temp = temp->next;
     
         }
        
        add_node(&temp->next, n);  
     }
 
    if(i == TABLE_SIZE)printf("\nelement cannot be inserted\n");
}



void fetch_record (  FILE *csv, struct record p) {
	char buf[MAX_BUFFER];

	next_field( csv, buf, MAX_BUFFER );      
	p.id = atoi(buf);                       

	next_field( csv, p.deposition, MAX_BUFFER );  
	next_field( csv, p.surname, MAX_BUFFER ); 
  
	next_field( csv, p.forename, MAX_BUFFER );

	
	next_field( csv, buf, MAX_BUFFER );
	p.age = atoi(buf);   
  next_field( csv, p.type, MAX_BUFFER );
	next_field( csv, p.gender, MAX_BUFFER );               
	next_field( csv, p.nationality, MAX_BUFFER );
	next_field( csv, p.religion, MAX_BUFFER );
  next_field( csv, p.occupation, MAX_BUFFER );

	
	insertKey(p);

}

void print_list (Node* list){
    Node* node = (Node*)malloc( sizeof( Node ) ); 
    node = list;
    struct record  p = list->after;

    
    while(list!=NULL){
        p = list->after;
        printf("%i\t|\t%s\t|\t%s\t|\t%s\t|\t%i\t|\t", 
			  p.id, p.deposition, p.surname, p.forename, p.age );
	    
      	printf("%s\t|\t%s\t|\t\t%s\t|\t%s\t|\t%s\n\n",p.type, p.gender, p.nationality, p.religion, p.occupation);
        list = list->next;
       

    }
    
}


void printdisplay(){
 int i, j=0;
 
  printf("\nELEMENTS IN THIS TABLE ARE \n");
  printf("\nID\t|\tDEPOSITION\t|\tSURNAME\t|\tFORENAME\t|\tAGE\t|\tTYPE\t|\tGENDER\t|\tNATIONALITY\t|\tRELIGION\t|\tOCCUPATION\n");
  for(i=0;i< TABLE_SIZE; i++){
      if (htable[i].next == NULL){
      printf("INDEX: %i \nNO RECORD HERE\n\n", i);
    }
    else{
    printf("INDEX: %i \n", j);
    print_list(htable[i].next);
    }
  j++;
  }
}


void findlist(char * cur){
  int index,i,hkey;
  hkey = hash(cur);
  

  printf("\nThe name key: %d The name %s\n", hkey, cur);
     
  index=hkey%TABLE_SIZE;

  if(htable[index].next == NULL){
      printf("THIS NAME IS NOT HERE");
      return;
    }

  else if(htable[index].next != NULL){
       Node * temp = (Node*)malloc( sizeof( Node ) );
      // Node * next = (Node*)malloc( sizeof( Node ) );
       
       temp->next = NULL;
       temp = htable[index].next;
       char * yeow = (char*)malloc( sizeof( char ) );
       struct record * now = (struct record *)malloc( sizeof( struct record * ) );
       //now = &temp->after;
       yeow = now->surname;
       
      
      while (htable[index+i].next !=NULL ){
          temp = htable[index+i].next;
          now = &temp->after;
          yeow = now->surname;
            if(strcmp(cur, yeow) == 0){      
             print_list(htable[index+i].next);  
             free(temp);  
              
             return;
       
            }
                 
           
           i++;
            

       }
       if(strcmp(cur, yeow) == 0){      
             print_list(htable[index+i].next);  
             free(temp);    
             return;
       }
     

  }


  printf("\nTHIS RECORD DOESNT EXIST");



}

void print_pokemon( struct record *p ) {

	printf("ID: %i Deposition ID: %s Surname: %s Forename: %s Age: %i",p->id, p->deposition, p->surname, p->forename, p->age );
	
	printf("Person Type: %s Gender: %s Nationality: %s Religion: %s Occupation: %s\n\n",p->type, p->gender, p->nationality, p->religion, p->occupation);
	
}

int main ( int argc, char *argv[] ) {
  FILE* f = (FILE*)malloc( sizeof( FILE ) ); 
	inittable();
	struct record * pArray = (struct record*)malloc( sizeof( struct record ) );	
	struct record p;
  
	f = fopen("people.csv", "r");


	if(!f) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}
	
	fetch_record( f, p );

	int nbPokemons = 0;
	while(!feof(f)) {
		fetch_record( f, pArray[nbPokemons] );
		nbPokemons++;
	}

char * current = (char*)malloc( sizeof( char ) );

while(strcmp(current, "quit") != 0){
  printf("\nWhat Surname would you like the records for?(Type quit to finish)\n");
  gets(current);
  if(strcmp(current, "quit") == 0){return 0;}
  printf("\nID\tDEPOSITION\tSURNAME\tFORENAME\t\tAGE\tTYPE\tGENDER\tNATIONALITY\tRELIGION\tOCCUPATION\n");
  findlist(current);
}

free(f);
free(pArray);

return 0;

}
