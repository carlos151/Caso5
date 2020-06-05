#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>

using namespace std;

typedef vector<pair<pair<int,int>,pair<int,int>>> estructuraDePuntos;
typedef pair<estructuraDePuntos,estructuraDePuntos> puntosSeparados;
class resultadosDeAnalisis {
    public:
    int diagonalesCrecientes = 0;
    int diagonalesDecrecientes = 0;
    int verticales = 0;
    int horizontales = 0;
    int cantidadTotal = 0;

    void calcularTotales(){
        cantidadTotal = diagonalesCrecientes + diagonalesDecrecientes + verticales + horizontales;
    }
};
const int margenDeError = 5;

int generarRandom(int min,int max){
    static bool first = true;
    if (first) 
    {  
       srand( time(NULL) );
       first = false;
    }
    return min + rand() % ((max) - min);
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

bool static compararNormal(int a, int b){
    return (a < b);
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
resultadosDeAnalisis analizar(puntosSeparados puntosSep,float porcentajeAnalisis,int cantLineas){
    resultadosDeAnalisis resultado;
    int cantidadLineasAnalizar = cantLineas*porcentajeAnalisis;
    pair<pair<int,int>,pair<int,int>> lineaActual;
    int diagonalesCrecientes = 0;
    int diagonalesDecrecientes = 0;
    int verticales = 0;
    int horizontales = 0;
    int indiceRandom;
    for(int contador = 0; contador < cantidadLineasAnalizar; contador++){
        if(contador < cantidadLineasAnalizar/2){
            indiceRandom = generarRandom(0,puntosSep.first.size());
            lineaActual = puntosSep.first.at(indiceRandom);
            if(lineaActual.first.first >= lineaActual.second.first-margenDeError && lineaActual.first.first <= lineaActual.second.first+margenDeError){
                resultado.verticales++;
            }
            else if(lineaActual.first.first > lineaActual.second.first+margenDeError){
                resultado.diagonalesCrecientes++;
            }
            else{
                resultado.diagonalesDecrecientes++;
            }
            puntosSep.first.erase(puntosSep.first.begin()+contador);
        }
        else{
            indiceRandom = generarRandom(0,puntosSep.second.size());
            lineaActual = puntosSep.second.at(indiceRandom);
            if(lineaActual.first.second >= lineaActual.second.second-margenDeError && lineaActual.first.second <= lineaActual.second.second+margenDeError){
                resultado.horizontales++;
            }
            else if(lineaActual.first.second > lineaActual.second.second+margenDeError){
                resultado.diagonalesCrecientes++;
            }
            else{
                resultado.diagonalesDecrecientes++;
            }
            puntosSep.second.erase(puntosSep.second.begin()+contador);
        }
    }
    resultado.calcularTotales();
    return resultado;
}

int calcularPromedioAux(vector<int> lista){
    float suma = 0;
    float listaSize = lista.size();
    for(int contador = 0; contador < lista.size(); contador++){
        suma += lista.at(contador);
    }
    return (int)suma/listaSize;
}

resultadosDeAnalisis calcularPromedio(unordered_map<int,resultadosDeAnalisis> ejecuciones){
    vector<int> horizontales;
    vector<int> verticales;
    vector<int> diagonalesCrecientes;
    vector<int> diagonalesDecrecientes;
    for(int contador = 0; contador < ejecuciones.size(); contador++){
         horizontales.push_back(ejecuciones.at(contador).horizontales);
         verticales.push_back(ejecuciones.at(contador).verticales);
         diagonalesCrecientes.push_back(ejecuciones.at(contador).diagonalesCrecientes);
         diagonalesDecrecientes.push_back(ejecuciones.at(contador).diagonalesDecrecientes);
    }

    int promedioHorizontales = calcularPromedioAux(horizontales);
    int promedioVerticales = calcularPromedioAux(verticales);
    int promedioDiagonalesCrecientes = calcularPromedioAux(diagonalesCrecientes);
    int promedioDiagonalesDecrecientes = calcularPromedioAux(diagonalesDecrecientes);

    resultadosDeAnalisis resultadoFinal;
    resultadoFinal.horizontales = promedioHorizontales;
    resultadoFinal.verticales = promedioVerticales;
    resultadoFinal.diagonalesCrecientes = promedioDiagonalesCrecientes;
    resultadoFinal.diagonalesDecrecientes = promedioDiagonalesDecrecientes;
    return resultadoFinal;

}

resultadosDeAnalisis realizarAnalisisCompleto(estructuraDePuntos puntos,float porcentajeAnalisis){
    unordered_map<int,resultadosDeAnalisis> ejecuciones;
    puntosSeparados puntosSep = separarPuntos(puntos);
    for(int contador = 0; contador < 50; contador++){
        resultadosDeAnalisis ejecucionActual = analizar(puntosSep,porcentajeAnalisis,puntos.size());
        ejecuciones.insert({contador,ejecucionActual});
    }
    resultadosDeAnalisis resultado = calcularPromedio(ejecuciones);
    return resultado;
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
            int randomX = generarRandom(0,1079);
            if(numerosUsadosX.find(randomX) == numerosUsadosX.end()){
                int randomEnd = generarRandom(-15,15);
                resultado.push_back({{randomX,0},{randomX+randomEnd,919}});
                cantidadHorizontales++;
                numerosUsadosX.insert({randomX,1});
            }
            if(!cantidadPar && cantidadHorizontales == (cantidad/2)){
                int randomX = generarRandom(0,1079);
                int randomEnd = generarRandom(-15,15);
                resultado.push_back({{randomX,0},{randomX+randomEnd,919}});
                cantidadHorizontales++;
                numerosUsadosX.insert({randomX,1});
            }
        }
        else{
            int randomY = generarRandom(0,919);
            if(numerosUsadosY.find(randomY) == numerosUsadosY.end()){
                int randomEnd = generarRandom(-15,15);
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
    estructuraDePuntos puntos = generarLineas(100);
    resultadosDeAnalisis resultados = realizarAnalisisCompleto(puntos,0.6);
    cout << "Horizontales: " << resultados.horizontales << endl;
    cout << "Verticales: " << resultados.verticales << endl;
    cout << "Diagonales crecientes: " << resultados.diagonalesCrecientes << endl;
    cout << "Diagonales decrecientes: " << resultados.diagonalesDecrecientes << endl;
}