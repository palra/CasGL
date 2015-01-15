#include "time.h"

static int SysCallCode[] = {0xD201422B,0x60F20000,0x80010070}; // déclaration en global des adresses
static int (*SysCall)(int R4, int R5, int R6, int R7, int FNo ) = (void*)&SysCallCode; // et des registres


int RTC_getTicks(void)
{
     return (*SysCall)(0, 0, 0, 0, 0x3B); // on déclare la fonction voulue selon son numéro (ici 0x3B)
}

void setFps(int fpsWish)
{
    static unsigned int fps = 0, fps_count = 0; // "static" permet de garder les valeurs en mémoire entre les différents appels

    do
    {
        fps = RTC_getTicks(); // on enregistre les ticks
                Sleep(1); // permet d'économiser de la batterie
    }
    while(fps < fps_count+fpsWish); // tant que ceux-ci ne se sont pas suffisamment écoulés
    fps_count = RTC_getTicks(); // on met à jour les dernières valeurs
}