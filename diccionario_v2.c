#include "diccionario.h"

int main(){
    int res;
    char nom[TAM];
    FILE *diccionario;
    nomArch(nom);
    do {
        res = menuGeneral(&diccionario, nom);
        if (res == EMPTY){
            cierraArch(diccionario);
            return 0;
        }
    } while (res != 3);
    if (res != 3)
        cierraArch(diccionario);
    return 0;
}

int abreArch(FILE **diccionario, char *modo, char *nom){
    int res = 0;
    *diccionario = fopen(nom, modo);
    if (*diccionario)
        res = 1;
    return res;
}

int cierraArch(FILE *diccionario){
    fclose(diccionario);
    return 1;
}

void nomArch(char *nom){
    printf("Ingrese el nombre del diccionario: ");
    scanf("%s", nom);
    strcat(nom, ".dic");
    fflush(stdin);
}

int iniArch(FILE **diccionario){
    long head = EMPTY;
    fwrite(&head, sizeof(long), 1, *diccionario);
    return 1;
}

int creaDiccionario(FILE **diccionario, char *nom){
    int op, res, aux = diccRepetido(diccionario, nom);
    if (aux){
        switch (aux){
            case 1: res = abreArch(diccionario, "wb+", nom);
                    if (res){
                        iniArch(diccionario);
                        printf("Diccionario Creado\n");
                    }
                    else
                        printf("Error al abrir diccionario\n"); 
            break;
            case 2: res = abreArch(diccionario, "wb+", nom);
                    if (res)
                        printf("Diccionario Abiero\n");
                    else
                        printf("Error al abrir diccionario\n");
            break;
            case 3: printf("Saliendo..Adiós c:\n");
                    res = 0;
            break;
        }
    }
    else
        if (abreArch(diccionario, "wb+", nom)){
            iniArch(diccionario);
            printf("Diccionario Creado\n");
        }
        else
            printf("Error al abrir diccionario\n");
    return res;
}

int diccRepetido(FILE **diccionario, char *nom){
    int res = 0;
    if (abreArch(diccionario,"rb",nom)){
        cierraArch(*diccionario);
            printf("\tEl diccionario ya existe\n");
            printf("1. Sobreescribirlo\n");
            printf("2. Abrir el diccionario existente\n");
            printf("3. Salir\n");
            res = opValida(3);
    }
    return res;
}

long leeHead(FILE *diccionario){
    long head;
    fseek(diccionario, 0, SEEK_SET);
    fread(&head, sizeof(long), 1, diccionario);
    return head;
}

int opValida(int nMax){
    int res = 1;
    do{
        printf("Ingrese la opción que desea: ");
        scanf("%d", &res);
        if (res < 1 || res > nMax){
            printf("Opción inválida\n");
            res = 0;
        }
    } while (!res);
    return res;
}

int menuGeneral(FILE **diccionario, char *nom){
    int op, aux, res;
    op = res = 0;
    printf("\tMenú\n");
    printf("1. Crear Diccionario\n");
    printf("2. Abrir Diccionario\n");
    printf("3. Salir\n");
    op = opValida(3);
    switch (op){
        case 1: if (creaDiccionario(diccionario, nom))
                    res = 1;
        break;
        case 2: if (abreArch(diccionario, "rb+", nom))
                    res = 1;
                else
                    printf("El diccionario no existe\n");
        break;
        case 3: printf("Saliendo..Adiós c:\n");
        break;
    }
    if (res)
        do {
            aux = menuSeleccion(diccionario);
            if ( aux == EMPTY)
            return EMPTY;
        } while (aux);
    return op;
}

int menuSeleccion(FILE **diccionario){
    int op, aux, res = 0;
    long head = leeHead(*diccionario);
    do {
        printf("\tMenú de Selección\n");
        printf("1. Trabajar Entidades\n");
        printf("2. Trabajar Atributo\n");
        printf("3. Trabajar Dato\n");
        printf("4. Regresar\n");
        printf("5. Salir\n");
        op = opValida(5);
        switch (op){
            case 1: res = menuEnt(diccionario);
            break;
            case 2: res = menuAtr(diccionario);
            break;
            // Opción datos
            case 3: res = 1;
            break;
            case 5: printf("Saliendo..Adiós c:\n");
                    res = EMPTY;
            break;
        }
        if ( res == EMPTY )
            return res;
    } while ( op < 4 && res);
    return res;
}

int menuEnt(FILE **diccionario){
    int op, res = 0;
    do {
        printf("\tMenú Entidades\n");
        printf("1. Alta\n");
        printf("2. Baja\n");
        printf("3. Consulta\n");
        printf("4. Actualizar\n");
        printf("5. Reporte\n");
        printf("6. Regresar\n");
        printf("7. Salir\n");
        op = opValida(7);
        switch (op){
            case 1: res = altaEnt(diccionario);
            break;
            case 2: res = bajaEnt(diccionario);
            break;
            case 3: res = consultaEnt(*diccionario);
            break;
            case 4: res = actualizaEnt(diccionario);
            break;
            case 5: res = reporteEnt(*diccionario);
            break;
            case 7: printf("Saliendo..Adiós c:\n");
                    res = EMPTY;
            break;
        }
    } while (op < 6);
    return res;
}

int menuAtr(FILE **diccionario){
    int op, res;
    do {
        printf("\tMenú de atributos\n");
        printf("1. Alta\n");
        printf("2. Baja\n");
        printf("3. Consulta\n");
        printf("4. Actualizar\n");
        printf("5. Reporte\n");
        printf("6. Regresar\n");
        printf("7. Salir\n");
        op = opValida(7);
        switch (op){
            case 1: // res = altaEnt(diccionario);
                    res = 1;
            break;
            case 2: // res = bajaEnt(diccionario);
                    res = 1;
            break;
            case 3: // res = consultEnt(*diccionario);
                    res = 1;
            break;
            case 4: // res = actuEntidad(diccionario);
                    res = 1;
            break;
            case 5: // res = reporteEnt(*diccionario);
                    res = 1;
            break;
            case 7: printf("Saliendo..Adiós c:\n");
                    res = EMPTY;
            break;
        }
    } while (op < 6);
    return res;
}

ENT creaEntidad(){
    ENT nvo;
    char nom[TAM];
    nomEnt(nom);
    strcpy(nvo.nomEnt, nom);
    nvo.headAtr = nvo.headDato = nvo.link = EMPTY;
    return nvo;
}

ATR creaAtributo(){
    ATR nvo;
    char nom[TAM];
    nomAtr(nom);
    strcpy(nvo.nomAtr, nom);
    printf("\tTipo de atributo\n");
    printf("1 Char\n");
    printf("2. Entero\n");
    printf("3. Flotante\n");
    printf("4. Cadena\n");
    nvo.tipo = opValida(4);
    switch (nvo.tipo){
        case 1: nvo.tam = sizeof(char);
        break;
        case 2: nvo.tam = sizeof(int);
        break;
        case 3: nvo.tam = sizeof(float);
        break;
        case 4: nvo.tam = strlen(nvo.nomAtr);
        break;
    }
    nvo.link = EMPTY;
    return nvo;
}


void nomEnt(char *nom){
    printf("Ingrese el nombre de la entidad: ");
    scanf("%s", nom);
}

void nomAtr(char *nom){
    printf("Ingrese el nombre del atributo: ");
    scanf("%s", nom);
}

int altaEnt(FILE **diccionario){
    ENT nvo, aux;
    long posPrev, head;
    int res = 1;
    printf("\tAlta de entidad\n");
    head = leeHead(*diccionario);
    nvo = creaEntidad();
    // Si esta vacía
    if (head == EMPTY){
        fseek(*diccionario, 0, SEEK_END);
        head = ftell(*diccionario);
        fseek(*diccionario, 0, SEEK_SET);
        fwrite(&head, sizeof(long), 1, *diccionario);
        fwrite(&nvo, sizeof(ENT), 1, *diccionario);
    }
    else {
        // Buscar Repetido
        posPrev = EMPTY;
        while (head != EMPTY && res){
            posPrev = head;
            fseek(*diccionario, head, SEEK_SET);
            fread(&aux, sizeof(ENT), 1, *diccionario);
            if (!strcmp(aux.nomEnt, nvo.nomEnt))
                res = 0;
            head = aux.link;
        }
        // Si NO lo encontró
        if (res){
            fseek(*diccionario, 0, SEEK_END);
            aux.link = ftell(*diccionario);
            fseek(*diccionario, -sizeof(ENT), SEEK_CUR);
            fwrite(&aux, sizeof(ENT), 1, *diccionario);
            fwrite(&nvo, sizeof(ENT), 1, *diccionario);
            printf("Entidad dada de alta\n");
        }
        else {
            printf("Error la entidad ya existe\n");
        }
    }
    return res;
}

int bajaEnt(FILE **diccionario){
    int res = 0;
    long head, prev, aux2;
    char nom[TAM];
    ENT aux, ant;
    printf("\tBaja de entidad\n");
    nomEnt(nom);
    head = aux2 = leeHead(*diccionario);
    // Buscar Entidad
    while (head != EMPTY && !res){
        fseek(*diccionario, head, SEEK_SET);
        fread(&aux, sizeof(ENT), 1, *diccionario);
        if (!strcmp(aux.nomEnt, nom))
            res = 1;
        else {
            prev = head;
            head = aux.link;
        }
    }
    // Verificar que se encontró
    if (res){
        if (prev == aux2){
            fseek(*diccionario, 0 , SEEK_SET);
            aux2 = aux.link;
            fwrite(&aux2, sizeof(long), 1, *diccionario);
        }
        else {
                fseek(*diccionario, prev, SEEK_SET);
                fread(&ant, sizeof(ENT), 1, *diccionario);
                ant.link = aux.link;
                fseek(*diccionario, prev, SEEK_SET);
                fwrite(&ant, sizeof(ENT), 1, *diccionario);
            }
        printf("Entidad dada de baja\n");
    }
    else
        printf("Error al dar de baja\n");
    return res;
}

int consultaEnt(FILE *diccionario){
    ENT aux;
    long head;
    int res = 0;
    char nom[TAM];
    nomEnt(nom);
    head = leeHead(diccionario);
    while (head != EMPTY && !res){
        fseek(diccionario, head, SEEK_SET);
        fread(&aux, sizeof(ENT), 1, diccionario);
        head = aux.link;
        if (!strcmp(nom, aux.nomEnt)){
            printf("Nombre de la entidad: %s\n", aux.nomEnt);
            res = 1;
        }
    }
    if (!res)
        printf("No se encontró la entidad\n");
    return res;
}

int actualizaEnt(FILE **diccionario){
    int res = 0;
    long head = leeHead(*diccionario);
    char nom[TAM], nvoNom[TAM];
    ENT aux;
    printf("\tActualiza entidad\n");
    fseek(*diccionario, head, SEEK_SET);
    nomEnt(nom);
    head = leeHead(*diccionario);
    while (head != EMPTY && !res){
        fseek(*diccionario, head, SEEK_SET);
        fread(&aux, sizeof(ENT), 1, *diccionario);
        head = aux.link;
        if (!strcmp(nom, aux.nomEnt)){
            printf("Ingrese el NUEVO nombre de la entidad: ");
            scanf("%s", nvoNom);
            fseek(*diccionario, -sizeof(ENT), SEEK_CUR);
            strcpy(aux.nomEnt, nvoNom);
            fwrite(&aux, sizeof(ENT), 1, *diccionario);
            printf("Entidad actualizada de alta\n");
            res = 1;
        }
    }
    if (!res)
        printf("No se encontró la entidad");
    return res;
}

int reporteEnt(FILE *diccionario){
    int cont = 1;
    long head;
    ENT aux;
    printf("\t--- Reporte de Entidades ---\n");
    head = leeHead(diccionario);
    while (head != EMPTY){
        fseek(diccionario, head, SEEK_SET);
        fread(&aux, sizeof(ENT), 1, diccionario);
        printf("%d. %s\n", cont, aux.nomEnt);
        cont++;
        head = aux.link;
    }
    return 1;
}

int altaAtr(FILE **diccionario){
    int res;
    char ent[TAM], atr[TAM];
    ENT ent;
    nomEnt(ent);
    nomAtr(atr);

    return res;
}
int bajaAtr(FILE **diccionario){

}
int consultaAtr(FILE *diccionario){

}
int actualizaAtr(FILE **diccionario){

}
int reporteAtr(FILE *diccionario){

}
