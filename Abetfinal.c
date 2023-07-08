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
};
int main()
{
    struct datos p[3];
    char nom[20], nomnue[20], linea[100], lineatiemp[50];
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
    if(archivo){
        time_t hora = time(NULL);  //declaracion de dato tipo 'time_t' para almacenar funcion 'time'
        struct tm *tiempo_completo = localtime(&hora); /*Se declara un puntero tipo 'struct tm', ya que esta ultima permitira colocar el tiempo almacenado en la variable
        'hora' declara anteriormente, de manera tal que se ordenara en "anio: mes: dia: horas: minutos: segundos" */
        for (int i = 0; i < 3; i++)
        {
            strftime(lineatiemp,sizeof(lineatiemp),"%Y-%m-%d %H:%M:%S",tiempo_completo); /*se utiliza la función strftime para formatear el tiempo almacenado en el
            puntero tipo struct, para obtener la forma de "%Anio-%mes-%dia %hora:%minutos:%segundo". Este formato se guardara en el string 'lineatemp', que posteriormente
            se almacenara junto a los otros datos del archivo al final de cada linea.*/
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
        /*Se vuelve a ocupar el proceso de declaracion, asginacion y formateo de tiempo local dentro de este bloque de codigo con el fin de añadirle a los datos de la
        fila actualizada un tiempo actual*/
        time_t hora = time(NULL); 
        struct tm *tiempo_completo = localtime(&hora);
        strftime(lineatiemp,sizeof(lineatiemp),"%Y-%m-%d %H:%M:%S",tiempo_completo);

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