#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
using namespace std;

void MenuDeCompra(float cred, int stockArray[], int mochila) {
    cout << "*************************************************" << endl;
    cout << "*          Bem-vindo a Lojinha do Blud!         *" << endl;
    cout << "*         Aqui nos vendemos so o basico!        *" << endl;
    cout << "*************************************************" << endl;
    cout << "*                                               *" << endl;
    cout << "* Produto                Preco     Stock        *" << endl;
    cout << "*  -------------------------------------------  * " << endl;
    cout << "* " << left << setw(18) << "1- Pao" << right << setw(10) << "$1.50" << right << setw(8) << stockArray[1] << "          *" << endl;
    cout << "* " << left << setw(18) << "2- Leite" << right << setw(10) << "$1.00" << right << setw(8) << stockArray[2] << "          *" << endl;
    cout << "* " << left << setw(18) << "3- Agua" << right << setw(10) << "$0.50" << right << setw(8) << stockArray[3] << "          *" << endl;
    cout << "* " << left << setw(18) << "4- Manteiga" << right << setw(10) << "$1.25" << right << setw(8) << stockArray[4] << "          *" << endl;
    cout << "* " << left << setw(18) << "5- Gelatina" << right << setw(10) << "$3.00" << right << setw(8) << stockArray[5] << "          *" << endl;
    cout << "* " << left << setw(18) << "6- Crepes" << right << setw(10) << "$3.50" << right << setw(8) << stockArray[6] << "          *" << endl;
    cout << "* " << left << setw(18) << "7- Pipocas" << right << setw(10) << "$3.50" << right << setw(8) << stockArray[7] << "          *" << endl;
    cout << "*                                               *" << endl;
    cout << "*************************************************" << endl;
    cout << "* Cred Atual: $" << fixed << setprecision(2) << cred << "                          *" << endl;
    cout << "* Mochila: " << mochila << " espacos livres                             *" << endl;
    cout << "* Digite 0 para sair da loja.                   *" << endl;
    cout << "*************************************************" << endl;
}

void compra(int opc, float &cred, int stockArray[], int min, int max, int &mochila) {
    char decisao;
    float precos[] = {0.0, 1.50, 1.00, 0.50, 1.25, 3.00, 3.50, 3.50};
    int produtos;
    char trabalho;

    if (opc < 1 || opc > 7) {
        cout << "Opcao Invalida! Escolhe um numero de 1 a 7 só.\n";
        return;
    }

    cout << "\nEscolheste ";
    switch (opc) {
        case 1: cout << "o Paozinho!\n"; break;
        case 2: cout << "o Leite!\n"; break;
        case 3: cout << "a Agua!\n"; break;
        case 4: cout << "a Manteiga!\n"; break;
        case 5: cout << "a Gelatina!\n"; break;
        case 6: cout << "os Crepes!\n"; break;
        case 7: cout << "as Pipocas!\n"; break;
    }

    if (stockArray[opc] == 0) {
        cout << "Nao temos mais stock desse produto. Escolhe outro.\n";
        return;
    }

    if (mochila <= 0) {
        cout << "Nao tens espaco na mochila para carregar mais nada.\n";
        cout << "Queres trabalhar para ganhar mais espaco? (s/n): ";
        cin >> trabalho;

        if (trabalho == 's' || trabalho == 'S') {
            int ganhoEspaco = rand() % 4 + 1;
            mochila += ganhoEspaco;
            cout << "Ganhaste +" << ganhoEspaco << " espacos na mochila! Agora tens " << mochila << " livres.\n";
        } else {
            cout << "Volta quando tiveres espaco na mochila.\n";
            return;
        }
    }

    while (true) {
        cout << "\nQuantas unidades queres comprar? ";
        cin >> produtos;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida! Digita um numero.\n";
            continue;
        }

        if (produtos <= 0) {
            cout << "Escolhe uma quantidade positiva.\n";
            continue;
        }

        if (produtos > stockArray[opc]) {
            cout << "Nao temos tantas unidades. Temos " << stockArray[opc] << " apenas.\n";
            continue;
        }

        if (produtos > mochila) {
            cout << "Nao tens espaco na mochila suficiente. Tens " << mochila << " espacos.\n";
            continue;
        }

        float total = produtos * precos[opc];

        if (cred < total) {
            cout << "Nao tens saldo suficiente. Precisas de $" << total << ", tens apenas $" << cred << ".\n";
            cout << "Queres trabalhar para ganhar dinheiro? (s/n): ";
            cin >> trabalho;

            if (trabalho == 's' || trabalho == 'S') {
                int ganho = rand() % (max - min + 1) + min;
                cred += ganho;
                int ganhoEspaco = rand() % 3 + 1;
                mochila += ganhoEspaco;

                cout << "Ganhaste $" << ganho << " e +" << ganhoEspaco << " espacos na mochila!\n";
                cout << "Saldo atual: $" << cred << ", Mochila: " << mochila << " espacos.\n";
            } else {
                cout << "Entao volta quando tiveres dinheiro.\n";
                return;
            }

            continue;
        }

        cout << "\nPor $" << total << ". Confirmas a compra? (s/n): ";
        cin >> decisao;

        if (decisao == 's' || decisao == 'S') {
            cred -= total;
            stockArray[opc] -= produtos;
            mochila -= produtos;

            cout << "Compra realizada! Saldo: $" << cred << ", Espaco na mochila: " << mochila << endl;

            if (stockArray[opc] == 0) {
                cout << "Acabou o stock deste produto!\n";
            }

            break;
        } else {
            cout << "Compra cancelada.\n";
            break;
        }
    }

    cout << "\nPressiona Enter para continuar...";
    cin.ignore();
    cin.get();

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    srand(time(0));
    int opc;
    float cred = 1000.00;
    int stockArray[8] = {0, 3, 5, 10, 4, 20, 10, 10};
    int min = 1;
    int max = 6;
    int mochila = 15;

    while (true) {
        MenuDeCompra(cred, stockArray, mochila);
        cout << "Escolhe uma das opcoes pelo Numero acima: ";
        cin >> opc;

        if (opc == 0) {
            cout << "Obrigado por visitar a lojinha! Volte sempre!\n";
            break;
        }

        compra(opc, cred, stockArray, min, max, mochila);
    }

    return 0;
}
