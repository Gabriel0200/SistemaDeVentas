#include "Controller.h"
#include <string>
using namespace std;

int code = 0;

void mainMenu(Controller* controller);
void adminLoginMenu(Controller* controller);
void adminMainMenu(Controller* controller);
void adminAVLMenu(Controller* controller);
void adminDeliveryMenu(Controller* controller);
void checkClientMenu(Controller* controller);
void buyProductsMenu(Controller* controller);
void shoppingCartMenu(Controller* controller);
void purchaseMenu(Controller* controller);
void orderInformationMenu(Controller* controller);

int main() {
    srand(time(0));
    Controller* controller = new Controller();
    mainMenu(controller);
}

void mainMenu(Controller* controller) {
    code = 0;
    system("cls");
    cout << "Bienvenido al sistema de compras de Hiraoka" << endl;
    cout << "___________________________________________" << endl;
    cout << "1. Ingresa nombre de Cliente" << endl;
    cout << "2. Ingresar a Admin" << endl;
    cout << "3. Salir" << endl;
    cout << "___________________________________________" << endl;
    cout << "Ingrese la opcion que desea: ";
    cin >> code;
    switch (code) {
    case 1:
        checkClientMenu(controller);
        break;
    case 2: adminLoginMenu(controller);
        break;
    case 3: exit(0);
    default: mainMenu(controller);
    }
}
void adminLoginMenu(Controller* controller) {
    unsigned int adminId = 0;
    system("cls");
    string name = "";
    cout << "         Ingresar ID de Administrador      " << endl;
    cout << "___________________________________________" << endl;
    cout << "Ingrese su ID de administrador: ";
    cin >> adminId;
    controller->enterAdminId(adminId);
    controller->get_loginAdminVerify() == true ? adminMainMenu(controller) : (cout << "ID no registrado" << endl, system("pause"), mainMenu(controller));
}
void adminMainMenu(Controller* controller) {
    code = 0;
    system("cls");
    cout << "Bienvenido " << controller->get_currentAdmin() << "!" << endl;
    cout << "____________________________________________" << endl;
    cout << "             Menu de administrador          " << endl;
    cout << "____________________________________________" << endl;
    cout << "1. Opciones de administrador (AVL)" << endl;
    cout << "2. Manejo de deliveries (BST)" << endl;
    cout << "3. Sucursales (HashTable)" << endl;
    cout << "4. Volver al menu principal" << endl;
    cout << "____________________________________________" << endl;
    cout << "Ingrese la opcion que desea: ";
    cin >> code;
    switch (code) {
    case 1:
        system("cls");
        adminAVLMenu(controller);
        break;
    case 2:
        system("cls");
        adminDeliveryMenu(controller);
        break;
    case 3:
        system("cls");

        break;
    case 4: 
        mainMenu(controller);
        break;
    default:adminMainMenu(controller);
    }
}
void adminAVLMenu(Controller* controller) {
    code = 0;
    string name = "";
    system("cls");
    cout << "                    Opciones de administrador                 " << endl;
    cout << "______________________________________________________________" << endl;
    cout << "1. Mostrar a los administradores en el sistema en un AVL      " << endl;
    cout << "2. Mostrar a los administradores en orden por ID" << endl;
    cout << "3. Mostrar a los administradores en orden por Nombre" << endl;
    cout << "4. Buscar administrador por nombre" << endl;
    cout << "5. Verificar si el arbol es perfecto" << endl;
    cout << "6. Volver al menu principal" << endl;
    cout << "______________________________________________________________" << endl;
    cout << "Ingrese la opcion que desea: ";
    cin >> code;
    switch (code) {
    case 1:
        system("cls");
        controller->displayAdmins();
        system("pause");
        adminAVLMenu(controller);
        break;
    case 2:
        system("cls");
        controller->inOrderAdminID();
        system("pause");
        adminAVLMenu(controller);
        break;
    case 3:
        system("cls");
        controller->inOrderAdminName();
        system("pause");
        adminAVLMenu(controller);
        break;
    case 4:
        system("cls");
        cout << "    Buscar administrador por nombre    " << endl;
        cout << "_______________________________________" << endl;
        cout << "Ingrese el nombre que desea buscar: ";
        cin >> name;
        controller->findAdminByName(name);
        system("pause");
        adminAVLMenu(controller);
        break;
    case 5:
        controller->isAdminAVLPerfect();
        system("pause");
        adminAVLMenu(controller);
        break;
    case 6:
        adminMainMenu(controller);
        break;
    default: adminAVLMenu(controller);
    }
}
void adminDeliveryMenu(Controller* controller) {
    int status = 0;
    int id = 0;
    code = 0;
    system("cls");
    cout << "            Menu de administrador           " << endl;
    cout << "____________________________________________" << endl;
    cout << "1. Mostrar los deliveries en un BST" << endl;
    cout << "2. Mostrar por estado del delivery" << endl;
    cout << "3. Buscar delivery por ID" << endl;
    cout << "4. Volver al menu principal" << endl;
    cout << "____________________________________________" << endl;
    cout << "Ingrese la opcion que desea: ";
    cin >> code;
    switch (code) {
    case 1:
        system("cls");
        controller->displayDeliveries();
        system("pause");
        adminDeliveryMenu(controller);
        break;
    case 2:
        system("cls");
        cout << "      Mostrar por estado del delivery      " << endl;
        cout << "___________________________________________" << endl;
        cout << "(1: En proceso, 2: Entregado, 3: Cancelado)" << endl;
        cout << "Ingrese su opcion: ";
        cin >> status;
        system("cls");
        controller->showByStatus(status);
        system("pause");
        adminDeliveryMenu(controller);
        break;
    case 3:
        system("cls");
        cout << "              Buscar Nodo hermano          " << endl;
        cout << "___________________________________________" << endl;
        cout << "Ingrese el ID del nodo que desea buscar: ";
        cin >> id;
        controller->searchSibling(id);
        system("pause");
        adminDeliveryMenu(controller);
        break;
    case 4:
        system("cls");
        adminMainMenu(controller);
        break;
    default:adminDeliveryMenu(controller);
    }
}
void checkClientMenu(Controller* controller) {
    system("cls");
    string name = "";
    cout << "         Ingresar nombre de Cliente        " << endl;
    cout << "___________________________________________" << endl;
    cout << "Ingrese el nombre del cliente: ";
    cin.ignore();
    getline(cin, name);
    controller->enterClientName(name);
    controller->get_loginVerify() == true ? buyProductsMenu(controller) : (cout << "Nombre no registrado" << endl, system("pause"), mainMenu(controller));
}
void buyProductsMenu(Controller* controller) {
    code = 0;
    string codProd = "";
    system("cls");
    cout << "           Compras de productos            " << endl;
    cout << "___________________________________________" << endl;
    cout << "1. Escoger productos" << endl;
    cout << "2. Volver al menu principal" << endl;
    cout << "___________________________________________" << endl;
    cout << "Ingrese la opcion que desea: ";
    cin >> code;
    switch (code) {
    case 1:
        system("cls");
        controller->seeProductList(); //manda la lista de productos y agregar productos desde la controladora
        cout << "______________________________________________________________" << endl;
        cout << "Ingrese el codigo del producto que desea agregar a su carrito: "; cin >> codProd;
        controller->chooseProducts(codProd);
        if (controller->get_productAdded() == true) {
            cout << "El producto fue ingresado correctamente" << endl;
            system("pause");
            shoppingCartMenu(controller);
        }
        else {
            cout << "El producto ingresado no existe" << endl;
            system("pause");
            buyProductsMenu(controller);
        }
        break;
    case 2:
        mainMenu(controller);
        break;
    default: buyProductsMenu(controller);
    }
}
void shoppingCartMenu(Controller* controller) {
    code = 0;
    string codeProduct = "";
    system("cls");
    cout << "            Carrito de compras             " << endl;
    cout << "___________________________________________" << endl;
    cout << "1. Agregar otro producto" << endl;
    cout << "2. Borrar producto del carrito" << endl;
    cout << "3. Vaciar carrito de compras" << endl;
    cout << "4. Mostrar productos en carrito" << endl;
    cout << "5. Proceder con la compra" << endl;
    cout << "6. Volver al menu principal" << endl;
    cout << "___________________________________________" << endl;
    cout << "Ingrese su opcion: ";
    cin >> code;
    switch (code) {
    case 1:
        buyProductsMenu(controller);
        break;
    case 2:
        system("cls");
        cout << "        Productos dentro del carrito       " << endl;
        cout << "___________________________________________" << endl;
        controller->printShoppingCart();
        cout << "___________________________________________" << endl;
        cout << "Ingrese el codigo del producto que desea eliminar: ";
        cin >> codeProduct;
        controller->deleteShoppingCartProduct(codeProduct);
        system("pause");
        shoppingCartMenu(controller);
        break;
    case 3:
        controller->clearShoppingCart();
        if (controller->get_shoppingCartEmpty() == true) {
            cout << "Su carrito se vacio correctamente" << endl;
            system("pause");
            shoppingCartMenu(controller);
        }
        else {
            cout << "Su carrito no pudo ser vaciado" << endl;
            system("pause");
            shoppingCartMenu(controller);
        }
        break;
    case 4:
        system("cls");
        cout << "        Productos dentro del carrito       " << endl;
        cout << "___________________________________________" << endl;
        controller->printShoppingCart();
        cout << "Precio total de productos: " << controller->get_ShoppingCartTotalPrice() << endl;
        system("pause");
        shoppingCartMenu(controller);
        break;
    case 5:
        purchaseMenu(controller);
        break;
    case 6:
        mainMenu(controller);
        break;
    default:shoppingCartMenu(controller);
    }
}
void purchaseMenu(Controller* controller) {
    code = 0;
    system("cls");
    cout << "           Compras de productos            " << endl;
    cout << "___________________________________________" << endl;
    cout << "1. Continuar comprando" << endl;
    cout << "2. Pagar" << endl;
    cout << "3. Volver al menu principal" << endl;
    cout << "___________________________________________" << endl;
    cout << "Ingrese la opcion que desea: ";
    cin >> code;
    switch (code) {
    case 1: shoppingCartMenu(controller);
        break;
    case 2:
        orderInformationMenu(controller);
        break;
    case 3: mainMenu(controller);
        break;
    default: purchaseMenu(controller);
    }
}
void orderInformationMenu(Controller* controller) {
    code = 0;
    system("cls");
    cout << "      Informacion de la orden de compra    " << endl;
    cout << "___________________________________________" << endl;
    cout << "********¡Compra realizada con exito!*******" << endl;
    cout << "1. Mostrar boleta" << endl;
    cout << "2. Volver al menu principal" << endl;
    cout << "3. Salir" << endl;
    cout << "___________________________________________" << endl;
    cout << "Ingrese la opcion que desea: ";
    cin >> code;
    switch (code) {
    case 1:
        controller->showPaidOrder();
        system("pause");
        break;
    case 2: mainMenu(controller);
        break;
    case 3: exit(0);
    default: orderInformationMenu(controller);
    }
}