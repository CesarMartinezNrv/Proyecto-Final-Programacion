#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Persona.hpp"
#include <string>

class Cliente : public Persona{
private:
    std::string direccion;
    std::string fechaDeRegistro;
    std::string estadoAtencionCliente;
    int cantidadDispositivosRegistrados {0};

    bool validarEstadoAtencionCliente(std::string estado) const;

public:
    Cliente();
    Cliente(std::string codigoPersona,
    std::string nombre,
    std::string numeroDeTelefono,
    std::string correo,
    std::string cedula,
    std::string direccion,
    std::string fechaDeRegistro,
    std::string estadoAtencionCliente);

    //Getters
    std::string getDireccion() const;
    std::string getFechaDeRegistro() const;
    std::string getEstadoAtencionCliente() const;
    int getCantidadDispositivosRegistrados() const;

    //Setters con validacion
    bool setDireccion(std::string nuevaDireccion);
    bool setFechaDeRegistro(std::string nuevaFecha);
    bool setEstadoAtencionCliente(std::string nuevoEstado);

    //Se llama desde GestorDispositivos cada vez que se registra un dispositivo de este cliente
    void incrementarDispositivosRegistrados();

    //Override de los metodos virtuales puros de Persona
    std::string tipoDePersona() const override;
    void imprimirInformacionPersona() const override;
    std::string transformarArchivo() const override;

    ~Cliente() override;
};

#endif
