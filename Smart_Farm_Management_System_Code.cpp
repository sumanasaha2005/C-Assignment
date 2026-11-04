// Smart Farm Management System
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Advisory {
public:
    virtual void giveAdvice() = 0;
    virtual ~Advisory() {}
};

class Crop : public Advisory {
protected:
    string name;
    double area;          
    string season;
    double yieldPerAcre; 
    static int count;     

public:
    
    Crop() {
        name = "Unknown";
        area = 0;
        season = "Unknown";
        yieldPerAcre = 0;
        count++;
    }

    Crop(string n, double a) {
        if (a <= 0)
            throw invalid_argument("Area must be greater than 0");
        name = n;
        area = a;
        season = "Unknown";
        yieldPerAcre = 0;
        count++;
    }

    Crop(string n, double a, string s, double y) {
        if (a <= 0)
            throw invalid_argument("Area must be greater than 0");
        if (y < 0)
            throw invalid_argument("Yield cannot be negative");
        name = n;
        area = a;
        season = s;
        yieldPerAcre = y;
        count++;
    }

    virtual ~Crop() {
        count--;
    }

    string getName() { return name; }
    static int getCount() { return count; }

    virtual double totalYield() {
        return area * yieldPerAcre;
    }

    virtual string getType() { return "Crop"; }

    virtual void display() {
        cout << left << setw(11) << getType()
             << setw(12) << name
             << setw(8) << area
             << setw(10) << season
             << setw(12) << yieldPerAcre
             << setw(12) << totalYield();
    }

    virtual void saveToFile(ofstream &fout) {
        fout << name << " " << area << " " << season << " " << yieldPerAcre << " ";
    }

    bool operator>(Crop &c) {
        return yieldPerAcre > c.yieldPerAcre;
    }
    bool operator<(Crop &c) {
        return yieldPerAcre < c.yieldPerAcre;
    }
    bool operator==(Crop &c) {
        return yieldPerAcre == c.yieldPerAcre;
    }
};

int Crop::count = 0;  

class CerealCrop : public Crop {
    string fertilizerType;
public:
    CerealCrop() : Crop() {
        fertilizerType = "None";
    }

    CerealCrop(string n, double a, string s, double y, string f) : Crop(n, a, s, y) {
        fertilizerType = f;
    }

    string getType() { return "Cereal"; }

    void display() {
        Crop::display();
        cout << "Fertilizer: " << fertilizerType << endl;
    }

    void saveToFile(ofstream &fout) {
        fout << "Cereal ";
        Crop::saveToFile(fout);
        fout << fertilizerType << endl;
    }

    void giveAdvice() {
        cout << name << ": Use " << fertilizerType
             << " fertilizer, remove weeds regularly and harvest when grains are hard." << endl;
    }
};

class VegetableCrop : public Crop {
    int irrigationFreq;   
public:
    VegetableCrop() : Crop() {
        irrigationFreq = 1;
    }

    VegetableCrop(string n, double a, string s, double y, int i) : Crop(n, a, s, y) {
        if (i <= 0)
            throw invalid_argument("Irrigation frequency must be positive");
        irrigationFreq = i;
    }

    string getType() { return "Vegetable"; }

    double totalYield() {
        return area * yieldPerAcre * 0.9;
    }

    void display() {
        Crop::display();
        cout << "Irrigation: every " << irrigationFreq << " days" << endl;
    }

    void saveToFile(ofstream &fout) {
        fout << "Vegetable ";
        Crop::saveToFile(fout);
        fout << irrigationFreq << endl;
    }

    void giveAdvice() {
        cout << name << ": Water every " << irrigationFreq
             << " days, use mulching and check for pests." << endl;
    }
};

double readNumber(string msg) {
    double x;
    cout << msg;
    cin >> x;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw invalid_argument("Please enter a valid number");
    }
    return x;
}

void addCrop(vector<Crop*> &crops) {
    int type;
    string name, season;
    double area, yield;

    cout << "1. Cereal crop\n2. Vegetable crop\nEnter type: ";
    cin >> type;
    if (cin.fail() || (type != 1 && type != 2)) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw invalid_argument("Type must be 1 or 2");
    }

    cout << "Enter name: ";
    cin >> name;
    area = readNumber("Enter area (acres): ");
    cout << "Enter season: ";
    cin >> season;
    yield = readNumber("Enter yield per acre (quintals): ");

    if (type == 1) {
        string fert;
        cout << "Enter fertilizer type: ";
        cin >> fert;
        crops.push_back(new CerealCrop(name, area, season, yield, fert));
    } else {
        int freq = (int)readNumber("Enter irrigation frequency (days): ");
        crops.push_back(new VegetableCrop(name, area, season, yield, freq));
    }
    cout << "Crop added successfully!" << endl;
}

void displayAll(vector<Crop*> &crops) {
    if (crops.empty()) {
        cout << "No crops recorded yet." << endl;
        return;
    }
    cout << left << setw(11) << "Type" << setw(12) << "Name" << setw(8) << "Area"
         << setw(10) << "Season" << setw(12) << "Yield/Acre" << setw(12) << "Total" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < crops.size(); i++)
        crops[i]->display();
    cout << "Total crops: " << Crop::getCount() << endl;
}

void showTotalYield(vector<Crop*> &crops) {
    double sum = 0;
    cout << fixed << setprecision(2);
    for (int i = 0; i < crops.size(); i++) {
        double y = crops[i]->totalYield();   
        cout << crops[i]->getName() << " (" << crops[i]->getType() << "): "
             << y << " quintals" << endl;
        sum += y;
    }
    cout << "Total farm yield: " << sum << " quintals" << endl;
}

void compareCrops(vector<Crop*> &crops) {
    if (crops.size() < 2)
        throw runtime_error("Need at least 2 crops to compare");
    int a, b;
    cout << "Enter two crop numbers (1 to " << crops.size() << "): ";
    cin >> a >> b;
    if (cin.fail() || a < 1 || b < 1 || a > crops.size() || b > crops.size()) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw invalid_argument("Invalid crop numbers");
    }
    Crop &c1 = *crops[a - 1];
    Crop &c2 = *crops[b - 1];
    if (c1 > c2)
        cout << c1.getName() << " has higher yield than " << c2.getName() << endl;
    else if (c1 < c2)
        cout << c2.getName() << " has higher yield than " << c1.getName() << endl;
    else
        cout << "Both crops have the same yield" << endl;
}

void saveData(vector<Crop*> &crops) {
    ofstream fout("crops.txt");
    if (!fout)
        throw runtime_error("Could not open file");
    for (int i = 0; i < crops.size(); i++)
        crops[i]->saveToFile(fout);
    fout.close();
    cout << "Data saved to crops.txt" << endl;
}

void loadData(vector<Crop*> &crops) {
    ifstream fin("crops.txt");
    if (!fin)
        throw runtime_error("File not found. Save some data first");

    
    for (int i = 0; i < crops.size(); i++)
        delete crops[i];
    crops.clear();

    string type, name, season, extra;
    double area, yield;
    while (fin >> type >> name >> area >> season >> yield >> extra) {
        try {
            if (type == "Cereal")
                crops.push_back(new CerealCrop(name, area, season, yield, extra));
            else if (type == "Vegetable")
                crops.push_back(new VegetableCrop(name, area, season, yield, stoi(extra)));
        } catch (exception &e) {
            cout << "Skipped a bad record: " << e.what() << endl;
        }
    }
    fin.close();
    cout << crops.size() << " crops loaded from file" << endl;
}

int main() {
    vector<Crop*> crops;
    int choice;

    do {
        cout << "\n===== SMART FARM MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add crop" << endl;
        cout << "2. Display all crops" << endl;
        cout << "3. Show total yield" << endl;
        cout << "4. Compare two crops" << endl;
        cout << "5. Get farming advice" << endl;
        cout << "6. Save data to file" << endl;
        cout << "7. Load data from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice!" << endl;
            choice = -1;
            continue;
        }

        try {
            switch (choice) {
                case 1: addCrop(crops); break;
                case 2: displayAll(crops); break;
                case 3: showTotalYield(crops); break;
                case 4: compareCrops(crops); break;
                case 5:
                    for (int i = 0; i < crops.size(); i++)
                        crops[i]->giveAdvice();
                    break;
                case 6: saveData(crops); break;
                case 7: loadData(crops); break;
                case 0: cout << "Thank you!" << endl; break;
                default: cout << "Invalid choice!" << endl;
            }
        } catch (exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (choice != 0);

    
    for (int i = 0; i < crops.size(); i++)
        delete crops[i];

    return 0;
}
