#include "property.h"
#include <stdexcept>
#include <algorithm> // Necessário para std::transform

// Inicialização do contador estático de ID
int Property::nextId = 1;

// Construtor
Property::Property(PropertyType type, int ownerId, double latitude, double longitude, const std::string& address, double price)
    : id(nextId++), type(type), ownerId(ownerId), latitude(latitude), longitude(longitude), address(address), price(price) {}

// Implementação dos métodos de acesso (getters)
int Property::getId() const {
    return id;
}

PropertyType Property::getType() const {
    return type;
}

int Property::getOwnerId() const {
    return ownerId;
}

double Property::getLatitude() const {
    return latitude;
}

double Property::getLongitude() const {
    return longitude;
}

const std::string& Property::getAddress() const {
    return address;
}

double Property::getPrice() const {
    return price;
}

// Implementação da função de conversão de string para o tipo de imóvel
PropertyType Property::stringToType(const std::string& typeStr) {
    std::string lowerTypeStr = typeStr;
    // Converte a string de entrada para minúsculas para não diferenciar "Casa" de "casa"
    std::transform(lowerTypeStr.begin(), lowerTypeStr.end(), lowerTypeStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    if (lowerTypeStr == "house" || lowerTypeStr == "casa") return PropertyType::House;
    if (lowerTypeStr == "apartment" || lowerTypeStr == "apartamento") return PropertyType::Apartment;
    if (lowerTypeStr == "land" || lowerTypeStr == "terreno") return PropertyType::Land;
    
    throw std::invalid_argument("Tipo de imóvel desconhecido: " + typeStr);
}

// Reseta o contador de ID para o valor inicial
void Property::resetIdCounter() {
    nextId = 1;
}
