#include "File.hpp"
      
std::string File::getName() const {
   return filename_;
}

std::string File::getContents() const {
   return contents_;
}

void File::setContents(const std::string& new_contents) {
   contents_ = new_contents;
}

int* File::getIcon() const {
   return icon_;
} 

void File::setIcon(int* new_icon) {
   if (icon_) { delete[] icon_; }
   icon_ = new_icon;
} 

std::ostream& operator<< (std::ostream& os, const File& target) {
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents(); 
   return os;
}

bool File::operator<(const File& rhs) const {
   return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE. 
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a; 
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================
File::File(std::string filename, std::string contents, int* icon) 
      : filename_ { filename }, contents_ { contents }, icon_ { icon }
{
   if(filename.empty()){
      filename_ = "NewFile.txt";
   } else {
        auto period_pos = std::find(filename.begin(), filename.end(), '.');
        if (period_pos == filename.end() || period_pos + 1 == filename.end()) {
            filename_ = filename + ".txt"; 
        } else {
            int period_count = std::count(filename.begin(), filename.end(), '.');
            bool valid = std::all_of(filename.begin(), filename.end(), [](char c) {
                return std::isalnum(c) || c == '.';
            });

            if (!valid || period_count != 1) {
                throw InvalidFormatException("Invalid filename format");
            }
            filename_ = filename;
        }

        //std::cout << "constructor worked yay \n";
    }

    if (icon) {
        icon_ = new int[ICON_DIM];
        std::copy(icon, icon + ICON_DIM, icon_);
    }
}

size_t File::getSize() const {
   return contents_.size();
}

File::File(const File& rhs)
    : filename_(rhs.filename_), contents_(rhs.contents_), icon_(nullptr) {
    if (rhs.icon_) {
        icon_ = new int[ICON_DIM];
        std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, icon_);
    }
}

File& File::operator=(const File& rhs) {
    if (this != &rhs) { 
        filename_ = rhs.filename_;
        contents_ = rhs.contents_;

        if (icon_) { delete[] icon_; }
        if (rhs.icon_) {
            icon_ = new int[ICON_DIM];
            std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, icon_);
        } else {
            icon_ = nullptr;
        }
    }
    return *this;
}

File::File(File&& rhs)
    : filename_(std::move(rhs.filename_)), contents_(std::move(rhs.contents_)), icon_(rhs.icon_) {
    rhs.icon_ = nullptr; 
}

// Move assignment operator
File& File::operator=(File&& rhs) {
    if (this != &rhs) { 
        filename_ = std::move(rhs.filename_);
        contents_ = std::move(rhs.contents_);

        if (icon_) { delete[] icon_; }
        icon_ = rhs.icon_;
        rhs.icon_ = nullptr; 
    }
    return *this;
}

File::~File() {
   delete[] icon_;
   //std::cout << "destructor worked yay\n";
}