#include "File.hpp"
#include "Folder.hpp"
#include <iostream>

int main() {
    try {
        // Create a few File objects
        File file1("document.txt", "This is a text document.");
        File file2("image.png", "This is an image file.");
        File file3("notes.md", "These are my notes.");
        File file4("document.txt"); // This will have the same name as file1

        // Create a Folder
        Folder myFolder("MyFolder");

        // Add files to the folder
        if (myFolder.addFile(file1)) {
            std::cout << "Added file: " << file1.getName() << std::endl;
        }
        if (myFolder.addFile(file2)) {
            std::cout << "Added file: " << file2.getName() << std::endl;
        }
        if (!myFolder.addFile(file4)) {
            std::cout << "Failed to add file: " << file4.getName() << " (already exists)" << std::endl;
        }

        // Display the folder contents
        std::cout << "Folder contents before renaming:" << std::endl;
        myFolder.display();

        // Rename the folder
        if (myFolder.rename("NewFolderName")) {
            std::cout << "Folder renamed to: " << myFolder.getName() << std::endl;
        }

        // Display the folder contents after renaming
        std::cout << "Folder contents after renaming:" << std::endl;
        myFolder.display();

        // Create another folder
        Folder destinationFolder("DestinationFolder");

        // Copy a file to another folder
        if (myFolder.copyFile("document.txt", destinationFolder)) {
            std::cout << "File copied to destination folder." << std::endl;
        } else {
            std::cout << "Failed to copy file to destination folder." << std::endl;
        }

        // Display the destination folder contents
        std::cout << "Destination folder contents:" << std::endl;
        destinationFolder.display();

    } catch (const InvalidFormatException& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
