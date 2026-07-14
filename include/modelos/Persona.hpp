#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <string>

//Clase base abstracta para luego utilizarla en las 
//clases Cliente y Tecnico
class Persona{
protected:
    std::string codigoPersona;
    std::string nombre;
    std::string numeroDeTelefono;
    std::string correo;
    std::string cedula;

    //Metodos de validacion de entrada
    bool validarTextoNoVacio(std::string texto) const;
    bool validarTelefono(std::string telefono) const;
    bool validarCorreo(std::string correo) const;
    bool validarCedula(std::string cedula) const;

public:
    Persona();
    Persona(
    std::string codigoPersona,
    std::string nombre,
    std::string numeroDeTelefono,
    std::string correo,
    std::string cedula);

    //Getters
    std::string getCodigoPersona() const;
    std::string getNombre() const;
    std::string getNumeroDeTelefono() const;
    std::string getCorreo() const;
    std::string getCedula() const;

    //Setters
    bool setNombre(std::string nuevoNombre);
    bool setNumeroDeTelefono(std::string nuevoTelefono);
    bool setCorreo(std::string nuevoCorreo);
    bool setCedula(std::string nuevaCedula);

    //Metodos virtuales puros (Depende de cada clase hija)
    virtual std::string tipoDePersona() const = 0;
    virtual void imprimirInformacionPersona() const = 0;
    virtual std::string transformarArchivo() const = 0;

    virtual ~Persona();
};

#endif
