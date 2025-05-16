#ifndef _CLASSES_H // Previne múltiplas inclusões do cabeçalho
#define _CLASSES_H // Início da definição de _CLASSES_H

#include <string>
#include <iostream>

// Classe que representa um cliente de banco
class Cliente {
private:
    std::string cpf;
    std::string nome;

public:
    // Construtor da classe Cliente
    Cliente(std::string numcpf, std::string nomecliente);

    // Métodos de acesso
    std::string obterCpf();
    std::string obterNome();
};

// Inicializa os atributos cpf e nome
Cliente::Cliente(std::string numcpf, std::string nomecliente)
    : cpf(numcpf), nome(nomecliente) {}

// Retorna o CPF do cliente
std::string Cliente::obterCpf() {
    return cpf;
}

// Retorna o nome do cliente
std::string Cliente::obterNome() {
    return nome;
}

// Classe que representa uma conta bancária
class ContaBancaria {
private:
    int numero;
    double saldo;
    Cliente titular;

public:
    // Construtor que define número, titular e saldo inicial opcional
    ContaBancaria(int nconta, Cliente titularconta, double sconta = 0);

    // Operações da conta
    double adicionarSaldo(double valor);
    double retirarSaldo(double valor);
    void enviarPara(double valor, ContaBancaria &destino1);
    void enviarPara(double valor, ContaBancaria &destino1, ContaBancaria &destino2);
    int obterNumero();
    void mostrarSaldo();
    void mostrarResumo();
};

// Inicializa os dados da conta bancária
ContaBancaria::ContaBancaria(int nconta, Cliente titularconta, double sconta)
    : numero(nconta), saldo(sconta), titular(titularconta) {}

// Exibe o saldo atual da conta
void ContaBancaria::mostrarSaldo() {
    std::cout << "O saldo atual da conta " << numero << ": R$ " << saldo << std::endl;
}

// Exibe as informações do titular e os dados da conta
void ContaBancaria::mostrarResumo() {
    std::cout << "Titular: " << titular.obterNome() << ", CPF: " << titular.obterCpf() << "\n"
              << "Número da Conta: " << numero << ", Saldo: R$ " << saldo << "\n"
              << std::endl;
}

// Retorna o número da conta
int ContaBancaria::obterNumero() {
    return numero;
}

// Realiza depósito caso o valor seja positivo
double ContaBancaria::adicionarSaldo(double valor) {
    if (valor <= 0) {
        return -1;
    }
    saldo += valor;
    return saldo;
}

// Realiza saque caso haja saldo suficiente
double ContaBancaria::retirarSaldo(double valor) {
    if (saldo < valor) {
        std::cout << "Não será possível realizar a operação \n";
        return -1;
    }
    std::cout << "Valor sacado. \n";
    saldo -= valor;
    return valor;
}

// Realiza transferência para uma conta de destino (versão 1)
void ContaBancaria::enviarPara(double valor, ContaBancaria &destino1) {
    if (saldo < valor) {
        std::cout << "Saldo insuficiente para transferência.\n";
        return;
    }
    saldo -= valor;
    destino1.adicionarSaldo(valor);
    std::cout << "Transferido: R$ " << valor << " da conta " << numero
              << " para a conta " << destino1.obterNumero() << "\n";
}

// Realiza transferência dividida igualmente entre duas contas de destino (versão 2)
void ContaBancaria::enviarPara(double valor, ContaBancaria &destino1, ContaBancaria &destino2) {
    if (saldo < valor) {
        std::cout << "Saldo insuficiente para transferência.\n";
        return;
    }
    saldo -= valor;
    destino1.adicionarSaldo(valor / 2);
    destino2.adicionarSaldo(valor / 2);
    std::cout << "Transferido: R$ " << (valor / 2) << " para cada conta "
              << "(" << destino1.obterNumero() << " e " << destino2.obterNumero() << ")"
              << " da conta " << numero << "\n";
}

#endif // Fim da definição de _CLASSES_H
