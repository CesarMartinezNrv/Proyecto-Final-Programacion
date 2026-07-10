#ifndef TECNICO_HPP
#define TECNICO_HPP

#include "Persona.hpp"
#include <string>

class Tecnico : public Persona{
private:
    std::string especialidad;
    bool estadoDisponible =  true;
    int cantidadServiciosAtendidos {0};

public:
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

    ~Tecnico() override;
};

#endif
