#ifndef GESTORTECNICOS_HPP
#define GESTORTECNICOS_HPP

#include "modelos/Tecnico.hpp" //Necesita la clase Tecnico
#include <string>

class GestorTecnicos{ //Administra a los tecnicos
private:
    Tecnico** tecnicos; //Doble puntero los cuales los elementos son punteros que apuntan a objetos tecnicos
    /*
    Esquema:
        tecnicos
            |
            v
    +-----------+-----------+-----------+-----------+
    | Tecnico*  | Tecnico*  | Tecnico*  | Tecnico*  |
    +-----|-----+-----|-----+-----|-----+-----------+
          |           |           |
          v           v           v
       TEC001      TEC002      TEC003
    */
    
    int capacidad; //Capacidad del arreglo
    int cantidad; //Cantidad utilizada en el arreglo

    void redimensionar();

public:
    //Constructor
    GestorTecnicos();
    //Destructor
    ~GestorTecnicos();

    bool agregarTecnico(Tecnico* nuevoTecnico);
    Tecnico* buscarPorIdentificacion(std::string codigoPersona) const;
    Tecnico* buscarPorCedula(std::string cedula) const;
    Tecnico* buscarDisponible() const;
    bool eliminarTecnico(std::string codigoPersona);
    void imprimirRegistro() const;
    int getCantidad() const;
    void guardarArchivo(std::string nombreArchivo) const;
    void cargarArchivo(std::string nombreArchivo);
};

#endif
