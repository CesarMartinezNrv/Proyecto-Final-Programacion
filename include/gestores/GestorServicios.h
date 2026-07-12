#include "GestorServicios.h"
#include <iostream>

GestorServicios::GestorServicios(int capacidadInicial){

    capacidad = capacidadInicial;
    cantidad = 0;
    servicios = new ServicioTecnico*[capacidad];
}

void GestorServicios::redimensionar(){
    capacidad *= 2;
    ServicioTecnico** nuevo = new ServicioTecnico*[capacidad];
    for(int i = 0; i < cantidad; i++){
        nuevo[i] = servicios[i];
    }

    delete[] servicios;
    servicios = nuevo;

}
void GestorServicios::agregarServicio(ServicioTecnico* servicio){
    if(cantidad == capacidad){
        redimensionar();
    }

    servicios[cantidad] = servicio;
    cantidad++;

}
ServicioTecnico* GestorServicios::buscarPorId(std::string id) const{
    for(int i = 0; i < cantidad; i++){
        if(servicios[i]->getIdServicio() == id){
            return servicios[i];
        }
    }
    return nullptr;
}

void GestorServicios::listarServicios() const{
    if(cantidad == 0){
        std::cout << "No existen servicios registrados."  << std::endl;
        return;
    }

    for(int i = 0; i < cantidad; i++){
        servicios[i]->mostrarInformacion();
        std::cout << "-----------------------------"  << std::endl;
    }

}
void GestorServicios::eliminarServicio(std::string id){
    for(int i = 0; i < cantidad; i++){
        if(servicios[i]->getIdServicio() == id){
            delete servicios[i];
            for(int j = i; j < cantidad - 1; j++){
                servicios[j] = servicios[j + 1];
            }
            cantidad--;
            std::cout << "Servicio eliminado correctamente."  << std::endl;
            return;
        }
    }

    std::cout << "Servicio no encontrado."  << std::endl;
}

GestorServicios::~GestorServicios(){
    for(int i = 0; i < cantidad; i++){
        delete servicios[i];
    }
    delete[] servicios;

}