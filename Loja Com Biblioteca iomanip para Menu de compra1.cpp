#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

void MenuDeCompra(float cred, int stockArray[]){
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
    cout << "*                                               *" << endl;
    cout << "*************************************************" << endl;
    cout << "* Cred Atual: $" << fixed << setprecision(2) << cred << "                          *" << endl;  
    cout << "* Digite 0 para sair da loja.                   *" << endl;
    cout << "*************************************************" << endl;
}

void compra(int opc, float &cred, int stockArray[], int min, int max, int &mochila) {
    char decisao;
    float precos[] = {0.0, 1.50, 1.00, 0.50, 1.25, 3.00, 3.50};
    int produtos;
    char trabalho;
    int inventario;

    if (opc < 1 || opc > 6) {
        cout << "Opcao Invalida! Escolhe um numero de 1 a 6 só.\n";
        return;
    }

    cout << "\nEscolheste ";
    switch (opc) {
        case 1: cout <<"1- " << "o Paozinho!\n"; break;
        case 2: cout <<"2- " <<"o Leite!\n"; break;
        case 3: cout <<"3- " <<"a Agua!\n"; break;
        case 4: cout <<"4- " <<"a Manteiga!\n"; break;
        case 5: cout <<"5- " <<"a Gelatina!\n"; break;
        case 6: cout <<"6- " <<"os Crepes!\n"; break;
    }

    cout << "Temos " << stockArray[opc] << " unidades restantes do/a mesmo/a." << endl;
    cout << "\nQuantas unidades queres comprar? " << endl;
    cin >> produtos;

    while (true) {
        float total = produtos * precos[opc];

        if (cred < total) {
            cout << "Nao tens dinheiro suficiente. Precisas de $" << total << ", tens apenas $" << cred << endl;
            cout << "Quantas unidades queres comprar? ";
            cin >> produtos;
            continue;
        } else if (cred == 0){
            cout << "Nao tens mais dinheiro\nQueres trabalhar? (s/n): ";
            cin >> trabalho;
            if (trabalho == 's' || trabalho == 'S') {
                int credrand = rand() % (max - min + 1) + min;
                cred += credrand;
                cout << "Ganhaste " << credrand << ". Agora tens " << cred << " em saldo.\n";
            }
        }

        if (produtos <= 0 || produtos > stockArray[opc]) {
            cout << "\nSo temos " << stockArray[opc] << " unidades do produto que pediste." << endl;
            cout << "\nEscolhe um Numero de unidades > 0 e <= " << stockArray[opc] << ": ";
            cin >> produtos;
            continue;
        }

        if (stockArray[opc] == 0) {
            cout << " Acabou o Stock " << endl;
            break;
        }

        cout << "\nPor $" << total << ". Tens a certeza? (s/n): ";
        cin >> decisao;

        if (decisao == 's' || decisao == 'S') {
            cred -= total;
            stockArray[opc] -= produtos;
            mochila-=produtos;
            
            cout << "\nCompra realizada com sucesso! \n\nSaldo restante: $" << cred << endl;
            cout << "\nSo Tens " << mochila <<" espacos na mochila restantes "<< endl;
            if(mochila == 0){
                cout << "\nNao tens espaco na mochila suficiente " << endl;
                continue;
            }
            cout << "\nSo temos " << stockArray[opc] << " restante(s) " << endl;
            if (stockArray[opc] == 0) {
                cout << "Acabou o Stock " << endl;
            }
            break;
        } else {
            cout << "A compra foi cancelada.\n";
            break;
        }
    }

    cout << "\nPressiona Enter se queres fazer Outra compra! ";
    cin.ignore();
    cin.get();

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int opc;
    float cred = 1000.00;
    int stockArray[7] = {0, 3, 5, 10, 4, 20, 10};
    int min = 1;
    int max = 6;
    int mochila = 15;

    while (true) {
        MenuDeCompra(cred, stockArray);
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

/*
Conclusão
05/04/25
*/
