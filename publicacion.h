#ifndef CONTRATACION_H_INCLUDED
#define CONTRATACION_H_INCLUDED
typedef struct
{
    int idCliente;
    int numeroRubro;
    char texto[65];
    int estado;
    //------------
    int idPublicacion;
    int isEmpty;
}Publicacion;

#include "cliente.h"


int pub_init(Publicacion* array,int limite);
int pub_mostrar(Publicacion* array, Cliente* clientes, int limite, int limiteCli);
int pub_mostrarDebug(Publicacion* array,int limite);

int pub_alta(Publicacion* arrayC,int limite,
              Cliente* pantallas, int lenClientes);

int pub_baja(Publicacion* array,int limite, int id);
int pub_modificacion(Publicacion* array,int limite, int id);
int pub_ordenar(Publicacion* array,int limite, int orden);
int pub_ordenarCuit(Publicacion* array,int limite, int orden);
int pub_reanudarPublicacion(Publicacion* array, Cliente* clientes, int limite, int limiteClientes);
int pub_pausarPublicacion(Publicacion* array, Cliente* clientes, int limite, int limiteClientes);
int pub_altaForzada(Publicacion* array, int limite, int idCliente, int rubro, char* texto);
int pub_mostrarPorIdCliente(Publicacion* array, int limite, int idCliente);
int pub_bajaPorIdCliente(Publicacion* array, int limite, int idCliente);
int pub_cantidadPublicacionesPorIdCliente(Publicacion* array, int limite, int idCliente);
int pub_cantidadPublicacionesPausadasPorIdCliente(Publicacion* array, int limite, int idCliente);
int pub_cantidadPublicacionesActivasPorIdCliente(Publicacion* array, int limite, int idCliente);
int pub_ordenarPorRubro(Publicacion* array,int limite, int orden);

#endif // PANTALLA_H_INCLUDED


