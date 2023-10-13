#include "trem.h"
#include <QtCore>
#include <QtDebug>
#include <string>
#include <stdio.h>
#include <mutex>
#include <chrono>
#include <unistd.h>
#include <map>


using namespace std;

#define N_CRIT 7 /* Número de regiões críticas */
#define N_TRENS 5 /* Número de trens */

QMutex mutexes[N_CRIT];

int state[N_TRENS]; //array para controlar o estado dos trens

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 50;

}

void Trem::setVelocidade(int velocidade){
    this->velocidade = velocidade;
}


void Trem::dir(){
    this->x += 10;
}

void Trem::esq(){
    this->x -= 10;
}

void Trem::sobe(){
    this->y -= 10;
}

void Trem::desce(){
    this->y += 10;
}



//Função a ser executada após executar trem->START
void Trem::run(){


    while(true){
       if (this->velocidade == 0){
                    emit updateGUI(this->ID, this->x, this->y);
                    continue;
                }
        switch(ID){
        case 1:     //Trem 1
            if (x < 240 && y == 30){
                if (x == 220){
                   mutexes[0].lock();
                   mutexes[1].lock();
                   mutexes[5].lock();
                }

                dir();

            }else if (x == 240 && y < 150){
                if (y == 130){
                    mutexes[2].lock();
                }
                desce();

            }else if (x > 120 && y == 150){
                if (x == 220){
                    mutexes[0].unlock();
                }

                if (x == 180){
                    mutexes[2].unlock();
                    mutexes[5].unlock();
                }
                esq();
            }else if (x == 120 && y > 30){
                if (y == 130){
                    mutexes[1].unlock();
                    mutexes[2].unlock();
                }
                sobe();
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (x < 360 && y == 30){
                if (x == 260){
                    mutexes[0].unlock();
                    mutexes[6].unlock();
                }
                dir();

            }else if (x == 360 && y < 150){
                if (y == 130){
                    mutexes[4].lock();
                    mutexes[3].lock();
                }
                desce();
            }else if (x > 240 && y == 150){
                /*if (x == 320){
                    mutexes[3].lock();
                }*/
                if (x == 300){
                    mutexes[4].unlock();
                    mutexes[6].unlock();
                }
                if (x == 260){
                    mutexes[0].lock();
                    mutexes[2].lock();
                }

                esq();
            }else{
                if (y == 130){
                    mutexes[3].unlock();
                    mutexes[2].unlock();
                }
                sobe();
                //compart12(TREM2);
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (x < 420 && y == 150){
                if(x == 320){
                    mutexes[6].unlock();
                }
                if(x == 370){
                    mutexes[4].unlock();
                }
                dir();
            }
            else if (x == 420 && y < 270){
                desce();
            }
            else if (x > 300 && y == 270){/////////////////////
                if(x == 320){
                    mutexes[6].lock();
                }
                esq();
            }
            else if(x == 300 && y > 150){
                if (y == 170){
                    mutexes[4].lock();
                }
                sobe();
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (x < 300 && y == 150){
                if(x==200){
                    mutexes[5].unlock();
                }
                if(x == 220){
                    mutexes[3].lock();
                    mutexes[6].lock();
                    mutexes[0].unlock();
                }
                if (x == 260){
                    mutexes[2].unlock();
                }

                dir();
            }else if (x == 300 && y < 270){
                if (y == 170){
                    mutexes[3].unlock();
                }
                desce();
            }else if (x > 180 && y == 270){
                if (x == 200){
                    mutexes[5].lock();
                }
                if (x == 280){
                    mutexes[6].unlock();
                }
                esq();
            }else if (x==180 && y>150){                           
                if (y == 170){

                      mutexes[0].lock();
                }
                if (y == 210){
                    mutexes[2].lock();
                }
                sobe();
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (x < 180 && y == 150){
                if (x == 100){
                    mutexes[1].lock();
                }
                if (x == 140){
                    mutexes[5].lock();
                }
                dir();
            }else if (x == 180 && y < 270){
                if (y == 170){
                    mutexes[1].unlock();
                }
                desce();
            }else if (x > 60 && y == 270){
                if (x == 160){
                    mutexes[5].unlock();
                }
                esq();
            }else if (x == 60 && y > 150){
                  sobe();
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;

        default:
            break;
        }
        msleep(velocidade);

    }

}

