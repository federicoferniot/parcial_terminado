#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "cliente.h"
#include "utn.h"


//Funciones privadas
static int proximoId(void);
static int buscarLugarLibre(Cliente* array,int limite);
//__________________



/** \brief  Inializa el array con lugares vacios
 * \param array Cliente*
 * \param limite int
 * \return int
 *
 */
int cliente_init(Cliente* array,int limite)
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

/** \brief Muestra datos del cliente indicado por el ID
 *
 * \param array Cliente*
 * \param limite int
 * \param idCliente int
 * \return int
 *
 */
int cliente_mostrarPorId(Cliente* array, int limite, int idCliente)
{
    int retorno=0;
    int pos;
    pos = cliente_buscarPorId(array, limite, idCliente);
    if(pos>=0)
    {
        if(!array[pos].isEmpty)
            printf(" Id: %d Nombre: %s Apellido: %s Cuit: %d\n",array[pos].idCliente, array[pos].nombre, array[pos].apellido, array[pos].cuit);
    }
    return retorno;
}

/** \brief Muestra datos de los clientes dados de alta
 *
 * \param array Cliente*
 * \param limite int
 * \return int
 *
 */
int cliente_mostrar(Cliente* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty)
                printf("[RELEASE] - %d : - %s %s - %d\n",array[i].idCliente, array[i].nombre, array[i].apellido, array[i].cuit);
        }
    }
    return retorno;
}

/** \brief Da de alta un cliente, solicitando ingresar los datos al usuario
 *
 * \param array Cliente*
 * \param limite int
 * \return int
 *
 */
int cliente_alta(Cliente* array,int limite)
{
    int retorno = -1;
    int i;
    char nombre[50];
    char apellido[50];
    int cuit;
    if(limite > 0 && array != NULL)
    {
        i = buscarLugarLibre(array,limite);
        if(i >= 0)
        {
            if(!getValidString("\nNombre? ","\nEso no es un nombre","El maximo es 50",nombre,50,2))
            {
                if(!getValidString("\nApellido? ","\nEso no es un apellido","El maximo es 50",apellido,50,2))
                {
                    if(!getValidInt("\nCuit? ","\nEso no es un cuit",&cuit,0,INT_MAX,2))
                    {
                        retorno = 0;
                        strcpy(array[i].nombre,nombre);
                        strcpy(array[i].apellido,apellido);
                        array[i].cuit = cuit;
                        //------------------------------
                        //------------------------------
                        array[i].idCliente = proximoId();
                        array[i].isEmpty = 0;
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

/** \brief Da de baja al cliente indicado por ID
 *
 * \param array Cliente*
 * \param limite int
 * \param id int
 * \return int
 *
 */
int cliente_baja(Cliente* array,int limite, int id)
{
    int indiceAEliminar;
    int retorno=-1;
    indiceAEliminar = cliente_buscarPorId(array,limite,id);
    if(indiceAEliminar>=0)
    {
        array[indiceAEliminar].isEmpty=1;
        retorno=0;
    }
    return retorno;
}

/** \brief Se le solicita ingresar al usuario los nuevos datos para el cliente indicado por ID
 *
 * \param array Cliente*
 * \param limite int
 * \param id int
 * \return int
 *
 */
int cliente_modificacion(Cliente* array,int limite, int id)
{
    int retorno = -1;
    int cuit, indiceAModificar;
    char buffer[50];

    indiceAModificar = cliente_buscarPorId(array,limite,id);
    if(indiceAModificar>=0)
    {
        if(!getValidString("\nNombre? ","\nEso no es un nombre","El maximo es 40",buffer,40,2))
        {
            retorno = 0;
            strcpy(array[indiceAModificar].nombre,buffer);
            if(!getValidString("\nApellido? ","\nEso no es un Apellido","El maximo es 40",buffer,40,2))
            {
                strcpy(array[indiceAModificar].apellido,buffer);
                if(!getValidInt("\nCuit? ","\nEso no es un cuit",&cuit,0,INT_MAX,2))
                {
                    array[indiceAModificar].cuit = cuit;
                }
                else
                {
                    retorno = -4;
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

int cliente_ordenar(Cliente* array,int limite, int orden)
{
    int retorno = -1;
    int i;
    int flagSwap;
    Cliente auxiliarEstructura;

    if(limite > 0 && array != NULL)
    {
        do
        {
            flagSwap = 0;
            for(i=0;i<limite-1;i++)
            {
                if(!array[i].isEmpty && !array[i+1].isEmpty)
                {
                    if((strcmp(array[i].nombre,array[i+1].nombre) > 0 && orden) || (strcmp(array[i].nombre,array[i+1].nombre) < 0 && !orden)) //******
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

static int buscarLugarLibre(Cliente* array,int limite)
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


/** \brief Devuelve el indice del array donde se encuentra el cliente indicado por ID
 *
 * \param array Cliente*
 * \param limite int
 * \param id int
 * \return int [-1] Si se pasa un limite incorrecto, [-2] Si no se encuentra el ID
 *
 */
int cliente_buscarPorId(Cliente* array,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente==id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int cliente_altaForzada(Cliente* array,int limite,char* nombre,char* apellido, int cuit)
{
    int retorno = -1;
    int i;

    if(limite > 0 && array != NULL)
    {
        i = buscarLugarLibre(array,limite);
        if(i >= 0)
        {
            retorno = 0;
            strcpy(array[i].nombre,nombre);
            strcpy(array[i].apellido,apellido);
            array[i].cuit = cuit;
            //------------------------------
            //------------------------------
            array[i].idCliente = proximoId();
            array[i].isEmpty = 0;
        }
        retorno = 0;
    }
    return retorno;
}

/** \brief Devuelve el cuit del cliente indicado por ID
 *
 * \param array Cliente*
 * \param limite int
 * \param idCliente int
 * \return int [-1] Si se pasa un limite incorrecto, [-2] Si no se encuentra el ID
 *
 */
int cliente_obtenerCuitPorId(Cliente* array, int limite, int idCliente)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente==idCliente)
            {
                retorno = array[i].cuit;
                break;
            }
        }
    }
    return retorno;
}



