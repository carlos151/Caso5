#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>

using namespace std;

typedef vector<pair<pair<int,int>,pair<int,int>>> estructuraDePuntos;
typedef pair<estructuraDePuntos,estructuraDePuntos> puntosSeparados;

//retorna una lista con solo los puntos del cuadrante definido por los limites (no funciona bien todavia)
puntosSeparados extraerCuadrante(int inferiorX, int superiorX, int inferiorY, int superiorY,puntosSeparados* puntos){
    puntosSeparados resultado;
    int contadorH = 0;
    int contadorV = 0;
    bool horizontalHecho = false;
    pair<pair<int,int>,pair<int,int>> actual;
    while(actual.first.first >= inferiorX && actual.first.first < superiorX && actual.first.second >= inferiorY && actual.first.second < superiorY){
        //cout << "(" << actual.first.first << "," << actual.first.first << ")" << endl;
        if(!horizontalHecho){
            actual = puntos->first.at(contadorH);
            resultado.first.push_back({actual.first,actual.second});
            puntos->first.erase(puntos->first.begin() + contadorH);
            if(contadorH == puntos->first.size()-1){
                horizontalHecho = true;
            }
            contadorH++;
        }
        else{
            actual = puntos->second.at(contadorV);
            resultado.second.push_back({actual.first,actual.second});
            puntos->second.erase(puntos->second.begin() + contadorV);
            contadorV++;
        }
    }
    return resultado;
}

bool static comparar(pair<pair<int,int>,pair<int,int>> a, pair<pair<int,int>,pair<int,int>> b){
    if(a.first.second == 0 && b.first.second == 0){
        return (a.first.first < b.first.first);
    }
    else if(a.first.second == 0 && b.first.second != 0){
        return false;
    }
    else if(a.first.second != 0 && b.first.second == 0){
        return true;
    }
    else{
        return (a.first.second < b.first.second);
    }
}

//separa los puntos en dos estructuraDePuntos, una con los puntos que salen del eje X (Horizontales) y otra del eje Y (Verticales)
puntosSeparados separarPuntos(estructuraDePuntos puntos){
    puntosSeparados resultado;
    sort(puntos.begin(),puntos.end(),comparar);
    estructuraDePuntos puntosHorizontales;
    estructuraDePuntos puntosVerticales;
    for(int i = 0; i < puntos.size(); i++){
        auto actual = puntos.at(i);
        if(actual.first.second == 0){
            puntosHorizontales.push_back(actual);
        }
        else{
            puntosVerticales.push_back(actual);
        }
    }
    resultado = {puntosHorizontales,puntosVerticales};
    return resultado;

}

//funcion principal
void analizar(int cuadrantesX, int cuadrantesY,estructuraDePuntos puntos){
    int cantidadLineas = puntos.size();
    int saltoX = 1080/cuadrantesX;
    int saltoY = 920/cuadrantesY;
    int limiteInferiorX = 0;
    int limiteSuperiorX = saltoX;
    int limiteInferiorY = 0;
    int limiteSuperiorY = saltoY;
    for(int contador = 0; contador < cuadrantesX*cuadrantesY; contador++){

    }
}

estructuraDePuntos generarLineas(int cantidad){
    estructuraDePuntos resultado;
    bool cantidadPar;
    if(cantidad % 2 == 0){
        cantidadPar == true;
    }
    else{
        cantidadPar == false;
        cantidad--;
    }
    int cantidadHorizontales = 0;
    int cantidadVerticales = 0;
    unordered_map<int,int> numerosUsadosX;
    unordered_map<int,int> numerosUsadosY;
    while(cantidadHorizontales+cantidadVerticales < cantidad){
        if(cantidadHorizontales < cantidad/2){
            int randomX = rand() % 1079;
            if(numerosUsadosX.find(randomX) == numerosUsadosX.end()){
                int randomEnd = (rand() % 15) - 15;
                resultado.push_back({{randomX,0},{randomX+randomEnd,919}});
                cantidadHorizontales++;
                numerosUsadosX.insert({randomX,1});
            }
            if(!cantidadPar && cantidadHorizontales == (cantidad/2)){
                randomX = rand() % 1079;
                int randomEnd = (rand() % 15) - 15;
                resultado.push_back({{randomX,0},{randomX+randomEnd,919}});
                cantidadHorizontales++;
                numerosUsadosX.insert({randomX,1});
            }
        }
        else{
            int randomY = rand() % 919;
            if(numerosUsadosY.find(randomY) == numerosUsadosY.end()){
                int randomEnd = (rand() % 15) - 15;
                resultado.push_back({{0,randomY},{1079,randomY+randomEnd}});
                cantidadVerticales++;
                numerosUsadosY.insert({randomY,1});
            }
        }
    }
    return resultado;
}

void printPuntos(estructuraDePuntos puntos){
    for(int i = 0;i<puntos.size();i++){
        auto actual = puntos.at(i);
        cout << "[(" << actual.first.first << "," << actual.first.second << "),(" << actual.second.first << "," << actual.second.second << ")]" << endl;
    }
}

int main(){
    estructuraDePuntos puntos = generarLineas(21);
    puntosSeparados sepPuntos = separarPuntos(puntos);
    puntosSeparados primerCuadrante = extraerCuadrante(0,250,0,160,&sepPuntos);
    printPuntos(primerCuadrante.first);
    printPuntos(primerCuadrante.second);

    cout << endl;

    printPuntos(sepPuntos.first);
    printPuntos(sepPuntos.second);
}