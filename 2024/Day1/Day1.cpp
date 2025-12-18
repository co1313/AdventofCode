#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Kan input.txt niet openen!\n";
        return 1;
    }

    std::vector<int> col1;
    std::vector<int> col2;

    int a, b;

    // Inlezen
    while (file >> a >> b) {
        col1.push_back(a);
        col2.push_back(b);
    }

    file.close();

    // Sorteren
    std::sort(col1.begin(), col1.end());
    std::sort(col2.begin(), col2.end());

    // Maak dist even groot
    std::vector<int> dist(col1.size());

    // Correcte index-lus
    for (size_t i = 0; i < col1.size(); i++) {
        dist[i] = std::abs(col1[i] - col2[i]);
    }

    // Som
    int distance = std::accumulate(dist.begin(), dist.end(), 0);

    // init similarity
    std::vector<int> sim(col1.size());

    // indexlus similarity
    for (size_t i = 0; i < col1.size(); i++) {
        sim[i] = col1[i]*std::count(col2.begin(), col2.end(), col1[i]);
    }
    // Som
    int similarity = std::accumulate(sim.begin(), sim.end(), 0);

    // Print
    std::cout << "Distance: ";
    for (int x : dist) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Total Distance: " << distance << "\n";
        
    std::cout << "Similarity: ";
    for (int x : sim) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Total Similarity: " << similarity << "\n";
    return 0;
}
