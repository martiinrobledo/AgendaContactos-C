#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define cant_contactos 100

void setColor(int);
void mostrarmenu();
struct contacto *agregarContacto(struct contacto *pcontacto, int *cantidad_guardados);
void buscarContacto(struct contacto *pcontacto, int cantidad_guardados);
void modificarContacto(struct contacto *pcontacto, int cantidad_guardados);
void mostrarContactos(struct contacto *pcontacto, int *cantidad_guardados);
void eliminarContacto(struct contacto *pcontacto, int *cantidad_guardados);

struct contacto {

        char nombre[40];
        int numero;
        char email[40];
        char direccion[40];
};

int main()
{
    int opcion;
    int cantidad_guardados = 0;

    struct contacto *pcontacto = NULL;

    FILE *archivo;
    archivo = fopen("registros.bin","rb"); //abro archivo para leer
    {
        if(archivo != NULL)
        {
            struct contacto auxiliar; //guardar los datos leídos uno por uno

            while (fread(&auxiliar, sizeof(struct contacto), 1, archivo) == 1) //lee 1 bloque del tamaño del struct contacto desde el archivo, lo guarda aux
                {
                    pcontacto = realloc(pcontacto,(cantidad_guardados + 1) * sizeof(struct contacto));
                    if (pcontacto == NULL)
                        {
                            setColor(12); // Rojo claro
                            printf("Error al reservar memoria\n");
                            break;
                        }
                    pcontacto[cantidad_guardados++] = auxiliar;
                }

                fclose(archivo);
        }
        else
        {
            setColor(12); // Rojo
            printf("No se pudo leer el archivo.\n");
            setColor(7);

        }
    }

    do
    {
        system("cls");
        mostrarmenu();

        printf("\nElija una opcion: \n");
        scanf("%d",&opcion);

        switch(opcion)
        {

        case 1:
            //cargar los datos
            pcontacto = agregarContacto(pcontacto, &cantidad_guardados);
            break;

        case 2:

            buscarContacto(pcontacto,cantidad_guardados);
            break;

        case 3:

            modificarContacto(pcontacto, cantidad_guardados);
            break;

        case 4:

            mostrarContactos(pcontacto,&cantidad_guardados);
            break;

        case 5:

             eliminarContacto(pcontacto,&cantidad_guardados);
             break;

        }

    }while(opcion!=6);


    archivo = fopen("registros.bin","wb");
    if(archivo != NULL)
    {
        fwrite(pcontacto,sizeof(struct contacto),cantidad_guardados,archivo);
        fclose(archivo);

        setColor(10);
        printf("Contactos guardados con exito.\n");
        setColor(8);
    }
    else
    {
        setColor(12); // Rojo claro
        printf("No se pudo guardar el archivo.\n");
        setColor(8);
    }

    free(pcontacto);

    return 0;
}

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //función de la API de Windows que obtiene un “handle” (identificador) a un dispositivo estándar.
    SetConsoleTextAttribute(hConsole, color);
}

void mostrarmenu() {

    setColor(13);
    printf("\n=====================================\n");
    setColor(15);
    printf("         AGENDA DE CONTACTOS         \n");
    setColor(13);
    printf("=====================================\n");

    setColor(11);
    printf("  1 - Nuevo contacto\n");
    printf("  2 - Buscar contacto\n");
    printf("  3 - Modificar contacto\n");
    printf("  4 - Ver lista de contactos\n");
    printf("  5 - Eliminar contacto\n");
    printf("  6 - Cerrar programa\n");

    setColor(13);
    printf("=====================================\n");
    setColor(8);
}


struct contacto *agregarContacto(struct contacto *pcontacto, int *cantidad_guardados)
{
    if (*cantidad_guardados >= cant_contactos)
    {
        setColor(12); // Rojo claro
        printf("Agenda llena, no se pueden agregar mas contactos.\n");
        setColor(8);
        system("pause");
        return pcontacto;
    }

        pcontacto = realloc(pcontacto, (*cantidad_guardados + 1) * sizeof(struct contacto));

        if (pcontacto == NULL)
    {
        setColor(12); // Rojo claro
        printf("Error al reservar memoria.\n");
        setColor(8);
        system("pause");
        return pcontacto;
    }

        setColor(15);
        printf("\nNUEVO CONTACTO\n");
        getchar(); //Limpia el buffer antes de usarlo

        setColor(11);
        printf("Nombre: \n");
        setColor(8);
        scanf(" %39[^\n]s",pcontacto[*cantidad_guardados].nombre);

        setColor(11);
        printf("Numero: \n");
        setColor(8);
        while (scanf("%d",&pcontacto[*cantidad_guardados].numero)!=1)
        {
            setColor(15);
            printf("Solo se permiten numeros\n");
            while (getchar() != '\n');  // Limpiar todo el buffer
            setColor(11);
            printf("Numero: \n");
            setColor(8);
        }
        setColor(11);
        printf("Email: \n");
        setColor(8);
        scanf(" %39[^\n]s",pcontacto[*cantidad_guardados].email);

        setColor(11);
        printf("Direccion: \n");
        setColor(8);
        scanf(" %39[^\n]s",pcontacto[*cantidad_guardados].direccion);

        (*cantidad_guardados)++;

        //Guardar al archivo
        FILE *archivo = fopen("registros.bin", "ab");
        if (archivo != NULL)
        {
            fwrite(&pcontacto[*cantidad_guardados - 1], sizeof(struct contacto), 1, archivo);
            fclose(archivo);
        }
        else
        {
            setColor(12); // Rojo claro
            printf("No se pudo guardar el contacto al archivo.\n");
            setColor(8);
        }

        setColor(10); // Verde claro
        printf("Contacto agregado con exito\n");
        setColor(8); // Gris oscuro
        system("pause");

        return pcontacto;
}



void buscarContacto(struct contacto *pcontacto, int cantidad_guardados)
{
        int opcion_buscar = 0;

        setColor(11);
        printf("BUSCAR\n");
        printf("1- Por nombre\n");
        printf("2- Por numero\n");
        setColor(8);
        scanf("%d",&opcion_buscar);

        // buscar por nombre e imprimir los datos

        int encontrado = 0;
        if(opcion_buscar == 1)
        {
            char buscarnombre[40];
            setColor(11);
            printf("Nombre: \n");
            setColor(8);
            scanf(" %39[^\n]s",buscarnombre);

            int i =0;
            for(i=0;i<cantidad_guardados;i++)
            {
                if(strcmp(buscarnombre,pcontacto[i].nombre)==0)
                {
                    setColor(15);
                    printf("\n %s\n %d\n %s\n %s\n\n ",pcontacto[i].nombre,
                                                        pcontacto[i].numero,
                                                        pcontacto[i].email,
                                                        pcontacto[i].direccion);

                    system("pause");
                    encontrado = 1;
                }
            }

                if(!encontrado)
                {
                    setColor(12); // Rojo claro
                    printf("No se encontro el contacto.\n");
                    setColor(8);
                    system("pause");
                }
        }


        encontrado = 0;
        if (opcion_buscar == 2)
        {
            int buscarnumero;
            setColor(11);
            printf("Numero: \n");
            setColor(8);
            scanf("%d",&buscarnumero);

            int i = 0;
            for (i = 0; i < cantidad_guardados; i++)
            {
                if(pcontacto[i].numero == buscarnumero)
                {
                    setColor(15);
                    printf("\n %s\n %d\n %s\n %s\n\n",pcontacto[i].nombre,
                                                    pcontacto[i].numero,
                                                    pcontacto[i].email,
                                                    pcontacto[i].direccion);

                    system("pause");
                    encontrado = 1;
                }
            }

            if (!encontrado)
                {
                    setColor(12); // Rojo claro
                    printf("No se encontro el contacto.\n");
                    setColor(8);
                    system("pause");
                }


        }

}

void modificarContacto(struct contacto *pcontacto, int cantidad_guardados)
{

    char nombrebuscado[40];
    int encontrado = 0;


    struct contacto aux;

    FILE *archivo;
    archivo = fopen("registros.bin", "rb+");
    if (archivo == NULL)
    {
        setColor(12); // Rojo claro
        printf(" No se pudo abrir el archivo.\n\n");
        setColor(8);
        system("pause");
        return;
    }

    setColor(15);
    printf("---MODIFICAR CONTACTO---\n");
    setColor(11);
    printf("Ingrese el nombre del contacto a modificar: \n");
    getchar();
    setColor(8);
    scanf(" %39[^\n]", nombrebuscado);

    while (fread(&aux, sizeof(struct contacto), 1, archivo) == 1) //lee un contacto y lo guarda en aux
    {
        int posicion = ftell(archivo) - sizeof(struct contacto); //ftell es la posicion actual y resto el tamaño, ya que fread avanza

        if (stricmp(aux.nombre, nombrebuscado) == 0)
        {
            setColor(15);
            printf("\nContacto encontrado:\n");
            setColor(11);
            printf("Nombre: %s\n", aux.nombre);
            printf("Numero: %d\n", aux.numero);
            printf("Email: %s\n", aux.email);
            printf("Direccion: %s\n", aux.direccion);

            setColor(15);
            printf("\nIngrese los nuevos datos:\n");

            setColor(11);
            printf("Nuevo nombre: ");
            setColor(8);
            scanf(" %39[^\n]", aux.nombre);

            setColor(11);
            printf("Nuevo numero: ");
            setColor(8);
            while ((scanf("%d", &aux.numero))!=1)
            {
                setColor(15);
                printf("Solo se permiten numeros\n");
                while (getchar() != '\n');
                setColor(11);
                printf("Nuevo numero: \n");
                setColor(8);
            }

            setColor(11);
            printf("Nuevo email: ");
            setColor(8);
            scanf(" %39[^\n]", aux.email);

            setColor(11);
            printf("Nueva direccion: ");
            setColor(8);
            scanf(" %39[^\n]", aux.direccion);

            // Actualizar archivo
            fseek(archivo, posicion, SEEK_SET); // se para en la posicion
            fwrite(&aux, sizeof(struct contacto), 1, archivo);

            // Actualizar arreglo en memoria
            int i = 0;
            for (i = 0; i < cantidad_guardados; i++)
            {
                if (stricmp(pcontacto[i].nombre, nombrebuscado) == 0)
                {
                    pcontacto[i] = aux;
                    break;
                }
            }

            setColor(10); // Verde
            printf("Contacto modificado con exito.\n");
            setColor(8);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        setColor(12); // Rojo
        printf("No se encontro el contacto.\n");
        setColor(7);
    }

    fclose(archivo);
    system("pause");

}


void mostrarContactos(struct contacto *pcontacto, int *cantidad_guardados)
{
    struct contacto aux;
    int i, j;

    // Ordenar alfabéticamente por nombre
    for(i = 0; i < *cantidad_guardados - 1; i++)
    {
        for(j = i + 1; j < *cantidad_guardados; j++)
        {
            if(strcmp(pcontacto[i].nombre, pcontacto[j].nombre) > 0) // si i>j lo invierte
            {
                aux = pcontacto[i];
                pcontacto[i] = pcontacto[j];
                pcontacto[j] = aux;
            }
        }
    }

    setColor(15);
    printf("\n--- Lista de Contactos ---\n\n");
    for(i = 0; i < *cantidad_guardados; i++)
    {
        setColor(8);
        printf("Nombre:");
        setColor(15);
        printf("%15s |", pcontacto[i].nombre);
        setColor(8);
        printf("Numero:");
        setColor(15);
        printf("%15d |", pcontacto[i].numero);
        setColor(8);
        printf("Email:");
        setColor(15);
        printf("%30s |", pcontacto[i].email);
        setColor(8);
        printf("Direccion:");
        setColor(15);
        printf("%15s |\n", pcontacto[i].direccion);

    }
    printf("\n");
    system("pause");
}

void eliminarContacto(struct contacto *pcontacto, int *cantidad_guardados)
{
    if(*cantidad_guardados == 0)
    {
        setColor(12);
        printf("No hay contactos para eliminar\n");
        system("pause");
    }

    char nombre_buscado[40];
    int encontrado = 0;

    setColor(15);
    printf("---ELIMINAR CONTACTO---\n");
    setColor(11);
    printf("Ingrese el nombre del contacto a eliminar: ");
    getchar(); // limpiar buffer
    setColor(8);
    scanf(" %39[^\n]", nombre_buscado);

    int i = 0;
    int j = 0;
    for(i = 0; i < *cantidad_guardados; i++)
    {
        if(stricmp(pcontacto[i].nombre,nombre_buscado)== 0)
        {
            for(j = i;j < *cantidad_guardados - 1; j++)
            {
                pcontacto[j] = pcontacto[j+1]; // sobreescribe el contacto siguiente a la posiciion actual
            }

            (*cantidad_guardados)--;

            FILE *archivo = fopen("registros.bin", "wb");
            if (archivo != NULL)
            {
                fwrite(pcontacto, sizeof(struct contacto), *cantidad_guardados, archivo);
                fclose(archivo);
            }
            else
            {
                setColor(12); // Rojo claro
                printf("No se pudo actualizar el archivo\n");
                setColor(7);
            }

            setColor(10); // Verde claro
            printf("Contacto eliminado con exito.\n");
            setColor(7);
            system("pause");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        setColor(12); // Rojo claro
        printf("No se encontro el contacto.\n");
        setColor(7);
        system("pause");
    }

}
