#include "Controller.h"
#include <string>
using namespace std;

int code = 0;

void mainMenu(Controller* controller);
void checkClientMenu(Controller* controller);
void buyProductsMenu(Controller* controller);
void shoppingCartMenu(Controller* controller);
void purchaseMenu(Controller* controller);
void orderInformationMenu(Controller* controller);

int main() {
    Controller* controller = new Controller();
    mainMenu(controller);
}

void mainMenu(Controller* controller) {
    code = 0;
    system("cls");
    cout << "Bienvenido al sistema de compras de Hiraoka" << endl;
    cout << "___________________________________________" << endl;
    cout << "1. Ingresa nombre de Cliente" << endl;
    cout << "2. Salir" << endl;
    cout << "___________________________________________" << endl;
    cout << "Ingrese la opcion que desea: ";
    cin >> code;
    switch (code) {
    case 1:
        checkClientMenu(controller);
        break;
    case 2: exit(0);
    default: mainMenu(controller);
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
    cout << "5. Ordenar el carrito" << endl;
    cout << "6. Proceder con la compra" << endl;
    cout << "7. Volver al menu principal" << endl;
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
        system("cls");
        controller->orderMerge();
        system("pause");
        shoppingCartMenu(controller);
        break;
    case 6:
        purchaseMenu(controller);
        break;
    case 7:
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
        break;
    case 2: mainMenu(controller);
        break;
    case 3: exit(0);
    default: orderInformationMenu(controller);
    }
}