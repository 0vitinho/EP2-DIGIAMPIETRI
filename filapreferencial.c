#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->idade = -1;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->ant;
	}
	printf("\n\n");
}


int consultarIdade(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, int idade){
	if (buscarID(f,id) != NULL || id<0 || idade<0)return false;
        PONT novo = (PONT) malloc (sizeof (ELEMENTO));
            novo->id=id;
            novo->idade=idade;
	
	if (novo->idade >= IDADEPREFERENCIAL){
		if (f->cabeca->prox == f->cabeca){
			novo->prox = f->cabeca;
			novo->ant = f->cabeca;
			f->cabeca->prox = novo;
			f->cabeca->ant = novo;
			return true;
		}
		
		else if (f->inicioNaoPref == f->cabeca && f->cabeca->prox != f->cabeca){
			novo->prox = f->cabeca;
			novo->ant = f->cabeca->ant;
			f->cabeca->ant->prox = novo;
			f->cabeca->ant = novo;
			return true;
		}
		
		else if (f->inicioNaoPref != f->cabeca && f->cabeca->prox != f->cabeca){
			novo->prox = f->inicioNaoPref;
			novo->ant = f->inicioNaoPref->ant;
			f->inicioNaoPref->ant->prox = novo;
			f->inicioNaoPref->ant = novo;
			return true;
		}
	}
	
	else if (novo->idade < IDADEPREFERENCIAL){
		if (f->cabeca->prox == f->cabeca){
			novo->prox = f->cabeca;
			novo->ant = f->cabeca;
			f->cabeca->prox = novo;
			f->cabeca->ant = novo;
			f->inicioNaoPref = novo;
			return true;
		}
		
		else if (f->inicioNaoPref == f->cabeca && f->cabeca->prox != f->cabeca){
			novo->prox = f->cabeca;
			novo->ant = f->cabeca->ant;
			f->cabeca->ant->prox = novo;
			f->cabeca->ant = novo;
			f->inicioNaoPref = novo;
			return true;
		}
		
		else if (f->inicioNaoPref != f->cabeca && f->cabeca->prox != f->cabeca){
			novo->prox = f->cabeca;
			novo->ant = f->cabeca->ant;
			f->cabeca->ant->prox = novo;
			f->cabeca->ant = novo;
			return true;
		}
	}

	return false;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){
	if (f->cabeca->prox == f->cabeca) return false;
		
	PONT primeira = f->cabeca->prox;
	*id = primeira->id;
	
	if(!f->cabeca->prox->prox){
		f->cabeca->prox = f->cabeca;
		f->cabeca->ant = f->cabeca;
		f->inicioNaoPref = f->cabeca;
		free (primeira);
		return true;
	}
	
	if (f->cabeca->prox == f->inicioNaoPref){
		f->cabeca->prox = f->cabeca->prox->prox;
		f->cabeca->prox->ant = f->cabeca;
		f->inicioNaoPref = f->cabeca->prox;
		free (primeira);
		return true;
	}
	
	else if(f->cabeca->prox != f->inicioNaoPref){
		f->cabeca->prox = f->cabeca->prox->prox;
		f->cabeca->prox->ant = f->cabeca;
		free (primeira);
		return true;
	}

	return false;
}


bool desistirDaFila(PFILA f, int id){
	PONT desistente = buscarID(f, id);
	if(!desistente) return false;

	desistente->ant->prox = desistente->prox;
	desistente->prox->ant = desistente->ant;
	free (desistente);
	return true;
}
