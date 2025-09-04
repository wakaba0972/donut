#include "core/renderer.h"
#include "ui/ui.h"
#include "log/logger.h"
#include <iostream>
#include <memory>

int main() {
    try {
        // Initialize logging
        ASCII3D::Logger::getInstance().setLevel(ASCII3D::LogLevel::INFO);
        LOG_INFO("ASCII 3D Renderer starting up");
        
        // Create and run the user interface
        auto ui = std::make_unique<ASCII3D::UserInterface>();
        ui->run();
        
        LOG_INFO("Application shutting down normally");
        return 0;
        
    } catch (const std::exception& e) {
        LOG_ERROR("Application error: " + std::string(e.what()));
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
}