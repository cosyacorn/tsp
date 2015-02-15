#include<stdio.h>
#include<stdlib.h>

typedef struct points_s
{
  struct points_s *next;
  struct points_s *prev;
  int data;
}cities;

cities* alloc_city(int new_city){
  
  cities *c;
  c=malloc(sizeof(int));
  
  c->next = NULL;
  c->prev = NULL;
  c->data = new_city;
  return c;
}

void append(cities *h, int new_city)
{
     while(h->next != NULL){
    h=h->next;
  }
  cities *w = alloc_city(new_city);
  h->next=w;
  w->prev=h;
}



void print_list(cities *c)
{
  while(c != NULL)
    {
      printf("%d\n", c->data);
      c=c->next;
    }
}



cities *delete(cities *c, int search){

  cities *ahead, *behind, *del;

  cities *temp = c;

  while(temp!=NULL){
    if(temp->data==search){

      //delete head
      if(temp->prev==NULL){
	ahead=temp->next;
	ahead->prev=NULL;
	c = ahead;
      }
      //delete tail
      else if(temp->next==NULL){
	behind=temp->prev;
	behind->next=NULL;
      }
      //delete from middle
      else{
	ahead = temp->next;
	behind = temp->prev;
	if(ahead!=NULL){
	  ahead->prev = behind;
	}
	if(behind!=NULL){
	  behind->next = ahead;
	}
      }
      del=temp;
      //printf("  %s\n", del->data);
      //free(del);
      //should free the node but everytime i try it gives a seg fault or different error
    }
    temp=temp->next;
  }
  return c;
}


