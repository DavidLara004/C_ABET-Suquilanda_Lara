//Librerias necesarias para las funciones utilizadas en el programa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOMBRE 20 //Definimos una constante que tenga el maximo de caracteres permitidos en el nombre

// Definicion de la estructura Producto
struct Producto
{
    char nombre[MAX_NOMBRE];
    int cantidad;
    float produccion;
    float venta;
    float ganancia;
    char fechaHora[20];  // Cambiamos el tipo a char[] para almacenar la fecha y hora como un string
};

// Funcion para obtener la fecha y hora actual y guardarla como un string
void obtenerFechaHora(char *fechaHora)
{
    time_t hora = time(NULL);
    struct tm *tiempo_completo = localtime(&hora);
    strftime(fechaHora, 20, "%Y-%m-%d %H:%M:%S", tiempo_completo);
}

// Funcion para imprimir la fecha y hora desde un string
void imprimirFechaHora(const char *fechaHora)
{
    printf("Fecha y Hora: %s\n", fechaHora);
}

// Funcion para ingresar los datos de un producto
void ingresarProducto(struct Producto *producto)
{
    printf("Ingresa el nombre del producto: ");
    scanf("%s", producto->nombre);
    fflush(stdin);

    printf("Ingresa la cantidad de productos: ");
    scanf("%d", &producto->cantidad);
    fflush(stdin);

    printf("Ingresa el precio unitario de produccion: ");
    scanf("%f", &producto->produccion);
    fflush(stdin);

    printf("Ingresa el precio unitario de venta: ");
    scanf("%f", &producto->venta);
    fflush(stdin);

    producto->ganancia = (producto->venta - producto->produccion) * producto->cantidad;

    obtenerFechaHora(producto->fechaHora);
}

// Funcion para agregar un producto al archivo  
void agregarProducto(FILE *archivo, const struct Producto *producto)
{
    fprintf(archivo, "%s;%d;%.2f;%.2f;%.2f;%s\n",
            producto->nombre, producto->cantidad, producto->produccion,
            producto->venta, producto->ganancia, producto->fechaHora);
}

// Funcion para buscar un producto por nombre en el archivo
void buscarProducto(const char *nombre)
{
    FILE *archivo = fopen("prod.csv", "r");
    char linea[100];

    if (archivo)
    {
        while (fgets(linea, sizeof(linea), archivo))
        {
            char *token = strtok(linea, ";");
            if (strcmp(nombre, token) == 0)
            {
                printf("Producto encontrado:\n");
                printf("%s;", token);

                token = strtok(NULL, ";");
                printf("%s;", token);

                token = strtok(NULL, ";");
                printf("%s;", token);

                token = strtok(NULL, ";");
                printf("%s;", token);

                token = strtok(NULL, ";");
                printf("%s;", token);

                token = strtok(NULL, "\n");
                imprimirFechaHora(token);
                fclose(archivo);
                return;
            }
        }

        printf("No se encontro el producto.\n");
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

// Funcion para eliminar un producto del archivo por linea
void eliminarProducto(int linea)
{
    FILE *archivo = fopen("prod.csv", "r");
    FILE *temporal = fopen("temporal.csv", "w");
    char lineaActual[100];
    int numeroLinea = 1;

    if (archivo && temporal)
    {
        while (fgets(lineaActual, sizeof(lineaActual), archivo))
        {
            if (numeroLinea != linea)
            {
                fprintf(temporal, "%s", lineaActual);
            }
            else
            {
                printf("La linea numero %d: '%s' ha sido eliminada\n", linea, lineaActual);
            }
            numeroLinea++;
        }

        fclose(archivo);
        fclose(temporal);
        remove("prod.csv");
        rename("temporal.csv", "prod.csv");
    }
    else
    {
        printf("Error al abrir los archivos.\n");
    }
}

// Funcion para modificar un producto del archivo por linea
void modificarProducto(int linea)
{
    FILE *archivo = fopen("prod.csv", "r");
    FILE *temporal = fopen("temporal.csv", "w");
    char lineaActual[100];
    char nuevoNombre[MAX_NOMBRE];
    int nuevaCantidad;
    float nuevaProduccion, nuevaVenta;
    int numeroLinea = 1;

    if (archivo && temporal)
    {
        while (fgets(lineaActual, sizeof(lineaActual), archivo))
        {
            if (numeroLinea == linea)
            {
                printf("A continuacion, ingrese los nuevos datos para la modificacion:\n");

                printf("Ingresa el nombre del nuevo producto: ");
                scanf("%s", nuevoNombre);
                fflush(stdin);

                printf("Ingresa la cantidad de elementos del nuevo producto: ");
                scanf("%d", &nuevaCantidad);
                fflush(stdin);

                printf("Ingresa el precio unitario del nuevo producto: ");
                scanf("%f", &nuevaProduccion);
                fflush(stdin);

                printf("Ingresa el precio unitario de venta del nuevo producto: ");
                scanf("%f", &nuevaVenta);
                fflush(stdin);

                struct Producto producto;
                strcpy(producto.nombre, nuevoNombre);
                producto.cantidad = nuevaCantidad;
                producto.produccion = nuevaProduccion;
                producto.venta = nuevaVenta;
                producto.ganancia = (producto.venta - producto.produccion) * producto.cantidad;
                obtenerFechaHora(producto.fechaHora);

                agregarProducto(temporal, &producto);
            }
            else
            {
                fprintf(temporal, "%s", lineaActual);
            }
            numeroLinea++;
        }

        fclose(archivo);
        fclose(temporal);
        remove("prod.csv");
        rename("temporal.csv", "prod.csv");
    }
    else
    {
        printf("Error al abrir los archivos.\n");
    }
}

// Funcion principal
int main()
{
    int opcion;
    int cantimax;
    printf("Antes de iniciar, coloque cuantos productos se ingresaran hoy:\n ");
    scanf("%d", &cantimax);
    struct Producto productos[cantimax];
//Creacion del menu con Switch case
    do
    {
        printf("\n========== Menu Principal ==========\n");
        printf("La informacion que usted busque o coloque se dispondra de la siguiente manera: \n");
        printf("NOMBRE; CANTIDAD; PRECIO UNITARIO; PRECIO VENTA; GANANCIA; HORA \n");
        printf("1. Ingresar productos\n");
        printf("2. Buscar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Modificar producto\n");
        printf("0. Salir\n");
        printf("=====================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            for (int i = 0; i < cantimax; i++)
            {
                printf("=== Ingrese los datos del Producto %d ===\n", i + 1);
                ingresarProducto(&productos[i]);
                printf("\n");
            }

            FILE *archivo = fopen("prod.csv", "a");
            if (archivo)
            {
                for (int i = 0; i < cantimax; i++)
                {
                    agregarProducto(archivo, &productos[i]);
                }
                fclose(archivo);
            }
            else
            {
                printf("Error al abrir el archivo.\n");
            }
            break;

        case 2:
        {
            char nombreBusqueda[MAX_NOMBRE];
            printf("Ingrese el nombre del producto que desea buscar: ");
            scanf("%s", nombreBusqueda);
            buscarProducto(nombreBusqueda);
        }
        break;

        case 3:
        {
            int lineaEliminar;
            printf("Ingrese el numero de linea quedesea eliminar: ");
            scanf("%d", &lineaEliminar);
            eliminarProducto(lineaEliminar);
        }
        break;

        case 4:
        {
            int lineaModificar;
            printf("Ingrese el numero de linea que desea modificar: ");
            scanf("%d", &lineaModificar);
            modificarProducto(lineaModificar);
        }
        break;

        case 0:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opcion invalida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 0);

    return 0;
}