#include <iostream>
#include <string>
using namespace std;

class Event {
protected:
    string name;
    int attendees;
public:
    Event(const string& n = "Default Event", int a = 0) : name(n), attendees(a) {}
    virtual void showDetails() const {
        cout << "Event: " << name << ", Attendees: " << attendees << endl;
    }
    virtual ~Event() {}
};

class Catering {
private:
    string menu;
    int costPerPerson;
public:
    Catering(const string& m, int cost) : menu(m), costPerPerson(cost) {} 
    int calculateCost(int attendees) const {
        return costPerPerson * attendees;
    }
    void showDetails() const {
        cout << "Catering Menu: " << menu << ", Cost per Person: " << costPerPerson << endl;
    }
};

class Decoration {
private:
    string theme;
    int budget;
public:
    Decoration(const string& t, int b) : theme(t), budget(b) {}
    void showDetails() const {
        cout << "Decoration Theme: " << theme << ", Budget: " << budget << endl;
    }
};

class TechnicalSupport {
private:
    bool soundSystem;
    bool lighting;
    bool projector;
public:
    TechnicalSupport(bool sound, bool light, bool proj) 
        : soundSystem(sound), lighting(light), projector(proj) {}
    void showDetails() const {
        cout << "Technical Support - Sound System: " << (soundSystem ? "Yes" : "No")
             << ", Lighting: " << (lighting ? "Yes" : "No")
             << ", Projector: " << (projector ? "Yes" : "No") << endl;
    }
};

class SocialEvent : public Event {
private:
    Catering* catering;
    Decoration* decoration;
public:
    SocialEvent(const string& n, int a, Catering* c, Decoration* d) 
        : Event(n, a), catering(c), decoration(d) {}
    void showDetails() const override {
        cout << "\nSocial Event: " << name << ", Attendees: " << attendees << endl;
        if (catering) catering->showDetails();
        if (decoration) decoration->showDetails();
    }
    ~SocialEvent() {
        delete catering;
        delete decoration;
    }
};

class CorporateEvent : public Event {
private:
    string topic;
    Catering* catering;
    TechnicalSupport* technical;
public:
    CorporateEvent(const string& n, int a, const string& t, Catering* c, TechnicalSupport* tech) 
        : Event(n, a), topic(t), catering(c), technical(tech) {}

    void showDetails() const override {
        cout << "\nCorporate Event: " << name << ", Attendees: " << attendees 
             << ", Topic: " << topic << endl;
        if (catering) catering->showDetails();
        if (technical) technical->showDetails();
    }
    ~CorporateEvent() {
        delete catering;
        delete technical;
    }
};

bool getYesOrNoInput(const string& prompt) {
    char choice;
    do {
        cout << prompt << " (y/n): ";
        cin >> choice;
        choice = tolower(choice);
    } while (choice != 'y' && choice != 'n');
    return choice == 'y';
}

int main() {
    string eventName, topic, menu, theme;
    int attendees, costPerPerson, decorationBudget;
    int eventType;

    cout << "Select Event Type:\n1. Social Event\n2. Corporate Event\nEnter choice (1 or 2): ";
    cin >> eventType;

    cout << "Enter Event Name: ";
    cin.ignore();
    getline(cin, eventName);
    cout << "Enter Number of Attendees: ";
    cin >> attendees;
    Event* event = NULL;

    switch (eventType) {
        case 1: {
            cout << "\n--- Social Event Details ---\n";
            cout << "Enter Catering Menu: ";
            cin >> menu;
            cout << "Enter Cost per Person for Catering: ";
            cin >> costPerPerson;
            cout << "Enter Decoration Theme: ";
            cin >> theme;
            cout << "Enter Decoration Budget: ";
            cin >> decorationBudget;

            Catering* catering = new Catering(menu, costPerPerson);
            Decoration* decoration = new Decoration(theme, decorationBudget);
            event = new SocialEvent(eventName, attendees, catering, decoration);
            break;
        }

        case 2: {
            cout << "\n--- Corporate Event Details ---\n";
            cout << "Enter Conference Topic: ";
            cin >> topic;
            cout << "Enter Catering Menu: ";
            cin >> menu;
            cout << "Enter Cost per Person for Catering: ";
            cin >> costPerPerson;

            cout << "\n--- Technical Support Details ---\n";
            bool soundSystem = getYesOrNoInput("Sound System required?");
            bool lighting = getYesOrNoInput("Lighting required?");
            bool projector = getYesOrNoInput("Projector required?");

            Catering* catering = new Catering(menu, costPerPerson);
            TechnicalSupport* technical = new TechnicalSupport(soundSystem, lighting, projector);
            event = new CorporateEvent(eventName, attendees, topic, catering, technical);
            break;
        }
        default:
            cout << "Invalid event type selected." << endl;
            return 1;
    }

    if (event) {
        event->showDetails();
        delete event;
    }
    return 0;
}

