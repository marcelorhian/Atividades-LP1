#include "broker.h"

// Inicialização do contador estático de ID
int Broker::nextId = 1;

// Construtor
Broker::Broker(const std::string& name, const std::string& phone, bool isAppraiser, double latitude, double longitude)
    : id(nextId++), name(name), phone(phone), isAppraiser(isAppraiser), latitude(latitude), longitude(longitude) {}

// Implementação dos métodos de acesso (getters)
int Broker::getId() const {
    return id;
}

const std::string& Broker::getName() const {
    return name;
}

const std::string& Broker::getPhone() const {
    return phone;
}

bool Broker::getIsAppraiser() const {
    return isAppraiser;
}

double Broker::getLatitude() const {
    return latitude;
}

double Broker::getLongitude() const {
    return longitude;
}

// Reseta o contador de ID para o valor inicial
void Broker::resetIdCounter() {
    nextId = 1;
}