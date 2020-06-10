#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Numero.cpp"
#include <ctime>

using namespace std;

typedef vector<pair<pair<int, int>, pair<int, int>>> estructuraDePuntos;
typedef pair<estructuraDePuntos, estructuraDePuntos> puntosSeparados;
typedef vector<Numero> vectorNumeros;
class resultadosDeAnalisis
{
public:
    int diagonalesCrecientes = 0;
    int diagonalesDecrecientes = 0;
    int verticales = 0;
    int horizontales = 0;
    int cantidadTotal = 0;

    void calcularTotales()
    {
        cantidadTotal = diagonalesCrecientes + diagonalesDecrecientes + verticales + horizontales;
    }
};
const int margenDeError = 7;

int generarRandom(int min, int max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max)-min);
}

bool static comparar(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
    if (a.first.second == 0 && b.first.second == 0)
    {
        return (a.first.first < b.first.first);
    }
    else if (a.first.second == 0 && b.first.second != 0)
    {
        return false;
    }
    else if (a.first.second != 0 && b.first.second == 0)
    {
        return true;
    }
    else
    {
        return (a.first.second < b.first.second);
    }
}

bool static compararNormal(int a, int b)
{
    return (a < b);
}

//separa los puntos en dos estructuraDePuntos, una con los puntos que salen del eje X (Horizontales) y otra del eje Y (Verticales)
puntosSeparados separarPuntos(estructuraDePuntos puntos)
{
    puntosSeparados resultado;
    sort(puntos.begin(), puntos.end(), comparar);
    estructuraDePuntos puntosHorizontales;
    estructuraDePuntos puntosVerticales;
    for (int i = 0; i < puntos.size(); i++)
    {
        auto actual = puntos.at(i);
        if (actual.first.second == 0)
        {
            puntosHorizontales.push_back(actual);
        }
        else
        {
            puntosVerticales.push_back(actual);
        }
    }
    resultado = {puntosHorizontales, puntosVerticales};
    return resultado;
}

//funcion principal
resultadosDeAnalisis analizar(puntosSeparados puntosSep, float porcentajeAnalisis, int cantLineas)
{
    resultadosDeAnalisis resultado;
    int cantidadLineasAnalizar = cantLineas * porcentajeAnalisis;
    pair<pair<int, int>, pair<int, int>> lineaActual;
    int diagonalesCrecientes = 0;
    int diagonalesDecrecientes = 0;
    int verticales = 0;
    int horizontales = 0;
    int indiceRandom;
    for (int contador = 0; contador < cantidadLineasAnalizar; contador++)
    {
        if (contador < cantidadLineasAnalizar / 2)
        {
            indiceRandom = generarRandom(0, puntosSep.first.size());
            lineaActual = puntosSep.first.at(indiceRandom);
            if (lineaActual.first.first >= lineaActual.second.first - margenDeError && lineaActual.first.first <= lineaActual.second.first + margenDeError)
            {
                resultado.verticales++;
            }
            else if (lineaActual.first.first > lineaActual.second.first + margenDeError)
            {
                resultado.diagonalesCrecientes++;
            }
            else
            {
                resultado.diagonalesDecrecientes++;
            }
            puntosSep.first.erase(puntosSep.first.begin() + contador);
        }
        else
        {
            indiceRandom = generarRandom(0, puntosSep.second.size());
            lineaActual = puntosSep.second.at(indiceRandom);
            if (lineaActual.first.second >= lineaActual.second.second - margenDeError && lineaActual.first.second <= lineaActual.second.second + margenDeError)
            {
                resultado.horizontales++;
            }
            else if (lineaActual.first.second > lineaActual.second.second + margenDeError)
            {
                resultado.diagonalesCrecientes++;
            }
            else
            {
                resultado.diagonalesDecrecientes++;
            }
            puntosSep.second.erase(puntosSep.second.begin() + contador);
        }
    }
    resultado.calcularTotales();
    return resultado;
}

int calcularPromedioAux(vector<int> lista)
{
    float suma = 0;
    float listaSize = lista.size();
    for (int contador = 0; contador < lista.size(); contador++)
    {
        suma += lista.at(contador);
    }
    return (int)suma / listaSize;
}

resultadosDeAnalisis calcularPromedio(unordered_map<int, resultadosDeAnalisis> ejecuciones)
{
    vector<int> horizontales;
    vector<int> verticales;
    vector<int> diagonalesCrecientes;
    vector<int> diagonalesDecrecientes;
    for (int contador = 0; contador < ejecuciones.size(); contador++)
    {
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
    resultadoFinal.calcularTotales();
    return resultadoFinal;
}

resultadosDeAnalisis realizarAnalisisCompleto(estructuraDePuntos puntos, float porcentajeAnalisis)
{
    unordered_map<int, resultadosDeAnalisis> ejecuciones;
    puntosSeparados puntosSep = separarPuntos(puntos);
    for (int contador = 0; contador < 50; contador++)
    {
        resultadosDeAnalisis ejecucionActual = analizar(puntosSep, porcentajeAnalisis, puntos.size());
        ejecuciones.insert({contador, ejecucionActual});
    }
    resultadosDeAnalisis resultado = calcularPromedio(ejecuciones);
    return resultado;
}

estructuraDePuntos generarLineas(int cantidad)
{
    estructuraDePuntos resultado;
    bool cantidadPar;
    if (cantidad % 2 == 0)
    {
        cantidadPar = true;
    }
    else
    {
        cantidadPar = false;
        cantidad--;
    }
    int cantidadHorizontales = 0;
    int cantidadVerticales = 0;
    unordered_map<int, int> numerosUsadosX;
    unordered_map<int, int> numerosUsadosY;
    while (cantidadHorizontales + cantidadVerticales < cantidad)
    {
        if (cantidadHorizontales < cantidad / 2)
        {
            int randomX = generarRandom(0, 1079);
            if (numerosUsadosX.find(randomX) == numerosUsadosX.end())
            {
                int randomEnd = generarRandom(-15, 15);
                resultado.push_back({{randomX, 0}, {randomX + randomEnd, 919}});
                cantidadHorizontales++;
                numerosUsadosX.insert({randomX, 1});
            }
            if (!cantidadPar && cantidadHorizontales == (cantidad / 2))
            {
                int randomX = generarRandom(0, 1079);
                int randomEnd = generarRandom(-15, 15);
                resultado.push_back({{randomX, 0}, {randomX + randomEnd, 919}});
                cantidadHorizontales++;
                numerosUsadosX.insert({randomX, 1});
            }
        }
        else
        {
            int randomY = generarRandom(0, 919);
            if (numerosUsadosY.find(randomY) == numerosUsadosY.end())
            {
                int randomEnd = generarRandom(-15, 15);
                resultado.push_back({{0, randomY}, {1079, randomY + randomEnd}});
                cantidadVerticales++;
                numerosUsadosY.insert({randomY, 1});
            }
        }
    }
    return resultado;
}

void printPuntos(estructuraDePuntos puntos)
{
    for (int i = 0; i < puntos.size(); i++)
    {
        auto actual = puntos.at(i);
        cout << "[(" << actual.first.first << "," << actual.first.second << "),(" << actual.second.first << "," << actual.second.second << ")]" << endl;
    }
}

vectorNumeros cargarEstructuraNumeros()
{
    vectorNumeros numeros;
    numeros.push_back(Numero{0, 2, 2, 0, 0});
    numeros.push_back(Numero{1, 1, 0, 1, 0});
    numeros.push_back(Numero{2, 2, 3, 0, 0});
    numeros.push_back(Numero{3, 1, 3, 0, 0});
    numeros.push_back(Numero{4, 1, 1, 1, 0});
    numeros.push_back(Numero{5, 2, 3, 0, 0});
    numeros.push_back(Numero{6, 2, 3, 0, 0});
    numeros.push_back(Numero{7, 0, 1, 1, 0});
    numeros.push_back(Numero{8, 2, 3, 0, 0});
    numeros.push_back(Numero{9, 2, 2, 0, 0});
    return numeros;
}

void analizarProbabilidades(vectorNumeros *numeros, resultadosDeAnalisis resultados)
{
    float probabilidad = 0;
    int lv = 0, lh = 0, ldc = 0, ldd = 0, total = 0, menor;
    vector<int> lineas;
    for (int i = 0; i < numeros->size(); i++)
    {
        Numero actual = numeros->at(i);
        if (actual.getVerticales() != 0)
            lv = (int)(resultados.verticales / actual.getVerticales());

        if (actual.getHorizontales() != 0)
            lh = (int)(resultados.horizontales / actual.getHorizontales());

        if (actual.getDiagonalesCrecientes() != 0)
            ldc = (int)(resultados.diagonalesCrecientes / actual.getDiagonalesCrecientes());

        if (actual.getDiagonalesDecrecientes() != 0)
            ldd = (int)(resultados.diagonalesDecrecientes / actual.getDiagonalesDecrecientes());

        //cout << "Numero:" << actual.getNumero() << " | Lv: " << lv << " /lh: " << lh << " /ldc: " << ldc << " /ldd: " << ldd << endl;

        if (lv != 0)
            lineas.push_back(lv);
        if (lh != 0)
            lineas.push_back(lh);
        if (ldc != 0)
            lineas.push_back(ldc);
        if (ldd != 0)
            lineas.push_back(ldd);

        if (lineas.size() != 0)
            menor = lineas.at(0);
        else
            menor = 0;

        for (int i = 1; i < lineas.size(); i++)
        {
            if (menor > lineas.at(i))
                menor = lineas.at(i);
        }

        total += menor;
        lineas.clear();
        numeros->at(i).setCantidadApariciones(menor);
    }

    for (int i = 0; i < numeros->size(); i++)
    {
        float result = (float)((numeros->at(i).getCantidadApariciones() * 100) / total);
        numeros->at(i).setProbabilidad(result);
    }
}

void imprimirResultados(vectorNumeros numeros)
{

    for (int i = 0; i < numeros.size(); i++)
    {
        int numeroRandom = generarRandom(0, 100);
        float numeroRandomFloat = numeroRandom / 100.0;
        cout << "Numero " << numeros.at(i).getNumero() << " |   Probabilidad: " << numeros.at(i).getProbabilidad() << "%  |  Status: ";
        if (numeroRandom > numeros.at(i).getProbabilidad())
        {
            cout << " No Aparece" << endl;
        }
        else
        {
            cout << " Aparece" << endl;
        }
    }
}
int main()
{
    estructuraDePuntos puntos = generarLineas(100);
    resultadosDeAnalisis resultados = realizarAnalisisCompleto(puntos, 0.6);
    vectorNumeros numeros = cargarEstructuraNumeros();
    analizarProbabilidades(&numeros, resultados);
    imprimirResultados(numeros);

    cout << "\n\nHorizontales: " << resultados.horizontales << endl;
    cout << "Verticales: " << resultados.verticales << endl;
    cout << "Diagonales crecientes: " << resultados.diagonalesCrecientes << endl;
    cout << "Diagonales decrecientes: " << resultados.diagonalesDecrecientes << endl;
    cout << "Lineas totales: " << resultados.cantidadTotal << endl;
}

/*
    Descripción General del Algoritmo

    Como base estudiamos el comportamiento de las lineas generadas aleatoriamente, clasificandolas en lineas: 
        ■ Crecientes
        ■ Decrecientes
        ■ Diagonales Crecientes
        ■ Diagonales Decrecientes
    Una vez estas lineas fueron procesadas, obtenemos una distribución del comportamiento de las mismas. Posteriormente, procedemmos a analizar y cargar la estructura de los números de un dígito. Los cuales presentan la siguiente estructura:

      UNO   DOS     TRES    CUATRO  CINCO   SEIS    SIETE   OCHO   NUEVE  CERO
      --   ------   -----     - -   -----   -----  ------  ------  -----  -----
     - -        -       -    -  -   -       -          -   -    -  -   -  -   -
    -  -   ------   -----   -----   -----   -----     -    ------  -----  -   -
       -   -            -       -       -   -   -    -     -    -      -  -   -
       -   ------   -----       -   -----   -----   -      ------      -  -----    
    
     Posteriormente, analizamos las maximas posibles apariciones de los numeros según su patron (cantiada de lineas de cada tipo que ocupen para formarse *ejemplo. el "4" ocupa 1 vertical, 1 horizontal y 1 diagonal creciente) y la distribución obtenida por el analisis de las lineas realizado previamente, de ahí obtenemos la probabilidad de formación que posee cada número. Finalmente se procede a realizar un random que permite dar respuesta de cuales de los números estan presentes según la probabilidad que tiene cada uno de ellos.   

    

    Explicación Detallada

    → Se generan las lineas aleatoriamente: Como parametros recibimos un int de cantidad de lineas que se van a generar.
    → Se analiza el N deseado: Realizamos un analisis de un porcentaje (se envia por parametros para tener la opción de reducir el tamaño N del problema) de lineas que se seleccionan aleatoriamente del arreglo.
    → Se procede a tener un analisis más acertado: ejecutamos el analisis previo en reiteradas ocaciones para usar un promedio de los resultados y obtener una mejor respuesta para continuar con el ejercicio.
    → Cargamos en la estructura el patrón de los Números de un Dígito
    → Analizamos las probabilidades: 
        * Recibe por parametros el arreglo de los numeros y el resultado del analisis de las lineas.
        * Se realiza el calculo (dividimos la cantidad total de lineas entre lo que ocupa el patron del numero según el tipo de linea) para determinar cuantas máximas posibles formaciones puede tener cada numero según su patron y la cantidad de lineas que arroje el resultado del analisis de las lineas.
        * Despues de analizar a todos los numeros se actualizan las probabilidades que tiene cada numero segun su cantidad maxima de apariciones
    → Se evalua con un random para determinar si el numero se forma o no tomando en cuenta su probabilidad.
    → Se imprimen los resultados.
*/