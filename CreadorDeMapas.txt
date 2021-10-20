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
    if (Keyboard::isKeyPressed(Keyboard::Num0)){    tilename="brick_wall";  t=0;   }
    if (Keyboard::isKeyPressed(Keyboard::Num1)){    tilename="grass";       t=1;   }
    if (Keyboard::isKeyPressed(Keyboard::Num2)){    tilename="CAMBIAR";     t=2;   }
    if (Keyboard::isKeyPressed(Keyboard::Num3)){    tilename="CAMBIAR2";    t=3;   }
    if (Keyboard::isKeyPressed(Keyboard::Num4)){    tilename="";            t=4;   }
    if (Keyboard::isKeyPressed(Keyboard::Num5)){    tilename="";            t=5;   }
    if (Keyboard::isKeyPressed(Keyboard::Num6)){    tilename="";            t=6;   }
    if (Keyboard::isKeyPressed(Keyboard::Num7)){    tilename="";            t=7;   }
    if (Keyboard::isKeyPressed(Keyboard::Num8)){    tilename="";            t=8;   }
    if (Keyboard::isKeyPressed(Keyboard::Num9)){    tilename="";            t=9;   }
    cout<<"Tile n°"<<t<<endl;
    return t;
}

void guardar_en_txt(int level[],int X, int Y){
    ofstream archivo;
    archivo.open("MatrizFinal.txt");
    fflush(stdin);
    archivo<<"int level[]{"<<endl;    //Abre
    int c=0;
    for(int x=0;x<X;x++){
        for(int y=0;y<Y;y++){
            archivo<<level[c]<<",";
            c++;
        }archivo<<endl;
    }
    archivo<<"};"<<endl;                    //Cierra
    archivo.close();
}

void selected_tile(int X, int Y,int windaltura, int windanchura,int bloqueX, int bloqueY){

    while(X>32){    X-=32;  if(bloqueX<windanchura-1){ bloqueX++;  }}
    while(Y>32){    Y-=32;  if(bloqueY<windaltura -1){ bloqueY++;  }}
    bloqueX++;
    bloqueY++;
    cout<<"X: "<<bloqueX<<"  Y: "<<bloqueY<<endl;

}

void rellenador(int bloqueX,int bloqueY,int level[]){
    int tipo=select_type_tile();
    bool click=mouse_click();

    int posarray=0;
    if(click==true){
        posarray=bloqueX*bloqueY;
        level[posarray]=tipo;
    }

}

int main(){

    /*  0 = brick_wall
        1 = grass_w_flowers
        2 = CAMBIAR
        3 = CAMBIAR
        4 = stone_path
        5 = brick_roof
    */

    RenderWindow window(sf::VideoMode(960, 540), "Tilemap");    // create the window
	window.setFramerateLimit(30);

    int X=30;       //Width
    int Y=17;       //Height
    int level[X*Y]; //Tamaño total array

    for(int c=0;c<(X*Y);c++){   level[c]=1;     }   //Rellena el array de nada

    TileMap mapa;   // create the tilemap from the level definition
    if (!mapa.load("casillas.png", sf::Vector2u(32, 32), level, X, Y))return -1;

    int bloqueY=0,bloqueX=0;

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){    if(event.type == sf::Event::Closed) window.close(); }

        Vector2i mouse_pos = sf::Mouse::getPosition(window);
        selected_tile(mouse_pos.x,mouse_pos.y,Y,X,bloqueX,bloqueY);
        rellenador(bloqueX,bloqueY,level);

        // draw the map
        window.clear();
        window.draw(mapa);
        window.display();
    }

    return 0;
}

