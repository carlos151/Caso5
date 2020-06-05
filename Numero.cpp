#include <iostream>
using std::cout;
using std::endl;
class Numero
{
      int numero;
      int verticales;
      int horizontales;
      int diagonalesCrecientes;
      int diagonalesDecrecientes;
      int cantApariciones;
      float probabilidad;

public:
      Numero(int pNumero, int pVerticales, int pHorizontales, int pDiagonalesCrecientes, int pDiagonalesDecrecientes)
      {
            numero = pNumero;
            verticales = pVerticales;
            horizontales = pHorizontales;
            diagonalesCrecientes = pDiagonalesCrecientes;
            diagonalesDecrecientes = pDiagonalesDecrecientes;
            probabilidad = -1.00;
      }

      void setProbabilidad(float pProbabilidad) { probabilidad = pProbabilidad; }
      void setCantidadApariciones(int pCantApariciones) { cantApariciones = pCantApariciones; }
      int getNumero() { return numero; }
      float getProbabilidad() { return probabilidad; }
      int getVerticales() { return verticales; }
      int getHorizontales() { return horizontales; }
      int getDiagonalesCrecientes() { return diagonalesCrecientes; }
      int getDiagonalesDecrecientes() { return diagonalesDecrecientes; }
      int getCantidadApariciones() { return cantApariciones; }

      void print()
      {
            cout << "Numero: " << numero << "\tCantidad de Apariciones: " << cantApariciones << "\tProbabilidad: " << probabilidad << " %" << endl;
      }
      void printStruct()
      {
            cout << "Numero " << numero << endl;
            cout << "Verticales: " << verticales << endl;
            cout << "Horizontales: " << horizontales << endl;
            cout << "Diagonales Crecientes: " << diagonalesCrecientes << endl;
            cout << "Diagonales Decrecientes: " << diagonalesDecrecientes << endl
                 << endl;
      }
};
