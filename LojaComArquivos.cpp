#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
using namespace std;

// Variáveis Globais
float precos[] = {0.0, 1.50, 1.00, 0.50, 1.25, 3.00, 3.50, 3.50};
float ProdutosTamanho[] = {0.0, 0.5, 0.6, 0.4, 0.7, 0.9, 1.5, 2};

void carregarProgresso(float &cred, int stockArray[], float &mochila) {
    std::ifstream arquivo("progresso.txt");

    if (arquivo.is_open()) {
        arquivo >> cred;

        for (int i = 1; i <= 7; ++i) {
            arquivo >> stockArray[i];
        }

        arquivo >> mochila;

        arquivo.close();  
        std::cout << "Progresso carregado com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao carregar o progresso ou arquivo não encontrado!" << std::endl;
    }
}

void salvarProgresso(float cred, int stockArray[], float mochila) {
    std::ofstream arquivo("progresso.txt");

    if (arquivo.is_open()) {
        arquivo << cred << "\n";  
        for (int i = 1; i <= 7; ++i) {
            arquivo << stockArray[i] << " ";  // Corrigido o comentário
        }
        arquivo << "\n";
        arquivo << mochila << "\n";  

        arquivo.close();  
        std::cout << "Progresso salvo com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao salvar o progresso!" << std::endl;
    }
}

void MenuDeCompra(float cred, int stockArray[], float mochila) {
    cout << "*************************************************" << endl;
    cout << "*          Bem-vindo a Lojinha do Blud!         *" << endl;
    cout << "*         Aqui nos vendemos so o basico!        *" << endl;
    cout << "*************************************************" << endl;
    cout << "*                                               *" << endl;
    cout << "* Produto                Preco     Stock        *" << endl;
    cout << "*  -------------------------------------------  * " << endl;
    cout << "* " << left << setw(18) << "1- Pao" << right << setw(10) << "$"<< precos[1] << right << setw(8) << stockArray[1] << "          *" << endl;
    cout << "* " << left << setw(18) << "2- Leite" << right << setw(10) << "$"<< precos[2] << right << setw(8) << stockArray[2] << "          *" << endl;
    cout << "* " << left << setw(18) << "3- Agua" << right << setw(10) << "$"<< precos[3] << right << setw(8) << stockArray[3] << "          *" << endl;
    cout << "* " << left << setw(18) << "4- Manteiga" << right << setw(10) << "$"<< precos[4] << right << setw(8) << stockArray[4] << "          *" << endl;
    cout << "* " << left << setw(18) << "5- Gelatina" << right << setw(10) << "$"<< precos[5] << right << setw(8) << stockArray[5] << "          *" << endl;
    cout << "* " << left << setw(18) << "6- Crepes" << right << setw(10) << "$" << precos[6]<< right << setw(8) << stockArray[6] << "          *" << endl;
    cout << "* " << left << setw(18) << "7- Pipocas" << right << setw(10) << "$"<< precos[7] << right << setw(8) << stockArray[7] << "          *" << endl;
    cout << "*                                               *" << endl;
    cout << "*************************************************" << endl;
    cout << "* Cred Atual: $" << fixed << setprecision(2) << cred << "                          *" << endl;
    cout << "* Mochila: " << mochila << " espacos livres                             *" << endl;
    cout << "* Digite 0 para sair da loja.                   *" << endl;
    cout << "*************************************************" << endl;
}

void compra(int opc, float &cred, int stockArray[], float &mochila) {
    char decisao;
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
                int ganho = rand() % 6 + 1;
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
            mochila -= ProdutosTamanho[opc];

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
    float mochila = 15;

    while (true) {
        MenuDeCompra(cred, stockArray, mochila);
        cout << "Escolhe uma das opcoes pelo Numero acima: ";
        cin >> opc;

        if (opc == 0) {
            cout << "Obrigado por visitar a lojinha! Volte sempre!\n";
            salvarProgresso(cred, stockArray, mochila); // Salvando progresso ao sair
            break;
        }

        compra(opc, cred, stockArray, mochila);
    }

    return 0;
}
