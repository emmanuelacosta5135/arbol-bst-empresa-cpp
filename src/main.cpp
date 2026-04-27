#include <iostream>
#include <string>
#include <algorithm> // Lo usamos para la funcion max que ayuda con la altura

using namespace std;

// 1. Definimos qué datos tiene un empleado
struct Empleado {
    int codigo;      // Su ID unico
    string nombre;   // Su nombre completo
    string cargo;    // Su puesto en la empresa
};

// 2. Definimos la estructura del "Nodo" (cada cajita del arbol) [cite: 41]
struct Nodo {
    Empleado dato;    // La info del empleado
    Nodo* izquierdo;  // Puntero al hijo menor
    Nodo* derecho;    // Puntero al hijo mayor

    // Constructor: crea la cajita vacia con sus brazos en null [cite: 45]
    Nodo(Empleado emp) {
        dato = emp;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

class ArbolBST {
private:
    Nodo* raiz; // El jefe de jefes, el inicio del arbol [cite: 53]

    // --- FUNCIONES INTERNAS (Recursivas) ---

    // Insertar: decide si el nuevo va a la izquierda o derecha [cite: 54]
    Nodo* insertar(Nodo* actual, Empleado nuevoEmp) {
        // Si el lugar está vacío, ponemos al empleado ahí
        if (actual == nullptr) {
            return new Nodo(nuevoEmp);
        }

        // Si el código es menor, se va a la izquierda
        if (nuevoEmp.codigo < actual->dato.codigo) {
            actual->izquierdo = insertar(actual->izquierdo, nuevoEmp);
        } 
        // Si el código es mayor, se va a la derecha
        else if (nuevoEmp.codigo > actual->dato.codigo) {
            actual->derecho = insertar(actual->derecho, nuevoEmp);
        } 
        // Si el código es igual, avisamos que ya existe [cite: 62]
        else {
            cout << "\n[!] Cuidado: El codigo " << nuevoEmp.codigo << " ya esta registrado." << endl;
        }

        return actual;
    }

    // Buscar: sigue el camino de menor/mayor hasta hallar al empleado [cite: 67]
    Nodo* buscar(Nodo* actual, int codigoBuscado) {
        // Si no hay nada o si lo encontramos, devolvemos el nodo
        if (actual == nullptr || actual->dato.codigo == codigoBuscado) {
            return actual;
        }

        // Si lo que busco es menor, me muevo a la izquierda
        if (codigoBuscado < actual->dato.codigo) {
            return buscar(actual->izquierdo, codigoBuscado);
        }
        // Si es mayor, me muevo a la derecha
        return buscar(actual->derecho, codigoBuscado);
    }

    // RECORRIDOS: Formas de visitar a todos los empleados

    // Inorden: Los muestra ordenaditos de menor a mayor codigo [cite: 77]
    void inorden(Nodo* actual) {
        if (actual == nullptr) return;
        inorden(actual->izquierdo);
        imprimirDatos(actual);
        inorden(actual->derecho);
    }

    // Preorden: Muestra primero al "padre" y luego a los hijos [cite: 84]
    void preorden(Nodo* actual) {
        if (actual == nullptr) return;
        imprimirDatos(actual);
        preorden(actual->izquierdo);
        preorden(actual->derecho);
    }

    // Postorden: Muestra primero a los hijos y al final al padre [cite: 91]
    void postorden(Nodo* actual) {
        if (actual == nullptr) return;
        postorden(actual->izquierdo);
        postorden(actual->derecho);
        imprimirDatos(actual);
    }

    // Altura: Cuenta que tan "profundo" es el arbol [cite: 98]
    int obtenerAltura(Nodo* actual) {
        if (actual == nullptr) return 0;
        // Comparamos cual lado es mas largo y sumamos 1 (la raiz actual) [cite: 104]
        return 1 + max(obtenerAltura(actual->izquierdo), obtenerAltura(actual->derecho));
    }

    // Hojas: Solo muestra a los empleados que no tienen hijos [cite: 106]
    void mostrarHojas(Nodo* actual) {
        if (actual == nullptr) return;
        // Si no tiene brazos izquierdo ni derecho, es una hoja [cite: 108]
        if (actual->izquierdo == nullptr && actual->derecho == nullptr) {
            imprimirDatos(actual);
        }
        mostrarHojas(actual->izquierdo);
        mostrarHojas(actual->derecho);
    }

    // Funcion auxiliar para no repetir tanto codigo al imprimir
    void imprimirDatos(Nodo* n) {
        cout << " -> ID: " << n->dato.codigo << " | Nombre: " << n->dato.nombre << " | Cargo: " << n->dato.cargo << endl;
    }

public:
    // Constructor de la clase
    ArbolBST() { raiz = nullptr; }

    // --- METODOS PUBLICOS (Los que llama el menu) ---

    void agregar(Empleado e) { raiz = insertar(raiz, e); }

    void buscar(int c) {
        Nodo* encontrado = buscar(raiz, c);
        if (encontrado) {
            cout << "\n--- Empleado Localizado ---" << endl;
            imprimirDatos(encontrado);
        } else {
            cout << "\n[!] No se encontro a nadie con ese ID." << endl;
        }
    }

    void verRaiz() {
        if (raiz) {
            cout << "\n--- Nodo Raiz (El inicio de todo) ---" << endl;
            imprimirDatos(raiz);
        } else cout << "\nEl arbol esta vacio." << endl;
    }

    void listarInorden() { inorden(raiz); }
    void listarPreorden() { preorden(raiz); }
    void listarPostorden() { postorden(raiz); }
    void verAltura() { cout << "\nAltura total del arbol: " << obtenerAltura(raiz) << endl; }
    void verHojas() { mostrarHojas(raiz); }
};

// 3. El Menu Principal [cite: 164]
int main() {
    ArbolBST miEmpresa;
    int opcion, codTemporal;

    do {
        cout << "\n**************************************";
        cout << "\n   GESTION DE EMPLEADOS (BST) - UTA";
        cout << "\n**************************************";
        cout << "\n1. Registrar Empleado";
        cout << "\n2. Buscar por ID";
        cout << "\n3. Ver la Raiz";
        cout << "\n4. Listado Inorden (Ordenado)";
        cout << "\n5. Listado Preorden";
        cout << "\n6. Listado Postorden";
        cout << "\n7. Calcular Altura";
        cout << "\n8. Ver Nodos Hoja";
        cout << "\n0. Salir";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Empleado nuevo;
            cout << "Ingrese ID numerico: "; cin >> nuevo.codigo;
            cin.ignore(); // Limpia el buffer para que deje escribir el nombre
            cout << "Nombre completo: "; getline(cin, nuevo.nombre);
            cout << "Cargo que ocupa: "; getline(cin, nuevo.cargo);
            miEmpresa.agregar(nuevo);
        } 
        else if (opcion == 2) {
            cout << "ID del empleado a buscar: "; cin >> codTemporal;
            miEmpresa.buscar(codTemporal);
        }
        else if (opcion == 3) miEmpresa.verRaiz();
        else if (opcion == 4) miEmpresa.listarInorden();
        else if (opcion == 5) miEmpresa.listarPreorden();
        else if (opcion == 6) miEmpresa.listarPostorden();
        else if (opcion == 7) miEmpresa.verAltura();
        else if (opcion == 8) {
            cout << "\n--- Empleados en las Hojas (Sin subordinados) ---\n";
            miEmpresa.verHojas();
        }

    } while (opcion != 0);

    return 0;
}
