# Sistema de Gestion de Servicios Tecnologicos

Proyecto final de Programacion Avanzada (CMP 2102). Modulo de estructura del sistema: personas, clientes, tecnicos, dispositivos e historial de servicios, administrados con arreglos dinamicos.

## Compilacion

```
g++ *.cpp -o proyecto
```

## Ejecucion

```
./proyecto
```

Al iniciar, el programa intenta cargar `clientes.txt`, `tecnicos.txt`, `dispositivos.txt` y `historial_servicios.txt`. Si alguno no existe, el sistema inicia con ese arreglo vacio sin fallar. Al salir (opcion 0), guarda el estado actual en esos mismos archivos.

## Clases

| Clase | Archivo | Responsabilidad |
|---|---|---|
| Persona | Persona.hpp/.cpp | Clase base abstracta (id, nombre, cedula, telefono, correo) |
| Cliente | Cliente.hpp/.cpp | Deriva de Persona; solicita servicios para sus dispositivos |
| Tecnico | Tecnico.hpp/.cpp | Deriva de Persona; atiende servicios tecnicos |
| Dispositivo | Dispositivo.hpp/.cpp | Equipo tecnologico asociado a un Cliente por id |
| HistorialServicio | HistorialServicio.hpp/.cpp | Registro de un servicio; se autoadministra con un arreglo dinamico estatico |
| GestorClientes | GestorClientes.hpp/.cpp | Arreglo dinamico de Cliente* |
| GestorTecnicos | GestorTecnicos.hpp/.cpp | Arreglo dinamico de Tecnico* |
| GestorDispositivos | GestorDispositivos.hpp/.cpp | Arreglo dinamico de Dispositivo* |

## Formato de persistencia

Cada linea de los `.txt` representa un objeto con sus campos separados por `|`, en el mismo orden que los atributos de la clase (ver `transformarArchivo()` / `aTextoArchivo()` de cada clase).

## Relaciones

- `Persona` es abstracta; `Cliente` y `Tecnico` derivan de ella.
- `Dispositivo` referencia a su `Cliente` mediante `idCliente`.
- `HistorialServicio` referencia a `Dispositivo` y `Tecnico` mediante `idDispositivo` e `idTecnico`.
- Los `Gestor*` administran el ciclo de vida (creacion y destruccion) de sus objetos mediante `new`/`delete`.
