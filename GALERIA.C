#include<allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include<string.h>
#include "LdobleC.h"



int Galeria();char *Nombre(int opc);
int Imagenes(BITMAP *galeria,BITMAP *galeria2,BITMAP *galeria3,BITMAP *galeria4,BITMAP *buffer, char *nom,TnodoD *listaDC);

int main()
{
    Galeria();
}
END_OF_MAIN();

int Galeria()
{

    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,MAXANCHO, MAXALTO, 0, 0);
    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT,NULL)!=0)
    {
        allegro_message("pene",allegro_error);
        return 1;
    }
    set_volume(230,200);

    BITMAP *buffer = create_bitmap(MAXANCHO,MAXALTO);
    BITMAP *menu1 = load_bitmap("Menus/Pantalla_Principal_Desktop/Pantalla_Principal_01.bmp",NULL);
    BITMAP *menu2 = load_bitmap("Menus/Pantalla_Principal_Desktop/Pantalla_Principal_02.bmp",NULL);
    BITMAP *menu3 = load_bitmap("Menus/Pantalla_Principal_Desktop/Pantalla_Principal_03.bmp",NULL);
    BITMAP *carpetas = load_bitmap("Menus/Albumes/Album_00.bmp",NULL);
    BITMAP *carpetas1 = load_bitmap("Menus/Albumes/Album_01.bmp",NULL);
    BITMAP *carpetas2 = load_bitmap("Menus/Albumes/Album_02.bmp",NULL);
    BITMAP *carpetas3 = load_bitmap("Menus/Albumes/Album_03.bmp",NULL);
    BITMAP *carpetas4 = load_bitmap("Menus/Albumes/Album_04.bmp",NULL);
    BITMAP *carpetas5 = load_bitmap("Menus/Albumes/Album_05.bmp",NULL);
    BITMAP *carpetas6 = load_bitmap("Menus/Albumes/Album_06.bmp",NULL);
    BITMAP *galeria = load_bitmap("Menus/Contenedor_de_Imagenes/Contenedor_01.bmp",NULL); //Principal
    BITMAP *galeria2 = load_bitmap("Menus/Contenedor_de_Imagenes/Contenedor_02.bmp",NULL); //Salir
    BITMAP *galeria3 = load_bitmap("Menus/Contenedor_de_Imagenes/Contenedor_03.bmp",NULL); //Eliminar
    BITMAP *galeria4 = load_bitmap("Menus/Contenedor_de_Imagenes/Contenedor_04.bmp",NULL); //Regresar

    MIDI *musica1  = load_midi("careless.mid");
    play_midi(musica1,1);
    int flag = 0,opc,arch;
    DIR *dir;
    struct dirent *ent;
    char nom[MAXDIR];
    TnodoD listaDC=NULL;

    flag = Menus(menu1,menu2,menu3,buffer);

    if( flag == 1 )
    {
        do{
            arch = 0;
            opc = Carpetas(buffer,carpetas,carpetas1,carpetas2,carpetas3,carpetas4,carpetas5,carpetas6);
            if( opc != 6 )
            {
                strcpy(nom,Nombre(opc));
                dir = opendir (nom);
                if(dir == NULL)
                error("No puedo abrir el directorio");

                while ((ent = readdir (dir)) != NULL)
                {
                    if ( (strcmp(ent->d_name, nom)!=0) && (strcmp(ent->d_name, "..")!=0) && arch == 1)
                    {
                        procesoArchivo(ent->d_name,&listaDC,nom);
                    }
                    arch=1;
                }
                opc = Imagenes(galeria,galeria2,galeria3,galeria4,buffer,nom,&listaDC);
                if(listaDC)
                {
                    printf("Archivos:\n");
                    ImprimirLDC(listaDC);
                    SalirLDC(&listaDC);
                }
                closedir (dir);
            }
            listaDC = NULL;
        }while( opc != 6 );
    }


    destroy_bitmap(buffer);
}

char *Nombre(int opc)
{
    char name[MAXDIR];
    switch(opc)
    {
        case 1:
            strcpy(name,"ALBUMES/ACTRICES");
            break;
        case 2:
            strcpy(name,"ALBUMES/COSPLAY");
            break;
        case 3:
            strcpy(name,"ALBUMES/INSTAGRAM");
            break;
        case 4:
            strcpy(name,"ALBUMES/SINCENSURA");
            break;
        case 5:
            strcpy(name,"ALBUMES/ONPAINT");
            break;
    }
    return name;
}

int Imagenes(BITMAP *galeria,BITMAP *galeria2,BITMAP *galeria3,BITMAP *galeria4,BITMAP *buffer, char *nom,TnodoD *listaDC)
{


    int salida = 0;
    TnodoD temp=NULL,nodo=NULL,aux=NULL;

    temp = *listaDC;
    while(salida == 0)
    {
        if(temp)
            draw_sprite(galeria,temp->foto,320,5);
        if( mouse_x > 119 && mouse_x < 167 && mouse_y > 9 && mouse_y < 50 )//salir
        {
            blit(galeria2,buffer,0,0,0,0,MAXANCHO,MAXALTO);
            draw_sprite(galeria2,temp->foto,320,5);
            if( mouse_b & 1 )
            {
                salida = 6;
            }
        }
        else
        {
            if( mouse_x > 913 && mouse_x < 993 && mouse_y > 217 && mouse_y < 302) //Siguiente
            {
                if( mouse_b & 1 )
                {
                    rest(200);
                    temp = temp->sig;
                    clear(buffer);
                }
            }
            else
            {
                if( mouse_x > 8 && mouse_x < 85 && mouse_y > 221 && mouse_y < 304) //anterior
                {
                    if( mouse_b & 1 )
                    {
                        rest(200);
                        temp = temp->ant;
                        clear(buffer);
                    }
                }
                else
                {
                    if( mouse_x > 14 && mouse_x < 44 && mouse_y > 9 && mouse_y < 50)//eliminar
                    {
                        if(temp)
                            blit(galeria3,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                        draw_sprite(galeria3,temp->foto,320,5);
                        if( mouse_b & 1 )
                        {
                            rest(200);
                            nodo = temp;
                            if(temp->sig == temp)
                            {
                                temp = NULL;
                                salida = 1;
                            }
                            else
                            {
                                temp = temp->sig;
                            }
                            aux = EliminarLDC(&*listaDC,&nodo);
                            free(aux);
                        }
                    }
                    else
                    {
                        if( mouse_x > 60 && mouse_x < 100 && mouse_y > 9 && mouse_y < 50)//regresar
                        {
                            blit(galeria4,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                            draw_sprite(galeria4,temp->foto,320,5);
                            if(mouse_b & 1)
                            {
                                salida = 1;
                            }
                        }
                    }

                }
            }
            blit(galeria,buffer,0,0,0,0,MAXANCHO,MAXALTO);
        }
        show_mouse(screen);
        blit(buffer,screen,0,0,0,0,MAXANCHO,MAXALTO);
    }

    return salida;
}
