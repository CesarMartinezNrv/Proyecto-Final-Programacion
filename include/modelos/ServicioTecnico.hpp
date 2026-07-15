#ifndef SERVICIOTECNICO_H
#define SERVICIOTECNICO_H
#include <string> 

// Clase abstracta: ServicioTecnico
// Representa un servicio técnico genérico.
// Todas las clases derivadas deberán implementar el cálculo
// del costo, el tipo de servicio y la forma de mostrar

class ServicioTecnico{

protected:

    // Datos generales del servicio
    std::string id_servicio;
    std::string nombre;
    std::string descripcion;

    // Información económica y de tiempo
    double precio_base;
    int duracion_minutos;

public:

    // Constructor
    ServicioTecnico(std::string idServicio, std::string nombre, std::string descripcion, double precio, int duracion);
   
    // Getters
    std::string getIdServicio() const;
    std::string getNombre() const;
    double getPrecioBase() const;

    // Setters
    void setPrecioBase(double precio);
    void setDuracionMinutos(int minutos);

    // Métodos virtuales puros que deberán implementarse
    // en las clases derivadas.
    virtual double calcularCosto() const = 0;
    virtual std::string getTipo() const = 0;
    virtual void mostrarInformacion() const = 0;

    // Destructor virtual para liberar correctamente
    // la memoria cuando se utilice polimorfismo.
    virtual ~ServicioTecnico();

};

#endif
