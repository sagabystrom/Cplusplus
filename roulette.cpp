//Inkluderar behövda bibliotek för programmet
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <thread> 
#include <chrono> 

using namespace std;

int main() { 
    //Initierar den slumpmässiga generatorn med nuvarande tid för att få olika resultat varje gång programmet körs
    srand(time(0)); 
    //Initierar variabler som behövs för att programmet ska fungera
    int saldo = 1000;  
    char spela_igen = 'j';  
    int satsning, nummer = 0; 
    char gissning, farg; 
    int snurr; 
    int omgang_vinst; // Variabel för att hålla koll på vinst eller förlust i varje omgång
    int total_vinst = 0; // Variabel för att hålla koll på den totala vinsten

    //Väkomstmeddelande med information om saldo
    std::cout << "Välkommen till detta Roulette spel!" << endl;
    std::cout << "Du får 1000 kr som läggs till i ditt saldo, spela lugnt!" << endl;
    std::cout << "" << endl; 

    //Påbörjar spelet så länge det finns pengar och om användaren skulle vilja spela igen  
    while (saldo > 0 && spela_igen == 'j') { 
        std::cout << "Ditt nuvarande saldo är: " << saldo << " kr" << endl; 
        omgang_vinst = 0; // Återställer omgångsvinst varje runda

        //Här får användaren välja hur mycket pengar den vill satsa och sparar det i variabeln satsning, vid felaktig summa får användaren frågan igen
        while (true) { 
            std::cout << "Välj hur mycket pengar du vill satsa (100, 300, 500): "; 
            cin >> satsning; 
            if ((satsning == 100 || satsning == 300 || satsning == 500) && satsning <= saldo) { 
                break; 
            } else { 
                std::cout << "Du kan inte satsa den summan. Försök igen." << endl; 
            } 
        } 

        //Frågra vad användaren vill satsa på, en färg eller ett nummer, koden körs till ett giltigt alternativ anges
        while (true) { 
            std::cout << "Vill du satsa på ett nummer eller en färg? (n/f): "; 
            cin >> gissning; 
            if (gissning == 'f' || gissning == 'F' || gissning == 'n' || gissning == 'N') { 
                break; 
            } else { 
                std::cout << "Ogiltigt val. Försök igen." << endl; 
            } 
        } 

        //Om användaren vill gissa på färg så initieras detta block där hen får välja svart eller röd 
        if (gissning == 'f' || gissning == 'F') { 
            while (true) { 
                std::cout << "Välj färg (röd (r) eller svart (s)): "; 
                cin >> farg; 
                if (farg == 'r' || farg == 'R' || farg == 's' || farg == 'S') { 
                    break; 
                } else { 
                    std::cout << "Ogiltig färg. Försök igen." << endl; 
                } 
            } 
        } 
        //Om användaren vill gissa på ett nummer så initieras detta block istället där hen kan välja en siffra mellan 1 och 36 
        else if (gissning == 'n' || gissning == 'N') { 
            while (true) { 
                std::cout << "Välj en siffra mellan 1 och 36: "; 
                cin >> nummer; 
                if (nummer >= 1 && nummer <= 36) { 
                    break; 
                } else { 
                    std::cout << "Ogiltigt nummer. Försök igen." << endl; 
                } 
            } 
        } 

        //Blocket skriver ut text och pausar resten av koden för att göra programmet mer verkligt
        std::cout << "" << endl;
        std::cout << "Lycka till!" << endl; 
        std::cout << "Hjulet snurrar..." << endl; 

        this_thread::sleep_for(chrono::seconds(2)); //Gör att programmet tar en paus på 2 sekunder innan den skriver ut nästa rad 

        //Här blir snurr variabeln tilldelad ett random nummer mellan 1 och 36, sedan kontrolleras det om talet är jämt eller udda
        snurr = rand() % 36 + 1; 
        bool snurra_rod = (snurr % 2 != 0); 

        //Här skrivs resultatet ut, och använder boolean värdet på snurra_rod för att skriva ut antingen svart eller röd
        std::cout << "" << endl;
        std::cout << "Hjulet landade på " << snurr << " (" << (snurra_rod ? "röd" : "svart") << ")" << endl; 

        //Här sker beräkningen med saldot och den valda satsningen på nummer vilket beror på om användaren vann eller inte 
        if (gissning == 'n' || gissning == 'N') { 
            if (snurr == nummer) { 
                omgang_vinst = satsning * 9; //Rätt nummer ger 10* tillbaka (Satsningen inkluderad) 
                saldo += omgang_vinst; 
                std::cout << "Du gissade rätt nummer! Grattis du vann " << omgang_vinst << " kr" << endl; 
            } else { 
                omgang_vinst = -satsning; 
                saldo += omgang_vinst; 
                std::cout << "Tyvärr fel. Du förlorade " << satsning << " kr" << endl; 
            } 
        } 
        //Här sker beräkningen med saldot och den valda satsningen på färg vilket beror på om användaren vann eller inte 
        else { 
            bool rod_farg = (farg == 'r' || farg == 'R'); 
            if (rod_farg == snurra_rod) { 
                omgang_vinst = satsning; //Rätt färg ger 2* tillbaka (Satsningen inkluderad) 
                saldo += omgang_vinst; 
                std::cout << "Du gissade rätt färg! Grattis du vann " << omgang_vinst << " kr" << endl; 
            } else { 
                omgang_vinst = -satsning; 
                saldo += omgang_vinst; 
                std::cout << "Tyvärr fel. Du förlorade " << satsning << " kr" << endl; 
            } 
        } 

        total_vinst += omgang_vinst; // Uppdaterar den totala vinsten

        this_thread::sleep_for(chrono::seconds(2));
        //Skriver ut nuvarande saldo, vinst och förlust för varje omgång samt totala vinst
        std::cout << "" << endl;
        std::cout << "Din vinst eller förlust denna omgång är: " << omgang_vinst << " kr" << endl;
        std::cout << "Din totala vinst eller förlust är: " << total_vinst << " kr" << endl;
        std::cout << "Ditt nuvarande saldo är: " << saldo << " kr" << endl; 

        //Frågar om användaren vill spela igen ifall det finns pengar på kontot 
        if (saldo > 0) { 
            std::cout << "Vill du spela igen? (j/n): "; 
            cin >> spela_igen; 
        } 
    } 

    //Om det inte finns pengar på kontot är spelet över, och om spelaren avslutar spelet är det också över 
    if (saldo <= 0) { 
        std::cout << "Du har inga pengar kvar på kontot, tyvärr är spelet över!" << endl; 
    } else { 
        std::cout << "Tack för att du spelade, ha det bra!" << endl; 
    } 

    return 0; 
}
