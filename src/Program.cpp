#include "../Bibliotecas/Program.hpp"

Program::Program(const std::string &moviesFile, const std::string &cinemasFile) /* : leitor(moviesFile, cinemasFile)  */ {
    
}

Program::~Program() {

}

void Program::run() {
    bool programRunning = true;
    
    // Usa o leitor para popular filmeBase;
    populate();

    // Loop principal
    while(programRunning) {

    }
}