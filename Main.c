#include <stdio.h>
#include <stdlib.h>

struct uzel {
	int data;
	struct uzel* levy;
	struct uzel* pravy;
	struct uzel* rodic;
	char barva;
}typedef uzel;

void balance(uzel** korenZac, uzel* novyList);
void printTree(uzel* koren);
void deletionBalance(uzel** korenZac, uzel* list);

void pravaRotace(uzel** korenZacatecni, uzel* actKoren) { //nk 15 act 20
	if (actKoren->levy == NULL || actKoren == NULL)
		return;
	uzel* novyKoren = actKoren->levy;
	actKoren->levy = novyKoren->pravy; 
	if(novyKoren->pravy != NULL)
		novyKoren->pravy->rodic = actKoren;
	novyKoren->rodic = actKoren->rodic;
	novyKoren->pravy = actKoren;

	if (novyKoren->rodic == NULL)
		*korenZacatecni = novyKoren;
	else if (actKoren == actKoren->rodic->levy)
		actKoren->rodic->levy = novyKoren;
	else actKoren->rodic->pravy = novyKoren;

	actKoren->rodic = novyKoren;
}

void levaRotace(uzel** korenZacatecni, uzel* actKoren) {
	if (actKoren->pravy == NULL || actKoren == NULL)
		return;
	uzel* novyKoren = actKoren->pravy;
	actKoren->pravy = novyKoren->levy;
	if (novyKoren->levy != NULL)
		novyKoren->levy->rodic = actKoren;
	novyKoren->rodic = actKoren->rodic;
	novyKoren->levy = actKoren;

	if (novyKoren->rodic == NULL)
		*korenZacatecni = novyKoren;
	else if (actKoren == actKoren->rodic->pravy)
		actKoren->rodic->pravy = novyKoren;
	else actKoren->rodic->levy = novyKoren;

	actKoren->rodic = novyKoren;
}

uzel* createList(int value) {
	uzel* vys = (uzel*)malloc(sizeof(uzel));
	vys->data = value;
	vys->levy = NULL;
	vys->pravy = NULL;
	vys->rodic = NULL;
	vys->barva = 'r';
	return vys;
}

void insertion(uzel** korenZacatecni, int data) {
	uzel* vys = createList(data);
	if (*korenZacatecni == NULL) {
		vys->barva = 'b';
		*korenZacatecni = vys;
	}
	else {
		uzel* akt = *korenZacatecni;
		uzel* rodic = NULL;
		while (akt != NULL) {
			rodic = akt;
			if (vys->data > akt->data)
				akt = akt->pravy;
			else akt = akt->levy;
		}
		vys->rodic = rodic;
		if (rodic->data > data)
			rodic->levy = vys;
		else rodic->pravy = vys;
		balance(korenZacatecni, vys);
	}		
}

void balance(uzel** korenZac, uzel* novyList) {
	uzel* stryc = NULL;
	while (novyList != *korenZac && novyList != (*korenZac)->levy && novyList != (*korenZac)->pravy && novyList->rodic->barva == 'r') {

		if (novyList->rodic == novyList->rodic->rodic->pravy)
			stryc = novyList->rodic->rodic->levy;
		else stryc = novyList->rodic->rodic->pravy;

		if (stryc != NULL && stryc->barva == 'r') {
			stryc->barva = novyList->rodic->barva = 'b';
			novyList->rodic->rodic->barva = 'r';
			novyList = novyList->rodic->rodic;
		}
		else{
			if (novyList->rodic != NULL && novyList->rodic->rodic != NULL && novyList->rodic == novyList->rodic->rodic->levy && novyList == novyList->rodic->levy) { // leva-leva rotace
				pravaRotace(korenZac, novyList->rodic->rodic);
				char color = novyList->rodic->barva;
				novyList->rodic->barva = novyList->rodic->rodic->barva;
				novyList->rodic->rodic->barva = color;
			}
			else if (novyList->rodic != NULL && novyList->rodic->rodic != NULL && novyList->rodic == novyList->rodic->rodic->pravy && novyList == novyList->rodic->pravy) { // prava-prava rotace
				levaRotace(korenZac, novyList->rodic->rodic);
				char color = novyList->rodic->barva;
				novyList->rodic->barva = novyList->rodic->rodic->barva;
				novyList->rodic->rodic->barva = color;
			}
			else if (novyList->rodic != NULL && novyList->rodic->rodic != NULL && novyList->rodic == novyList->rodic->rodic->levy && novyList == novyList->rodic->pravy) { //leva-prava rotace
				levaRotace(korenZac, novyList->rodic);
				pravaRotace(korenZac, novyList->rodic->rodic);
				char color = novyList->rodic->barva;
				novyList->rodic->barva = novyList->rodic->rodic->barva;
				novyList->rodic->rodic->barva = color;
			}
			else if (novyList->rodic != NULL && novyList->rodic->rodic != NULL && novyList->rodic == novyList->rodic->rodic->pravy && novyList == novyList->rodic->levy) { //prava-leva rotace
				pravaRotace(korenZac, novyList->rodic);
				levaRotace(korenZac, novyList->rodic->rodic);
				char color = novyList->rodic->barva;
				novyList->rodic->barva = novyList->rodic->rodic->barva;
				novyList->rodic->rodic->barva = color;
			}
		}
	}
	(*korenZac)->barva = 'b';
}

uzel* findList(uzel* koren, int value) {
	if (koren == NULL) {
		printf("Node was not found");
		return NULL;
	}
	if (koren->data < value)
		return findList(koren->pravy, value);
	if (koren->data > value)
		return findList(koren->levy, value);
	if (koren->data == value) {
		printf("Ur node has been found!");
		return koren;
	}
}

uzel* findLastLeft(uzel* koren) {
	uzel* tmp = koren;
	while (tmp->levy != NULL)
		tmp = tmp->levy;
	return tmp;
}

uzel* findLastRight(uzel* koren) {
	uzel* tmp = koren;
	while (tmp->pravy != NULL)
		tmp = tmp->pravy;
	return tmp;
}

void deletion(uzel** korenZac, int value) {
	uzel* mazList = findList(*korenZac, value);
	printf("mazlist data: %d\n", mazList->data);
	uzel* tmp = NULL;

	if (mazList == NULL) {
		printf("The node was not found");
		return;
	}
	
	//pokud je koren zac
	if (mazList == *korenZac) {
		if (mazList->levy == NULL && mazList->pravy == NULL) {
			free(mazList);
			return;
		}
		else if (mazList->levy != NULL && mazList->pravy == NULL) {
			mazList->levy->rodic = NULL;
			*korenZac = mazList->levy;
			(*korenZac)->barva = 'b';
			mazList->levy = NULL;
			free(mazList);
		}
		else if (mazList->levy == NULL && mazList->pravy != NULL) {
			mazList->pravy->rodic = NULL;
			*korenZac = mazList->pravy;
			(*korenZac)->barva = 'b';
			mazList->pravy = NULL;
			free(mazList);
		}
		else if (mazList->levy != NULL && mazList->pravy != NULL) {
			tmp = findLastLeft(mazList->pravy);
			tmp->rodic->levy = NULL;
			tmp->rodic = NULL;
			tmp->levy = mazList->levy;
			tmp->pravy = mazList->pravy;
			*korenZac = tmp;
			(*korenZac)->barva = 'b';
			mazList->levy = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
	}
	else if (mazList->pravy == NULL && mazList->levy == NULL && mazList->barva == 'r') { 
		if (mazList == mazList->rodic->pravy) {
			mazList->rodic->pravy = NULL;
			mazList->rodic = NULL;
			free(mazList);
			printf("list je vymazan\n");
		}
		else {
			mazList->rodic->levy = NULL;
			mazList->rodic = NULL;
			free(mazList);
		}
	}
	else if (mazList->pravy == NULL && mazList->levy == NULL && mazList->barva == 'b') {
		if (mazList == mazList->rodic->levy) {
			mazList->rodic->levy = NULL;
			mazList->rodic->barva = 'b';
			mazList->rodic = NULL;
			free(mazList);
		}
		else {
			mazList->rodic->pravy = NULL;
			mazList->rodic->barva = 'b';
			mazList->rodic = NULL;
			free(mazList);
		}
	}
	else if (mazList->pravy != NULL && mazList->levy == NULL && mazList->barva == 'r') { 
		if (mazList == mazList->rodic->pravy) {
			mazList->rodic->pravy = mazList->pravy;
			mazList->pravy->rodic = mazList->rodic;
			mazList->rodic = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
		else {
			mazList->rodic->levy = mazList->pravy;
			mazList->pravy->rodic = mazList->rodic;
			mazList->rodic = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
	}
	else if (mazList->pravy != NULL && mazList->levy == NULL && mazList->barva == 'b') {
		if (mazList == mazList->rodic->pravy) {
			mazList->rodic->pravy = mazList->pravy;
			mazList->pravy->rodic = mazList->rodic;
			mazList->pravy->barva = 'b';
			mazList->rodic = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
		else {
			mazList->rodic->levy = mazList->pravy;
			mazList->pravy->rodic = mazList->rodic;
			mazList->pravy->barva = 'b';
			mazList->rodic = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
	}
	else if (mazList->pravy == NULL && mazList->levy != NULL && mazList->barva == 'r') { 
		if(mazList == mazList->rodic->pravy) {
			mazList->rodic->pravy = mazList->levy;
			mazList->levy->rodic = mazList->rodic;
			mazList->rodic = NULL;
			mazList->levy = NULL;
			free(mazList);
		}
		else {
			mazList->rodic->levy = mazList->levy;
			mazList->levy->rodic = mazList->rodic;
			mazList->rodic = NULL;
			mazList->levy = NULL;
			free(mazList);
		}
	}
	else if (mazList->pravy == NULL && mazList->levy != NULL && mazList->barva == 'b') {
		if (mazList == mazList->rodic->pravy) {
			mazList->rodic->pravy = mazList->levy;
			mazList->levy->rodic = mazList->rodic;
			mazList->levy->barva = 'b';
			mazList->rodic = NULL;
			mazList->levy = NULL;
			free(mazList);
		}
		else {
			mazList->rodic->levy = mazList->levy;
			mazList->levy->rodic = mazList->rodic;
			mazList->levy->barva = 'b';
			mazList->rodic = NULL;
			mazList->levy = NULL;
			free(mazList);
		}
	}
	else if (mazList->pravy != NULL && mazList->levy != NULL && mazList->barva == 'r') { 
		if (mazList == mazList->rodic->pravy) {
			if (mazList->pravy->levy != NULL) {
				tmp = findLastLeft(mazList->pravy);
				tmp->pravy = mazList->pravy;
				tmp->pravy->rodic = tmp;
				tmp->rodic->levy = NULL;
			}
			else {
				tmp = mazList->pravy;
			}
			tmp->rodic = mazList->rodic;
			mazList->rodic->pravy = tmp;
			tmp->levy = mazList->levy;
			mazList->levy->rodic = tmp;
			tmp->pravy = mazList->pravy;
			mazList->pravy->rodic = tmp;
			mazList->rodic = NULL;
			mazList->levy = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
		else {
			if (mazList->pravy->levy != NULL) {
				tmp = findLastLeft(mazList->pravy);
				tmp->pravy = mazList->pravy;
				tmp->pravy->rodic = tmp;
				tmp->rodic->levy = NULL;
			}
			else {
				tmp = mazList->pravy;
			}
			tmp->rodic = mazList->rodic;
			mazList->rodic->levy = tmp;
			tmp->levy = mazList->levy;
			mazList->levy->rodic = tmp;
			tmp->pravy = mazList->pravy;
			mazList->pravy->rodic = tmp;
			mazList->rodic = NULL;
			mazList->levy = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
	}
	else if (mazList->pravy != NULL && mazList->levy != NULL && mazList->barva == 'b') {
		if (mazList == mazList->rodic->pravy) {
			if (mazList->pravy->levy != NULL) {
				tmp = findLastLeft(mazList->pravy);
				tmp->pravy = mazList->pravy;
				tmp->pravy->rodic = tmp;
				tmp->rodic->levy = NULL;
			}
			else {
				tmp = mazList->pravy;
			}
			tmp->rodic = mazList->rodic;
			mazList->rodic->pravy = tmp;
			tmp->levy = mazList->levy;
			mazList->levy->rodic = tmp;
			tmp->pravy = mazList->pravy;
			mazList->pravy->rodic = tmp;
			tmp->barva = 'b';
			mazList->rodic = NULL;
			mazList->levy = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
		else {
			if (mazList->pravy->levy != NULL) {
				tmp = findLastLeft(mazList->pravy);
				tmp->pravy = mazList->pravy;
				tmp->pravy->rodic = tmp;
				tmp->rodic->levy = NULL;
			}
			else {
				tmp = mazList->pravy;
			}
			tmp->rodic = mazList->rodic;
			mazList->rodic->levy = tmp;
			tmp->levy = mazList->levy;
			tmp->levy->rodic = tmp;
			tmp->barva = 'b';
			mazList->rodic = NULL;
			mazList->levy = NULL;
			mazList->pravy = NULL;
			free(mazList);
		}
	}
}

void printTree(uzel* koren) {
	if (koren != NULL) {
		printf("%d%c ", koren->data, koren->barva);
		printTree(koren->levy);
		printTree(koren->pravy);
	}
}

void deleteTree(uzel* koren) {
	if (koren != NULL) {
		deleteTree(koren->levy);
		deleteTree(koren->pravy);
		free(koren);
	}
}

int main(int argc, char** argv) {
	uzel* koren = NULL;   
	char key = '0';
	int inputed = 0;
	for (int i = 1; i < argc; i++)
	{
		int value = atoi(argv[i]);
		insertion(&koren, value);
	}
	while (key != 'q') {
		scanf("%c", &key);
		switch (key) {
		case 'q':
			printf("Quiting the program");
			break;
		case 'p':
			printTree(koren);
			break;
		case 'i':
			printf("Enter the inserted number");
			scanf("%d", &inputed);
			insertion(&koren, inputed);
			break;
		case 'f':
			printf("What number are u looking for?");
			scanf("%d", &inputed);
			findList(koren, inputed);
			break;
		case 'd':
			printf("What number do u want to delete?");
			scanf("%d", &inputed);
			deletion(&koren, inputed);
			break;
		}
	}
	deleteTree(koren);
	return 0;
}