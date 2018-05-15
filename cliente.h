#ifndef cliente_H_INCLUDED
#define cliente_H_INCLUDED
typedef struct
{
    char nombre[50];
    char apellido[50];
    int cuit;
    //------------
    int idCliente;
    int isEmpty;
}Cliente;
#endif // cliente_H_INCLUDED


int cliente_init(Cliente* array,int limite);
int cliente_mostrar(Cliente* array,int limite);
int cliente_mostrarDebug(Cliente* array,int limite);
int cliente_alta(Cliente* array,int limite);
int cliente_baja(Cliente* array,int limite, int id);
int cliente_modificacion(Cliente* array,int limite, int id);
int cliente_ordenar(Cliente* array,int limite, int orden);
int cliente_buscarPorId(Cliente* array,int limite, int id);
int cliente_altaForzada(Cliente* array,int limite,char* nombre,char* apellido, int cuit);
int cliente_mostrarPreciosMenoresA(Cliente* array, int limite, float precioLimite);
int cliente_promedioPrecios(Cliente* array, int limite, float* promedio);
int cliente_listarSuperenPromedioPrecio(Cliente* array, int limite);
int cliente_mostrarPreciosMayoresA(Cliente* array, int limite, float precioLimite);
int cliente_mostrarPorId(Cliente* array, int limite, int idCliente);
int cliente_obtenerCuitPorId(Cliente* array, int limite, int idCliente);
//int buscarLugarLibre(Cliente* array,int limite);
//int proximoId();
//int cliente_buscarPorId(Cliente* array,int limite, int id);

