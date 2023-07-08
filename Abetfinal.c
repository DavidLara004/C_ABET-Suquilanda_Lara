#include <stdio.h>
#include <string.h>
#include <time.h>

struct datos
{
    char nombre[20];
    int cantidad;
    float produccion;
    float venta;
    float ganancia;
    time_t fechaHora;
};

void obtenerFechaHora(time_t *t)
{
    time(t);
}

void imprimirFechaHora(time_t t)
{
    struct tm *infoTiempo;
    char buffer[80];

    infoTiempo = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", infoTiempo);
    printf("Fecha y Hora: %s\n", buffer);
}

int main()
{
    struct datos p[3];
    char nom[20], nomnue[20], linea[100], lineatiemp[50], buscador[20];
    char *sep = ";";
    int cant, cantnue, filborr, filmod, cont = 0, cont2 = 1, cont3 = 1;
    float prod, prodnue, vent, ventnue, gana[3], gananue;
    FILE *archivo, *temporal;

    for (int i = 0; i < 2; i++)
    {
        printf("Ingresa el nombre del producto: ");
        scanf("%s", nom);
        fflush(stdin);
        printf("Ingresa la cantidad de productos: ");
        scanf("%d", &cant);
        fflush(stdin);
        printf("Ingresa el precio unitario de producción: ");
        scanf("%f", &prod);
        fflush(stdin);
        printf("Ingresa el precio unitario de venta: ");
        scanf("%f", &vent);
        fflush(stdin);
        gana[i] = ((vent - prod) * cant);
        strcpy(p[i].nombre, nom);
        p[i].cantidad = cant;
        p[i].produccion = prod;
        p[i].venta = vent;
        p[i].ganancia = gana[i];
        obtenerFechaHora(&p[i].fechaHora); // Obtener la fecha y hora actual
    }

    archivo = fopen("prod.csv", "a");
    if (archivo)
    {
        for (int i = 0; i < 2; i++)
        {
            strftime(lineatiemp, sizeof(lineatiemp), "%Y-%m-%d %H:%M:%S", localtime(&p[i].fechaHora));
            fprintf(archivo, "%s; ", p[i].nombre);
            fprintf(archivo, "%d; ", p[i].cantidad);
            fprintf(archivo, "%.2f; ", p[i].produccion);
            fprintf(archivo, "%.2f; ", p[i].venta);
            fprintf(archivo, "%.2f; ", p[i].ganancia);
            fprintf(archivo, "%s", lineatiemp);
            fprintf(archivo, "\n");
        }
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }

    // Búsqueda de datos
     archivo = fopen("prod.csv", "r");
    printf("Ingrese el nombre del producto que desea buscar: ");
    scanf("%s", buscador);
    fflush(stdin);
    if (archivo)
    {
        printf("Los datos del producto buscado son:\n");
        while (fgets(linea, sizeof(linea), archivo))
        {
            char *token = strtok(linea, sep);
            if (strcmp(buscador, token) == 0)
            {
                printf("%s;", token);
                token = strtok(NULL, sep);
                printf("%s;", token);
                token = strtok(NULL, sep);
                printf("%s;", token);
                token = strtok(NULL, sep);
                printf("%s;", token);
                token = strtok(NULL, sep);
                printf("%s;", token);
                token = strtok(NULL, sep);
                printf("%s", token);
                break;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
    // borrado de fila
    archivo = fopen("prod.csv", "r");
    temporal = fopen("temporal.csv", "a");
    printf("Ingrese el numero de linea que desea eliminar: ");
    scanf("%d", &filborr);
    if (archivo && temporal)
    {
        while (fgets(linea, sizeof(linea), archivo))
        {
            if (cont2 != filborr)
            {
                fprintf(temporal, "%s", linea);
            }
            else
            {
                if (cont2 == filborr)
                {
                    printf("La linea numero %d: '%s' ha sido eliminada\n", filborr, linea);
                }
            }
            cont2++;
        }
        fclose(archivo);
        fclose(temporal);
        remove("prod.csv");
        rename("temporal.csv", "prod.csv");
    }
    // Modificacion de filas:
    archivo = fopen("prod.csv", "r");
    temporal = fopen("temporal.csv", "w");
    printf("Ingrese el numero de linea que desea modificar: ");
    scanf("%d", &filmod);
    if (archivo && temporal)
    {
        /*Se vuelve a ocupar el proceso de declaracion, asginacion y formateo de tiempo local dentro de este bloque de codigo con el fin de añadirle a los datos de la
        fila actualizada un tiempo actual*/
        time_t hora = time(NULL);
        struct tm *tiempo_completo = localtime(&hora);
        strftime(lineatiemp, sizeof(lineatiemp), "%Y-%m-%d %H:%M:%S", tiempo_completo);

        while (fgets(linea, sizeof(linea), archivo))
        {
            if (cont3 == filmod)
            {

                printf("A continuacion ingrese los nuevos que desea reemplazar con la modificacion\n");
                printf("Ingresa el nombre del nuevo producto: ");
                scanf("%s", &nomnue);
                fflush(stdin);
                printf("Ingresa la cantidad de elementos del nuevo producto: ");
                scanf("%d", &cantnue);
                fflush(stdin);
                printf("Ingresa el precio unitario del nuevo produccto: ");
                scanf("%f", &prodnue);
                fflush(stdin);
                printf("Ingresa el precio unitario de venta del neuvo prodcuto: ");
                scanf("%f", &ventnue);
                fflush(stdin);
                gananue = ((ventnue - prodnue) * cantnue);
                fprintf(temporal, "%s; ", nomnue);
                fprintf(temporal, "%d; ", cantnue);
                fprintf(temporal, "%.2f; ", prodnue);
                fprintf(temporal, "%.2f; ", ventnue);
                fprintf(temporal, "%.2f; ", gananue);
                fprintf(temporal, "%s", lineatiemp);
                fprintf(temporal, "\n");
            }
            else
            {
                fprintf(temporal, "%s", linea);
            }
            cont3++;
        }
        fclose(archivo);
        fclose(temporal);
        remove("prod.csv");
        rename("temporal.csv", "prod.csv");
    }
    return 0;
}