#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <time.h>
using namespace std;

//Tertis
//Display 80 horizontal = x
//Display 24 vertical   = y
//Area x de juego? = 10

//Duplicar tamaño fichas
//    +-----------------------------------------+
//    |FICHAS                                   |
//    +-----+-----+----+-----+-----+------+-----+
//    | @@  |  @@ | @@ | @   |   @ |      |  @  |
//    |  @@ | @@  | @@ | @@@ | @@@ | @@@@ | @@@ |
//    +-----+-----+----+-----+-----+------+-----+


void rellenador(string matriz[80][24]){   //Rellena de #
    for(int y=0;y<24;y++){
        for(int x=0;x<80;x++){
            matriz[x][y]="#";
        }
    }
}

int random_valor(){                     //Hay solamente 7 fichas
    int iSecret;
    srand (time(NULL));
    iSecret = rand() % 7 + 1;
    return iSecret;
}

void insertar(string matriz[80][24], string palabra, int x, int y){
    for(int pos=0;pos<palabra.size();pos++){
        matriz[x+pos][y]=palabra[pos];
    }
}

void grilla(string matriz[80][24],int decorado){   //Crea las rayitas y eso + menu principal si decorado==1

    if(decorado==1){                //pantalla inicial
         for(int y=0;y<24;y++){
            for(int x=0;x<80;x++){
                if(x<20 || x>58){
                    matriz[x][y]="/";
                }else{
                    matriz[x][y]=" ";
                }

            }
        }
    }else{                      //Pantalla juego
        for(int y=0;y<24;y++){
            for(int x=0;x<80;x++){
                if((y==3 && x<20) || (y==3 && x>58)){
                    matriz[x][y]="-";
                }else if(x==20 || x==58){
                    if(y==3){
                        matriz[x][y]="+";
                    }else{
                        matriz[x][y]="|";
                    }
                }else{
                    matriz[x][y]=" ";
                }
            }
        }
    }
}

void delay(int milisegundos){
    //milisegundos*=1000;
    clock_t start_time = clock();
    while (clock() < start_time + milisegundos);
}

void displayer(string matriz[80][24]){  //Displayea
    for(int y=0;y<23;y++){
        for(int x=0;x<80;x++){
            //delay(2000);
            cout<<matriz[x][y]<<"";
        }cout<<endl;
    }
    //cout<<endl<<endl;
}

void timer(string matriz[80][24],int segundos){
    int minutos=segundos/60;
    segundos-=minutos*60;
    string minu=to_string(minutos);
    string segu=to_string(segundos);

    insertar(matriz,"Tiempo:"    ,3,9); //Tiempo
    if(minutos>=0 && minutos<10){        //SI acomoda la posicion de _1 a 01
        insertar(matriz," ",3,10);
        insertar(matriz,minu,4,10);
    }else{
        insertar(matriz,minu,3,10);
    }

    insertar(matriz,":",5,10);          //El divisor

    if(segundos==0){
        insertar(matriz,"00",6,10);
    }else if(segundos>0 && segundos<10){
        insertar(matriz,"0" ,6,10);
        insertar(matriz,segu,7,10);
    }else{
        insertar(matriz,segu,6,10);
    }
}

void puntajeador(string matriz[80][24],int puntaje){
    string puntos=to_string(puntaje);
    insertar(matriz,"Puntaje: "  ,3,6); //Puntos
    insertar(matriz,puntos       ,3,7);
}

void cursor(string matriz[80][24],int pos){

    int puntox=24;
    int puntoy=10;
    string icono="@";

    if      (pos==1){       //Jugar
        insertar(matriz,icono,puntox,puntoy+0);
    }else if(pos==2){       //Puntajes
        insertar(matriz,icono,puntox,puntoy+3);
    }else{                  //Salir
        insertar(matriz,icono,puntox,puntoy+8);
    }
}

void menu_principal(string matriz[80][24]){
    grilla(matriz,1);
    insertar(matriz,"- T E T R I S -",32,3);
    int puntox=26;
    int puntoy=10;
    insertar(matriz,"Jugar"   ,puntox,puntoy+0);
    insertar(matriz,"Puntajes",puntox,puntoy+3);
    insertar(matriz,"Salir"   ,puntox,puntoy+8);

    //Hacer lo de conexion con el teclado
    //int
    cursor(matriz,1);   //Pos inicial    @ Jugar
    displayer(matriz);


    //Solo flechas arriba y abajo                       //IMPORTANTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    string flechas;
    bool enter=false;
    int pos=1;
}

void perdiste(string matriz[80][24],int puntaje){

    int puntox=24;
    int puntoy=8;
    string a="cghfdjhfdhgjkdshasjkhdhiurhgreh",puntos;
    puntos=to_string(puntaje);

    while(a=="cghfdjhfdhgjkdshasjkhdhiurhgreh"){
        grilla(matriz,1);

        insertar(matriz,"Perdiste!",puntox+10,puntoy-4);

        insertar(matriz,"Puntaje: ",puntox   ,puntoy+4);
        insertar(matriz,puntos     ,puntox+10,puntoy+4);

        insertar(matriz,"Presione cualquier"  ,puntox,puntoy+8);
        insertar(matriz,"tecla para continuar",puntox,puntoy+9);
        displayer(matriz);
        cin>>a;
        system("clear");
    }
}

void interfaz_juego(string matriz[80][24],int puntaje,int segundos){
    grilla(matriz,0);
    insertar(matriz,"T E T R I S",4,1); //Titulo
    puntajeador(matriz,puntaje);
    timer(matriz,segundos);
}

void juego(string matriz[80][24]){

    int segundos=0;
    int puntaje=0;
    bool game=true;
    while(game==true){  //Si perdes game=false
        interfaz_juego(matriz,puntaje,segundos);
        displayer(matriz);
        segundos++;
        delay(1000);
        system("clear");
        //if(segundos==3){   game=false; }
    }
    perdiste(matriz,puntaje);
    menu_principal(matriz);
}

void copiador(string original[80][24],string datos[80][24]){     //No funciona este :c

     for(int y=0;y<24;y++){     //Rellena area de juego
        for(int x=0;x<80;x++){
            if(x>20 && x<58){
                original[x][y]="#";
            }
        }
     }

    for(int y=0;y<24;y++){     //Copia matriz juego a matriz display
        for(int x=0;x<80;x++){
            if(x>20 && x<58){
                original[x][y]=datos[x][y];
            }
        }
     }
}

void creador_fichas(){          //NO FUNCIONA
    //Entre 20 y 58
    //    +-----------------------------------------+
    //    |FICHAS                                   |  ####    ##
    //    +-----+-----+----+-----+-----+------+-----+  ####    ##
    //    | @@  |  @@ | @@ | @   |   @ |      |  @  |    ####  ######
    //    |  @@ | @@  | @@ | @@@ | @@@ | @@@@ | @@@ |    ####  ######
    //    +-----+-----+----+-----+-----+------+-----+

    string piezas[7][3][6];
    string caracter="0";
    //string pieza1[8][4];

    //Ficha 1   ##
    //           ##
    string pieza1[8][4]={
        {"#","#"," "," "},
        {"#","#"," "," "},
        {"#","#","#","#"},
        {"#","#","#","#"},
        {" "," ","#","#"},
        {" "," ","#","#"},
        {" "," "," "," "},
        {" "," "," "," "}
    };



    //for(int z=0;z<7;z++){       //Couteador de las fichas
        for(int y=0;y<4;y++){
            for(int x=0;x<8;x++){
                cout<<pieza1[y][x];
            }cout<<endl;
        }cout<<endl<<endl;
    //}

}

void fichas_test(string matriz[80][24]){
    //Entre 20 y 58
    string game[80][24];
    for(int y=0;y<24;y++){      //Matriz de juego
        for(int x=0;x<80;x++){
            game[x][y]="@";
        }
    }
    //for(int y=0;y<24;y++){  for(int x=0;x<38;x++){  cout<<game[x][y];   }cout<<endl;    }
    copiador(matriz,game);
    displayer(matriz);
}

int main(){

    string matriz[80][24];      //Matriz principal
    int puntaje=0;
    int segundos=0;
    //rellenar(matriz);     //Testea los parametros de la matriz
    //interfaz_juego(matriz,puntaje,segundos);    //Para cuando jugas
    //menu_principal(matriz);                   //Menu principal
    //displayer(matriz);
    //segundos++;
    //system("color b1"); //cambia el color uwu
    //juego(matriz);
    //fichas_test(matriz);
    creador_fichas();

    return 0;
}
