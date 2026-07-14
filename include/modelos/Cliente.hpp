#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Persona.hpp" //Se incluye la informacion de la clase Persona
#include <string>

//Clase hija derivada de la clase Persona
class Cliente : public Persona{
private:
    std::string direccion; //Informacion del cliente
    std::string fechaDeRegistro; //Riesgo de datos erroneos
    std::string estadoAtencionCliente; //Si el cliente esta habilitado para enlazarlo con algun dispositivo
    int cantidadDispositivosRegistrados {0}; //Numero de dispositivos enlazados con el cliente
    //Validacion del estado del cliente
    //Es privado porque las demas clases no necesitan solicitar esto ya que el estadoAtencionCliente
    //es un atributo que solo le pertenece a cliente
    bool validarEstadoAtencionCliente(std::string estado) const;

public:

    //Constructores
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
    void incrementarDispositivosRegistrados();

    //Override para sobreescribir los metodos virtuales de la clase Persona
    std::string tipoDePersona() const override;
    void imprimirInformacionPersona() const override;
    std::string transformarArchivo() const override;
    
    //Destructor
    ~Cliente() override;
};

#endif
