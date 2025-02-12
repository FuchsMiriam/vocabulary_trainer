#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

string print_menu()
{
    cout << "Vokabeltrainer\n";
    cout << "Bitte wähle etwas aus:\n";
    cout << "(1) Neue Vokabel hinzufügen\n";
    cout << "(2) Vokabeltest starten\n";
    string option;
    cin >> option;
    return option;
}

// Liest Textdatei und speichert Text
vector<string> load_txt_file(string textFile)
{
    string str;
    ifstream in(textFile);
    vector<string> newVector;

    while (getline(in, str))
    {
        if (str.size() > 0)
        {
            newVector.push_back(str);
        }
    }
    return newVector;
}

// Deutsche und spanische Vokabeln speichern
void save_vector_to_txt_file(string fileName, vector<string> myVector)
{
    ofstream output_file(fileName);
    ostream_iterator<string> output_iterator(output_file, "\n");
    copy(myVector.begin(), myVector.end(), output_iterator);
}

void ask_word(vector<string> voc_german, vector<string> voc_spanish){
    cout << "Vokabeltest wird gestartet ...\n\n";
    int random = rand() % voc_german.size();
    string sel_elem = voc_german[random];
    string sel_translation = voc_spanish[random];
    cout << "Bitte übersetze folgendes Wort auf Spanisch: " + sel_elem + "\n";
    string userInput;
    cin >> userInput;
    if (userInput == sel_translation)
    {
        cout << "Korrekt.\n";
    }
    else
    {
        cout << "Das ist leider falsch.\n";
    }
}

int main()
{
    vector<string> voc_german = load_txt_file("voc_german.txt");
    vector<string> voc_spanish = load_txt_file("voc_spanish.txt");

    string option = print_menu();

    if (option == "1")
    {
        cout << "Welche Vokabel (Deutsch)?\n";
        string german_word;
        string spanish_word;
        cin >> german_word;
        cout << "Wie lautet die spanische Übersetzung?\n";
        cin >> spanish_word;

        // Deutsches Wort hinzufügen
        voc_german.push_back(german_word);
        voc_spanish.push_back(spanish_word);

        cout << "Vokabel wurde hinzugefügt.\n";

        // Gib Zahl aus, diese wird in einen String umgewandelt, um anzeigbar zu sein
        cout << "Hinzugefügte Vokabeln: " + to_string(voc_german.size());

        // Deutsche und spanische Vokabeln speichern
        save_vector_to_txt_file("./voc_german.txt", voc_german);
        save_vector_to_txt_file("./voc_spanish.txt", voc_spanish);
    }
    else
    {
        int i = 0;
        while (i < 100)
        {
            ask_word(voc_german, voc_spanish);
            i++;
        }
    }

    return 0;
}
