#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char tipo;
    int id;
} Peca;

Peca fila[5];
int frente = 0, tras = 0, qtdFila = 0;
Peca pilha[3];
int topo = 0;
int proximoID = 1;

int filaVazia() { return qtdFila == 0; }
int filaCheia() { return qtdFila == 5; }
int pilhaVazia() { return topo == 0; }
int pilhaCheia() { return topo == 3; }

Peca gerarPeca() {
    char tipos[7] = {'I','O','T','L','J','S','Z'};
    Peca p;
    p.tipo = tipos[rand() % 7];
    p.id = proximoID++;
    return p;
}

void inicializarFila() {
    for (int i = 0; i < 5; i++) {
        fila[i] = gerarPeca();
        qtdFila++;
        tras = (tras + 1) % 5;
    }
}

void enqueue(Peca p) {
    if (filaCheia()) return;
    fila[tras] = p;
    tras = (tras + 1) % 5;
    qtdFila++;
}

Peca dequeue() {
    Peca vazio = {'-', 0};
    if (filaVazia()) return vazio;
    Peca p = fila[frente];
    frente = (frente + 1) % 5;
    qtdFila--;
    return p;
}

void inicializarPilha() { topo = 0; }

void push(Peca p) {
    if (pilhaCheia()) return;
    pilha[topo++] = p;
}

Peca pop() {
    if (pilhaVazia()) {
        Peca vazio = {'-',0};
        return vazio;
    }
    return pilha[--topo];
}

void mostrarFila() {
    printf("FILA: ");
    int idx = frente;
    for (int i = 0; i < qtdFila; i++) {
        printf("[%c|%d] ", fila[idx].tipo, fila[idx].id);
        idx = (idx + 1) % 5;
    }
    printf("\n");
}

void mostrarPilha() {
    printf("PILHA: ");
    for (int i = 0; i < topo; i++)
        printf("[%c|%d] ", pilha[i].tipo, pilha[i].id);
    printf("\n");
}

void trocarFrenteTopo() {
    if (filaVazia() || pilhaVazia()) {
        printf("Troca impossivel!\n");
        return;
    }
    int idx = frente;
    Peca temp = fila[idx];
    fila[idx] = pilha[topo - 1];
    pilha[topo - 1] = temp;
}

void trocarTres() {
    if (topo != 3 || qtdFila < 3) {
        printf("Troca impossivel!\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int idx = (frente + i) % 5;
        Peca temp = fila[idx];
        fila[idx] = pilha[i];
        pilha[i] = temp;
    }
}

int main() {
    srand(time(NULL));
    inicializarFila();
    inicializarPilha();

    int op;
    do {
        printf("\n1 - Jogar peça\n");
        printf("2 - Enviar peça da fila para a pilha\n");
        printf("3 - Usar peça da pilha\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (op == 1) {
            if (!filaVazia()) {
                dequeue();
                enqueue(gerarPeca());
            }
        }

        else if (op == 2) {
            if (!filaVazia() && !pilhaCheia()) {
                push(dequeue());
                enqueue(gerarPeca());
            }
        }

        else if (op == 3) {
            if (!pilhaVazia()) {
                pop();
            }
        }

        else if (op == 4) {
            trocarFrenteTopo();
        }

        else if (op == 5) {
            trocarTres();
        }

        mostrarFila();
        mostrarPilha();

    } while (op != 0);

    return 0;
}



