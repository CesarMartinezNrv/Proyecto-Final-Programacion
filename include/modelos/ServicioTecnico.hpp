#ifndef SERVICIOTECNICO_H
#define SERVICIOTECNICO_H
#include <string>

class ServicioTecnico{

protected:

    std::string id_servicio;
    std::string nombre;
    std::string descripcion;
    double precio_base;
    int duracion_minutos;

public:

    ServicioTecnico(std::string id, std::string nombre, std::string descripcion, double precio, int duracion);
 
    std::string getIdServicio() const;
    std::string getNombre() const;
    double getPrecioBase() const;

    void setPrecioBase(double precio);
    void setDuracionMinutos(int minutos);

    virtual double calcularCosto() const = 0;
    virtual std::string getTipo() const = 0;
    virtual void mostrarInformacion() const = 0;
    virtual std::string transformarArchivo() const = 0;

    virtual ~ServicioTecnico();
};

#endif