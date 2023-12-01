#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct HeaderNode {
	char info;
	int num;
	int weight;
	struct ListNode* list;
	struct HeaderNode* next;
} HeaderNode;

typedef struct ListNode {
	char info;
	struct ListNode* next;
} ListNode;

typedef struct StackNode {
	char info;
	struct StackNode *next;
} StackNode;

void push(StackNode** stack, char x) {
	StackNode* p;
	p = malloc(sizeof(StackNode));
	if (!p) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	p->info = x;
	p->next = *stack;
	*stack = p;
	return;
}

char pop(StackNode** stack) {
	StackNode* p;
	char x;
	if (*stack == NULL) {
		printf("Underflow\n");
		exit(1);
	}
	else {
		p = *stack;
		*stack = p->next;
		x = p->info;
		free(p);
		return x;
	}
}

int stackEmpty(StackNode** stack) {
	if (*stack == NULL) return 1;
	else return 0;
}

HeaderNode* initGraphStdIn() {
	char c; int flag = 1, i = 1;
	HeaderNode *graph = NULL, *tail = NULL, *hnode = NULL, *h;
	ListNode *lnode = NULL, *p;
	while (!((c = getchar()) == '\n' && flag)) {
		if (c == '\n') flag = 1;
		else {
			if (c >= 'a' && c <= 'z') {
				if (flag) {
					hnode = malloc(sizeof(HeaderNode));
					if (!hnode) {
						printf("MEM_GRESKA\n");
						exit(0);
					}
					hnode->info = c;
					hnode->num = i++;
					hnode->list = NULL;
					hnode->next = NULL;
					if (!graph) graph = hnode;
					else tail->next = hnode;
					tail = hnode;
				}
				else {
					for (h = graph; h->next != NULL; h = h->next) {
						if (h->info == c) {
							lnode = malloc(sizeof(ListNode));
							if (!lnode) {
								printf("MEM_GRESKA\n");
								exit(0);
							}
							lnode->info = tail->info;
							lnode->next = NULL;
							if (!h->list) h->list = lnode;
							else {
								for (p = h->list; p->next != NULL; p = p->next);
								p->next = lnode;
							}
							break;
						}
					}
				}
			}
			else {
				if (c >= 'A' && c <= 'Z') hnode->weight = 1;
				if (c == '+' || c == '-') hnode->weight = 3;
				if (c == '*') hnode->weight = 10;
				if (c == '/') hnode->weight = 23;
			}
			flag = 0;
		}
	}
	return graph;
}

HeaderNode* initGraphFile(FILE *in) {
	char c; int flag = 1, i = 1;
	HeaderNode *graph = NULL, *tail = NULL, *hnode = NULL, *h;
	ListNode *lnode = NULL, *p;
	while ((c = fgetc(in)) != EOF) {
		if (c == '\n') flag = 1;
		else {
			if (c >= 'a' && c <= 'z') {
				if (flag) {
					hnode = malloc(sizeof(HeaderNode));
					if (!hnode) {
						printf("MEM_GRESKA\n");
						exit(0);
					}
					hnode->info = c;
					hnode->num = i++;
					hnode->list = NULL;
					hnode->next = NULL;
					if (!graph) graph = hnode;
					else tail->next = hnode;
					tail = hnode;
				}
				else {
					for (h = graph; h->next != NULL; h = h->next) {
						if (h->info == c) {
							lnode = malloc(sizeof(ListNode));
							if (!lnode) {
								printf("MEM_GRESKA\n");
								exit(0);
							}
							lnode->info = tail->info;
							lnode->next = NULL;
							if (!h->list) h->list = lnode;
							else {
								for (p = h->list; p->next != NULL; p = p->next);
								p->next = lnode;
							}
							break;
						}
					}
				}
			}
			else {
				if (c >= 'A' && c <= 'Z') hnode->weight = 1;
				if (c == '+' || c == '-') hnode->weight = 3;
				if (c == '*') hnode->weight = 10;
				if (c == '/') hnode->weight = 23;
			}
			flag = 0;
		}
	}
	return graph;
}

void addBranch(HeaderNode* graph, char from, char to) {
	HeaderNode *h = graph;
	while (h) {
		if (h->info == from) break;
		h = h->next;
	}
	ListNode *l, *node = malloc(sizeof(ListNode));
	if (!node) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	node->info = to;
	node->next = NULL;
	if (h->list == NULL) h->list = node;
	else {
		for (l = h->list; l->next != NULL; l = l->next);
		l->next = node;
	}
	return;
}

void addNode(HeaderNode* graph, char c) {
	HeaderNode *h, *node;
	for (h = graph; h->next; h = h->next);
	node = malloc(sizeof(HeaderNode));
	if (!node) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	node->info = c;
	node->weight = 0;
	node->list = NULL;
	node->next = NULL;
	if (!graph) {
		graph = node;
		node->num = 1;
	}
	else {
		h->next = node;
		node->num = h->num + 1;
	}
}

void addExp(HeaderNode* graph, char* exp) {
	char *c; int flag = 1, i = 1;
	HeaderNode *hnode = NULL, *h;
	ListNode *lnode, *p;
	for (c = exp; *c != '\0'; c++) {
		if (*c >= 'a' && *c <= 'z') {
			if (flag) {
				addNode(graph, *c);
				for (hnode = graph; hnode->next; hnode = hnode->next);
				flag = 0;
			}
			else {
				for (h = graph; h->next != NULL; h = h->next) {
					if (h->info == *c) {
						lnode = malloc(sizeof(ListNode));
						if (!lnode) {
							printf("MEM_GRESKA\n");
							exit(0);
						}
						lnode->info = hnode->info;
						lnode->next = NULL;
						if (!h->list) h->list = lnode;
						else {
							for (p = h->list; p->next != NULL; p = p->next);
							p->next = lnode;
						}
						break;
					}
				}
			}
		}
		else {
			if (*c >= 'A' && *c <= 'Z') hnode->weight = 1;
			if (*c == '+' || *c == '-') hnode->weight = 3;
			if (*c == '*') hnode->weight = 10;
			if (*c == '/') hnode->weight = 23;
		}
	}
}

void deleteBranch(HeaderNode* graph, char from, char to) {
	HeaderNode *h = graph;
	while (h) { //pronalazi izlazni cvor
		if (h->info == from) break;
		h = h->next;
	}
	ListNode *l = h->list, *prev = NULL;
	while (l) {
		if (l->info == to) { //pronalazi ulazni cvor
			if (l == h->list) h->list = l->next;
			else prev->next = l->next;
			free(l);
			break;
		}
		prev = l;
		l = l->next;
	}
	return;
}

HeaderNode* deleteNode(HeaderNode* graph, char c) {
	HeaderNode *h = graph, *prev = NULL, *q;
	while (h) {
		if (h->info == c) {
			ListNode *l = h->list;
			while (l) { //brise listu izlaznih grana
				ListNode* p = l;
				l = l->next;
				free(p);
			}
			//brise sam cvor
			if (h == graph) graph = h->next;
			else prev->next = h->next;
			q = h;
			h = h->next;
			free(q);
		}
		else {
			ListNode *l = h->list;
			//brise ulazne grane
			while (l) {
				if (l->info == c) {
					deleteBranch(graph, h->info, c);
					break;
				}
				l = l->next;
			}
			prev = h;
			h = h->next;
		}
	}
	return graph;
}

void deleteGraph(HeaderNode* graph) {
	while (graph) {
		HeaderNode* p = graph;
		graph = graph->next;
		ListNode *q = p->list;
		while (q) {
			ListNode* r = q;
			q = q->next;
			free(r);
		}
		free(p);
	}
}

void printGraph(HeaderNode* graph) {
	for (HeaderNode* h = graph; h; h = h->next) {
		printf("%c: ", h->info);
		for (ListNode* l = h->list; l; l = l->next)
			if (l->next != NULL) printf("%c, ", l->info);
			else printf("%c", l->info);
		printf("\n");
	}
	return;
}

HeaderNode* findNode(HeaderNode* graph, char c) {
	HeaderNode* h;
	for (h = graph; h; h = h->next)
		if (h->info == c) return h;
	return NULL;

}

void printTransitBranches(HeaderNode* graph, char c) {
	int visit[26] = { 0 }, flag[26] = { 0 }; char node;
	StackNode *stack = NULL; HeaderNode* h; ListNode* l;
	h = findNode(graph, c);
	for (l = h->list; l; l = l->next) {
		flag[l->info - 'a'] = 1;
		push(&stack, l->info);
	}
	while (!stackEmpty(&stack)) {
		node = pop(&stack);
		if (flag[node - 'a'] && visit[node - 'a'])
			printf("%c -> %c\n", c, node);
		visit[node - 'a'] = 1;
		h = findNode(graph, node);
		for (l = h->list; l; l = l->next)
			push(&stack, l->info);
	}
	return;
}

HeaderNode* findNodeWithoutInputEdges(HeaderNode* graph) {
	HeaderNode *h, *p; ListNode *l; int flag;
	for (h = graph; h; h = h->next) { //cvor koji proveravamo
		flag = 1;
		for (p = graph; p; p = p->next) { //cvor sa kojim proveravamo postojanje grane
			if (p != h) {
				for (l = p->list; l; l = l->next)
					if (l->info == h->info) {
						flag = 0;
						break;
					}
			}
		}
		if (flag) return h;
	}
	return NULL;
}

char* findAllPredecessors(HeaderNode* graph, char node) {
	int i = 0; char *predecessors = NULL;
	HeaderNode *h; ListNode *l;
	for (h = graph; h; h = h->next) {
		if (h->info != node) {
			for (l = h->list; l; l = l->next)
				if (l->info == node) {
					predecessors = realloc(predecessors, (i + 1) * sizeof(char));
					if (!predecessors) {
						printf("MEM_GRESKA\n");
						exit(0);
					}
					predecessors[i] = h->info;
					i++;
				}
		}
	}
	predecessors = realloc(predecessors, (i + 1) * sizeof(char));
	if (!predecessors) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	predecessors[i] = '\0';
	return predecessors;
}

void** criticalPath(HeaderNode* graph) {
	int *EST, *LST, *L, n = 1; char *predecessors = NULL;
	HeaderNode *h, *node, *pre; ListNode *l;
	char* topsort = NULL;
	for (h = graph; h->next; h = h->next) {
		topsort = realloc(topsort, n * sizeof(char));
		if (!topsort) {
			printf("MEM_GRESKA\n");
			exit(0);
		}
		topsort[n - 1] = h->info;
		n++;
	}
	topsort = realloc(topsort, (n + 1) * sizeof(char));
	if (!topsort) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	topsort[n - 1] = h->info;
	topsort[n] = '\0';
	EST = calloc(n, sizeof(int));
	if (!EST) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	LST = calloc(n, sizeof(int)); for (int i = 0; i < n; i++) LST[i] = INT_MAX;
	if (!LST) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	L = calloc(n, sizeof(int));
	if (!L) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	EST[0] = 0;
	for (int i = 1; i < n; i++) {
		node = findNode(graph, topsort[i]);
		predecessors = findAllPredecessors(graph, topsort[i]);
		for (char *c = predecessors; *c != '\0'; c++) {
			pre = findNode(graph, *c);
			if (EST[pre->num - 1] + pre->weight > EST[i])
				EST[i] = EST[pre->num - 1] + pre->weight;
		}
		if (predecessors) free(predecessors); predecessors = NULL;
	}
	LST[n - 1] = EST[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		node = findNode(graph, topsort[i]);
		if (node->list == NULL)
			LST[node->num - 1] = EST[n - 1] + (findNode(graph, topsort[n - 1]))->weight - node->weight;
		for (l = node->list; l; l = l->next) {
			h = findNode(graph, l->info);
			if (LST[h->num - 1] - node->weight < LST[node->num - 1])
				LST[node->num - 1] = LST[h->num - 1] - node->weight;
		}
	}
	for (int i = 0; i < n; i++) L[i] = LST[i] - EST[i];
	void** table = malloc(4 * sizeof(void*));
	if (!table) {
		printf("MEM_GRESKA\n");
		exit(0);
	}
	table[0] = topsort; table[1] = EST; table[2] = LST; table[3] = L;
	return table;
}

void printSchedule(HeaderNode* graph, void** table) {
	char* nodes = table[0]; int *EST = table[1], *LST = table[2], *L = table[3];
	int n = 1; for (HeaderNode* h = graph; h->next; h = h->next) n++;
	int time = 0;
	for (int i = 0; i < n; i++)
		if (L[i] == 0) time += (findNode(graph, nodes[i]))->weight;
	for (int i = 0; i <= time; i++) {
		printf("\n%d: ", i);
		for (int j = 0; j < n; j++)
			if (i >= EST[j] && i <= LST[j]) printf("%c ", nodes[j]);
	}

	return;
}

int main(int argc, const char **argv) {
	int i, n = 0, time, *EST = NULL, *LST = NULL, *L = NULL;
	char u, from, to, c, str[4], *exp, *file_name, *nodes = NULL;
	HeaderNode* graph = NULL;
	FILE *in = NULL;
	void** table = NULL;
	printf("Meni:\na) Unos programskog segmenta sa standardnog ulaza\nb) Unos programskog segmenta iz datoteke\nc) Ispis grafa\n"
		"d) Dodavanje grane\ne) Dodavanje cvora tj novog izraza\nf) Brisanje grane\ng) Brisanje cvora\n"
		"h) Odrediti najkrace trajanje programskog segmenta\ni) Odstampati cvorove koji se nalaze na kriticnom putu\n"
		"j) Prikazati razlicite moguce rasporede svih operacija tako da ukupno trajanje bude najkrace\n"
		"k) Odediti tranzitivnih grane odredjenog cvora\nl) Kraj programa\n");
	while (1) {
		printf("\nOdaberite stavku iz menija: "); 
		scanf(" %c%*c", &u);
		switch (u) {
		case 'a': { //unos sa standardnog ulaza
			printf("Unesite programski segment\n");
			graph = initGraphStdIn();
			printf("Programski segment je unet.\n");
			n = 1; for (HeaderNode* h = graph; h->next; h = h->next) n++;
			table = criticalPath(graph);
			nodes = table[0]; EST = table[1]; LST = table[2]; L = table[3];
			break;
		}
		case 'b': { //unos iz datoteke
			printf("Unesite ime datoteke: ");
			file_name = NULL; i = 0;
			while ((c = getchar()) != '\n') {
				file_name = realloc(file_name, (i + 1) * sizeof(char));
				if (!file_name) {
					printf("MEM_GRESKA\n");
					exit(0);
				}
				file_name[i] = c;
				i++;
			}
			file_name = realloc(file_name, (i + 1) * sizeof(char));
			if (!file_name) {
				printf("MEM_GRESKA\n");
				exit(0);
			}
			file_name[i] = '\0';
			in = fopen(file_name, "r");
			if (!in) {
				printf("ARG_GRESKA");
				exit(0);
			}
			free(file_name);
			graph = initGraphFile(in);
			printf("Programski segment je unet.\n");
			n = 1; for (HeaderNode* h = graph; h->next; h = h->next) n++;
			table = criticalPath(graph);
			nodes = table[0]; EST = table[1]; LST = table[2]; L = table[3];
			break;
		}
		case 'c': { //ispis grafa
			printGraph(graph);
			break;
		}
		case 'd': { //dodavanje grane
			printf("Unesite odakle dokle grana ide: ");
			scanf("%c %c", &from, &to);
			addBranch(graph, from, to);
			printf("Grana je dodata.\n");
			break;
		}
		case 'e': { //dodavanje cvora/izraza
			printf("Unesite novi izraz: ");
			exp = NULL; i = 0;
			while ((c = getchar()) != '\n') {
				exp = realloc(exp, (i + 1) * sizeof(char));
				if (!exp) {
					printf("MEM_GRESKA\n");
					exit(0);
				}
				exp[i] = c;
				i++;
			}
			exp = realloc(exp, (i + 1) * sizeof(char));
			if (!exp) {
				printf("MEM_GRESKA\n");
				exit(0);
			}
			exp[i] = '\0';
			addExp(graph, exp);
			printf("Izraz je dodat.\n");
			free(exp);
			break;
		}
		case 'f': { //brisanje grane
			printf("Unesite odakle dokle grana ide: ");
			scanf("%c %c", &from, &to);
			deleteBranch(graph, from, to);
			printf("Grana je obrisana.\n");
			break;
		}
		case 'g': { //brisanje cvora
			printf("Unesite cvor: ");
			scanf("%c", &c);
			deleteNode(graph, c);
			printf("Cvor je obrisan.\n");
			break;
		}
		case 'h': { //odrediti najkrace trajanje programskog segmenta
			time = 0;
			for (int i = 0; i < n; i++)
				if (L[i] == 0) time += (findNode(graph, nodes[i]))->weight;
			printf("\nNajkrace trajanje segmenta: %d\n", time);
			break;
		}
		case 'i': { //odstampati kritican put
			printf("Kritican put: ");
			for (int i = 0; i < n; i++)
				if (L[i] == 0) printf("%c ", nodes[i]);
			printf("\n");
			break;
		}
		case 'j': { //razliciti rasporedi operacija
			printSchedule(graph, table);
			printf("\n");
			break;
		}
		case 'k': { //tranzitivne grane nekog cvora
			printf("Unesite cvor: ");
			scanf("%c", &c);
			printTransitBranches(graph, c);
			break;
		}
		case 'l': { //kraj programa
			printf("Kraj programa\n");
			exit(0);
		}
		default: {
			printf("Uneta opcija ne postoji u meniju, pokusajte ponovo\n");
		}
		}
	}
	for (i = 0; i < 4; i++) free(table[i]); free(table);
	deleteGraph(graph);
	if (!in) fclose(in);
	return 0;
}