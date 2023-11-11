#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <windows.h>
#include <map>
#include <thread>
#include <conio.h>

using namespace std;

class Medicamento {
public:
    string nom;
    string numRegis;
    string categ;
    string prinAct;
    string dosrec;

    Medicamento() = default;

    Medicamento(string nom, string numRegis, string categ, string prinAct, string dosrec)
        : nom(nom), numRegis(numRegis), categ(categ), prinAct(prinAct), dosrec(dosrec) {}
};

class Proveedor {
public:

    string nom;
    string nit;
    string direcFiscal;
    string direcContacto;
    string celular;
    string correo;

    Proveedor(string nom, string nit, string direcFiscal, string direcContacto, string celular, string correo)
        : nom(nom), nit(nit), direcFiscal(direcFiscal), direcContacto(direcContacto), celular(celular), correo(correo) {}
};

class Inventario {
public:
    int cantStock;
    string fechaCaducidad;
    Proveedor proveedor;
    double precCompra;
    double precVenta;
   
    Inventario(int cantStock, string fechaCaducidad, Proveedor proveedor, double precCompra, double precVenta)
        : cantStock(cantStock), fechaCaducidad(fechaCaducidad), proveedor(proveedor), precCompra(precCompra), precVenta(precVenta) {}
};

class Farmacia {
private:
    list<Medicamento> medic;
    list<Proveedor> prov;
    list<Inventario> invent;

public:

    void pausa() {
        string uno;
        cin >> uno;
    }

    void gotoxy(int x, int y) {
        COORD coordinates;
        coordinates.X = x;
        coordinates.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
    }

    Proveedor dar(string nombre) {
        for (Proveedor med : prov)
        {
            if (nombre == med.nom) {
                return med;
            }
        }
    }

    void agregarAlInventario() {
        string nombre;
        cout << "Nombre del medicamento: " << endl;
        cin >> nombre;

        int cantidadStock;
        string fechaCaducidad;
        double precioCompra;
        double precioVenta;

        cout << "Ingrese la cantidad en Stock: " << endl;
        cin >> cantidadStock;

        cout << "Ingrese la fecha de caducidad: " << endl;
        cin >> fechaCaducidad;

        string nombreDeProveedor;
        cout << "Ingrese el nombre del proveedor" << endl;
        cin >> nombreDeProveedor;


        cout << "Ingrese el precio de compra: " << endl;
        cin >> precioCompra;

        cout << "Ingrese el precio de venta: " << endl;
        cin >> precioVenta;

        Inventario inventario(cantidadStock, fechaCaducidad, dar(nombreDeProveedor), precioCompra, precioVenta);
        agregarInventario(inventario);
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
            Sleep(30);
        }

        cout << endl;
    }

    void agregarMedicamento(const Medicamento& medicamento) {
        medic.push_back(medicamento);
    }

    void agregarProveedor(const Proveedor& proveedor) {
        prov.push_back(proveedor);
    }

    void agregarInventario(const Inventario& item) {
        invent.push_back(item);
        cout << "hola";
    }

    Medicamento buscarMedicamentoPorNombre(const string& nom) {
        for (const Medicamento& med : medic) {
            if (med.nom == nom) {
                return med;
            }
        }
        throw runtime_error("Medicamento no encontrado");
    }

    Medicamento buscarMedicamentoPorPrincipioActivo(const string& principioActivo) {
        for (const Medicamento& med : medic) {
            if (med.prinAct == principioActivo) {
                return med;
            }
        }
        throw runtime_error("Medicamento no encontrado");
    }


    Medicamento medicamentoMasCaroProveedor(const string& nombreProveedor) {
        double precioMaximo = 0.0;
        Medicamento medicamentoMasCaro;

        for (const Inventario& item : invent) {
            if (item.proveedor.nom == nombreProveedor && item.precCompra > precioMaximo) {
                precioMaximo = item.precCompra;
                medicamentoMasCaro = buscarMedicamentoPorNombre(item.proveedor.nom);
            }
        }

        if (precioMaximo == 0.0) {
            throw runtime_error("Proveedor no encontrado o no se encontraron medic suministrados por el proveedor");
        }

        return medicamentoMasCaro;
    }

    void generarInformeCSV() {
        ofstream archivo("informe_medicamentos.csv");
        archivo << "nom,numRegis,categ,prinAct,dosrec" << endl;
        for (const Medicamento& med : medic) {
            archivo << med.nom << "," << med.numRegis << "," << med.categ << "," << med.prinAct << "," << med.dosrec << endl;
        }
        archivo.close();
    }

    double calcularPrecioPromedio() {
        double total = 0.0;
        int count = 0;
        for (const Inventario& item : invent) {
            total += item.precVenta;
            count++;
        }
        return total / count;
    }

    void agregarMedicamentoDesdeMenu() {
        system("cls");
        string nom;
        string numRegis;
        string categ;
        string prinAct;
        string dosrec;

        cout << "=== Agregar Medicamento ===" << endl;
        cout << "Ingrese el nom del medicamento: ";
        cin.ignore();
        getline(cin, nom);

        cout << "Ingrese el número de registro: ";
        cin.ignore();
        cin >> numRegis;

        cout << "Ingrese la categoría: ";
        cin.ignore();
        getline(cin, categ);

        cout << "Ingrese los principios activos: ";
        cin.ignore();
        getline(cin, prinAct);

        cout << "Ingrese la dosis recomendada: ";
        cin.ignore();
        getline(cin, dosrec);

        Medicamento nuevoMedicamento(nom, numRegis, categ, prinAct, dosrec);
        agregarMedicamento(nuevoMedicamento);
        cout << "Medicamento agregado con éxito." << endl;

        pausa();
    }
    void agregarProveedorDesdeMenu() {

        system("cls");

        string nom;
        string nit;
        string direcFiscal;
        string direcContacto;
        string celular;
        string correo;

        cout << "=== Agregar Proveedor ===" << endl;
        cout << "Ingrese el nom del proveedor: ";
        cin.ignore();
        getline(cin, nom);

        cout << "Ingrese el NIT del proveedor: ";
        cin >> nit;

        cout << "Ingrese la dirección fiscal: ";
        cin.ignore();
        getline(cin, direcFiscal);

        cout << "Ingrese la dirección de contacto: ";
        cin.ignore();
        getline(cin, direcContacto);

        cout << "Ingrese el número de teléfono: ";
        cin >> celular;

        cout << "Ingrese el correo electrónico: ";
        cin >> correo;

        Proveedor nuevoProveedor(nom, nit, direcFiscal, direcContacto, celular, correo);
        agregarProveedor(nuevoProveedor);
        cout << "Proveedor agregado con éxito." << endl;

        pausa();
    }


    void mostrarMenu() {
        int opcion;
        do {
            system("cls");
            titulo();
            cout << endl;
            cout << "1. Consultar medicamento por nombre" << endl;
            cout << "2. Consultar medicamento por principio activo" << endl;
            cout << "3. Agregar medicamento" << endl;
            cout << "4. Agregar proveedor" << endl;
            cout << "5. Generar informe CSV de medicicamentos" << endl;
            cout << "6. Calcular precio promedio de medicamentos" << endl;
            cout << "7. Encontrar medicamento más caro de un proveedor" << endl;
            cout << "8. Agregar inventario" << endl;
            cout << "9. Salir" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
            {
                system("cls");
                string nom;
                cout << "Ingrese el nom del medicamento: ";
                cin.ignore();
                getline(cin, nom);
                try {
                    Medicamento med = buscarMedicamentoPorNombre(nom);
                    cout << "Información del medicamento:" << endl;
                    cout << "nom: " << med.nom << endl;
                    cout << "Número de Registro: " << med.numRegis << endl;
                    cout << "Categoría: " << med.categ << endl;
                    cout << "Principios Activos: " << med.prinAct << endl;
                    cout << "Dosis Recomendada: " << med.dosrec << endl;
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
                string principioActivo;
                cout << "Ingrese el principio activo del medicamento: ";
                cin.ignore();
                getline(cin, principioActivo);
                try {
                    Medicamento med = buscarMedicamentoPorPrincipioActivo(principioActivo);
                    cout << "Información del medicamento:" << endl;
                    cout << "nom: " << med.nom << endl;
                    cout << "Número de Registro: " << med.numRegis << endl;
                    cout << "Categoría: " << med.categ << endl;
                    cout << "Principios Activos: " << med.prinAct << endl;
                    cout << "Dosis Recomendada: " << med.dosrec << endl;
                }
                catch (const runtime_error& e) {
                    cerr << e.what() << endl;
                }
                pausa();
            }
            break;
            case 3:
                agregarMedicamentoDesdeMenu();
                break;
            case 4:
                agregarProveedorDesdeMenu();
                break;
            case 5:
                generarInformeCSV();
                break;
            case 6:
                system("cls");
                cout << "Precio promedio de los medic: Q" << calcularPrecioPromedio() << endl;
                pausa();
                break;
            case 7:
            {
                system("cls");
                string nombreProveedor;
                cout << "Ingrese el nombre del proveedor: ";
                cin.ignore();
                getline(cin, nombreProveedor);
                try {
                    Medicamento masCaro = medicamentoMasCaroProveedor(nombreProveedor);
                    cout << "Medicamento más caro suministrado por " << nombreProveedor << ": " << masCaro.nom << endl;
                }
                catch (const runtime_error& e) {
                    cerr << e.what() << endl;
                }
                pausa();
            }
            break;
            case 8:
                agregarAlInventario();
            case 9:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion no válida. Intente de nuevo." << endl;
            }
        } while (opcion != 9);
    }

};

int main() {
    Farmacia farma;
    farma.mostrarMenu();
}