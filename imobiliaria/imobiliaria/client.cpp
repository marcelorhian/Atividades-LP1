#include "client.h"

// Inicialização do contador estático de ID
int Client::nextId = 1;

// Construtor
Client::Client(const std::string& name, const std::string& phone)
    : id(nextId++), name(name), phone(phone) {}

// Implementação dos métodos de acesso (getters)
int Client::getId() const {
    return id;
}

const std::string& Client::getName() const {
    return name;
}

const std::string& Client::getPhone() const {
    return phone;
}

// Reseta o contador de ID para o valor inicial
void Client::resetIdCounter() {
    nextId = 1;
}