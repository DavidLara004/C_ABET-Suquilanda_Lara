#include <stdio.h>
#include <string.h>
struct datos
{
    char nombre[20];
    int cantidad;
    float produccion;
    float venta;
    float ganancia;
};
int main()
{
    struct datos p[3];
    char nom[20], nomnue[20], linea[100], lineatemp[100];
    int cant, cantnue, filborr, filmod, cont = 0, cont2 = 1, cont3 = 1;
    float prod, prodnue, vent, ventnue, gana[3], gananue;
    FILE *archivo, *temporal;
    for (int i = 0; i < 3; i++)
    {
        printf("Ingresa el nombre del produccto: ");
        scanf("%s", &nom);
        fflush(stdin);
        printf("Ingresa la cantidad de productos: ");
        scanf("%d", &cant);
        fflush(stdin);
        printf("Ingresa el precio unitario de produccion: ");
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
    }
    archivo = fopen("prod.csv", "w");
    for (int i = 0; i < 3; i++)
    {
        fprintf(archivo, "%s; ", p[i].nombre);
        fprintf(archivo, "%d; ", p[i].cantidad);
        fprintf(archivo, "%.2f; ", p[i].produccion);
        fprintf(archivo, "%.2f; ", p[i].venta);
        fprintf(archivo, "%.2f", p[i].ganancia);
        fprintf(archivo, "\n");
    }
    fclose(archivo);

    // Impresion de filas de datos
    archivo = fopen("prod.csv", "r");
    if (archivo)
    {
        while (fgets(linea, sizeof(linea), archivo))
        {
            if (linea[strlen(linea) - 1] == '\n')
            {
                linea[strlen(linea) - 1] = '\0';
            }
            printf("%s\n", linea);
            cont++;
        }
        fclose(archivo);
    }

    // borrado de fila
    archivo = fopen("prod.csv", "r");
    temporal = fopen("temporal.csv", "w");
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
                fprintf(temporal, "%.2f", gananue);
                fprintf(temporal, "\n");
            }
            else{
                fprintf(temporal,"%s",linea);
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