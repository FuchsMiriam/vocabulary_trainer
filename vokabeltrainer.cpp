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
    cout << "(3) Beenden\n";
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

void ask_word(vector<string> voc_german, vector<string> voc_spanish)
{
    static bool test_started = false;
    if (!test_started)
    {
        cout << "Vokabeltest wird gestartet ...\n\n";
        test_started = true;
    }
    int random = rand() % voc_german.size();
    string sel_elem = voc_german[random];
    string sel_translation = voc_spanish[random];
    cout << "Bitte übersetze folgendes Wort auf Spanisch: " + sel_elem + "\n";

    string userInput;
    int attempts = 2;
    bool correct = false;
    while (attempts > 0 && !correct)
    {
        cin >> userInput;
        if (userInput == sel_translation)
        {
            cout << "Korrekt.\n";
            correct = true;
        }
        else
        {
            attempts--;
            if (attempts > 0)
                cout << "Das ist leider falsch. Du hast noch " << attempts << " Versuche.\n";
            else
            {
                cout << "Leider falsch. Die richtige Antwort lautet: " << sel_translation << endl;

                char choice;
                cout << "Möchtest du weitermachen? (j/n)\n";
                cin >> choice;

                if (choice == 'n' || choice == 'N')
                {
                    cout << "Test beendet.\n";
                    return;
                }
                else if (choice == 'j' || choice == 'J')
                {
                    cout << "Weiter gehts!\n";
                    attempts = 2;
                }
                else
                {
                    cout << "Ungültige Eingabe. Die Frage wird erneut gestellt.\n";
                    attempts = 2;
                }
            }
        }
    }
}

int main()
{
    vector<string> voc_german = load_txt_file("voc_german.txt");
    vector<string> voc_spanish = load_txt_file("voc_spanish.txt");

    string option = print_menu();

    while (option != "3")
    {
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
        else if (option == "2")
        {
            char continueTest = 'j';
            while (continueTest == 'j' || continueTest == 'J')
            {
                ask_word(voc_german, voc_spanish);

                cout << "Möchtest du noch ein weiteres Wort testen? (j/n)\n";
                cin >> continueTest;
            }
        }
        else
        {
            cout << "Ungültige Auswahl, bitte versuche es noch einmal.\n";
        }
        option = print_menu();
    }

    cout << "Programm beendet.\n";
    return 0;
}