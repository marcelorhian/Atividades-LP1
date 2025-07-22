#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>

#include "broker.h"
#include "client.h"
#include "property.h"

constexpr double EARTH_RADIUS_KM = 6371.0;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Função para calcular a distância entre coordenadas geográficas (Haversine)
double haversine(double lat1, double lon1, double lat2, double lon2) {
    auto deg2rad = [](double d){ return d * M_PI / 180.0; };
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);
    double a = std::pow(std::sin(dLat / 2), 2) +
               std::cos(deg2rad(lat1)) * std::cos(deg2rad(lat2)) *
               std::pow(std::sin(dLon / 2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return EARTH_RADIUS_KM * c;
}

/**
 * @param brokers Vetor de todos os corretores
 * @param properties Vetor de todos os imóveis
 */
void generateSchedule(std::vector<Broker>& brokers, std::vector<Property>& properties) {

    // Filtra apenas os corretores que são avaliadores
    std::vector<Broker*> appraisers;
    for (Broker& broker : brokers) {
        if (broker.getIsAppraiser()) {
            appraisers.push_back(&broker);
        }
    }

    // Verifica se existe pelo menos um corretor avaliador
    if (appraisers.empty()) {
        return;
    }

    // Ordena os imóveis por ID para garantir uma distribuição consistente
    std::sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getId() < b.getId();
    });

    // Distribui os imóveis para os avaliadores em modo round-robin
    for (size_t i = 0; i < properties.size(); ++i) {
        appraisers[i % appraisers.size()]->propertiesToAppraise.push_back(&properties[i]);
    }

    // Para cada avaliador, ordena a rota e imprime a agenda
    bool firstBroker = true;
    for (Broker* broker : appraisers) {
        if (broker->propertiesToAppraise.empty()) {
            // Pula corretores sem imóveis para avaliar
            continue;
        }
        
        if (!firstBroker) {
            // Linha em branco entre a agenda de um corretor e outro
            std::cout << std::endl;
        }
        firstBroker = false;

        std::cout << "Corretor " << broker->getId() << std::endl;
        // O dia de trabalho começa às 9:00
        double totalTimeInMinutes = 9 * 60;
        
        // Ponto de partida inicial é a localização do corretor
        double currentLat = broker->getLatitude();
        double currentLng = broker->getLongitude();

        // Cria uma cópia da lista de imóveis para poder ordenar a rota (algoritmo do vizinho mais próximo)
        std::vector<Property*> unvisitedProperties = broker->propertiesToAppraise;

        while (!unvisitedProperties.empty()) {
            // Encontra o imóvel não visitado mais próximo
            Property* closestProperty = nullptr;
            auto itClosestProperty = unvisitedProperties.begin();
            double shortestDistance = std::numeric_limits<double>::max();

            for (auto it = unvisitedProperties.begin(); it != unvisitedProperties.end(); ++it) {
                double dist = haversine(currentLat, currentLng, (*it)->getLatitude(), (*it)->getLongitude());
                if (dist < shortestDistance) {
                    shortestDistance = dist;
                    closestProperty = *it;
                    itClosestProperty = it;
                }
            }

            // Calcula o tempo de deslocamento (2 minutos por km) e atualiza o relógio
            double travelTime = shortestDistance * 2.0;
            totalTimeInMinutes += travelTime;

            // Imprime o horário e o imóvel a ser visitado
            int hour = static_cast<int>(totalTimeInMinutes) / 60;
            int minute = static_cast<int>(totalTimeInMinutes) % 60;
            std::cout << std::setfill('0') << std::setw(2) << hour << ":"
                      << std::setw(2) << minute << " Imóvel " << closestProperty->getId() << std::endl;

            // Adiciona o tempo da avaliação (60 minutos)
            totalTimeInMinutes += 60;

            // Atualiza a localização atual para o imóvel que acabou de ser visitado
            currentLat = closestProperty->getLatitude();
            currentLng = closestProperty->getLongitude();

            // Remove o imóvel da lista de não visitados
            unvisitedProperties.erase(itClosestProperty);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Resetar os contadores para garantir um estado limpo a cada execução
    Broker::resetIdCounter();
    Client::resetIdCounter();
    Property::resetIdCounter();

    std::vector<Broker> brokers;
    std::vector<Client> clients;
    std::vector<Property> properties;

    // Leitura dos dados dos corretores
    int numBrokers;
    std::cin >> numBrokers;
    for (int i = 0; i < numBrokers; ++i) {
        std::string phone, name;
        int isAppraiserInt;
        double latitude, longitude;
        
        std::cin >> phone >> isAppraiserInt >> latitude >> longitude;
        std::getline(std::cin >> std::ws, name);
        
        bool isAppraiserBool = (isAppraiserInt == 1);
        brokers.emplace_back(name, phone, isAppraiserBool, latitude, longitude);
    }

    // Leitura dos dados dos clientes
    int numClients;
    std::cin >> numClients;
    for (int i = 0; i < numClients; ++i) {
        std::string phone, name;
        std::cin >> phone;
        std::getline(std::cin >> std::ws, name);
        clients.emplace_back(name, phone);
    }

    // Leitura dos dados dos imóveis
    int numProperties;
    std::cin >> numProperties;
    for (int i = 0; i < numProperties; ++i) {
        std::string typeStr, address;
        int ownerId;
        double latitude, longitude, price;

        std::cin >> typeStr >> ownerId >> latitude >> longitude >> price;
        std::getline(std::cin >> std::ws, address);
        
        try {
            PropertyType type = Property::stringToType(typeStr);
            properties.emplace_back(type, ownerId, latitude, longitude, address, price);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro ao ler imóvel: " << e.what() << std::endl;
        }
    }
    
    // Gera e imprime a agenda de visitas
    generateSchedule(brokers, properties);

    return 0;
}