#ifndef DISPOSITIVO_HPP
#define DISPOSITIVO_HPP

#include <string>

class Dispositivo{
private:
    std::string identificacionDispositivo;
    std::string identificacionCliente;
    std::string tipo;
    std::string marca;
    std::string modelo;
    std::string numeroSerie;
    std::string estado;
    bool validarTextoNoVacio(std::string texto) const;
    bool validarEstado(std::string estado) const;

public:
    Dispositivo();
    Dispositivo(std::string identificacionDispositivo,
    std::string idCliente,
    std::string tipo,
    std::string marca,
    std::string modelo,
    std::string numeroSerie,
    std::string estado);

    //Getters
    std::string getIdentificacionDispositivo() const;
    std::string getIdentificacionCliente() const;
    std::string getTipo() const;
    std::string getMarca() const;
    std::string getModelo() const;
    std::string getNumeroSerie() const;
    std::string getEstado() const;

    //Setters
    bool setTipo(std::string nuevoTipo);
    bool setMarca(std::string nuevaMarca);
    bool setModelo(std::string nuevoModelo);
    bool setNumeroSerie(std::string nuevoNumeroSerie);
    bool setEstado(std::string nuevoEstado);

    void mostrarInformacion() const;

    
    std::string aTextoArchivo() const;
    //Transforma el string desde el txt a un objeto
    static Dispositivo desdeTextoArchivo(std::string linea);
};

#endif
