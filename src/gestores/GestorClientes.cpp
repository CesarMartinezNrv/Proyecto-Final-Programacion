#include "gestores/GestorClientes.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

GestorClientes::GestorClientes() : clientes{nullptr}, capacidad{0}, cantidad{0}{}

//Destructor (Con liberación de la memoria dinamica)
GestorClientes::~GestorClientes(){
    for(int i{0}; i < cantidad; i++){
        delete clientes[i];
        clientes[i] = nullptr;
    }
    delete[] clientes;
    clientes = nullptr;
}

void GestorClientes::redimensionar(){
    int nuevaCapacidad{0};
    if(capacidad == 0){
        nuevaCapacidad = 2; //El nuevo arreglo se inicializa en 2
    }
    else{
        nuevaCapacidad = capacidad * 2; //Si ya existe un arreglo se duplica su tamano
    }
    Cliente** nuevoArreglo = new Cliente*[nuevaCapacidad];
    for(int i{0}; i < cantidad; i++){
        nuevoArreglo[i] = clientes[i]; //Se pasan los punteros de un arreglo a otro
    }
    delete[] clientes; //Se elimina el viejo arreglo pero los objetos deben seguir existiendo
    clientes = nuevoArreglo;
    capacidad = nuevaCapacidad;
}


bool GestorClientes::agregarCliente(Cliente* nuevoCliente){
    if(nuevoCliente == nullptr){
        return false; //Si el puntero apunta a nullptr se termina el metodo
    }
    if(buscarPorIdentificacion(nuevoCliente->getCodigoPersona()) != nullptr){ //Si no es igual a nullptr significa que ya existe el cliente
        std::cout<<"ERROR. Ya existe un cliente con ese codigo."<<std::endl;
        return false;
    }
    if(cantidad == capacidad){
        redimensionar(); //Redimensiona el arreglo si no hay espacio
    }
    clientes[cantidad] = nuevoCliente; //Agrega el nuevo cliente al arreglo
    cantidad++;
    return true;
}

Cliente* GestorClientes::buscarPorIdentificacion(std::string codigoPersona) const{
    for(int i{0}; i < cantidad; i++){ //Bucle para buscar si existe algun codigo repetido en el arreglo
        if(clientes[i]->getCodigoPersona() == codigoPersona){
            return clientes[i];
        }
    }
    return nullptr;
}

Cliente* GestorClientes::buscarPorCedula(std::string cedula) const{
    for(int i{0}; i < cantidad; i++){
        if(clientes[i]->getCedula() == cedula){
            return clientes[i];
        }
    }
    return nullptr;
}

//Los metodos son constantes porque no cambian, pero si devuelven un puntero.

bool GestorClientes::eliminarCliente(std::string codigoPersona){
    for(int i{0}; i < cantidad; i++){
        if(clientes[i]->getCodigoPersona() == codigoPersona){
            delete clientes[i]; //Elimina el puntero del cliente
            for(int j{i}; j < cantidad - 1; j++){
                clientes[j] = clientes[j + 1]; //Los objetos se mueven una posicion hacia atras
            }
            clientes[cantidad - 1] = nullptr; //Deja libre la ultima posicion
            cantidad--; //Reduce la usada disponible
            return true;
        }
    }
    return false;
}

void GestorClientes::imprimirRegistro() const{
    for(int i{0}; i < cantidad; i++){
        clientes[i]->imprimirInformacionPersona();
        std::cout<<"----------------------------"<<std::endl;
    }
}

int GestorClientes::getCantidad() const{
    return cantidad; //Numero de clientes guardados
}

void GestorClientes::guardarArchivo(std::string nombreArchivo) const{
    std::ofstream archivo(nombreArchivo); //Abre el archivo
    if(archivo.is_open() == false){
        std::cout<<"ERROR. No se pudo abrir el archivo para guardar los clientes."<<std::endl;
        return;
    }
    for(int i{0}; i < cantidad; i++){
        //Cada cliente registra su informacion en una linea
        archivo<<clientes[i]->transformarArchivo()<<std::endl;
    }
    archivo.close();
}


void GestorClientes::cargarArchivo(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"PRECAUCION. No existe archivo previo de clientes, se inicia vacio."<<std::endl;
        return;
    }
    std::string linea;
    while(std::getline(archivo, linea)){ //Lee desde el archivo hasta encontrar un salto de línea
        if(linea == ""){
            continue;
        }
        std::stringstream flujo(linea); //tarta al string linea como una entrada (cin)
        //Cada variable contendra el atributo extraido de linea
        std::string codigoPersona, nombre, numeroDeTelefono, correo, cedula, direccion, fechaDeRegistro, estadoAtencionCliente, dispositivosTexto;
        //Estructurra de getline (origen, destino, hasta donde)
        std::getline(flujo, codigoPersona, '|');
        std::getline(flujo, nombre, '|');
        std::getline(flujo, numeroDeTelefono, '|');
        std::getline(flujo, correo, '|');
        std::getline(flujo, cedula, '|');
        std::getline(flujo, direccion, '|');
        std::getline(flujo, fechaDeRegistro, '|');
        std::getline(flujo, estadoAtencionCliente, '|');
        std::getline(flujo, dispositivosTexto, '|');
        //Se crea un objeto cliente con memoria dinamica
        Cliente* nuevoCliente = new Cliente(codigoPersona, nombre, numeroDeTelefono, correo, cedula, direccion, fechaDeRegistro, estadoAtencionCliente);
        for(int i{0}; i < std::stoi(dispositivosTexto); i++){ //stoi convierte de string a int
            nuevoCliente->incrementarDispositivosRegistrados();
        }
        agregarCliente(nuevoCliente); //agrega el puntero de cliente dentro del arreglo dinamico
                                        //de gestor de clientes
    }
    archivo.close(); //Se cierra el archivo
}
