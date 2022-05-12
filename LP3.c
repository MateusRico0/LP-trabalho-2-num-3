#include <stdio.h>
#include <stdlib.h>


struct Pointers{
  int *pt;
  int qtd;
  struct Pointers *next;
};

//headers
void new_item(struct Pointers **node, int *p);
void increasing(struct Pointers **node, int *p);
void decreasing(struct Pointers **node, int *p);
struct Pointers *search_node(struct Pointers *node);
void delete_item(struct Pointers **node);




//                  ---- ------------------------- -----


int *malloc2(int x, struct Pointers **gc){
  int *v = (int*) malloc(sizeof(int)*x);
  new_item(&(*gc),v);
  increasing(&(*gc),v);
  return v;
}

void atrib2(int **p, int **p2, struct Pointers **gc){
  int *aux = *p;
  *p = *p2;
  increasing(&(*gc),*p2);
  decreasing(&(*gc),aux);
}

void free_pointer(int **p, struct Pointers **gc){
  delete_item(&(*gc));
  free(*p);
}


int main(){
  struct Pointers *gc = NULL;
  int *v = malloc2(1,&gc);
  *v = 10;
  printf("%d\n",*v);
  int *w = malloc2(1,&gc);
  atrib2(&w,&v,&gc);
}


//                  ---- ------------------------- -----




// linked list auxiliar functions

void new_item(struct Pointers **node, int *p){
  struct Pointers *new = (struct Pointers*) malloc(sizeof(struct Pointers));
  new->pt = p;
  new->next = *node;

  *node = new;
}

void increasing(struct Pointers **node, int *p){
  struct Pointers *aux = *node;
    while(aux!=NULL){
      if(aux->pt == p){
        aux->qtd++;
        printf("memoria: %ld com %d ponteiros.\n",(*node),(*node)->qtd++);
      }
      aux = aux->next;
    }
}

void decreasing(struct Pointers **node, int *p){
    while((*node)!=NULL){
      if((*node)->pt == p){
        (*node)->qtd--;
        delete_item(&(*node));
      }
      *node = (*node)->next;
    }
}

struct Pointers *search_node(struct Pointers *node){
    while(node!=NULL){
      if(node->qtd == 0){
        return node;
      }
      node = node->next;
    }
}

void delete_item(struct Pointers **node){
  struct Pointers *result = search_node(*node);
  struct Pointers *aux = *node;

  if(result!=NULL){
    if(*node == result){
      *node = result->next;
      printf("memoria %ld liberada\n",result);
      free(result);
    }else{
      while((aux != result) && (aux != NULL)){
        if(aux->next == result){
          aux->next = result->next;
          printf("memoria %ld liberada\n",result);
          free(result);
        }
        aux = aux->next;
      }
    }
  }
}
