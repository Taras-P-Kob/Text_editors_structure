#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <limits>
#include <set>
#include <locale>
#include <regex>

struct Text_Editor {
    std::string name;
    std::string manufacturer;
    std::string license;
    int rating = 0;
    int price = 0;
};

void processMenu();
void Menu();
void DisplayText_Editors(const std::string& editors);
void Edit();
void Sort();
void Search();
void SortByName(std::vector < Text_Editor >& editors);
void SortByManufacturer(std::vector < Text_Editor >& editors);
void SortByLicense(std::vector < Text_Editor >& editors);
void SortByRating(std::vector < Text_Editor >& editors);
void SortByPrice(std::vector < Text_Editor >& editors);
void printText_Editor(const std::vector < Text_Editor >& editors);
template < typename T >
std::string to_string_with_precision(const T value,
    const int n = 6);
void printLine(const std::vector < int >& widths);
void printTableHeader(const std::vector < int >& widths);
void printTableRow(const Text_Editor& editor, const std::vector<int>& widths, int lineNumber);
void searchText_Editor(const std::string& searchKeyword,
    const std::string& searchField);
bool is_number_between_1_and_100(const std::string& str);
bool is_number_between_0_and_1000(const std::string& str);
void findText_EditorByName(const std::string& editorName);
void findText_EditorByManufacturer(const std::string& editorManufacturer);
void findText_EditorByLicense(const std::string& editorLicense);
bool nameExists(const std::string& name,
    const std::string& filename);
void findText_EditorByRating(const std::string& editorRating);
void findText_EditorByPrice(const std::string& editorPrice);
void deleteLinesFromFile(std::string filename);
std::string promptAndValidateInput(const std::string& prompt, bool(*validator)(const std::string&));
void appendText_EditorToFile(const std::string& filename);
int Output_Text_Editors();
std::set < std::string > readNamesFromFile(const std::string& filename);
std::vector < Text_Editor > readEditorsFromFile(const std::string& filename);
bool isOnlySpaces(const std::string& str);
bool isValidEnglishInput(const std::string& input);
void createFileIfNotExists(const std::string& filename);
std::string toLowerCase(const std::string& str);
void editTextEditor();
bool confirmOut();
void case2_EditMenu();
void case3_SortMenu();
void case4_SearchMenu();


int main() {
    createFileIfNotExists("./text_editors.txt");
    processMenu();
    return 0;
}


void processMenu() {
    char q, l = '0';
    int p = 10, s = 10;
    std::string editorsinfo;

    Menu();

    while (p == 10) {
        std::cin >> q;

        if (std::cin.peek() != '\n') {
            std::cout << "Please enter only one character." << std::endl;

            std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            continue;
        }

        if (q < '1' || q > '5') {
            std::cout << "Invalid input. Please enter a number between 1 and 5." << std::endl;
            continue;
        }
        switch (q) {


        case '1':
            Output_Text_Editors();
            Menu();
            break;

        case '2':
            case2_EditMenu();
            break;

        case '3':
            case3_SortMenu();
            break;

        case '4':
            case4_SearchMenu();
            break;

        case '5': {
            if (confirmOut()) {
                exit(0);
            }
            else {
                p = 10;
                Menu();
            }
            break;
        }
        }
    }
}


void Menu() {
    std::cout << std::endl << "\tMenu" << std::endl << std::endl;
    std::cout << "1.Display text editors" << std::endl;
    std::cout << "2.Edit" << std::endl;
    std::cout << "3.Sort" << std::endl;
    std::cout << "4.Search" << std::endl;
    std::cout << "5.Out" << std::endl << std::endl;
    std::cout << "Choose command: ";
}
std::vector < Text_Editor > editors;
void DisplayText_Editors(const std::string& editors) {
    std::ifstream file(editors);
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    int nameWidth = 22;
    int manufWidth = 25;
    int licenseWidth = 15;
    int ratingWidth = 6;
    int priceWidth = 5;
    int lineNumber = 0;

    std::cout << "+------+------------------------+---------------------------+-----------------+--------+-------+" << std::endl;
    std::cout << "| line |          Name          |        Manufacture        |    License      | Rating | Price |" << std::endl;
    std::cout << "+------+------------------------+---------------------------+-----------------+--------+-------+" << std::endl;

    Text_Editor editor;
    while (file >> editor.name >> editor.manufacturer >> editor.license >> editor.rating >> editor.price) {
        std::cout << "| " << std::right << std::setw(4) << ++lineNumber << " | " <<
            std::left << std::setw(nameWidth) << editor.name << " | " <<
            std::left << std::setw(manufWidth) << editor.manufacturer << " | " <<
            std::left << std::setw(licenseWidth) << editor.license << " | " <<
            std::left << std::setw(ratingWidth) << editor.rating << " | " <<
            std::left << std::setw(priceWidth) << editor.price << " |" << std::endl;
    }

    std::cout << "+------+------------------------+---------------------------+-----------------+--------+-------+" << std::endl;
}

void Edit() {
    std::cout << std::endl << "\tEdit" << std::endl;
    std::cout << "1.Edit text editor" << std::endl;
    std::cout << "2.Enter new text editor" << std::endl;
    std::cout << "3.Delete text editor" << std::endl;
    std::cout << "4.Back" << std::endl;
    std::cout << "5.Out" << std::endl;
    std::cout << "Choose command: ";
}

void Sort() {
    std::cout << std::endl << "\tSort by:" << std::endl;
    std::cout << std::endl;
    std::cout << "1.Name" << std::endl;
    std::cout << "2.Manufacturer" << std::endl;
    std::cout << "3.License" << std::endl;
    std::cout << "4.Rating" << std::endl;
    std::cout << "5.Price" << std::endl;
    std::cout << "6.Back" << std::endl;
    std::cout << "7.Out" << std::endl << std::endl;
    std::cout << "Choose command: ";
}

void Search() {
    std::cout << std::endl << "\tSearch by:" << std::endl;
    std::cout << std::endl;
    std::cout << "1.Name" << std::endl;
    std::cout << "2.Manufacturer" << std::endl;
    std::cout << "3.License" << std::endl;
    std::cout << "4.Rating" << std::endl;
    std::cout << "5.Price" << std::endl;
    std::cout << "6.Back" << std::endl;
    std::cout << "7.Out" << std::endl << std::endl;
    std::cout << "Choose command: ";
}


void SortByName(std::vector < Text_Editor >& editors) {
    std::sort(editors.begin(), editors.end(), [](const Text_Editor& a,
        const Text_Editor& b) {
            return a.name < b.name;
        });
}

void SortByManufacturer(std::vector < Text_Editor >& editors) {
    std::sort(editors.begin(), editors.end(), [](const Text_Editor& a,
        const Text_Editor& b) {
            return a.manufacturer < b.manufacturer;
        });
}

void SortByLicense(std::vector < Text_Editor >& editors) {
    std::sort(editors.begin(), editors.end(), [](const Text_Editor& a,
        const Text_Editor& b) {
            return a.license < b.license;
        });
}

void SortByRating(std::vector < Text_Editor >& editors) {
    std::sort(editors.begin(), editors.end(), [](const Text_Editor& a,
        const Text_Editor& b) {
            return a.rating > b.rating;
        });
}

void SortByPrice(std::vector < Text_Editor >& editors) {
    std::sort(editors.begin(), editors.end(), [](const Text_Editor& a,
        const Text_Editor& b) {
            return a.price < b.price;
        });
}

void printText_Editor(const std::vector<Text_Editor>& editors) {
    std::vector<int> widths = { 6, 23, 26, 16, 10, 10 };
    int lineNumber = 0;

    printTableHeader(widths);

    for (const auto& editor : editors) {
        printTableRow(editor, widths, ++lineNumber);
    }

    printLine(widths);
}


template < typename T >
std::string to_string_with_precision(const T value,
    const int n) {
    std::ostringstream out;
    try {
        out.precision(n);
        out << std::fixed << value;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return "";
    }
    return out.str();
}


void printLine(const std::vector < int >& widths) {
    std::cout << "+";
    for (auto width : widths) {
        std::cout << std::string(width, '-') << "+";
    }
    std::cout << std::endl;
}

void printTableHeader(const std::vector<int>& widths) {
    std::vector<std::string> headers = { "Line", "Name", "Manufacturer", "License", "Rating", "Price" };
    printLine(widths);
    std::cout << "|";
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << " " << std::left << std::setw(widths[i] - 1) << headers[i] << "|";
    }
    std::cout << std::endl;
    printLine(widths);
}

void printTableRow(const Text_Editor& editor, const std::vector<int>& widths, int lineNumber) {
    std::cout << "|" << std::right << std::setw(widths[0] - 1) << lineNumber << " |";
    std::cout << " " << std::left << std::setw(widths[1] - 1) << editor.name.substr(0, widths[1] - 2) << "|";
    std::cout << " " << std::left << std::setw(widths[2] - 1) << editor.manufacturer.substr(0, widths[2] - 2) << "|";
    std::cout << " " << std::left << std::setw(widths[3] - 1) << editor.license.substr(0, widths[3] - 2) << "|";
    std::cout << " " << std::left << std::setw(widths[4] - 1) << to_string_with_precision(editor.rating, 2) << "|";
    std::cout << " " << std::left << std::setw(widths[5] - 1) << to_string_with_precision(editor.price, 2) << "|";
    std::cout << std::endl;
}


void searchText_Editor(const std::string& searchKeyword, const std::string& searchField) {
    std::ifstream infile("./text_editors.txt");


    Text_Editor editor;
    if (!infile) {
        std::cerr << "File opening error! Search cannot be performed." << std::endl;
        return;
    }

    std::vector < int > columnWidths = {
     5, 22, 26, 15, 10, 6
    };

    std::string lowercaseSearchKeyword = searchKeyword;
    std::transform(lowercaseSearchKeyword.begin(), lowercaseSearchKeyword.end(), lowercaseSearchKeyword.begin(), ::tolower);

    bool found = false;
    int lineNumber = 0;
    while (infile >> editor.name >> editor.manufacturer >> editor.license >> editor.rating >> editor.price) {
        std::string lowercaseField;
        if (searchField == "name") {
            lowercaseField = editor.name;
        }
        else if (searchField == "manufacturer") {
            lowercaseField = editor.manufacturer;
        }
        else if (searchField == "license") {
            lowercaseField = editor.license;
        }
        else if (searchField == "rating") {
            lowercaseField = to_string_with_precision(editor.rating);
        }
        else if (searchField == "price") {
            lowercaseField = to_string_with_precision(editor.price);
        }
        else {
            std::cerr << "Invalid search field." << std::endl;
            return;
        }

        std::transform(lowercaseField.begin(), lowercaseField.end(), lowercaseField.begin(), ::tolower);

        if (lowercaseField.find(lowercaseSearchKeyword) != std::string::npos) {
            if (!found) {
                printTableHeader(columnWidths);
                found = true;
            }
            printTableRow(editor, columnWidths, ++lineNumber);
        }
    }


    if (!found) {
        std::cout << "No matching text editors found for the keyword '" << searchKeyword << "' in the field '" << searchField << "'." << std::endl;
    }
    else {
        printLine(columnWidths);
    }
}

bool is_number_between_1_and_100(const std::string& str) {
    try {
        int number = std::stoi(str);
        return number >= 1 && number <= 100;
    }
    catch (const std::invalid_argument&) {
        return false;
    }
    catch (const std::out_of_range&) {
        return false;
    }
}

bool is_number_between_0_and_1000(const std::string& str) {
    try {
        int number = std::stoi(str);
        return number >= 0 && number <= 1000;
    }
    catch (const std::invalid_argument&) {
        return false;
    }
    catch (const std::out_of_range&) {
        return false;
    }

}

void findText_EditorByName(const std::string& editorName) {

    searchText_Editor(editorName, "name");
}

void findText_EditorByManufacturer(const std::string& editorManufacturer) {
    searchText_Editor(editorManufacturer, "manufacturer");
}

void findText_EditorByLicense(const std::string& editorLicense) {
    searchText_Editor(editorLicense, "license");
}

void findText_EditorByRating(const std::string& editorRating) {
    searchText_Editor(editorRating, "rating");
}

void findText_EditorByPrice(const std::string& editorPrice) {
    searchText_Editor(editorPrice, "price");
}

void deleteLinesFromFile(std::string filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cout << "File could not be opened.\n";
        return;
    }

    std::vector < std::string > lines;
    std::string currentLine;
    for (; std::getline(inFile, currentLine);) {
        lines.push_back(currentLine);
    }
    inFile.close();

    std::vector < std::string > linesToDelete;
    std::cout << "Enter the lines you want to delete. Enter 'END' to finish:\n";
    for (; std::getline(std::cin, currentLine);) {
        if (currentLine == "END") {
            break;
        }
        linesToDelete.push_back(currentLine);
    }

    bool found = false;
    std::vector < std::string > updatedLines;
    for (const std::string& line : lines) {
        if (std::find(linesToDelete.begin(), linesToDelete.end(), line) == linesToDelete.end()) {
            updatedLines.push_back(line);
        }
        else {
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching lines found to delete.\n";
        return;
    }

    std::ofstream outFile(filename, std::ios_base::trunc);
    for (const std::string& line : updatedLines) {
        outFile << line << std::endl;
    }
    outFile.close();

    std::cout << "Lines successfully deleted from the file.\n";
}

std::set < std::string > readNamesFromFile(const std::string& filename) {
    std::set < std::string > names;
    std::ifstream inFile(filename.c_str());
    std::string name;

    while (inFile >> name) {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        names.insert(name);
        inFile.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
    }

    return names;
}



std::string promptAndValidateInput(const std::string& prompt, bool(*validator)(const std::string&)) {
    std::string input;
    do {
        std::cout << prompt;
        std::getline(std::cin, input);
    } while (!validator(input));
    return input;
}

bool nameExists(const std::string& name,
    const std::string& filename) {
    std::ifstream inFile(filename.c_str());
    if (!inFile) {
        std::cout << "Could not open file to read data.\n";
        return false;
    }

    std::string existingName;
    while (inFile >> existingName) {
        if (existingName == name) {
            return true;
        }
        inFile.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
    }

    return false;
}

void appendText_EditorToFile(const std::string& filename) {
    std::ifstream infileTest(filename);
    if (!infileTest) {
        std::cout << "File does not exist.\n";
        return;
    }
    infileTest.close();

    std::ofstream outFile(filename, std::ios_base::app);
    if (!outFile) {
        std::cout << "File could not be opened for appending.\n";
        return;
    }

    Text_Editor editor;

    std::string name, manufacturer, license;
    do {
        name = promptAndValidateInput("\nEnter the name (max 20 characters) or 'cancel' to go back\nChoose command: ", [](const std::string& s) {
            return !s.empty() && s.length() <= 20;
            });

        if (name == "cancel") {
            return;
        }

        if (nameExists(name, filename)) {
            std::cout << "Name already exists, please enter a different name.\n";
            continue;
        }

        if (!isValidEnglishInput(name)) {
            std::cout << "Name must contain only English letters and numbers.\n";
            continue;
        }

        if (isOnlySpaces(name)) {
            std::cout << "Input cannot be just spaces. Please enter a valid input.\n";
            continue;
        }
    } while (nameExists(name, filename) || !isValidEnglishInput(name) || isOnlySpaces(name));

    editor.name = name;

    do {
        manufacturer = promptAndValidateInput("\nEnter the manufacture (max 23 characters) or 'cancel' to go back\nChoose command: ", [](const std::string& s) {
            return !s.empty() && s.length() <= 23;
            });

        if (manufacturer == "cancel") {
            return;
        }

        if (!isValidEnglishInput(manufacturer)) {
            std::cout << "Manufacture must contain only English letters and numbers.\n";
            continue;
        }

        if (isOnlySpaces(manufacturer)) {
            std::cout << "Input cannot be just spaces. Please enter a valid input.\n";
            continue;
        }
    } while ((isOnlySpaces(manufacturer)) || !isValidEnglishInput(manufacturer));

    editor.manufacturer = manufacturer;

    do {
        license = promptAndValidateInput("\nEnter the license (max 15 characters) or 'cancel' to go back\nChoose command: ", [](const std::string& s) {
            return !s.empty() && s.length() <= 15;
            });

        if (license == "cancel") {
            return;
        }

        if (!isValidEnglishInput(license)) {
            std::cout << "License must contain only English letters and numbers.\n";
            continue;
        }

        if (isOnlySpaces(license)) {
            std::cout << "Input cannot be just spaces. Please enter a valid input.\n";
            continue;
        }
    } while ((isOnlySpaces(license)) || !isValidEnglishInput(license));

    editor.license = license;

    std::string input = promptAndValidateInput("\nEnter the rating (1 - 100) or 'cancel' to go back\nChoose command: ", [](const std::string& s) {
        if (s == "cancel") {
            return true;
        }
        if (!s.empty() && std::all_of(s.begin(), s.end(), ::isdigit)) {
            int rating = std::stoi(s);
            return rating >= 1 && rating <= 100;
        }
        return false;
        });

    if (input == "cancel") {
        return;
    }

    if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) {
        editor.rating = std::stoi(input);
    }

    input = promptAndValidateInput("\nEnter the price in $ per year (number) or 'cancel' to go back\nChoose command: ", [](const std::string& s) {
        if (s == "cancel") {
            return true;
        }

        if (!s.empty() && std::all_of(s.begin(), s.end(), ::isdigit)) {
            try {
                long long price = std::stoll(s);
                return price >= 0 && price <= 1000 && price <= std::numeric_limits < int > ::max();
            }
            catch (const std::invalid_argument&) {
                return false;
            }
            catch (const std::out_of_range&) {
                return false;
            }
        }
        return false;
        });

    if (input == "cancel") {
        return;
    }

    if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) {
        editor.price = std::stoi(input);
    }

    outFile << editor.name << " ";
    outFile << editor.manufacturer << " ";
    outFile << editor.license << " ";
    outFile << editor.rating << " ";
    outFile << editor.price << std::endl;

    outFile << std::endl;

    outFile.close();
    std::cout << "The data has been successfully added to the file.\n";
}

int Output_Text_Editors() {
    std::cout << "Display text editors" << std::endl;
    std::ifstream file("./text_editors.txt");
    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    Text_Editor editor;
    std::string editors = "./text_editors.txt";
    DisplayText_Editors(editors);

    file.close();
    return 0;
}

std::vector < Text_Editor > readEditorsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file" << std::endl;
        return {};
    }

    std::vector < Text_Editor > editors;
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        Text_Editor editor;
        if (iss >> editor.name >> editor.manufacturer >> editor.license >> editor.rating >> editor.price) {
            editors.push_back(editor);
        }
    }
    return editors;
}

bool isOnlySpaces(const std::string& str) {
    return std::all_of(str.begin(), str.end(), isspace);
}

bool isValidEnglishInput(const std::string& input) {
    std::regex inputPattern("^[A-Za-z0-9_]+$");
    return std::regex_match(input, inputPattern);
}

void createFileIfNotExists(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.good()) {

        std::ofstream outfile(filename);
    }
}

std::string toLowerCase(const std::string& str) {
    std::string lowerCaseStr = str;
    std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(), ::tolower);
    return lowerCaseStr;
}


bool confirmOut() {
    char l;
    while (true) {
        std::cout << std::endl << "\tDo you really want to Out?" << std::endl;
        std::cout << "1. Yes" << std::endl << "2. No" << std::endl;
        std::cout << std::endl << "Choose command: ";
        std::cin >> l;

        if (l == '1') {
            std::cout << "Out" << std::endl;
            return true;
        }
        else if (l == '2') {
            return false;
        }
        else {
            std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void editTextEditor() {
    int p = 10;
    std::vector<Text_Editor> editors;
    std::string name, input;
    int choice;
    bool found = false;
    bool isUnique;


    std::ifstream inFile("./text_editors.txt");
    Text_Editor editor;
    while (inFile >> editor.name >> editor.manufacturer >> editor.license >> editor.rating >> editor.price) {
        editors.push_back(editor);
    }
    inFile.close();

    std::cout << "Enter the name of the text editor to edit or else to go back: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (auto& ed : editors) {
        if (toLowerCase(ed.name) == toLowerCase(name)) {
            found = true;
            std::cout << "1 Name\n2 Manufacturer\n3 License\n4 Rating\n5 Price\n6 Back\n7 Out\nEnter your choice: ";
            bool validChoice = false;
            do {
                std::cin >> choice;
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else if (choice < 1 || choice > 7) {
                    std::cout << "Please enter a number between 1 and 7." << std::endl;
                }
                else {
                    validChoice = true;
                }
            } while (!validChoice);
            bool isUnique = true;
            switch (choice) {

            case 1:
                std::cout << "Edit name (current: " << ed.name << "), or enter 'cancel' to go back: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                if (input == "cancel") break;



                for (const auto& otherEd : editors) {
                    if (toLowerCase(otherEd.name) == toLowerCase(input)) {
                        isUnique = false;
                        break;
                    }
                }

                if (!isUnique) {
                    std::cout << "This name already exists. Please enter a different name." << std::endl;
                }
                else {
                    if (!input.empty() && !isOnlySpaces(input) && isValidEnglishInput(input)) {
                        if (input.length() > 20) {
                            std::cout << "Input is too long. Please enter up to 20 characters." << std::endl;
                        }
                        else {
                            ed.name = input;
                        }
                    }
                    else {
                        std::cout << "Invalid input." << std::endl;
                    }
                }
                break;

            case 2:
                std::cout << "Edit manufacturer (current: " << ed.manufacturer << "), or enter 'cancel' to go back: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                if (input == "cancel") break;

                if (!input.empty() && !isOnlySpaces(input) && isValidEnglishInput(input)) {
                    if (input.length() > 23) {
                        std::cout << "Input is too long. Please enter up to 23 characters." << std::endl;
                    }
                    else {
                        ed.manufacturer = input;
                    }
                }
                else {
                    std::cout << "Manufacturer name cannot be empty or only spaces." << std::endl;
                }
                break;


            case 3:
                std::cout << "Edit license (current: " << ed.license << "), or enter 'cancel' to go back: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                if (input == "cancel") break;

                if (!input.empty() && !isOnlySpaces(input)) {
                    if (input.length() > 15) {
                        std::cout << "Input is too long. Please enter up to 15 characters." << std::endl;
                    }
                    else {
                        ed.license = input;
                    }
                }
                else {
                    std::cout << "Invalid license. Please enter a valid English name (up to 15 alphanumeric characters)." << std::endl;
                }
                break;



            case 4:
                std::cout << "Edit rating from 1 to 100 (current: " << ed.rating << "), or enter 'cancel' to go back: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                if (input == "cancel") break;

                try {
                    int newRating = std::stoi(input);
                    if (newRating >= 1 && newRating <= 100) {
                        ed.rating = newRating;
                    }
                    else {
                        std::cout << "Rating must be between 1 and 100." << std::endl;
                    }
                }
                catch (std::invalid_argument const& e) {
                    std::cout << "Invalid rating. Please enter a valid number." << std::endl;
                }
                catch (std::out_of_range const& e) {
                    std::cout << "Rating is too large." << std::endl;
                }
                break;

            case 5:
                std::cout << "Edit price in $ per year from 0 to 1000 (current: " << ed.price << "), or enter 'cancel' to go back: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                if (input == "cancel") break;

                try {
                    int newPrice = std::stoi(input);
                    if (newPrice >= 0 && newPrice <= 1000) {
                        ed.price = newPrice;
                    }
                    else {
                        std::cout << "Price must be between 0 and 1000." << std::endl;
                    }
                }
                catch (std::invalid_argument const& e) {
                    std::cout << "Invalid price. Please enter a valid number." << std::endl;
                }
                catch (std::out_of_range const& e) {
                    std::cout << "Price is too large." << std::endl;
                }
                break;
            case 6:
                return;
                break;

            case 7:
            {
                if (confirmOut()) {
                    exit(0);
                }
                else {
                    p = 10;
                }
                break;
            }
            default:
                std::cout << "Invalid choice." << std::endl;
                break;
            }



        }
    }

    if (!found) {
        std::cout << "Text editor not found." << std::endl;
        return;
    }

    std::ofstream outFile("./text_editors.txt", std::ios::trunc);
    for (const auto& ed : editors) {
        outFile << ed.name << " " << ed.manufacturer << " " << ed.license << " " << ed.rating << " " << ed.price << std::endl;
    }
    outFile.close();
}

void case2_EditMenu() {
    Edit();
    int s = 10;

    while (s == 10) {
        char l = '0';
        std::cin >> l;
        int p = 10;

        if (l < '1' || l > '5' || std::cin.peek() != '\n') {
            std::cout << "Invalid input. Please enter a number between 1 and 5." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (l) {
        case '1':
            Output_Text_Editors();
            editTextEditor();
            Edit();
            break;

        case '2':
            Output_Text_Editors();
            {
                std::string filename = "./text_editors.txt";
                std::cin.ignore();
                appendText_EditorToFile(filename);
            }
            Edit();
            break;

        case '3':
            Output_Text_Editors();
            {
                std::string filename = "./text_editors.txt";
                std::cin.ignore();
                deleteLinesFromFile(filename);
            }
            Edit();
            break;

        case '4':
            s = 0;
            Menu();
            break;

        case '5': {
            if (confirmOut()) {
                exit(0);
            }
            else {
                p = 10;
                Edit();
            }
            break;
        }

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}
void case3_SortMenu() {
    Sort();

    std::ifstream file("./text_editors.txt");
    if (!file) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    std::vector<Text_Editor> editors;
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        Text_Editor editor;
        if (iss >> editor.name >> editor.manufacturer >> editor.license >> editor.rating >> editor.price) {
            editors.push_back(editor);
        }
    }
    file.close();

    int s = 10;
    char l;

    while (s == 10) {
        std::cin >> l;

        if (std::cin.peek() != '\n') {
            std::cout << "Please enter only one character." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (l) {
        case '1':
            SortByName(editors);
            std::cout << "Text editors sorted by name:" << std::endl;
            printText_Editor(editors);
            Sort();
            break;

        case '2':
            SortByManufacturer(editors);
            std::cout << "Text editors sorted by manufacturer:" << std::endl;
            printText_Editor(editors);
            Sort();
            break;

        case '3':
            SortByLicense(editors);
            std::cout << "Text editors sorted by license:" << std::endl;
            printText_Editor(editors);
            Sort();
            break;

        case '4':
            SortByRating(editors);
            std::cout << "Text editors sorted by rating:" << std::endl;
            printText_Editor(editors);
            Sort();
            break;

        case '5':
            SortByPrice(editors);
            std::cout << "Text editors sorted by price:" << std::endl;
            printText_Editor(editors);
            Sort();
            break;

        case '6':
            s = 0;
            Menu();
            break;

        case '7':
            if (confirmOut()) {
                exit(0);
            }
            else {
                s = 10;
                Sort();
            }
            break;

        default:
            std::cout << "Invalid input. Please enter a number between 1 and 7." << std::endl;
        }
    }
}

void case4_SearchMenu() {
    Search();
    char l;
    std::string editorsinfo;
    int s = 10, p = 10;

    while (s == 10) {
        std::cin >> l;

        if (std::cin.peek() != '\n') {
            std::cout << "Please enter only one character." << std::endl;
            std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            continue;
        }

        if (l < '1' || l > '7') {
            std::cout << "Invalid input. Please enter a number between 1 and 7." << std::endl;
            continue;
        }

        switch (l) {
        case '1':
            std::cout << "Enter name: ";
            std::cin >> editorsinfo;
            std::cout << "Result" << std::endl;
            findText_EditorByName(editorsinfo);
            Search();
            break;

        case '2':
            std::cout << "manufacturer: ";
            std::cin >> editorsinfo;
            std::cout << "Result" << std::endl;
            findText_EditorByManufacturer(editorsinfo);
            Search();
            break;

        case '3':
            std::cout << "Enter license: ";
            std::cin >> editorsinfo;
            std::cout << "Result" << std::endl;
            findText_EditorByLicense(editorsinfo);
            Search();
            break;

        case '4':
            std::cout << "Enter rating: ";
            std::cin >> editorsinfo;
            if (is_number_between_1_and_100(editorsinfo)) {
                std::cout << "Result" << std::endl;
                findText_EditorByRating(editorsinfo);
                Search();
            }
            else {
                std::cout << "Invalid rating. Please enter a number for rating between 1 and 100." << std::endl;
                Search();
            }
            break;

        case '5':
            std::cout << "Enter price: ";
            std::cin >> editorsinfo;
            if (is_number_between_0_and_1000(editorsinfo)) {
                std::cout << "Result" << std::endl;
                findText_EditorByPrice(editorsinfo);
                Search();
            }
            else {
                std::cout << "Invalid rating. Please enter a number for price between 0 and 1000." << std::endl;
                Search();
            }
            break;

        case '6':
            s = 0;
            Menu();
            break;

        case '7': {
            if (confirmOut()) {
                exit(0);
            }
            else {
                p = 10;
                Search();
            }
            break;
        }

        default:
            std::cout << std::endl << "You have entered an invalid character, please enter the present character" << std::endl;
        }
    }
}
