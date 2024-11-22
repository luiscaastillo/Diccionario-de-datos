#include "diccionario.h"


int main(){
    int res;
    char nom[TAM];
    FILE *diccionario;
    nomArch(nom);
    do {
        res = menuGeneral(&diccionario, nom);
    } while (res != 3);
    if (res == 1 || res == 2)
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
    long aux = EMPTY;
    fwrite(&aux, sizeof(long), 1, *diccionario);
    long head = leeHead(*diccionario);
    return 1;
}

int creaDiccionario(FILE **diccionario, char *nom){
    int op, res, aux = diccRepetido(diccionario, nom);
    if (aux){
        op = opValida(3);
        switch (op){
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
    int op, aux, band;
    op = band = 0;
    printf("\tMenú\n");
    printf("1. Crear Diccionario\n");
    printf("2. Abrir Diccionario\n");
    printf("3. Salir\n");
    op = opValida(3);
    switch (op){
        case 1: if(creaDiccionario(diccionario, nom))
                    band = 1;
        break;
        case 2: if (abreArch(diccionario, "rb+", nom))
                    band = 1;
                else
                    printf("El diccionario no existe\n");
        break;
        case 3: printf("Saliendo..Adiós c:\n");
        break;
    }
    if (band)
        do {
            aux = menuSeleccion(diccionario);
        } while (aux);
    return op;
}

int menuSeleccion(FILE **diccionario){
    int op, aux, res = 0;
    long head = leeHead(*diccionario);
    printf("Cabecera: %ld\n", head);
    printf("\tMenú de Selección\n");
    printf("1. Trabajar Entidades\n");
    printf("2. Trabajar Atributo\n");
    printf("3. Trabajar Dato\n");
    printf("4. Regresar\n");
    op = opValida(4);
    switch (op){
        case 1: do {
                    aux = menuEnt(diccionario);
                } while (aux);
                res = 1;
        break;
        case 2: do {
                    // aux = menuAtr(diccionario);
                    aux = 1;
                } while (aux); // !(aux)
                res = 1;
        break;
        // Opción datos
        case 3: 
                res = 1;
        break;
    }   
    return res;
}

int menuEnt(FILE **diccionario){
    int op, res = 0;
    printf("\tMenú Entidades\n");
    printf("1. Alta\n");
    printf("2. Baja\n");
    printf("3. Consulta\n");
    printf("4. Actualizar\n");
    printf("5. Reporte\n");
    printf("6. Regresar\n");
    op = opValida(6);
    switch (op){
        case 1: 
                // res = altaEnt(diccionario);
                res = 1;
                if (res)
                    printf("Entidad dada de alta\n");
                else
                    printf("Error\n");
        break;
        case 2: 
                // res = bajaEnt(diccionario);
                res = 1;
                if (res)
                    printf("Entidad dada de baja\n");
                else
                    printf("Error\n");
        break;
        case 3: 
                // res = consultEnt(*diccionario);
                res = 1;
        break;
        case 4: 
                // res = actuEntidad(diccionario);
                res = 1;
                if (res)
                    printf("Entidad actualizada\n");
                else
                    printf("Error\n");
        break;
        case 5: 
                // res = reporteEnt(*diccionario);
                res = 1;
        break;
    }
    return res;
}

int menuAtr(FILE **diccionario){
    int op, res;
    printf("\tMenú de atributos\n");
    printf("1. Alta\n");
    printf("2. Baja\n");
    printf("3. Consulta\n");
    printf("4. Actualizar\n");
    printf("5. Reporte\n");
    printf("6. Regresar\n");
    op = opValida(6);
    switch (op){
        case 1: 
                // res = altaEnt(diccionario);
                res = 1;
                if (res)
                    printf("Atributo dado de alta\n");
                else
                    printf("Error\n");
        break;
        case 2: 
                // res = bajaEnt(diccionario);
                res = 1;
                if (res)
                    printf("Atributo dado de baja\n");
                else
                    printf("Error\n");
        break;
        case 3: 
                // res = consultEnt(*diccionario);
                res = 1;
        break;
        case 4: 
                // res = actuEntidad(diccionario);
                res = 1;
                if (res)
                    printf("Atributo actualizado\n");
                else
                    printf("Error\n");
        break;
        case 5: 
                // res = reporteEnt(*diccionario);
                res = 1;
        break;
    }
    return res;
}

ENT creaEntidad(){
    ENT nvo;
    char nom[TAM];
    nomEntidad(nom);
    strcpy(nvo.nomEnt, nom);
    nvo.headAtr = nvo.headDato = nvo.link = EMPTY;
    return nvo;
}

void nomEnt(char *nom){
    printf("Ingrese el nombre de la entidad: ");
    scanf("%s", nom);
}

void muestraEnt(FILE *diccionario, char *nomEnt){
    ENT aux;
    long head, link;
    int band = 0;
    head = leeHead(diccionario);
    fseek(diccionario, head, SEEK_SET);
    do {
        fread(&aux, sizeof(ENT), 1, diccionario);
        if(!strcmp(nomEnt, aux.nomEnt)){
            printf("Nombre: %s\n", aux.nomEnt);
            band = 1;
        }
        fseek(diccionario, aux.link, SEEK_SET);
    } while(aux.link != EMPTY);
    if (!band)
        printf("No se encontró la entidad\n");
}

