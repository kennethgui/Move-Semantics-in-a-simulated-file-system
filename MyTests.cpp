#include <iostream>
#include <cassert>
#include "Folder.hpp"
#include "File.hpp"

void testFolderConstructor() {
    Folder defaultFolder;
    assert(defaultFolder.getName() == "NewFolder");

    try {
        Folder invalidFolder("Invalid@Name");
        assert(false); // Should not reach this line
    } catch (const InvalidFormatException&) {
        // Expected
    }

    Folder validFolder("ValidName");
    assert(validFolder.getName() == "ValidName");
}

void testRename() {
    Folder folder("MyFolder");
    assert(folder.rename("NewName") == true);
    assert(folder.getName() == "NewName");
    assert(folder.rename("Invalid@Name") == false); // Invalid name should not rename
    assert(folder.getName() == "NewName"); // Name should remain unchanged
}

void testAddFile() {
    Folder folder("MyFolder");
    File file1("File1.txt");
    File file2("File2.txt");

    assert(folder.addFile(file1) == true); // Should be added successfully
    assert(folder.addFile(file2) == true); // Should be added successfully
    assert(folder.addFile(file1) == false); // File1 already exists

    // Check if file names are correct
    folder.display(); // Expected output: File1.txt, File2.txt
}

void testRemoveFile() {
    Folder folder("MyFolder");
    File file1("File1.txt");
    folder.addFile(file1);

    assert(folder.removeFile("File1.txt") == true); // Should remove successfully
    assert(folder.removeFile("File1.txt") == false); // Should fail since it's already removed
}

void testMoveFileTo() {
    Folder source("SourceFolder");
    Folder destination("DestinationFolder");
    File file1("File1.txt");

    source.addFile(file1);
    assert(source.moveFileTo("File1.txt", destination) == true); // Should move successfully
    assert(destination.removeFile("File1.txt") == true); // Should find the file in the destination
    assert(source.moveFileTo("File1.txt", destination) == false); // Should fail since the file doesn't exist in source
}

void testCopyFileTo() {
    Folder source("SourceFolder");
    Folder destination("DestinationFolder");
    File file1("File1.txt");

    source.addFile(file1);
    assert(source.copyFileTo("File1.txt", destination) == true); // Should copy successfully
    assert(destination.removeFile("File1.txt") == true); // Should find the file in the destination
    assert(source.copyFileTo("File1.txt", destination) == false); // Should fail since file already exists in destination
}

void testGetSize() {
    Folder folder("MyFolder");
    File file1("File1.txt", "Some content");
    File file2("File2.txt", "More content");

    folder.addFile(file1);
    folder.addFile(file2);
    assert(folder.getSize() == 2); // Assuming 1 file = 1 size for simplicity
}

void testDisplay() {
    Folder folder("MyFolder");
    File file1("File1.txt");
    File file2("File2.txt");

    folder.addFile(file1);
    folder.addFile(file2);

    std::cout << "Testing display output:\n";
    folder.display(); // Check console output manually
}

int main() {
    testFolderConstructor();
    testRename();
    testAddFile();
    testRemoveFile();
    testMoveFileTo();
    testCopyFileTo();
    testGetSize();
    testDisplay();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
