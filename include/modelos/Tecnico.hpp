#ifndef TECNICO_HPP
#define TECNICO_HPP

#include "Persona.hpp" //Se incluye los datos de la clase Persona
#include <string>

class Tecnico : public Persona{ //Herencia de la clase Persona a la clase Tecnico
private:
    std::string especialidad; //Descripcion del área de experticio
    bool estadoDisponible =  true; //Disponibilidad para recibir un servicio
    int cantidadServiciosAtendidos {0}; //Registro del numero de servicios realizados

public:
    //Constructores
    Tecnico();
    Tecnico(std::string codigoPersona,
    std::string nombre,
    std::string numeroDeTelefono,
    std::string correo,
    std::string cedula,
    std::string especialidad);

    //Getters
    std::string getEspecialidad() const;
    bool getEstadoDisponible() const;
    int getCantidadServiciosAtendidos() const;

    //Setter
    bool setEspecialidad(std::string nuevaEspecialidad);

    //Metodos de Tecnico
    void marcarComoOcupado();
    void marcarComoDisponible();
    void registrarServicioAtendido();
    std::string tipoDePersona() const override;
    void imprimirInformacionPersona() const override;
    std::string transformarArchivo() const override;

    //Destructor
    ~Tecnico() override;
};

#endif
