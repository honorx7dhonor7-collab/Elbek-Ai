#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class ElbekAIApp {
private:
    int trials;
    bool isPaid;
    bool isAdmin;
    string file = "elbek_data.dat";
    string historyFile = "elbek_history.txt";
    string secretKey = "KlingSecure2026";

    char secureCipher(char c, int index) {
        return c ^ secretKey[index % secretKey.length()];
    }

public:
    ElbekAIApp(string role) {
        isPaid = false;
        if (role == "admin") {
            isAdmin = true;
            cout << "[ADMIN] Elbek AI to'liq cheksiz rejimda ishga tushdi!\n";
        } else {
            isAdmin = false;
            loadData();
        }
    }

    void loadData() {
        ifstream in(file, ios::binary);
        if (in.is_open()) {
            char c;
            in.get(c);
            in.close();
            trials = secureCipher(c, 0) - '0';
            if (trials < 0 || trials > 3) trials = 3;
        } else {
            trials = 3;
            saveData();
        }
    }

    void saveData() {
        ofstream out(file, ios::binary);
        if (out.is_open()) {
            char c = secureCipher(trials + '0', 0);
            out.put(c);
            out.close();
        }
    }

    void saveHistory(string prompt, string status) {
        ofstream out(historyFile, ios::ios_base::app);
        if (out.is_open()) {
            out << "Holat: " << status << " | Prompt: " << prompt << "\n";
            out.close();
        }
    }

    void checkPaymentStatus() {
        cout << "\n[TIZIM] To'lov holati tekshirilmoqda...\n";
        bool paymentReceived = true;

        if (paymentReceived) {
            isPaid = true;
            cout << "✅ To'lov muvaffaqiyatli tasdiqlandi! Elbek AI Premium faollashdi.\n\n";
        } else {
            cout << "⏳ To'lov hali amalga oshirilmadi.\n\n";
        }
    }

    void generateVideo(string prompt) {
        if (isAdmin || isPaid) {
            cout << "\n🎬 [ELBEK AI PREMIUM] Video yaratilmoqda...\nPrompt: " << prompt << "\nNatija: Muvaffaqiyatli tayyorlandi!\n\n";
            saveHistory(prompt, "PREMIUM/ADMIN");
        } else if (trials > 0) {
            trials--;
            saveData();
            cout << "\n🎁 [BEPUL REJIM] Video yaratilmoqda...\nPrompt: " << prompt << "\nQolgan bepul urinishlar: " << trials << " ta\n\n";
            saveHistory(prompt, "BEPUL (Qolgan: " + to_string(trials) + ")");
        } else {
            cout << "\n❌ Bepul urinishlar tugadi! Obuna bo'ling.\n\n";
            saveHistory(prompt, "RAD ETILDI (Urinish yo'q)");
        }
    }
};

int main() {
    string role;
    cout << "=== ELBEK AI ILOVASIGA XUSH KELIBSIZ ===\n";
    cout << "Rolni kiriting (admin yoki user): ";
    cin >> role;

    ElbekAIApp app(role);
    int choice;
    string prompt;

    while (true) {
        cout << "------------------------------------\n";
        cout << "1. Video yaratish (Prompt berish)\n";
        cout << "2. Obuna bo'lish / To'lovni tekshirish\n";
        cout << "3. Chiqish\n";
        cout << "Tanlovingiz: ";
        cin >> choice;

        if (choice == 1) {
            cout << "AI uchun prompt yozing: ";
            cin.ignore();
            getline(cin, prompt);
            app.generateVideo(prompt);
        } else if (choice == 2) {
            app.checkPaymentStatus();
        } else if (choice == 3) {
            cout << "Elbek AI yopildi. Xayr!\n";
            break;
        } else {
            cout << "Noto'g'ri tanlov!\n";
        }
    }
    return 0;
}
