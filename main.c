#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Cliente.h"
#include "utn.h"
#include "publicacion.h"
#include "informar.h"

#define LEN_CLI 10
#define LEN_PUB 100

int main()
{
    Cliente clientes[LEN_CLI];
    Publicacion publicaciones[LEN_PUB];
    int menu;
    int auxiliarId;
    char opcion;


    cliente_init(clientes,LEN_CLI);
    pub_init(publicaciones,LEN_PUB);


    cliente_altaForzada(clientes, LEN_CLI, "Carlos", "Fredes", 3);
    cliente_altaForzada(clientes, LEN_CLI, "Juan", "Perez", 2);
    pub_altaForzada(publicaciones, LEN_PUB, 0, 10, "Publicacion 1");
    pub_altaForzada(publicaciones, LEN_PUB, 0, 10, "Publicacion 2");
    do
    {
        getValidInt("\n\n1.Alta Cliente\n2.Modificar Cliente\n3.Baja Cliente\n4.Publicar\n5.Pausar Publicacion\n6.Reanudar Publicacion\n7.Imprimir Clientes\n8.Imprimir Publicaciones\n9.Informar clientes\n11.Salir\n10.Informar publicaciones\n","\nNo valida\n",&menu,1,11,1);
        switch(menu)
        {
            case 1:
                cliente_alta(clientes, LEN_CLI);
                break;
            case 2:
                cliente_modificacion(clientes, LEN_CLI, auxiliarId);
                break;
            case 3:
                if(!getValidInt("\nId?", "\nEso no es un Id", &auxiliarId, 0, 200000, 2))
                {
                    pub_mostrarPorIdCliente(publicaciones, LEN_PUB, auxiliarId);
                    opcion = getChar("\nDesea dar de baja el cliente?(s/n)");
                    if(opcion=='s')
                    {
                        if(!cliente_baja(clientes, LEN_CLI, auxiliarId))
                        {
                            pub_bajaPorIdCliente(publicaciones, LEN_PUB, auxiliarId);
                        }
                    }
                }
                break;
            case 4:
                pub_alta(publicaciones, LEN_PUB, clientes, LEN_CLI);
                break;
            case 5:
                pub_pausarPublicacion(publicaciones, clientes, LEN_PUB, LEN_CLI);
                break;
            case 6:
                pub_reanudarPublicacion(publicaciones, clientes, LEN_PUB, LEN_CLI);
                break;
            case 7:
                informe_mostrarClientes(clientes, publicaciones, LEN_CLI, LEN_PUB);
                break;
            case 8:
                pub_mostrar(publicaciones, clientes, LEN_PUB, LEN_CLI);
                break;
            case 9:
                informe_clienteMasAvisosActivos(clientes, publicaciones, LEN_CLI, LEN_PUB);
                informe_clienteMasAvisosPausados(clientes, publicaciones, LEN_CLI, LEN_PUB);
                informe_clienteMasAvisos(clientes, publicaciones, LEN_CLI, LEN_PUB);
                break;
            case 10:
                informe_cantidadPublicacionesPorRubro(publicaciones, LEN_PUB);
                break;
        }

    }while(menu != 11);

    return 0;
}
