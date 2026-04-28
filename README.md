# Árbol Binario de Búsqueda — Gestión de Empleados

Sistema de gestión de empleados implementado con un Árbol Binario de Búsqueda (BST) en C++, desarrollado como práctica de la materia Estructura de Datos — Universidad Técnica de Ambato.

## Tecnologías
- C++11
- Compilador g++

## Estructura
arbol-bst-empresa-cpp/
├── README.md
├── src/
│   └── main.cpp
└── capturas/
## Compilar y ejecutar
```bash
g++ -std=c++11 main.cpp -o arbol

# Linux/macOS
./arbol

# Windows
arbol.exe
```

## Funcionalidades
- Registrar empleado (código, nombre, cargo)
- Buscar empleado por ID
- Ver nodo raíz
- Recorrido inorden (orden ascendente)
- Recorrido preorden
- Recorrido postorden
- Calcular altura del árbol
- Ver nodos hoja (sin subordinados)

## Dato de prueba
| Código | Nombre              | Cargo              |
|--------|---------------------|--------------------|
| 12345  | Juan Carlos Bodoque | Ingeniero en Jefe  |

> Al ser un único nodo, actúa como raíz, nodo interno y hoja al mismo tiempo. La altura del árbol es 1.

## Autor
**Nombre:** Emmanuel Acosta
**Materia:** Estructura de Datos  
**Semestre:** 3ro B
