#ifndef HISTORIALSERVICIO_HPP
#define HISTORIALSERVICIO_HPP

#include <string>
#include <iostream>

class HistorialServicio{
private:
    std::string identificacionServicio; //Codigo que identifica el registro del historial
    std::string identificacionDispositivo; //Codigo del dispositivo del registro
    std::string identificacionTecnico; //Codigo del tecnico responsable del servicio
    std::string fecha; //Fecha registrada
    std::string descripcion; //Problema reportado
    std::string diagnostico; //Posible problema tecnico
    std::string solucion;   //Accion que se realizó para solucionar el problema
    double costo {0.0}; //Valor a pagar por el servicio
    bool validarTextoNoVacio(std::string texto) const;
    bool validarCosto(double costo) const;

    //Arreglo dinamico de que almacena los registros creados por el sistema
    //Se hace un puntero registros que apunta a mas punteros de la clase HistorialServicio
    /*
    Ejemplo:
        registros
        |
        v
    [ puntero 0] [ puntero 1] [ puntero 2] [ puntero 3]
        |          |          |
        v          v          v
        HIS001     HIS002     HIS003
    
    */
    //Es statica porque solo existe una sola copia para clase, no va a haber mas.
    static HistorialServicio** registros;
    //Capacidad y cantidad del arreglo 
    static int capacidad;
    static int cantidad;
    static void redimensionar(); //Permite aumentar la capacidad si el arreglo se llega
                                 //a llenar

public:
    //Constructores
    HistorialServicio();
    HistorialServicio(std::string identificacionServicio,
    std::string identificacionDispositivo,
    std::string identificacionTecnico,
    std::string fecha,
    std::string descripcion,
    std::string diagnostico,
    std::string solucion,
    double costo);

    //Getters
    std::string getIdentificacionServicio() const;
    std::string getIdentificacionDispositivo() const;
    std::string getIdentificacionTecnico() const;
    std::string getFecha() const;
    std::string getDescripcion() const;
    std::string getDiagnostico() const;
    std::string getSolucion() const;
    double getCosto() const;

    //Setters
    bool setDescripcion(std::string nuevaDescripcion);
    bool setDiagnostico(std::string nuevoDiagnostico);
    bool setSolucion(std::string nuevaSolucion);
    bool setCosto(double nuevoCosto);

    void mostrarInformacion() const;
    std::string aTextoArchivo() const;


    //Sobrecarga para imprimir el historial directamente con std::cout
    //friend permite que la funcion operator<< pueda acceder a los atributos privados de HistorialServicio
    friend std::ostream& operator<<(std::ostream& salida, const HistorialServicio& historial);

    static bool agregar(HistorialServicio* nuevoRegistro);
    static HistorialServicio* buscarPorDispositivo(std::string identificacionDispositivo);
    static HistorialServicio* buscarPorTecnico(std::string identificacionTecnico);
    static void imprimirRegistro();
    static void guardarArchivo(std::string nombreArchivo);
    static void cargarArchivo(std::string nombreArchivo);
    static void liberarMemoria();
    static int getCantidad();
    
    //Destructor
    ~HistorialServicio();
};

#endif
