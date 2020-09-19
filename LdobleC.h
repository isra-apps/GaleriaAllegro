#include<allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include<string.h>

#define MAXANCHO 1000
#define MAXALTO 562
#define MAXDIR 100

typedef struct _tdatoD{
    BITMAP *foto;
    char name[MAXDIR];
    struct _tdatoD *sig;
    struct _tdatoD *ant;
}TdatoD;

typedef TdatoD *TnodoD;

TnodoD GenDatoD(char *nom);
void AgregarLDC(TnodoD *listaDC, TnodoD *nuevo);
TnodoD EliminarLDC(TnodoD *listaDC, TnodoD *nodo);
void ImprimirLDC(TnodoD listaD);
void ServicioDC(TnodoD temp);
void SalirLDC(TnodoD *listaD);

int Menus(BITMAP *menu1, BITMAP *menu2, BITMAP *menu3,BITMAP *buffer);
int Carpetas(BITMAP *buffer, BITMAP *carpetas, BITMAP *carpetas1, BITMAP *carpetas2, BITMAP *carpetas3, BITMAP *carpetas4,BITMAP *carpetas5,BITMAP *carpetas6);
void error(const char *s);
void procesoArchivo(char *archivo,TnodoD *lista,char *nom);

TnodoD GenDatoD(char *nom)
{
    TnodoD temp=NULL;

    temp = (TnodoD)malloc(sizeof(TdatoD));
    temp->foto = load_bitmap(nom,NULL);
    strcpy(temp->name,nom);
    temp->sig = NULL;
    temp->ant = NULL;

    return temp;
}

void AgregarLDC(TnodoD *listaDC, TnodoD *nuevo)
{
    TnodoD temp=NULL;

    if(!*listaDC)
    {
        *listaDC = *nuevo;
        (*listaDC)->sig = *listaDC;
        (*listaDC)->ant = *listaDC;
        *nuevo = NULL;
    }
    else
    {
        temp = (*listaDC)->ant;
        (*nuevo)->ant = temp;
        (*nuevo)->sig = temp->sig;
        temp->sig = *nuevo;
        (*listaDC)->ant = *nuevo;
        *nuevo = NULL;
    }
}

void ServicioDC(TnodoD temp)
{
    printf("Nombre = %s\n",temp->name);
}

void ImprimirLDC(TnodoD listaD)
{
    TnodoD temp=NULL;

    temp = listaD;
    while(temp->sig != listaD)
    {
        ServicioDC(temp);
        temp = temp->sig;
    }
    ServicioDC(temp);
}


void SalirLDC(TnodoD *listaD)
{
    TnodoD aux=NULL;

    while( (*listaD)->sig != *listaD)
    {
        aux = *listaD;
        (aux->ant)->sig = aux->sig;
        *listaD = (*listaD)->sig;
        (*listaD)->ant = aux->ant;
        aux->sig = NULL;
        aux->ant = NULL;
        free(aux);
    }
        free(*listaD);
}

int Menus(BITMAP *menu1, BITMAP *menu2, BITMAP *menu3,BITMAP *buffer)
{
    int salida = 0;
    int flag = 0;
    while( salida == 0 )
    {
        if( mouse_x > 22 && mouse_x < 134 && mouse_y > 399 && mouse_y < 512 )
        {
            blit(menu2,buffer,0,0,0,0,MAXANCHO,MAXALTO);
            if( mouse_b & 1 )
            {
                salida = 1;
                flag = 1;
            }
        }
        else
        {
            if( mouse_x > 868 && mouse_x < 978 && mouse_y > 402 && mouse_y < 520 )
            {
                blit(menu3,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                if( mouse_b & 1 )
                {
                    salida = 1;
                }
            }
            else
            {
                blit(menu1,buffer,0,0,0,0,MAXANCHO,MAXALTO);
            }
        }
        show_mouse(screen);
        blit(buffer,screen,0,0,0,0,MAXANCHO,MAXALTO);

    }
    return flag;
}

int Carpetas(BITMAP *buffer, BITMAP *carpetas, BITMAP *carpetas1, BITMAP *carpetas2, BITMAP *carpetas3, BITMAP *carpetas4,BITMAP *carpetas5,BITMAP *carpetas6)
{

    int salida = 0;
    int opc;
    while( salida == 0 )
        {
            if( mouse_x > 113 && mouse_x < 330 && mouse_y > 78 && mouse_y < 269 )
            {
                blit(carpetas1,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                if( mouse_b & 1 )
                {
                    salida = 1;
                    opc = 1;
                }
            }
            else
            {
                if( mouse_x > 385 && mouse_x < 600 && mouse_y > 78 && mouse_y < 269 )
                {
                    blit(carpetas2,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                    if( mouse_b & 1 )
                    {
                        salida = 1;
                        opc = 2;
                    }
                }
                else
                {
                    if( mouse_x > 665 && mouse_x < 880 && mouse_y > 78 && mouse_y < 269 )
                    {
                        blit(carpetas3,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                        if( mouse_b & 1 )
                        {
                            salida = 1;
                            opc = 3;
                        }
                    }
                    else
                    {
                        if( mouse_x > 248 && mouse_x < 465 && mouse_y > 317 && mouse_y < 507 )
                        {
                            blit(carpetas4,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                            if( mouse_b & 1 )
                            {
                                salida = 1;
                                opc = 4;
                            }
                        }
                        else
                        {
                            if( mouse_x > 530 && mouse_x < 747 && mouse_y > 317 && mouse_y < 507 )
                            {
                                blit(carpetas5,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                                if( mouse_b & 1 )
                                {
                                    salida = 1;
                                    opc = 5;
                                }
                            }
                            else
                            {
                                if( mouse_x > 897 && mouse_x < 961 && mouse_y > 429 && mouse_y < 490 )
                                {
                                    blit(carpetas6,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                                    if( mouse_b & 1 )
                                    {
                                        salida = 1;
                                        opc = 6;
                                    }
                                }
                                else
                                {
                                    blit(carpetas,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                                }
                            }
                        }
                    }
                }
            }
            show_mouse(screen);
            blit(buffer,screen,0,0,0,0,MAXANCHO,MAXALTO);
        }
    return opc;
}


void error(const char *s)
{
    perror (s);               // perror() devuelve la cadena S y el error
    exit(EXIT_FAILURE);       // (en cadena de caracteres) que tenga errno
}
//---------------------------------------------------------------------------
void procesoArchivo(char *archivo,TnodoD *lista,char *nom)
{
    FILE *fich;
    long ftam;
    TnodoD nuevo=NULL;
    char dir[MAXDIR];
    strcpy(dir,nom);
    strcat(dir,"/");
    fich=fopen(archivo, "r");
    if (fich)
    {
        fseek(fich, 0L, SEEK_END);
        ftam=ftell(fich);
        fclose(fich);
    }
    else
    {
        strcat(dir,archivo);
        nuevo = GenDatoD(dir);
        AgregarLDC(&*lista,&nuevo);
    }
}

TnodoD EliminarLDC(TnodoD *listaDC, TnodoD *nodo)
{
    TnodoD temp=NULL;

    temp = *nodo;
    if(temp->sig == temp)
    {
        *listaDC = NULL;
        temp->sig = NULL;
        temp->ant = NULL;
        return temp;
    }
    if( temp == *listaDC )
    {
        *listaDC = (*listaDC)->sig;
        (*listaDC)->ant = temp->ant;
        (temp->ant)->sig = *listaDC;
        temp->ant = NULL;
        temp->sig = NULL;
        *nodo = NULL;
        return temp;
    }
    if( temp == (*listaDC)->ant )
    {
        (*listaDC)->ant = temp->ant;
        (temp->ant)->sig = *listaDC;
        temp->sig = NULL;
        temp->ant = NULL;
        *nodo = NULL;
        return temp;
    }
    (temp->ant)->sig = temp->sig;
    (temp->sig)->ant = temp->ant;
    temp->sig = NULL;
    temp->ant = NULL;
    *nodo = NULL;
    return temp;
}
