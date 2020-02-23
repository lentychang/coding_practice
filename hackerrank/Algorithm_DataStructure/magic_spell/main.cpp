#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {

  /* Enter your code here */
    if(Fireball* counterspell = dynamic_cast<Fireball*>(spell)) {
        counterspell->revealFirepower();
    }
    else if(Frostbite* counterspell = dynamic_cast<Frostbite*>(spell)) {        
        counterspell->revealFrostpower();
    }
    else if(Waterbolt* counterspell = dynamic_cast<Waterbolt*>(spell)) {
        counterspell->revealWaterpower();
    }
    else if(Thunderstorm* counterspell = dynamic_cast<Thunderstorm*>(spell)) {
        counterspell->revealThunderpower();
    } 
    else {        
        string spellName = spell->revealScrollName() ;
        string spellJournal = SpellJournal::journal;

        // LCS Algorithm
        string &a = spellName, &b = spellJournal;
        vector<vector<int> > dp(a.size() + 1, vector<int>(b.size() + 1));
        string common;
        for(int i = 1; i <= a.size(); i++) {
            for(int j = 1; j <= b.size(); j++) {
                if(a[i - 1] == b[j - 1]){
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        cout << dp[a.size()][b.size()] << endl;

        for(int i = 1; i <= a.size(); i++) {
            for(int j = 1; j <= b.size(); j++) {
                cout << dp[i][j] << " ";
            }
            cout << ";" << endl;
        }
        int i = a.size();
        int j = b.size();
        int node = 0;

        // get characters
        while(dp[i][j] !=0){
            node = dp[i][j];
            if(dp[i][j-1] == dp[i][j]){
                j--;
            }
            else if(dp[i-1][j] == dp[i][j]){
                i--;
            }
            else{
                if(dp[i-1][j] == dp[i][j-1] && dp[i][j]-dp[i-1][j] == 1){
                    common+=a[i-1];
                    i--;
                    j--;
                }
                else{
                    cout << "Error";
                }
            }
        }
        for(auto iter=common.rbegin(); iter!=common.rend();iter++){
            cout << *iter;
        }
        

    }    
}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}