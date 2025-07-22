#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private:
    // Contador estático para IDs
    static int nextId;
    int id;
    std::string name;
    std::string phone;

public:
    // Construtor
    Client(const std::string& name, const std::string& phone);

    // Métodos de acesso (getters)
    int getId() const;
    const std::string& getName() const;
    const std::string& getPhone() const;

    // Reseta o contador de ID
    static void resetIdCounter();
};

#endif // CLIENT_H