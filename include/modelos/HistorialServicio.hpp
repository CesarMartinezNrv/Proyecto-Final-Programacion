#ifndef HISTORIALSERVICIO_HPP
#define HISTORIALSERVICIO_HPP

#include <string>
#include <iostream>

class HistorialServicio{
private:
    std::string identificacionServicio;
    std::string identificacionDispositivo;
    std::string identificacionTecnico;
    std::string fecha;
    std::string descripcion;
    std::string diagnostico;
    std::string solucion;
    double costo {0.0};

    bool validarTextoNoVacio(std::string texto) const;
    bool validarCosto(double costo) const;

    //Arreglo dinamico de que almacena los registros creados por el sistema
    //Se hace un puntero registros que apunta a mas punteros de la clase HistorialServicio
    /*
    Ejemplo:
        registros
        |
        v
    [ puntero ] [ puntero ] [ puntero ] [ puntero ]
        |          |          |
        v          v          v
        HIS001     HIS002     HIS003
    
    */
    static HistorialServicio** registros;
    //Capacidad y cantidad del arreglo 
    static int capacidad;
    static int cantidad;
    static void redimensionar();

public:
    HistorialServicio();
    HistorialServicio(std::string idServicio,
    std::string idDispositivo,
    std::string idTecnico,
    std::string fecha,
    std::string descripcion,
    std::string diagnostico,
    std::string solucion,
    double costo);

    //Getters
    std::string getIdServicio() const;
    std::string getIdDispositivo() const;
    std::string getIdTecnico() const;
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


    //EN REVISION
    //Sobrecarga para imprimir el historial directamente con cout
    friend std::ostream& operator<<(std::ostream& salida, const HistorialServicio& historial);

    //Metodos estaticos que administran el arreglo dinamico compartido por todos los registros
    static bool agregar(HistorialServicio* nuevoRegistro);
    static HistorialServicio* buscarPorDispositivo(std::string idDispositivo);
    static HistorialServicio* buscarPorTecnico(std::string idTecnico);
    static void mostrarTodos();
    static void guardarArchivo(std::string nombreArchivo);
    static void cargarArchivo(std::string nombreArchivo);
    static void liberarMemoria();
    static int getCantidad();

    ~HistorialServicio();
};

#endif
