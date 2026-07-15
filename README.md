# Sistema de Gestión de Servicios Técnicos (SGST)

Proyecto final de la materia de Programación, desarrollado por estudiantes de segundo semestre de la carrera de Ciencias de la Computación (Universidad San Francisco de Quito).

El sistema simula la operación de un taller de servicio técnico: permite registrar clientes, técnicos, dispositivos, servicios técnicos, órdenes de servicio y el historial de atenciones, todo mediante una aplicación de consola escrita en C++ con persistencia en archivos de texto.

## Objetivo del proyecto

Aplicar de forma práctica los conceptos de Programación Orientada a Objetos vistos durante el curso, construyendo un sistema completo y funcional en C++ que integre modelado de clases, relaciones entre objetos y manejo de memoria dinámica.

## Temas de POO aplicados

- Encapsulamiento
- Herencia
- Polimorfismo
- Clases abstractas y métodos virtuales puros
- Constructores y destructores (incluyendo destructores virtuales)
- Memoria dinámica (`new` / `delete`)
- Arreglos dinámicos y manejo de punteros
- Persistencia de datos mediante archivos `.txt`

## Estructura de clases

**Jerarquía de personas** (clase base abstracta `Persona`):
- `Cliente`
- `Tecnico`

**Jerarquía de servicios técnicos** (clase base abstracta `ServicioTecnico`):
- `Diagnostico`
- `Reparacion`
- `MantenimientoPreventivo`

**Otras entidades del dominio:**
- `Dispositivo`: equipo perteneciente a un cliente.
- `OrdenServicio`: relaciona a un cliente, un dispositivo, un servicio técnico y, opcionalmente, un técnico asignado.
- `HistorialServicio`: registro histórico de atenciones realizadas.

Cada entidad cuenta con una clase gestora (`GestorClientes`, `GestorTecnicos`, `GestorDispositivos`, `GestorServicios`, `GestorOrdenes`) encargada del alta, búsqueda, listado y persistencia en archivo de esa colección.

## Estructura del repositorio

```
Proyecto-Final-Programacion/
├── include/
│   ├── gestores/       Cabeceras de las clases gestoras
│   ├── modelos/        Cabeceras de las clases del dominio
│   └── utilidades/     Cabeceras de constantes y validaciones
│
├── src/
│   ├── gestores/        Implementación de las clases gestoras
│   ├── modelos/         Implementación de las clases del dominio
│   ├── utilidades/       Implementación de utilidades
│   └── main.cpp         Punto de entrada y menús de consola
│
├── data/                 Archivos .txt de persistencia
├── docs/                 Documentación de apoyo del proyecto
├── frontend/             Panel web de demostración (ver más abajo)
├── CONTRIBUCIONES.txt    Registro de aportes por integrante
└── LICENSE
```

## Cómo compilar y ejecutar

El proyecto no usa un sistema de build externo (CMake, Makefile); se compila directamente con `g++`.

Desde la raíz del repositorio:

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/modelos/*.cpp src/gestores/*.cpp src/utilidades/*.cpp -o proyecto
```

Y luego se ejecuta:

```bash
./proyecto
```

Al iniciar, el programa carga automáticamente los datos existentes en la carpeta `data/`. Al salir (opción `0` del menú principal), guarda los cambios en esos mismos archivos.

## Menú principal

```
===== SISTEMA DE GESTION DE SERVICIOS TECNICOS =====
1. Clientes
2. Tecnicos
3. Dispositivos
4. Servicios tecnicos
5. Ordenes de servicio
6. Historial
0. Salir
```

Cada opción despliega un submenú propio para registrar, mostrar y buscar información de esa entidad.

## Persistencia de datos

Toda la información se guarda en archivos de texto plano dentro de `data/`:

| Archivo | Contenido |
|---|---|
| `clientes.txt` | Clientes registrados |
| `tecnicos.txt` | Técnicos registrados |
| `dispositivos.txt` | Dispositivos registrados |
| `servicios.txt` | Servicios técnicos (diagnóstico, reparación, mantenimiento) |
| `ordenes.txt` | Órdenes de servicio |
| `historial_servicios.txt` | Historial de atenciones |

## Integrantes

El detalle de las contribuciones de cada integrante se encuentra en [`CONTRIBUCIONES.txt`](CONTRIBUCIONES.txt).

---

## Frontend de demostración

La carpeta [`frontend/`](frontend/README.md) contiene un panel web independiente que representa visualmente las mismas entidades y reglas del sistema en C++, pensado únicamente para fines de presentación del proyecto. **No se conecta al ejecutable en C++ ni comparte datos con los archivos de `data/`**; guarda su propia información en el `localStorage` del navegador.

Este frontend (HTML, CSS y JavaScript) **fue generado con ayuda de inteligencia artificial** como una capa de demostración visual adicional al trabajo académico en C++, que es el que corresponde íntegramente a los estudiantes. Los detalles técnicos completos están documentados en [`frontend/README.md`](frontend/README.md).
