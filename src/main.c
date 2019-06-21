#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <complex.h>

struct list
{
	char name[20];
	char func_name[20];
	char strt_name[20];
	struct list *next;
	struct list *prev;
};

void AddList(struct list** head, struct list** tail, char *n, char *f_n, char *s_n)
{
	if ((*head) == NULL)
	{
		(*head) = (struct list*)malloc(sizeof(struct list));
		for(int i =0; i<20; i++){
			(*head) -> name[i] = n[i];
			(*head) -> func_name[i] = f_n[i];
			(*head) -> strt_name[i] = s_n[i];
		}
		(*head) -> next = NULL;
		(*head) -> prev = NULL;
		(*tail) = (*head);
	}
	else
	{
		struct list *tmp = (struct list*)malloc(sizeof(struct list));
		for (int i =0; i<20; i++){
			tmp -> name[i] = n[i];
			tmp -> func_name[i] = f_n[i];
			tmp -> strt_name[i] = s_n[i];
		}
		tmp -> next = NULL;
		tmp -> prev = (*tail);
		(*tail) -> next = tmp;
		(*tail) = tmp;
	}
}
void OutList(struct list* head)
{
	struct list *tmp = head;
	int ch = 2;
	while(tmp!=NULL)
	{
		printf("%d. ", ch);
		printf("%s", tmp->name);
		tmp=tmp->next;
		ch+=1;
	}
}
int main()
{
	int list_count=0;
	struct list *head = NULL, *tail = NULL, *list_ptr;
	struct complex a, b, c;
	int ch=1;
	char *ptr_ch;
	void *ld;
	int *ptr;
	int i;
	char tmp_n[20], tmp_n_f[20], tmp_n_s[100];
	struct complex (*ptr_func)(struct complex, struct complex);
	a.a = 0;
	a.i = 0;
	b.a = 0;
	b.i = 0;
	while(ch>0){
		printf("\n1. Input elements\n");
		OutList(head);
		printf("%d. Add lib\n", list_count+2);
		printf("0. Exit\n");
		printf("Input: ");
		scanf("%d", &ch);
		if (ch >=  list_count + 2){
			fgets(tmp_n,20,stdin);
			printf("Input name of operation: ");
			fgets(tmp_n, 20, stdin);
			printf("Input name of function: ");
			fgets(tmp_n_f, 20, stdin);
			printf("Input directory to library: ");
			fgets(tmp_n_s, 100, stdin);
//			printf("%s",tmp_n_s);
			ptr_ch = strchr(tmp_n_s,'\n');
			*ptr_ch = '\0';
			ld = dlopen(tmp_n_s, RTLD_NOW);
			ptr_ch = strchr(tmp_n_f,'\n');
			*ptr_ch = '\0';
			if (ld==NULL) printf("\nDirectory doesn't exist\n");
			else if (!dlsym(ld,tmp_n_f)) printf("\nFunction doesn't exist\n");
			else{
				AddList(&head, &tail, tmp_n, tmp_n_f, tmp_n_s);
				list_count+=1;
				printf("\nOperation has been added\n");
			}
		}
		else if (ch>1){
			list_ptr = head;
			i = 1;
			while(i<ch-1){
				list_ptr = list_ptr->next;
				i++;
			}
			ld = dlopen(list_ptr->strt_name, RTLD_NOW);
			ptr_func = dlsym(ld, list_ptr->func_name);
			c = ptr_func(a,b);
			printf("\nResault: %d+%di\n", c.a, c.i);
			dlclose(ld);
		}
		else if (ch == 1){
			printf("Input first number: ");
			scanf("%d+%di", &a.a, &a.i);
			printf("Input second number: ");
			scanf("%d+%di", &b.a, &b.i);
		}
		printf("\n------------------------------\n");
	}
return 0;
}
