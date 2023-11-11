#include <iostream>
#include <string>
#include <list>
#include <algorithm> // para sort

using namespace std;

// Clase Medicamento
class Medicamento {
public:
    std::string nombre;
    int numeroRegistro;
    std::string categoria;
    std::string principiosActivos;
    std::string dosisRecomendada;
};

// Clase Proveedor
class Proveedor {
public:
    std::string nombre;
    int nit;
    std::string direccionFiscal;
    std::string contactoNombre;
    std::string contactoTelefono;
    std::string contactoCorreo;
};

// Clase Inventario
class Inventario {
public:
    int cantidadEnStock;
    string fechaCaducidad;
    Proveedor proveedor;
    double precioCompra;
    double precioVenta;
};

// Clase Farmacia
class Farmacia {
private:
    std::list<Medicamento> medicamentos;
    std::list<Proveedor> proveedores;
    std::list<Inventario> inventario;

public:
    // Métodos para gestionar medicamentos
    void pausa() {
        string uno;
        cin >> uno;
    }

    void agregarMedicamento(Medicamento& medicamento) {
        system("cls");
        medicamentos.push_back(medicamento);
    }

    void actualizarMedicamento(const string& nombre, Medicamento& medicamento) {
        system("cls");
        auto it = find_if(medicamentos.begin(), medicamentos.end(), [&nombre](const Medicamento& m) {
            return m.nombre == nombre;
            });

        if (it != medicamentos.end()) {
            *it = medicamento;
            cout << "Medicamento actualizado correctamente." << endl;
        }
        else {
            cout << "Error: Medicamento no encontrado." << endl;
        }
        pausa();
    }

    Medicamento consultarMedicamento(string& clave) {
        auto it = std::find_if(medicamentos.begin(), medicamentos.end(), [&clave](const Medicamento& m) {
            return m.nombre == clave || m.principiosActivos == clave;
            });

        if (it != medicamentos.end()) {
            return *it;
        }
        else {
            throw std::runtime_error("Error: Medicamento no encontrado.");
        }
    }

    // Métodos para gestionar proveedores
    void agregarProveedor(Proveedor& proveedor) {
        proveedores.push_back(proveedor);
    }

    // Métodos para gestionar inventario
    void agregarInventario(Inventario& inventarioItem) {
        inventario.push_back(inventarioItem);
    }

    void mostrarInventarioPorNombre(std::string& nombre) {
        auto it = std::find_if(inventario.begin(), inventario.end(), [&nombre](Inventario& item) {
            return item.proveedor.nombre == nombre;
            });

        if (it != inventario.end()) {
            std::cout << "Proveedor: " << it->proveedor.nombre << std::endl;
            std::cout << "Cantidad en Stock: " << it->cantidadEnStock << std::endl;
            std::cout << "Fecha de Caducidad: " << it->fechaCaducidad << std::endl;
            // ... Mostrar otros detalles del inventario ...
        }
        else {
            std::cout << "Error: Medicamento no encontrado en el inventario." << std::endl;
        }
    }

    void mostrarMedicamentoMasCaroPorProveedor(const std::string& nombreProveedor) {
        auto it = std::find_if(inventario.begin(), inventario.end(), [&nombreProveedor](const Inventario& item) {
            return item.proveedor.nombre == nombreProveedor;
            });

        if (it != inventario.end()) {
            std::cout << "Proveedor: " << it->proveedor.nombre << std::endl;
            // ... Mostrar otros detalles del medicamento más caro ...
        }
        else {
            std::cout << "Error: Proveedor no encontrado en el inventario." << std::endl;
        }
    }

    void buscarMedicamentos(string& criterio) {
        // Ejemplo: Búsqueda por principio activo
        auto it = std::find_if(medicamentos.begin(), medicamentos.end(), [&criterio](Medicamento& m) {
            return m.principiosActivos == criterio;
            });

        if (it != medicamentos.end()) {
            cout << "Medicamento encontrado: " << it->nombre << std::endl;
        }
        else {
            cout << "Error: Medicamento no encontrado con el criterio especificado." << std::endl;
        }
    }

    // Funcionalidades adicionales
    void generarInformeCSV();
    double calcularPrecioPromedio();

    // Menú principal

    void mostrarMenu() {
        Medicamento medicamentos;

        int numero = 0;

        while (numero != 9)
        {
            system("cls");
            cout << "1.Registro de nuevos medicamentos y su inventario." << endl;
            cout << "2.Actualizacion de detalles de los medicamentos y su disponibilidad en el inventario." << endl;
            cout << "3.Consulta de información sobre un medicamento específico por el nombre o principio activo." << endl;
            cout << "4.Generacion de informes sobre los medicamentos, generando un listado con la información del medicamento, brindando la opción de exportar la información a un archivo CSV ordenado por nombre del medicamento." << endl;
            cout << "5.Calcular el precio promedio de todos los medicamentos disponibles en farmacia." << endl;
            cout << "6.Dado el nombre de un medicamento, mostrar sus datos de inventario." << endl;
            cout << "7.Dado un proveedor conocer el medicamento con el precio más alto que distribuye a la farmacia." << endl;
            cout << "8.Busqueda y filtrado de medicamentos por diferentes criterios(por ejemplo, por categoría, por principio activo, por proveedor, por fecha de caducidad)." << endl;

            cin >> numero;

            switch (numero)
            {
            case 1:
                cout << "Ingrese el nombre del medicamento" << endl;
                cin >> medicamentos.nombre;

                cout << "Ingrese el numero de registro" << endl;
                cin >> medicamentos.numeroRegistro;

                cout << "Ingrese categoria (por ejemplo, medicamentos de venta libre o con receta)" << endl;
                cin >> medicamentos.categoria;

                cout << "Ingrese principios activos" << endl;
                cin >> medicamentos.principiosActivos;

                cout << "Ingrese dosis recomendada" << endl;
                cin >> medicamentos.dosisRecomendada;

                agregarMedicamento(medicamentos);
                break;
            case 2:
                string nombre;
                cout << "Ingrese el nombre del medicamento que desea buscar";
                cin >> nombre;
                actualizarMedicamento(nombre, medicamentos);
            }
        }
    }
};

int main() {
    // Aquí va la lógica principal del programa, creando un objeto de la clase Farmacia y llamando a sus métodos.
    Farmacia a;
    a.mostrarMenu();
    return 0;
}
