#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "classes.h"

int main() {
    // Criação dos clientes
    Cliente cliente1("111.111.111-11", "Antony");
    Cliente cliente2("222.222.222-22", "Bruno");
    Cliente cliente3("333.333.333-33", "Carlos");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Antony
    conta1.mostrarSaldo();

    // Antony transfere R$200 para Bruno
    conta1.enviarPara(200.0, conta2);

    // Antony transfere R$300 divididos entre Bruno e Carlos
    conta1.enviarPara(300.0, conta2, conta3);

    // Exibição dos saldos finais
    cout << endl;
    conta1.mostrarResumo();
    conta2.mostrarResumo();
    conta3.mostrarResumo();

    return 0;
}
