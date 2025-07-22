#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

// Enum para os tipos de imóvel
enum class PropertyType {
    House,
    Apartment,
    Land
};

class Property {
private:
    // Contador estático para IDs
    static int nextId; 
    int id;
    PropertyType type;
    int ownerId;
    double latitude;
    double longitude;
    std::string address;
    double price;

public:
    // Construtor
    Property(PropertyType type, int ownerId, double latitude, double longitude, const std::string& address, double price);

    // Métodos de acesso (getters)
    int getId() const;
    PropertyType getType() const;
    int getOwnerId() const;
    double getLatitude() const;
    double getLongitude() const;
    const std::string& getAddress() const;
    double getPrice() const;

    // Função auxiliar para converter string para PropertyType
    static PropertyType stringToType(const std::string& typeStr);

    // Reseta o contador de ID
    static void resetIdCounter();
};

#endif // PROPERTY_H