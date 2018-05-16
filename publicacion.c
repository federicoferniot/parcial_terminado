#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "publicacion.h"
#include "utn.h"
#include "cliente.h"

#define ACTIVA 1
#define PAUSADA 0



//Funciones privadas
static int proximoId(void);
static int buscarPorId(Publicacion* array,int limite, int id);
static int buscarLugarLibre(Publicacion* array,int limite);
//__________________



/** \brief
 * \param array Cliente*
 * \param limite int
 * \return int
 *
 */
int pub_init(Publicacion* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            array[i].isEmpty=1;
        }
    }
    return retorno;
}

int pub_mostrarDebug(Publicacion* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            //printf("[DEBUG] - %d - %s - %s - %d - %d\n",array[i].id, array[i].cuit,array[i].archivo,array[i].dias, array[i].isEmpty);
        }
    }
    return retorno;
}

int pub_mostrar(Publicacion* array, Cliente* clientes, int limite, int limiteCli)
{
    int retorno = -1;
    int i, auxCuit;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].estado)
            {
                auxCuit = cliente_obtenerCuitPorId(clientes, limiteCli, array[i].idCliente);
                printf("Id: %d - Cuit Cliente: %d - Texto: %s - Rubro: %d - Estado: %d\n",array[i].idPublicacion, auxCuit,array[i].texto,array[i].numeroRubro, array[i].estado);
            }
        }
    }
    return retorno;
}

int pub_alta(Publicacion* array,int limite,
              Cliente* Clientes, int lenClientes)
{
    int retorno = -1;
    int i;
    int idCli;
    int posCli;
    int rubro;
    char texto[65];


    if(limite > 0 && array != NULL)
    {
        i = buscarLugarLibre(array,limite);
        if(i >= 0)
        {

            if(!getValidInt("ID?","\nNumero no valido\n",&idCli,0,999999,2))
            {
                posCli = cliente_buscarPorId(Clientes,lenClientes,idCli);
                if(posCli>=0)
                {
                    if(!getValidInt("Numero de rubro?","\nNumero no valido\n",&rubro,0,200,2))
                    {
                        if(!getValidString("\nTexto? ","\nEso no es un texto","El maximo es 64",texto,65,2))
                        {
                            retorno = 0;
                            strcpy(array[i].texto, texto);
                            array[i].numeroRubro = rubro;
                            array[i].idCliente = idCli;
                            array[i].isEmpty=0;
                            array[i].idPublicacion = proximoId();
                            array[i].estado = ACTIVA;
                        }
                        else
                        {
                            retorno = -5;
                        }
                    }
                    else
                    {
                        retorno = -4;
                    }
                }
            }
            else
            {
                retorno = -3;
            }
        }
        else
        {
            retorno = -2;
        }

    }
    return retorno;
}


int pub_baja(Publicacion* array,int limite, int id)
{
    int indiceAEliminar;
    int retorno=-1;
    indiceAEliminar = buscarPorId(array,limite,id);
    if(indiceAEliminar>=0)
    {
        array[indiceAEliminar].isEmpty=1;
        retorno=0;
    }
    return retorno;
}


int pub_pausarPublicacion(Publicacion* array, Cliente* clientes, int limite, int limiteClientes)
{
    int auxId;
    int posPublicacion;
    char opcion;
    if(!getValidInt("\nId publicacion?", "\nEso no es un Id", &auxId, 0, 200000, 2))
    {
        posPublicacion = buscarPorId(array, limite, auxId);
        if(posPublicacion>=0)
        {
            cliente_mostrarPorId(clientes, limiteClientes, array[posPublicacion].idCliente);
            opcion = getChar("Desea pausar la publicacion (s/n)");
            if(opcion=='s')
            {
                array[posPublicacion].estado = PAUSADA;
            }
        }
    }
    return 0;
}

int pub_reanudarPublicacion(Publicacion* array, Cliente* clientes, int limite, int limiteClientes)
{
    int auxId;
    int posPublicacion;
    char opcion;
    if(!getValidInt("\nId publicacion?", "\nEso no es un Id", &auxId, 0, 200000, 2))
    {
        posPublicacion = buscarPorId(array, limite, auxId);
        if(posPublicacion>=0)
        {
            cliente_mostrarPorId(clientes, limiteClientes, array[posPublicacion].idCliente);
            opcion = getChar("Desea reanudar la publicacion (s/n)");
            if(opcion=='s')
            {
                array[posPublicacion].estado = ACTIVA;
            }
        }
    }
    return 0;
}

static int buscarLugarLibre(Publicacion* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        for(i=0;i<limite;i++)
        {
            if(array[i].isEmpty==1)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}



static int proximoId(void)
{
    static int proximoId = -1;
    proximoId++;
    return proximoId;
}


static int buscarPorId(Publicacion* array,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idPublicacion==id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int pub_altaForzada(Publicacion* array, int limite, int idCliente, int rubro, char* texto)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        i = buscarLugarLibre(array,limite);
        if(i >= 0)
        {
            strcpy(array[i].texto,texto);
            array[i].idCliente = idCliente;
            array[i].isEmpty=0;
            array[i].estado = ACTIVA;
            array[i].idPublicacion = proximoId();
        }
        retorno = 0;
    }
    return retorno;
}

int pub_mostrarPorIdCliente(Publicacion* array, int limite, int idCliente)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente == idCliente)
                printf("[RELEASE] - %d - %d - %s - %d - %d\n",array[i].idPublicacion, array[i].idCliente,array[i].texto,array[i].numeroRubro, array[i].estado);
        }
    }
    return retorno;
}

int pub_cantidadPublicacionesPorIdCliente(Publicacion* array, int limite, int idCliente)
{
    int cantidadPublicaciones = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        cantidadPublicaciones = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente == idCliente)
                cantidadPublicaciones++;
        }
    }
    return cantidadPublicaciones;
}

int pub_cantidadPublicacionesPausadasPorIdCliente(Publicacion* array, int limite, int idCliente)
{
    int cantidadPublicaciones = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        cantidadPublicaciones = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && !array[i].estado && array[i].idCliente == idCliente)
                cantidadPublicaciones++;
        }
    }
    return cantidadPublicaciones;
}

int pub_cantidadPublicacionesActivasPorIdCliente(Publicacion* array, int limite, int idCliente)
{
    int cantidadPublicaciones = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        cantidadPublicaciones = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].estado && array[i].idCliente == idCliente)
                cantidadPublicaciones++;
        }
    }
    return cantidadPublicaciones;
}

int pub_bajaPorIdCliente(Publicacion* array, int limite, int idCliente)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente == idCliente)
            {
                array[i].isEmpty = 1;
            }
        }
    }
    return retorno;
}

int pub_ordenarPorRubro(Publicacion* array,int limite, int orden)
{
    int retorno = -1;
    int i;
    int flagSwap;
    Publicacion auxiliarEstructura;

    if(limite > 0 && array != NULL)
    {
        do
        {
            flagSwap = 0;
            for(i=0;i<limite-1;i++)
            {
                if(!array[i].isEmpty && !array[i+1].isEmpty)
                {
                    if(((array[i].numeroRubro > array[i+1].numeroRubro) && orden || (array[i].numeroRubro < array[i+1].numeroRubro) && !orden)) //******
                    {
                        auxiliarEstructura = array[i];
                        array[i] = array[i+1];
                        array[i+1] = auxiliarEstructura;
                        flagSwap = 1;
                    }
                }
            }
        }while(flagSwap);
    }
    return retorno;
}
