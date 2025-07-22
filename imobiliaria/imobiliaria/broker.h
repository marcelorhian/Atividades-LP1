#ifndef BROKER_H
#define BROKER_H

#include <string>
#include <vector>

// Forward declaration para evitar dependência circular com Property
class Property;

class Broker {
private:
    // Contador estático para gerar IDs únicos
    static int nextId;
    int id;
    std::string name;
    std::string phone;
    bool isAppraiser;
    double latitude;
    double longitude;
    
public:
    // Vetor para armazenar os imóveis atribuídos a este corretor
    std::vector<Property*> propertiesToAppraise;

    // Construtor
    Broker(const std::string& name, const std::string& phone, bool isAppraiser, double latitude, double longitude);

    // Métodos de acesso (getters)
    int getId() const;
    const std::string& getName() const;
    const std::string& getPhone() const;
    bool getIsAppraiser() const;
    double getLatitude() const;
    double getLongitude() const;

    // Reseta o contador de ID
    static void resetIdCounter();
};

#endif // BROKER_H