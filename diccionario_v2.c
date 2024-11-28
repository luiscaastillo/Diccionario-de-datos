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
        printf("2. Trabajar Atributos\n");
        printf("3. Trabajar Dato\n");
        printf("4. Reporte General\n");
        printf("5. Regresar\n");
        printf("6. Salir\n");
        op = opValida(5);
        switch (op){
            case 1: res = menuEnt(diccionario);
            break;
            case 2: res = menuAtr(diccionario);
            break;
            case 3: res = menuDat(diccionario);
            break;
            case 4: res = reporteGen(*diccionario);
            break;
            case 6: printf("Saliendo..Adiós c:\n");
                    res = EMPTY;
            break;
        }
        if (res == EMPTY)
            return res;
    } while ( op < 4 && res);
    return res;
}

int menuEnt(FILE **diccionario){
    int op, res, again = 0;
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
            case 1: do {
                        res = altaEnt(diccionario);
                        printf("Otro? (1. Si | 0. No): ");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 2: do {
                        res = bajaEnt(diccionario);
                        printf("Otro? (1. Si | 0. No): ");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 3: do {
                        res = consultaEnt(*diccionario);
                        printf("Otro? (1. Si | 0. No): ");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 4: do {
                        res = actualizaEnt(diccionario);
                        printf("Otro? (1. Si | 0. No): ");
                        scanf("%d", &again);
                    } while (again);
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
    int op, res, again = 0;
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
            case 1: do {
                        res = altaAtr(diccionario);
                        printf("Otro? (1. Si | 0. No): ");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 2: do {
                        res = bajaAtr(diccionario);
                        printf("Otro? (1. Si | 0. No): ");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 3: do {
                        res = consultaAtr(*diccionario);
                        printf("Otro? (1. Si | 0. No): ");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 4: do {
                        res = actualizaAtr(diccionario);
                        printf("Otro? (1. Si | 0. No): ");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 5: res = reporteAtr(*diccionario);
            break;
            case 7: printf("Saliendo..Adiós c:\n");
                    res = EMPTY;
            break;
        }
    } while (op < 6);
    return res;
}

int menuDat(FILE **diccionario){
    int op, res, again = 0;
    do {
        printf("\tMenú de datos\n");
        printf("1. Alta\n");
        printf("2. Baja\n");
        printf("3. Consulta\n");
        printf("4. Actualizar\n");
        printf("5. Reporte\n");
        printf("6. Regresar\n");
        printf("7. Salir\n");
        op = opValida(7);
        switch (op){
            case 1: do {
                        res = altaDat(diccionario);
                        printf("Otro? (1. Si | 2. No): \n");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 2: do {
                        res = bajaDat(diccionario);
                        printf("Otro? (1. Si | 2. No): \n");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 3: do {
                        res = consultaDat(*diccionario);
                        printf("Otro? (1. Si | 2. No): \n");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 4: do {
                        res = actualizaDat(diccionario);
                        printf("Otro? (1. Si | 2. No): \n");
                        scanf("%d", &again);
                    } while (again);
            break;
            case 5: res = reporteGen(*diccionario);
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
    printf("1. Char\n");
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
        case 4: nvo.tam = TAM;
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
    printf("\t--- Alta de entidad ---\n");
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
    printf("\t--- Baja de entidad ---\n");
    nomEnt(nom);
    head = prev = aux2 = leeHead(*diccionario);
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
        // Si es el primero
        if (prev == head){
            fseek(*diccionario, 0, SEEK_SET);
            fwrite(&aux.link, sizeof(long), 1, *diccionario);
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
    printf("\t--- Consulta entidad ---\n");
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
    printf("\t--- Actualiza entidad ---\n");
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
            printf("Entidad actualizada\n");
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
    long posPrev, headArch, headAtr, posEnt;
    int res = 0, res2 = 1;
    char nomEntidad[TAM];
    ATR nvo, aux;
    ENT ent;
    printf("\t--- Alta de atributo ---\n");
    headArch = leeHead(*diccionario);
    // Busca Entidad
    nomEnt(nomEntidad);
    while (headArch != EMPTY && !res){
        posEnt = headArch;
        fseek(*diccionario, headArch, SEEK_SET);
        fread(&ent, sizeof(ENT), 1, *diccionario);
        headArch = ent.link;
        if (!strcmp(nomEntidad, ent.nomEnt))
            res = 1;
    }
    // Si la encuentra
    if (res){
        headAtr = ent.headAtr;
        nvo = creaAtributo();
        // Si no hay atributos
        if (headAtr == EMPTY){
            fseek(*diccionario, 0, SEEK_END);
            headAtr = ftell(*diccionario);
            fwrite(&nvo, sizeof(ATR), 1, *diccionario);
            ent.headAtr = headAtr;
            fseek(*diccionario, posEnt, SEEK_SET);
            fwrite(&ent, sizeof(ENT), 1, *diccionario);
            printf("Atributo dado de alta\n");
        }
        else {
            // Buscar Repetido
            posPrev = EMPTY;
            while (headAtr != EMPTY && res){
                posPrev = headAtr;
                fseek(*diccionario, headAtr, SEEK_SET);
                fread(&aux, sizeof(ATR), 1, *diccionario);
                if (!strcmp(aux.nomAtr, nvo.nomAtr))
                    res2 = 0;
                headAtr = aux.link;
            }
            // Si NO hay repetido
            if (res2){
                fseek(*diccionario, 0, SEEK_END);
                aux.link = ftell(*diccionario);
                fwrite(&nvo, sizeof(ATR), 1, *diccionario);
                fseek(*diccionario, posPrev, SEEK_SET);
                fwrite(&aux, sizeof(ATR), 1, *diccionario);
                printf("Atributo dado de alta\n");
            }
            else {
                printf("Error el atributo ya existe\n");
            }
        }
    }
    else 
        printf("No se encontró la entidad\n");
    return res;
}

int bajaAtr(FILE **diccionario){
    long prevAtr, headArch, headAtr;
    int res = 0, res2 = 1;
    char nomEntidad[TAM], nomAtributo[TAM];
    ATR atr, ant;
    ENT ent;
    printf("\t--- Baja de atributo ---\n");
    // Busca Entidad
    headArch = leeHead(*diccionario);
    nomEnt(nomEntidad);
    while (headArch != EMPTY && !res){
        fseek(*diccionario, headArch, SEEK_SET);
        fread(&ent, sizeof(ENT), 1, *diccionario);
        if (!strcmp(ent.nomEnt, nomEntidad))
            res = 1;
        else
            headArch = ent.link;
    }
    // Si la encuentra
    if (res){
        prevAtr = EMPTY;
        headAtr = ent.headAtr;
        nomAtr(nomAtributo);
        while (headAtr != EMPTY && !res){
            fseek(*diccionario, headAtr, SEEK_SET);
            fread(&atr, sizeof(ATR), 1, *diccionario);
            if (!strcmp(nomAtributo, atr.nomAtr))
                res2 = 1;
            else {
                prevAtr = headAtr;
                headAtr = atr.link;
            }
        }
        if (res2){
            if (prevAtr == ent.headAtr){
                fseek(*diccionario, headArch, SEEK_SET);
                ent.headAtr = EMPTY;
                fwrite(&ent, sizeof(ENT), 1, *diccionario);
            }
            else {
                fseek(*diccionario, prevAtr, SEEK_SET);
                fread(&ant, sizeof(ATR), 1, *diccionario);
                ant.link = atr.link;
                fseek(*diccionario, prevAtr, SEEK_SET);
                fwrite(&ant, sizeof(ATR), 1, *diccionario);
            }
            printf("Atributo dado de baja\n");
        }
        else 
            printf("Error al dar de baja el atributo\n");
    }
    else 
        printf("No se encontró la entidad\n");
    return res;
}

int consultaAtr(FILE *diccionario){
    long headArch, headAtr, posEnt;
    int res, res2;
    char nomEntidad[TAM], nomAtributo[TAM];
    ATR atr;
    ENT ent;
    res = res2 = 0;
    printf("\t--- Consulta atributo ---\n");
    headArch = leeHead(diccionario);
    // Busca Entidad
    nomEnt(nomEntidad);
    while (headArch != EMPTY && !res){
        posEnt = headArch;
        fseek(diccionario, headArch, SEEK_SET);
        fread(&ent, sizeof(ENT), 1, diccionario);
        headArch = ent.link;
        if (!strcmp(nomEntidad, ent.nomEnt))
            res = 1;
    }
    // Si la encuentra
    if (res){
        headAtr = ent.headAtr;
        nomAtr(nomAtributo);
        while (headAtr != EMPTY && res){
            fseek(diccionario, headAtr, SEEK_SET);
            fread(&atr, sizeof(ATR), 1, diccionario);
            headAtr = atr.link;
            if (!strcmp(nomAtributo, atr.nomAtr)){
                printf("Nombre del atributo: %7s\tTipo: %2d\n", atr.nomAtr, atr.tipo);
                res2 = 1;
            }
        }
        if (!res2)
           printf("No se encontró el atributo\n");
    }
    else 
        printf("No se encontró la entidad\n");
    return res;
}

int actualizaAtr(FILE **diccionario){
    long headArch, headAtr, posEnt;
    int res, res2;
    char nomEntidad[TAM], nomAtributo[TAM];
    ATR atr, nvo;
    ENT ent;
    res = res2 = 0;
    printf("\t--- Actualiza atributo ---\n");
    headArch = leeHead(*diccionario);
    // Busca Entidad
    nomEnt(nomEntidad);
    while (headArch != EMPTY && !res){
        posEnt = headArch;
        fseek(*diccionario, headArch, SEEK_SET);
        fread(&ent, sizeof(ENT), 1, *diccionario);
        headArch = ent.link;
        if (!strcmp(nomEntidad, ent.nomEnt))
            res = 1;
    }
    // Si la encuentra
    if (res){
        headAtr = ent.headAtr;
        nomAtr(nomAtributo);
        while (headAtr != EMPTY && res){
            fseek(*diccionario, headAtr, SEEK_SET);
            fread(&atr, sizeof(ATR), 1, *diccionario);
            headAtr = atr.link;
            if (!strcmp(nomAtributo, atr.nomAtr)){
                printf("\tIngrese los datos del NUEVO atributo\n");
                nvo = creaAtributo();
                fseek(*diccionario, -sizeof(ATR), SEEK_CUR);
                fwrite(&nvo, sizeof(ATR), 1, *diccionario);
                printf("Atributo actualizado\n");
                res2 = 1;
            }
        }
        if (!res2)
            printf("Error al actualizar atributo\n");
    }
    else 
        printf("No se encontró la entidad\n");
    return res;
}

int reporteAtr(FILE *diccionario){
    int res = 0, cont = 1;
    char nomEntidad[TAM];
    long posEnt, head;
    ENT ent;
    ATR atr;
    printf("\t--- Reporte de Atributos ---\n");
    nomEnt(nomEntidad);
    printf("Atributos de \"%s\":\n", nomEntidad);
    // Busca entidad
    posEnt = leeHead(diccionario);
    while (posEnt != EMPTY && !res){
        fseek(diccionario, posEnt, SEEK_SET);
        fread(&ent, sizeof(ENT), 1, diccionario);
        posEnt = ent.link;
        if (!strcmp(nomEntidad, ent.nomEnt)){
            res = 1;
        }
    }
    // Imprime atributos
    if (res){
        head = ent.headAtr;
        while (head != EMPTY){
            fseek(diccionario, head, SEEK_SET);
            fread(&atr, sizeof(ATR), 1, diccionario);
            printf("%d. %7s\tTipo: %2d\n", cont, atr.nomAtr, atr.tipo);
            cont++;
            head = atr.link;
        }
    }
    else 
        printf("No se encontró la entidad\n");
    return res;
}

int altaDat(FILE **diccionario){
    void *dato;
    int res, prim = 0;
    long posEnt, posSigDat, posAntDat, posHeadDat, posAntHeadDat, aux;
    char nomEntidad[TAM];
    ENT ent;
    ATR atr;
    DAT nvo, auxDat;
    printf("\t--- Alta dato ---\n");

    // Busca Entidad
    posEnt = leeHead(*diccionario);
    nomEnt(nomEntidad);
    while (posEnt != EMPTY && !res){
        fseek(*diccionario, posEnt, SEEK_SET);
        fread(&ent, sizeof(ENT), 1, *diccionario);
        if (!strcmp(nomEntidad, ent.nomEnt))
            res = 1;
        else
            posEnt = ent.link;
    }
    if (!res){
        printf("No se encontró la entidad\n");
        return res;
    }
    if (ent.headAtr == EMPTY){
        printf("No hay atributos en esta entidad\n");
        return 0;
    }
    // Ajustes
    res = 0;

    //checar si es el primero, si es primero actu ent
    // sino actu DAT (registro) 

    // Escribe la cabecera de datos
    fseek(*diccionario, 0 , SEEK_END);
    posHeadDat = ftell(*diccionario);
    nvo.link = nvo.dat = EMPTY;
    fwrite(&nvo, sizeof(DAT), 1, *diccionario);
    fseek(*diccionario, 0 , SEEK_END);
    nvo.dat = ftell(*diccionario);
    fwrite(&nvo, sizeof(DAT), 1, *diccionario);

    // No hay datos / es el primero;
    if (ent.headDato == EMPTY){
        fseek(*diccionario, posEnt, SEEK_SET);
        ent.headDato = posHeadDat;
        fwrite(&ent, sizeof(ENT), 1, *diccionario);
    }
    else {
        // recorrido DAT, guardar actual (anterior)
        posHeadDat = ent.headDato;
        while (posHeadDat != EMPTY){
            posAntHeadDat = posHeadDat;
            fseek(*diccionario, posHeadDat, SEEK_SET);
            fread(&auxDat, sizeof(DAT), 1, *diccionario);
            posHeadDat = auxDat.link;
        }
    }

    auxDat.link = posHeadDat;
    fseek(*diccionario, posAntHeadDat, SEEK_SET);
    fwrite(&auxDat, sizeof(DAT), 1, *diccionario);

    // Lee atributos y pide datos
    aux = ent.headAtr;
    posAntDat = EMPTY;
    while (aux != EMPTY){
        fseek(*diccionario, aux, SEEK_SET);
        fread(&atr, sizeof(ATR), 1, *diccionario);
        printf("Ingrese el valor de \"%s\": ", atr.nomAtr);
        // Leer según el tipo
        dato = malloc(atr.tam + sizeof(long));
        if (dato)
            switch (atr.tipo){
                case 1: scanf(" %c", (char*)dato); 
                break;
                case 2: scanf("%d", (int*)dato); 
                break;
                case 3: scanf("%f", (float*)dato); 
                break;
                case 4: scanf("%s", (char*)dato); 
                break;
            }
        // Primer dato
            fseek(*diccionario, 0, SEEK_END);
            posSigDat = ftell(*diccionario);
            if (atr.link == EMPTY)
                // Darle EMPTY al link del dato;
                *((char*) dato + sizeof(char)) = EMPTY;
            else 
                //Darle el final del arch 
                *((char*) dato + sizeof(char)) = posSigDat;
            fwrite(dato, atr.tipo + sizeof(long), 1, *diccionario);

        free(dato);
        aux = atr.link;
    }
       
    return res;
}

int bajaDat(FILE **diccionario){
    int res = 0;
    long posEnt, posHDat, posDatAnt, posDatActual;
    char nomEntidad[TAM], datBusc[TAM];
    ENT ent;
    DAT hDat;

    printf("\t--- Baja dato ---\n");
    
    posEnt = leeHead(*diccionario);
    nomEnt(nomEntidad);
    while (posEnt != EMPTY && !res){
        fseek(*diccionario, posEnt, SEEK_SET);
        fread(&ent, sizeof(ENT), 1, *diccionario);
        if (!strcmp(nomEntidad, ent.nomEnt))
            res = 1;
        else
            posEnt = ent.link;
    }
    
    if (!res){
        printf("No se encontró la entidad\n");
        return 0;
    }

    res = 0;
    
    posHDat = ent.headDato;
    posDatAnt = EMPTY;
    
    printf("Ingrese el nombre del dato a eliminar: ");
    scanf("%s", datBusc);

    while (posHDat != EMPTY && !res){
        fseek(*diccionario, posHDat, SEEK_SET);
        fread(&hDat, sizeof(DAT), 1, *diccionario);
        
        fseek(*diccionario, hDat.dat, SEEK_SET);
        char nombreDato[TAM];
        fread(nombreDato, sizeof(nombreDato), 1, *diccionario);

        if (!strcmp(nombreDato, datBusc)){
            if (posDatAnt == EMPTY){
                ent.headDato = hDat.link;
                
                fseek(*diccionario, posEnt, SEEK_SET);
                fwrite(&ent, sizeof(ENT), 1, *diccionario);
            }
            else {
                fseek(*diccionario, posDatAnt, SEEK_SET);
                DAT datAnt;
                fread(&datAnt, sizeof(DAT), 1, *diccionario);
                datAnt.link = hDat.link;
                
                // Write back the updated previous data
                fseek(*diccionario, posDatAnt, SEEK_SET);
                fwrite(&datAnt, sizeof(DAT), 1, *diccionario);
            }
            
            printf("Dato eliminado exitosamente\n");
            res = 1;
            break;
        }
        posDatAnt = posHDat;
        posHDat = hDat.link;
    }

    if (!res){
        printf("No se encontró el dato\n");
    }

    return res;
}

int consultaDat(FILE *diccionario){
    int res;
    long posEnt, posHDat;
    char nomEntidad[TAM], nomDato[TAM], datBusc[TAM];;
    DAT hDat;
    ENT ent;
    ATR atr;
    printf("\t--- Consulta dato ---\n");

    // Busca Entidad
    posEnt = leeHead(diccionario);
    nomEnt(nomEntidad);
    while (posEnt != EMPTY && !res){
        fseek(diccionario, posEnt, SEEK_SET);
        fread(&ent, sizeof(ENT), 1, diccionario);
        if (!strcmp(nomEntidad, ent.nomEnt))
            res = 1;
        else
            posEnt = ent.link;
    }
    // Si NO la encuentra
    if (!res)
        return res;
    res = 0;
    posHDat = ent.headDato;
    printf("Ingrese el nombre del dato: ");
    scanf(" %s", datBusc);
    while (posHDat != EMPTY && !res){
        fseek(diccionario, posHDat, SEEK_SET);
        fread(&hDat, sizeof(DAT), 1, diccionario);
        fseek(diccionario, hDat.dat, SEEK_SET);
        fread(nomDato, sizeof(DAT), 1, diccionario);
        if (!strcmp(nomDato, datBusc)){
            muestraDato(hDat.dat, ent.headAtr, diccionario);
            res = 1;
        }  
        else
            posHDat = hDat.link;
    }
    return res;   
}

int actualizaDat(FILE **diccionario){
    int res = 0;
    return res;
}

// Agregar todos los datos de una sola entidad

int reporteGen(FILE *diccionario){
    int res = 0;
    return res;
}

void muestraDato(long head, long hAtr, FILE *diccionario){
    void *dato;
    long posDat;
    DAT dat;
    ATR atr;
    printf("El valor de los datos es:\n");
    while (hAtr != EMPTY){
        fseek(diccionario, hAtr, SEEK_SET);
        fread(&atr, sizeof(ATR), 1, diccionario);
        printf("%s: ", atr.nomAtr);
        dato = malloc(atr.tam);
        fseek(diccionario, posDat, SEEK_SET);
        switch (atr.tipo){
            case 1:
            fread(dato, sizeof(char), 1, diccionario);
            break;
            case 2:
            fread(dato, sizeof(int), 1, diccionario);
            break;
            case 3:
            fread(dato, sizeof(float), 1, diccionario);
            break;
            case 4:
            fread(dato, TAM, 1, diccionario);
            break;
        }
        muestraValor(dato, atr.tipo);
        printf("\n");
        free(dato);
        hAtr = atr.link;
    }
}

void muestraValor(void *dato, int tipo){
    if (dato)
        switch (tipo){
            case 1:
            printf("%c ", *(char*)dato);
            break;
            case 2:
            printf("%d ", *(int*)dato);
            break;
            case 3:
            printf("%.2f ", *(float*)dato);
            break;
            case 4:
            printf("%10s ", (char*)dato);
            break;
        }
}

