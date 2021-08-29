#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <string>
#include "./include/tarjeta.h"
#include <windows.h>

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Declaracion funciones
void procesarVisa(double importeIngresado);
void procesarAmex(double importeIngresado);
void procesarNara(double importeIngresado);


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

using namespace std;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Tarjeta
{
    private:
        string tipoTarjeta;
        int tasaExcepcional;
        int numeroRandom;
        double coeficiente;
        double importe;
        double importeTotal;
    public:
        // Getter
        double getCoeficiente() {
            return coeficiente;
        };
        double getImporte() {
            return importe;
        };
        double getImporteTotal() {
            return importeTotal;
        };
        int getTasaExcepcion() {
            return tasaExcepcional;
        };
        int getNumeroRandom() {
            return numeroRandom;
        };
        // Setter
        void setImporteTotal(double _importe) {
            importeTotal = _importe;
        };
        void setNumeroRandom(double _numeroRandom) {
            numeroRandom = _numeroRandom;
        }

        Tarjeta(string, int, double, double);
        virtual void calcularCoeficiente(){};
        void mostrarImporteTotal();
};

class Visa : public Tarjeta
{
    private:
        string descripcion;
    public:
        Visa(double); // Contructor
        ~Visa(){}; //Destructor
        void calcularCoeficiente();
};

class Amex : public Tarjeta
{
    private:
        int codigoRandom;
    public:
        Amex(double); // Contructor
        ~Amex(){}; //Destructor
        void calcularCoeficiente();
};

class Nara : public Tarjeta
{
    private:
        time_t fecha;
    public:
        Nara(double); // Contructor
        ~Nara(){}; //Destructor
        void calcularCoeficiente();
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CONTRUCTORES
Tarjeta::Tarjeta(string _tipoTarjeta, int _tasaExcepcional, double _coeficiente, double _importe) {
    tasaExcepcional = _tasaExcepcional;
    tipoTarjeta = _tipoTarjeta;
    coeficiente = _coeficiente;
    importe = _importe;
    numeroRandom = 0;
};

Visa::Visa(double _importe) : Tarjeta(TIPO_VISA, EXCEPTIONAL_RATE_VISA, COEF_VISA, _importe) {
    descripcion = "";
};

Amex::Amex(double _importe) : Tarjeta(TIPO_AMEX, EXCEPTIONAL_RATE_AMEX, COEF_AMEX, _importe) {
    codigoRandom = 0;
};

Nara::Nara(double _importe) : Tarjeta(TIPO_NARA, EXCEPTIONAL_RATE_NARA, COEF_NARA, _importe) {
    fecha = time(NULL);
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Visa::calcularCoeficiente(){
    int rdesde=2, rhasta=5;
    int numeroRandom = rand()%(rhasta-rdesde+1)+rdesde; // random entre 2 y 5
    double importeTransaccion = getImporte();
    double porcentaje = ( (importeTransaccion+getTasaExcepcion()) * (getCoeficiente()+numeroRandom))/100;
    double importeTotal = importeTransaccion + porcentaje;
    
    setImporteTotal(importeTotal);
    setNumeroRandom(numeroRandom);
}

void Amex::calcularCoeficiente() {
    double importeTransaccion = getImporte();
    double porcentaje = ( (importeTransaccion+getTasaExcepcion()) * getCoeficiente())/100;
    double importeTotal = importeTransaccion + porcentaje;
    
    setImporteTotal(importeTotal);
}

void Nara::calcularCoeficiente() {
    int rdesde=6, rhasta=9;
    int numeroRandom = rand()%(rhasta-rdesde+1)+rdesde; // random entre 6 y 9
    double importeTransaccion = getImporte();
    double porcentaje = ( (importeTransaccion+getTasaExcepcion()) * (getCoeficiente()+numeroRandom))/100;
    double importeTotal = importeTransaccion + porcentaje;
    
    setImporteTotal(importeTotal);
    setNumeroRandom(numeroRandom);
}

void Tarjeta::mostrarImporteTotal(){
    cout << "El importe original : " << importe <<endl;
    cout << "Coef aplicado    :  " << coeficiente <<endl;
    cout << "Tasa excepcional :  " << tasaExcepcional <<endl;
    if(numeroRandom!=0) cout << "Numero Random    :  " << numeroRandom <<endl;

    cout << "\n";

    cout << "Importe Total : " << importeTotal <<endl;
}



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Programa Principal
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main(void)
{
    double importeIngresado =0;
    int opc = 0;

    // PARA NUMEROS RANDOM
    srand(time(NULL));

    do
    {
        cout <<""<< endl;
        cout <<""<< endl;
        cout <<""<< endl;
        cout <<"MENU DE OPCIONES"<< endl;
        cout <<"1. ingrese los valores : "<< endl;
        if(importeIngresado>0) cout <<"Importe ingresado para procesar--> : " << importeIngresado << endl;
        cout <<"2. calcular VISA"<< endl;
        cout <<"3. calcular AMEX"<< endl;
        cout <<"4. calcular NARA"<< endl;
        cout <<"5. S.A.L.I.R"<< endl;

        cout <<" "<< endl;
        cout <<"Opcion a escoger :";
        cin >> opc;
        system("clear");
        switch (opc)
        {
            system("clear");
        case 1:
            cout <<"ingrese el importe de la transaccion : -->";
            cin >> importeIngresado;
            break;
            cout <<" "<< endl;

        case 2:
            system("clear");

            procesarVisa(importeIngresado);

            system("pause"); 
            system("clear");

            break;
            cout <<" "<< endl;
        case 3:
            system("clear");
            
            procesarAmex(importeIngresado);

            system("pause"); 
            system("clear");

            break;
            cout <<" "<< endl;
        case 4:
            system("clear");
            
            procesarNara(importeIngresado);

            system("pause"); 
            system("clear");

            break;
            cout <<" "<< endl;
        case 5:
            break;
        default:
            system("clear");
            cout <<"la opcion que ingreso es incorrecta"<< endl;
            break;
        }
    } while (opc != 5);
    return 0;
}

void procesarVisa(double importeIngresado){
    if(importeIngresado>0){
        Visa visa(importeIngresado);
        visa.calcularCoeficiente();
        visa.mostrarImporteTotal();
    }else{
        cout << "El importe ingresado es incorrecto, debe ser mayor a cero" << endl;
    }
    
}

void procesarAmex(double importeIngresado){
    if(importeIngresado>0){
        Amex amex(importeIngresado);
        amex.calcularCoeficiente();
        amex.mostrarImporteTotal();
    }else{
        cout << "El importe ingresado es incorrecto, debe ser mayor a cero" << endl;
    }

}

void procesarNara(double importeIngresado){
    if(importeIngresado){
        Nara nara(importeIngresado);
        nara.calcularCoeficiente();
        nara.mostrarImporteTotal();
    }else{
        cout << "El importe ingresado es incorrecto, debe ser mayor a cero" << endl;
    }
}