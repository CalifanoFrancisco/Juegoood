#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

class TileMap : public sf::Drawable, public sf::Transformable{
    public:
        bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height){
            if (!m_tileset.loadFromFile(tileset))   // load the tileset texture
                return false;

            // resize the vertex array to fit the level size
            m_vertices.setPrimitiveType(sf::Quads);
            m_vertices.resize(width * height * 4);

            // populate the vertex array, with one quad per tile
            for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                int tileNumber = tiles[i + j * width];  // get the current tile number

                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x); // find its position in the tileset texture
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];        // get a pointer to the current tile's quad

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
            return true;
        }

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        states.transform *= getTransform();  // apply the transform
        states.texture = &m_tileset;         // apply the tileset texture
        target.draw(m_vertices, states);     // draw the vertex array
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

bool mouse_click(){
    bool shot=false;
    if(Mouse::isButtonPressed(Mouse::Left)){    return true;    }
    else{                                       return false;   }
}

int select_type_tile(){
    string tilename;
    int t=0;
    if (Keyboard::isKeyPressed(Keyboard::Num0)){    tilename="brick_wall";          t=0;   }
    if (Keyboard::isKeyPressed(Keyboard::Num1)){    tilename="grass";               t=1;   }
    if (Keyboard::isKeyPressed(Keyboard::Num2)){    tilename="brick_roof";          t=2;   }
    if (Keyboard::isKeyPressed(Keyboard::Num3)){    tilename="right_grass_water";   t=3;   }
    if (Keyboard::isKeyPressed(Keyboard::Num4)){    tilename="left_grass_water";    t=4;   }
    if (Keyboard::isKeyPressed(Keyboard::Num5)){    tilename="up_grass_water";      t=5;   }
    if (Keyboard::isKeyPressed(Keyboard::Num6)){    tilename="down_grass_water";    t=6;   }
    if (Keyboard::isKeyPressed(Keyboard::Num7)){    tilename="water";               t=7;   }
    if (Keyboard::isKeyPressed(Keyboard::Num8)){    tilename="";            t=8;   }
    if (Keyboard::isKeyPressed(Keyboard::Num9)){    tilename="";            t=9;   }
    cout<<"Tile selected: "<<tilename<<" NÂ°"<<t<<endl;
    return t;
}

void guardar_en_txt(bool level[],int X, int Y){
    int c=0;
    ofstream archivo;
    archivo.open("matrizcolisiones.txt");
    fflush(stdin);

    archivo<<"int matriz_colisiones[]{"<<endl;      //Abre

    for(int x=0;x<Y;x++){
        archivo<<"      ";
        for(int y=0;y<X;y++){
            archivo<<level[c]<<" , ";
            c++;
        }archivo<<endl;
    }
    archivo<<"};"<<endl;                            //Cierra
    archivo.close();
}

Vector2i selected_tile(int X, int Y,int windaltura, int windanchura,int &bloqueX, int &bloqueY){

    while(X>32){    X-=32;  if(bloqueX<windanchura-1){ bloqueX++;  }}
    while(Y>32){    Y-=32;  if(bloqueY<windaltura -1){ bloqueY++;  }}
    bloqueX++;
    bloqueY++;
    Vector2i bloques;
    bloques.x=bloqueX;
    bloques.y=bloqueY;
    //cout<<"X: "<<bloqueX<<"  Y: "<<bloqueY<<" NÂ°: "<<bloqueY*30+bloqueX<<endl;
    return bloques;

}

void tecladoj2(Sprite &sprite2,View &view,IntRect &todo,bool derecha,bool izquierda,bool adelante,bool atras){
    float avance=1.2;
    int multiplicador=6;
    //float movimiento=5;
    if (adelante  == true && Keyboard::isKeyPressed(Keyboard::W)){
        todo.left=18;
         if (Keyboard::isKeyPressed(Keyboard::LShift)){
            sprite2.setPosition(sprite2.getPosition().x, sprite2.getPosition().y - (avance*multiplicador));
            view.move(0,-(avance)*multiplicador);
        }else{
            sprite2.setPosition(sprite2.getPosition().x, sprite2.getPosition().y - (avance));
            view.move(0,-(avance));
        }
    }
    if (izquierda == true && Keyboard::isKeyPressed(Keyboard::A)){
        todo.left=12;
        if (Keyboard::isKeyPressed(Keyboard::LShift)){
            sprite2.setPosition(sprite2.getPosition().x - (avance*multiplicador), sprite2.getPosition().y);
            view.move(-(avance)*multiplicador,0);
        }else{
            sprite2.setPosition(sprite2.getPosition().x - avance, sprite2.getPosition().y);
            view.move(-(avance),0);

        }        //sprite2.rotate(rot);
    }
    if (atras     == true && Keyboard::isKeyPressed(Keyboard::S)){
        todo.left=0;
        if (Keyboard::isKeyPressed(Keyboard::LShift)){
            sprite2.setPosition(sprite2.getPosition().x, sprite2.getPosition().y + (avance*multiplicador));
            view.move(0,(avance)*multiplicador);
        }else{
            sprite2.setPosition(sprite2.getPosition().x, sprite2.getPosition().y + avance);
            view.move(0,(avance));
        }
    }
    if (derecha   == true && Keyboard::isKeyPressed(Keyboard::D)){
        todo.left=6 ;
        if (Keyboard::isKeyPressed(Keyboard::LShift)){
            sprite2.setPosition(sprite2.getPosition().x + (avance*multiplicador), sprite2.getPosition().y);
            view.move(avance*multiplicador,0);
        }else{
            sprite2.setPosition(sprite2.getPosition().x + avance, sprite2.getPosition().y);
            view.move(avance,0);
        }
        //sprite2.rotate(0-rot);
    }
    sprite2.setTextureRect(todo);
}

void collision_map(int level[510],bool matriz_colisiones[510]){
//------------------------------------------------------------------------------------------------------------------
//                               |0|1|2|3|4|5|6|7|8|9|
    bool bloques_de_colision[10]={1,0,1,1,1,1,1,1,0,0};     //RELLENAR MANUALMENTE
//------------------------------------------------------------------------------------------------------------------
    for(int i=0;i<510;i++){ matriz_colisiones[i]=false; }
//------------------------------------------------------------------------------------------------------------------
    for(int l=0;l<9;l++){                      //l=cantidad de texturas
        if(bloques_de_colision[l]==true){       //Chequea si el valor de pos es verdadero
            for(int i=0;i<510;i++){
                if(level[i]==l){    matriz_colisiones[i]=true;  }
            }
        }
    }
}

bool colisiones_con_mapa(bool mapa_colision[510],float X, float Y){
    int pos=Y*30+X;
    for(int i=0;i<510;i++){
        if(mapa_colision[i]==true && pos==i){
            cout<<"Colision!"<<endl;
            return true;
        }
    }
    return false;
}

void flechas(bool mapa_colision[510],Sprite j1,bool &arriba,bool &abajo,bool &derecha, bool &izquierda){

    //float x=j1.getPosition().x/32;
    int m=-10;
    float y=(j1.getPosition().y-m)/32;
    float x=(j1.getPosition().x-m)/32;
    int   X=x;
    int   Y=y;
    cout<<"X: "<<X<<"  Y: "<<Y<<endl;
    //------------------------------------------------------------------------------------------------------------------
    bool colision=colisiones_con_mapa(mapa_colision,X,Y);
    if(colision==true){
/*      :/              */
    }
    //------------------------------------------------------------------------------------------------------------------
    if(x<0    ){   izquierda = false;  }else{  /*izquierda = true;*/   }
    if(y<0.08 ){   arriba    = false;  }else{  /*arriba    = true;*/   }
    if(x>29.5 ){   derecha   = false;  }else{  /*derecha   = true;*/   }
    if(y>16.25){   abajo     = false;  }else{  /*abajo     = true;*/   }
}

void collision_map_couter(bool matriz_colisiones[510]){
    cout<<"bool matriz_colisiones[]={"<<endl;
    for(int y=0;y<17;y++){
        cout<<"     ";
        for(int x=0;x<30;x++){
            int pos=y*30+x;
            if(matriz_colisiones[pos]==true){   cout<<"1";  }
            else{                               cout<<"0";  }
        }cout<<endl;
    }cout<<"}; "<<endl<<endl;
    //guardar_en_txt(matriz_colisiones,30,17);
}

int main(){
//----------------------------------------------------------------------------------------------------------------------
    int alturapantalla =1080/2;
    int anchurapantalla=1920/2;
    RenderWindow window(sf::VideoMode(anchurapantalla,alturapantalla), "Juwuego");    // create the window
    int X=30;       //Width
    int Y=17;       //Height
//----------------------------------------------------------------------------------------------------------------------
	window.setFramerateLimit(30);       //Poner en 60
//----------------------------------------------------------------------------------------------------------------------
    int level1[]{
      2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 0 , 0 , 0 ,
      2 , 0 , 0 , 0 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 1 , 1 , 2 , 3 , 7 , 4 ,
      2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 3 , 7 , 7 , 7 , 7 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 2 , 1 , 1 , 1 , 2 , 3 , 7 , 4 , 2 , 2 , 1 , 1 ,
      1 , 1 , 1 , 1 , 1 , 3 , 7 , 7 , 7 , 7 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
      2 , 2 , 1 , 1 , 1 , 2 , 3 , 7 , 4 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 ,
      1 , 3 , 7 , 7 , 7 , 7 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 0 , 1 ,
      0 , 0 , 3 , 0 , 4 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 3 , 7 ,
      4 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 0 , 0 , 0 , 0 ,
      0 , 0 , 0 , 2 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 3 , 7 , 4 , 1 , 1 , 1 ,
      1 , 1 , 1 , 1 , 1 , 2 , 2 , 2 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 ,
      2 , 2 , 2 , 1 , 1 , 1 , 1 , 8 , 8 , 8 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 2 , 1 ,
      1 , 1 , 1 , 3 , 7 , 4 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 1 , 1 , 1 , 3 ,
      7 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 ,
      1 , 1 , 1 , 1 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 3 , 7 , 2 , 1 , 1 ,
      1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      2 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 3 , 7 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 ,
      1 , 1 , 1 , 1 , 3 , 7 , 4 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 1 , 1 , 1 , 1 ,
      8 , 8 , 8 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 1 , 1 , 1 , 1 , 3 , 7 , 4 , 1 ,
      1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      1 , 1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
    };
//----------------------------------------------------------------------------------------------------------------------
    int level2[]{
      2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 0 , 0 , 0 ,
      0 , 0 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 2 , 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      0 , 1 , 1 , 1 , 3 , 7 , 4 , 1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
      2 , 1 , 2 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      8 , 8 , 8 , 1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 0 , 1 , 0 , 2 ,
      2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 1 , 1 , 3 , 7 , 4 , 1 ,
      1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 1 , 1 , 2 , 2 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 1 , 1 , 1 , 2 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 1 , 1 , 1 , 0 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      1 , 3 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 4 , 1 , 1 , 1 , 1 , 1 ,
      1 , 2 , 2 , 1 , 2 , 0 , 0 , 2 , 1 , 0 , 0 , 2 , 0 , 1 , 3 , 7 , 7 ,
      7 , 7 , 7 , 7 , 7 , 7 , 7 , 4 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 1 ,
      2 , 1 , 1 , 2 , 1 , 1 , 1 , 2 , 1 , 1 , 3 , 7 , 7 , 5 , 5 , 5 , 5 ,
      7 , 7 , 7 , 4 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 1 , 0 , 0 , 1 , 2 ,
      1 , 1 , 1 , 2 , 1 , 1 , 3 , 7 , 4 , 1 , 1 , 1 , 1 , 3 , 7 , 7 , 4 ,
      1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 , 1 , 1 , 1 , 1 , 2 , 0 , 0 , 1 , 2 ,
      1 , 8 , 8 , 8 , 8 , 8 , 1 , 1 , 8 , 8 , 8 , 8 , 8 , 8 , 1 , 1 , 1 ,
      1 , 1 , 2 , 2 , 1 , 2 , 0 , 1 , 2 , 1 , 1 , 1 , 2 , 1 , 1 , 3 , 7 ,
      4 , 1 , 1 , 1 , 1 , 3 , 7 , 7 , 4 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 2 ,
      1 , 2 , 1 , 1 , 2 , 1 , 1 , 1 , 2 , 1 , 1 , 3 , 7 , 7 , 6 , 6 , 6 ,
      6 , 7 , 7 , 7 , 7 , 6 , 6 , 6 , 6 , 6 , 6 , 2 , 2 , 1 , 0 , 0 , 0 ,
      0 , 1 , 0 , 0 , 0 , 0 , 1 , 3 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 ,
      7 , 5 , 5 , 5 , 5 , 5 , 5 , 2 , 2 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
      1 , 1 , 1 , 3 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 4 , 1 , 1 , 1 ,
      1 , 1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
      2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
};
//----------------------------------------------------------------------------------------------------------------------
    //Cambiar el mapa desde aca
    int level[510];
    for(int c;c<510;c++){   level[c]=level2[c]; }
//----------------------------------------------------------------------------------------------------------------------
    bool matriz_colisiones[510];
    collision_map(level,matriz_colisiones);
    //collision_map_couter(matriz_colisiones);
//----------------------------------------------------------------------------------------------------------------------
    TileMap mapa;   // create the tilemap from the level definition
//----------------------------------------------------------------------------------------------------------------------
    View camara;
    camara.zoom(0.25);
    camara.move(-370,-375);
//----------------------------------------------------------------------------------------------------------------------
    Texture alien;
    if (!alien.loadFromFile("alien.png")){  cout<<"No esta la imagen";  return 0; }
    IntRect adelanten(0,1,6,10);
    Sprite j1(alien,adelanten);
    j1.scale(2.5,2.5);
    j1.move(90,100);
//----------------------------------------------------------------------------------------------------------------------
    Texture fondo;
    if (!fondo.loadFromFile("techo.png")){  cout<<"No esta la imagen";  return 0; }
    Sprite background;
    background.setTexture(fondo);
    background.scale(50,50);
    background.move(-300,-300);
//----------------------------------------------------------------------------------------------------------------------
    bool derecha,izquierda,adelante,atras;
    derecha   = true;
    izquierda = true;
    adelante  = true;
    atras     = true;
//----------------------------------------------------------------------------------------------------------------------
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){    if(event.type == sf::Event::Closed) window.close(); }

        flechas(matriz_colisiones,j1,adelante,atras,derecha,izquierda);

        tecladoj2(j1,camara,adelanten,derecha,izquierda,adelante,atras);

        if (!mapa.load("tileset2.png", Vector2u(32, 32), level, X, Y))return -1; //Mapa 1
        //if (!mapa.load("tileset2.png", sf::Vector2u(32, 32), level2, X, Y))return -1;   //Mapa 2

        window.clear();

        window.setView(camara);

        window.draw(background);
        window.draw(mapa);
        window.draw(j1);
        window.display();
    }
    return 0;
}

