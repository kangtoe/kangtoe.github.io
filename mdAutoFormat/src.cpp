#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

std::string getFormattedDate() {
    // Get current time
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);   
    std::string timeZone = "+0900";

    // Format the date part: YYYY-MM-DD
    std::stringstream dateStream;
    dateStream << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return dateStream.str() + " " + timeZone;
}

int main(int argc, char* argv[]) {
    // Get filename either from command line argument or user input
    std::string fileName;
    
    if (argc > 1) {
        // Use the first command line argument as filename
        fileName = argv[1];
    } else {
        // Prompt user for filename
        std::cout << "Enter filename (with .md extension): ";
        std::getline(std::cin, fileName);
        
        // Add .md extension if not provided
        if (fileName.length() < 3 || 
            fileName.substr(fileName.length() - 3) != ".md") {
            fileName += ".md";
        }
    }
    
    // Get formatted date
    std::string formattedDate = getFormattedDate();
    
    // Get title (default to filename without extension)
    std::string title;
    size_t lastDot = fileName.find_last_of('.');
    std::string defaultTitle = (lastDot != std::string::npos) ? 
                               fileName.substr(0, lastDot) : fileName;
    
    std::cout << "Enter title (press Enter to use '" << defaultTitle << "'): ";
    std::string inputTitle;
    std::getline(std::cin, inputTitle);
    title = inputTitle.empty() ? defaultTitle : inputTitle;
    
    // Get categories
    std::string topCategory, subCategory;
    std::cout << "Enter top category: ";
    std::getline(std::cin, topCategory);
    std::cout << "Enter sub category: ";
    std::getline(std::cin, subCategory);
    
    // Get tags
    std::string tags;
    std::cout << "Enter tags (comma separated): ";
    std::getline(std::cin, tags);
    
    // Convert tags to lowercase
    for (char& c : tags) {
        c = std::tolower(c);
    }
    
    // Create template content
    std::string templateContent = 
        "---\n"
        "title: " + title + "\n"
        "date: " + formattedDate + "\n"
        "categories: [" + topCategory + ", " + subCategory + "]\n"
        "tags: [" + tags + "]     # TAG names should always be lowercase\n"
        "---\n";
    
    // Write to file
    std::ofstream outFile(fileName);
    
    if (outFile.is_open()) {
        outFile << templateContent;
        outFile.close();
        std::cout << "Template file created as " << fileName << std::endl;
        std::cout << "Current content:" << std::endl;
        std::cout << templateContent;
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }
    
    return 0;
}
