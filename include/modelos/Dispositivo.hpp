#ifndef DISPOSITIVO_HPP
#define DISPOSITIVO_HPP

#include <string>

class Dispositivo{
private:
    std::string identificacionDispositivo; //Codigo unico que identidica al dispositivo
    std::string identificacionCliente;  //Codigo unico que identifica al cliente
    std::string tipo; //Categoria del equipo (celular, laptop, consola, etc)
    std::string marca;  //Marca del producto (Leonovo, Samsung, Apple, etc)
    std::string modelo; //Guarda la especificacion técnica del dispositivo (Legion, Pro, S23 Ultra, etc)
    std::string numeroSerie; //Numero de fabricacion (asignado por el fabricante)
    std::string estado; //Situacion actual del dispositivo en el proceso de atencion del servicio
    bool validarTextoNoVacio(std::string texto) const;
    bool validarEstado(std::string estado) const;

public:
    //Constructores
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

    //Crea un dispositivo a partir de una linea de archivo
    static Dispositivo desdeTextoArchivo(std::string linea);
};

#endif
