#include "diccionario.h"


int main(){
    int res = 0;
    FILE *diccionario;

    menuGeneral(&diccionario);

    closeFile(diccionario);
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
    scanf("%c[^\n]", nom);
    strcat(nom, ".dic");
}

int iniArch(FILE **diccionario){
    long aux = EMPTY;
    fwrite(&aux, sizeof(long), 1, *diccionario);
    long head = posIniLec(*diccionario);
    return 1;
}

int creaDiccionario(FILE **diccionario, char *nom){
    int res, op = diccRepetido(diccionario, nom);
    if (op)
        switch (opValida(3)){
            case 1: res = abreArch(diccionario, "wb+", nom);
                    if (res)
                        printf("Diccionario Creado\n");
                    else
                        printf("Error al abrir diccionario\n"); 
            break;
            case 2: res = abreArch(diccionario, "wb+", nom);
                    if (res)
                        printf("Diccionario Creado\n");
                    else
                        printf("Error al abrir diccionario\n");
            break;
            case 3: printf("Saliendo..Adiós c:\n");
            break;
        } 
    else
        if (abreArch(diccionario, "wb+", nom))
            printf("Diccionario Creado\n");
        else
            printf("Error al abrir diccionario\n");
    return res;
}

int diccRepetido(FILE **diccionario, char *nom){
    int res = 0;
    if (abreArch(diccionario,"rb",nom)){
        cierraArch(diccionario);
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

void menuGeneral(FILE **diccionario){
    int op, aux, res;
    char nom[TAM];
    printf("\tMenú\n");
    printf("1. Crear Diccionario\n");
    printf("2. Abrir Diccionario\n");
    printf("3. Salir\n");
    nomArch(nom);
    switch (opValida(3)){
        case 1: if(creaDiccionario(diccionario, nom))
                    do {
                        aux = menuSeleccion(diccionario);
                    } while (aux);
        break;
        case 2: if (abreArch(diccionario, "rb+", nom))
                    do {
                        aux = menuSeleccion(diccionario);
                    } while (aux);
                else
                    printf("El diccionario no existe\n");
        break;
        case 3: printf("Saliendo..Adiós c:\n");
        break;
    }
}

int menuSeleccion(FILE **diccionario){
    int op, aux, res = 0;
    long head = posIniLec(*diccionario);
    printf("Cabecera: %ld\n", head);
    printf("\tMenú de Selección\n");
    printf("1. Trabajar Entidades\n");
    printf("2. Trabajar Atributo\n");
    printf("3. Trabajar Dato\n");
    printf("4. Regresar\n");
    switch (!opValida(4)){
        case 1: do {
                    aux = menuEntidad(diccionario);
                } while (aux);
                res = 1;
        break;
        case 2: do {
                    aux = menuAtributo(diccionario);
                } while (aux);
                res = 1;
        break;
        // Opción datos
        case 3: 
                res = 1;
        break;
        case 4: printf("Saliendo..Adiós c:\n");
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
    switch (!opValida(6)){
        case 1: res = altaEnt(diccionario);
                if (res)
                    printf("Entidad dada de alta\n");
                else
                    printf("Error\n");
        break;
        case 2: res = bajaEnt(diccionario);
                if (res)
                    printf("Entidad dada de baja\n");
                else
                    printf("Error\n");
        break;
        case 3: res = consultEnt(*diccionario);
        break;
        case 4: res = actuEntidad(diccionario);
                if (res)
                    printf("Entidad actualizada\n");
                else
                    printf("Error\n");
        break;
        case 5: res = reporteEnt(*diccionario);
        break;
        case 6: printf("Saliendo..Adiós:)\n");
        break;
    }
    return res;
}
