#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <windows.h>
#include <map>
#include <thread>
#include <conio.h>

using namespace std;

class Inventario;

class Proveedor {
public:
    string nom;
    string nit;
    string direccionFiscal;
    string direccionContacto;
    string telefono;
    string correoElectronico;

    Proveedor(string nom, string nit, string direccionFiscal, string direccionContacto, string telefono, string correoElectronico)
        : nom(nom), nit(nit), direccionFiscal(direccionFiscal), direccionContacto(direccionContacto), telefono(telefono), correoElectronico(correoElectronico) {}
};

class Inventario {
public:
    int cantidadStock;
    string fechaCaducidad;
    Proveedor proveedor;
    double precioCompra;
    double precioVenta;

    Inventario(int cantidadStock, string fechaCaducidad, Proveedor proveedor, double precioCompra, double precioVenta)
        : cantidadStock(cantidadStock), fechaCaducidad(fechaCaducidad), proveedor(proveedor), precioCompra(precioCompra), precioVenta(precioVenta) {};

    Inventario() : cantidadStock(0), fechaCaducidad(""), proveedor(Proveedor("", "", "", "", "", "")), precioCompra(0.0), precioVenta(0.0) {}

};


class Medicamento {
public:
    string nom;
    string numRegistro;
    string categoria;
    string principiosActivos;
    string dosisRecomendada;
    Inventario inventario;

    Medicamento(string nom, string numRegistro, string categoria, string principiosActivos, string dosisRecomendada)
        : nom(nom), numRegistro(numRegistro), categoria(categoria), principiosActivos(principiosActivos), dosisRecomendada(dosisRecomendada) {}

    Medicamento() : nom(""), numRegistro(""), categoria(""), principiosActivos(""), dosisRecomendada(""), inventario(Inventario()) {}
};

class Farmacia {
private:
    list<Medicamento> medicamentos;
    list<Proveedor> proveedores;
    list<Inventario> inventario;

public:
    void gotoxy(int x, int y) {
        COORD coordinates;
        coordinates.X = x;
        coordinates.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
    }

    void pausa() {
        string uno;
        cin >> uno;
    }
    void titulo() {

        int xcol;
        gotoxy(1, 2); printf("%c", 201);
        gotoxy(1, 3); printf("%c", 186);
        gotoxy(1, 4); printf("%c", 200);

        for (xcol = 2; xcol <= 79; xcol++) {
            gotoxy(xcol, 2); printf("%c", 205);
            gotoxy(xcol, 4); printf("%c", 205);
            Sleep(5);
        }

        gotoxy(80, 2); printf("%c", 187);
        gotoxy(80, 3); printf("%c", 186);
        gotoxy(80, 4); printf("%c", 188);

        char titulo[] = "MENU FARMACIA";
        int longitud;
        longitud = strlen(titulo);
        int vcentro = (((80 - longitud) / 2) + 1);
        for (xcol = 2; xcol <= vcentro; xcol++) {
            gotoxy(xcol, 3);
            cout << ' ';
            printf(titulo);
            Sleep(10);
        }

        cout << endl;
    }
    void agregarAlInventario() {
        string nom;
        cout << "Nombre del medicamento: " << endl;
        cin >> nom;

        auto it = find_if(medicamentos.begin(), medicamentos.end(), [&nom](const Medicamento& medicamentonom) {
            return medicamentonom.nom == nom;
            });

        if (it != medicamentos.end()) {
            int cantidadStock;
            string fechaCaducidad;
            double precioCompra;
            double precioVenta;

            cout << "Ingrese la cantidad en Stock: " << endl;
            cin >> cantidadStock;

            cout << "Ingrese la fecha de caducidad: " << endl;
            cin >> fechaCaducidad;

            string nomDeProveedor;
            cout << "Ingrese el nom del proveedor" << endl;
            cin >> nomDeProveedor;

            cout << "Ingrese el precio de compra: " << endl;
            cin >> precioCompra;

            cout << "Ingrese el precio de venta: " << endl;
            cin >> precioVenta;

            auto proveedorit = find_if(proveedores.begin(), proveedores.end(), [&nomDeProveedor](const Proveedor& proveedornom) {
                return proveedornom.nom == nomDeProveedor;
                });

            if (proveedorit != proveedores.end()) {
                Inventario nuevoInventario(cantidadStock, fechaCaducidad, *proveedorit, precioCompra, precioVenta);
                it->inventario = nuevoInventario;
                inventario.push_back(nuevoInventario);
                cout << "Medicamento agregado al inventario" << endl;
            }
            else {
                cout << "Proveedor no encontrado" << endl;
            }
        }
        else {
            cout << "Medicamento no encontrado" << endl;
        }
    };

    void agregarMedicamento(const Medicamento& medicamento) {
        medicamentos.push_back(medicamento);
    }

    void agregarProveedor(const Proveedor& proveedor) {
        proveedores.push_back(proveedor);
    }

    void agregarInventario(const Inventario& item) {
        inventario.push_back(item);
    }

    Medicamento buscarMedicamentoPornom(const string& nom) {
        for (const Medicamento& med : medicamentos) {
            if (med.nom == nom) {
                return med;
            }
        }
        throw runtime_error("Medicamento no encontrado");
    }

    Medicamento buscarMedicamentoPorPrincipioActivo(const string& principioActivo) {
        for (const Medicamento& med : medicamentos) {
            if (med.principiosActivos == principioActivo) {
                return med;
            }
        }
        throw runtime_error("Medicamento no encontrado");
    }


    Medicamento medicamentoMasCaroProveedor(const string& nomProveedor) {
        double precioMaximo = 0.0;
        Medicamento medicamentoMasCaro;

        for (const Medicamento& med : medicamentos) {
            if (med.inventario.proveedor.nom == nomProveedor && med.inventario.precioCompra > precioMaximo) {
                precioMaximo = med.inventario.precioCompra;
                medicamentoMasCaro = med;
            }
        }

        if (precioMaximo == 0.0) {
            throw runtime_error("Proveedor no encontrado o no se hallaron medicamentos del proveedor");
        }

        return medicamentoMasCaro;
    }

    void generarInformeCSV() {
        ofstream archivo("informe_medicamentos.csv");
        archivo << "nom;numRegistro;Categoria;PrincipiosActivos;DosisRecomendada" << endl;
        for (const Medicamento& med : medicamentos) {
            archivo << med.nom << ";" << med.numRegistro << ";" << med.categoria << ";" << med.principiosActivos << ";" << med.dosisRecomendada << endl;
        }
        archivo.close();
    }

    double calcularPrecioPromedio() {
        double total = 0.0;
        int count = 0;
        for (const Inventario& item : inventario) {
            total += item.precioVenta;
            count++;
        }
        return total / count;
    }

    void agregarMedicamentoDesdeMenu() {
        string nom;
        string numRegistro;
        string categoria;
        string principiosActivos;
        string dosisRecomendada;

        cout << "=== Agregar Medicamento ===" << endl;
        cout << "Ingrese el nombre del medicamento: ";
        cin.ignore();
        getline(cin, nom);

        cout << "Ingrese el número de registro: ";
        cin >> numRegistro;

        cout << "Ingrese la categoría: ";
        cin.ignore();
        getline(cin, categoria);

        cout << "Ingrese los principios activos: ";
        cin.ignore();
        getline(cin, principiosActivos);

        cout << "Ingrese la dosis recomendada: ";
        cin.ignore();
        getline(cin, dosisRecomendada);

        Medicamento nuevoMedicamento(nom, numRegistro, categoria, principiosActivos, dosisRecomendada);
        agregarMedicamento(nuevoMedicamento);
        cout << "Medicamento agregado con éxito." << endl;
    }
    void agregarProveedorDesdeMenu() {
        string nom;
        string nit;
        string direccionFiscal;
        string direccionContacto;
        string telefono;
        string correoElectronico;

        cout << "=== Agregar Proveedor ===" << endl;
        cout << "Ingrese el nombre del proveedor: ";
        cin.ignore();
        getline(cin, nom);

        cout << "Ingrese el NIT del proveedor: ";
        cin >> nit;

        cout << "Ingrese la dirección fiscal: ";
        cin.ignore();
        getline(cin, direccionFiscal);

        cout << "Ingrese la dirección de contacto: ";
        cin.ignore();
        getline(cin, direccionContacto);

        cout << "Ingrese el número de teléfono: ";
        cin >> telefono;

        cout << "Ingrese el correo electrónico: ";
        cin >> correoElectronico;

        Proveedor nuevoProveedor(nom, nit, direccionFiscal, direccionContacto, telefono, correoElectronico);
        agregarProveedor(nuevoProveedor);
        cout << "Proveedor agregado con éxito." << endl;
    }

    void printMenu() {
        int opcion;

        string nom;
        string principioActivo;
        string nomProveedor;



        do {
            system("cls");
            titulo();
            cout << endl;
            cout << "1-Detalles de medicamento por nombre" << endl;
            cout << "2-Detalles de medicamento por principio activo" << endl;
            cout << "3-Generar informe CSV de medicamentos" << endl;
            cout << "4-Calcular precio promedio de medicamentos" << endl;
            cout << "5-Encontrar medicamento más caro de un proveedor" << endl;
            cout << "6-Insertar medicamento" << endl;
            cout << "7-Insertar proveedor" << endl;
            cout << "8-Insertar a inventario" << endl;
            cout << "9-Salir" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
            {
                system("cls");
                cout << "Ingrese el nombre del medicamento: ";
                cin.ignore();
                getline(cin, nom);
                try {
                    Medicamento med = buscarMedicamentoPornom(nom);
                    cout << "Información del medicamento:" << endl;
                    cout << "nom: " << med.nom << endl;
                    cout << "Número de Registro: " << med.numRegistro << endl;
                    cout << "Categoría: " << med.categoria << endl;
                    cout << "Principios Activos: " << med.principiosActivos << endl;
                    cout << "Dosis Recomendada: " << med.dosisRecomendada << endl;
                }
                catch (const runtime_error& e) {
                    cerr << e.what() << endl;
                }
                pausa();
            }
            break;
            case 2:
            {
                system("cls");
                cout << "Ingrese el principio activo del medicamento: ";
                cin.ignore();
                getline(cin, principioActivo);
                try {
                    Medicamento med = buscarMedicamentoPorPrincipioActivo(principioActivo);
                    cout << "Información del medicamento:" << endl;
                    cout << "nom: " << med.nom << endl;
                    cout << "Número de Registro: " << med.numRegistro << endl;
                    cout << "Categoría: " << med.categoria << endl;
                    cout << "Principios Activos: " << med.principiosActivos << endl;
                    cout << "Dosis Recomendada: " << med.dosisRecomendada << endl;
                }
                catch (const runtime_error& e) {
                    cerr << e.what() << endl;
                }
                pausa();
            }

            break;
            case 3:
                system("cls");
                generarInformeCSV();
                pausa();
                break;
            case 4:
                system("cls");
                cout << "Precio promedio de los medicamentos: Q" << calcularPrecioPromedio() << endl;
                pausa();
                break;
            case 5:
                system("cls");
                cout << "Ingrese el nom del proveedor: ";
                cin.ignore();
                getline(cin, nomProveedor);
                try {
                    Medicamento masCaro = medicamentoMasCaroProveedor(nomProveedor);
                    cout << "Medicamento más caro suministrado por " << nomProveedor << ": " << masCaro.nom << endl;
                }
                catch (const runtime_error& e) {
                    cerr << e.what() << endl;
                }
                generarInformeCSV();
                pausa();

                break;
            case 6:
                system("cls");
                agregarMedicamentoDesdeMenu();
                pausa();
                break;
            case 7:
            {
                system("cls");
                agregarProveedorDesdeMenu();
                pausa();

            }
            break;
            case 8:
                system("cls");
                agregarAlInventario();
                pausa();

                break;
            case 9:
                system("cls");
                cout << "Saliendo del programa." << endl;
                Sleep(40);
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
            }
        } while (opcion != 9);
    }
};

int main() {
    Farmacia farma;
    farma.printMenu();
}