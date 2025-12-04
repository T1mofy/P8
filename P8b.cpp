#include <iostream>
#include <windows.h>

using namespace std;

// Symbolische Bezeichnungen der Eingaben
enum eingabe {
	// ****************************************************************************
	// TODO: Eingabemenge definieren
	// ****************************************************************************
	TEG,
	TS1,
	TS2,
	TS3
};

// Symbolische Bezeichnungen der Ausgaben
enum ausgabe {
	// ****************************************************************************
	// TODO: Ausgabemenge definieren
	// ****************************************************************************
	b_up = 2,
	b_down = 1,
	b_stop = 0
};

// Symbolische Bezeichnungen der Zustände
enum zustand {
	// ****************************************************************************
	// TODO: Zustandsmenge definieren
	// ****************************************************************************
	EG,
	S1,
	S2,
	S3,
	Fahrt_nach_oben,
	Fahrt_nach_unten,
};

// ********************************************************************************
// TODO: Aktuellen Zustand initialisieren
zustand aktueller_zustand = EG;
// ********************************************************************************

/*
* Die Funktion simuliert die Fahrten des Aufzugs, indem sie den Zustandsübergang
* verzögert. Während der Verzögerung bewegt der Motor den Aufzug nach oben bzw.
* unten. Die Dauer einer Fahrt wird über die Variable fahrtdauer definiert.
* Das Öffnen und das Schließen der Tür wird vernachlässigt.
*/
void fahre(int stock, int befehl) {
	const int fahrtdauer = 2000; // Einheit ms -> 2 Sekunden
	// Fahrt nach oben
	if (stock < befehl) {
		for (int i = stock; i < befehl; i++) {
			// Ausgabe des aktuellen Stockwerks (beim Vorbeifahren)
			cout << "\t... Stock " << i << endl;
			Sleep(fahrtdauer);
		}
	}

	// Fahrt nach unten
	else {
		for (int i = stock; i > befehl; i--) {
			// Ausgabe des aktuellen Stockwerks (beim Vorbeifahren)
			cout << "\t... Stock " << i << endl;
			Sleep(fahrtdauer);
		}
	}
}

// ********************************************************************************
// TODO: Hier bei Bedarf weitere Funktionen implementieren
// ********************************************************************************
int befehl_einlesen() {
	int b;
	cout << "Geben Sie das gewuenschte Stockwerk ein: ";
	cin >> b;
	return b;
}
void umwandlung_dez_bin(int bit[], int dez_zahl) {
	unsigned char y = dez_zahl;

	for (int i = 0; i < 2; i++) {
		int bit_index = 1 - i;
		int maske = 1 << bit_index;
		int b = (y & maske) >> bit_index;
		bit[i] = b;
	}
}

/*
* Funktion zur Beschreibung des Zustandsautomaten
* Der Automat läuft in einer Endlosschleife
*/
void zustandsautomat() {
	zustand stock = aktueller_zustand; // Zwischenspeichern des aktuellen Zustands
	
	// ****************************************************************************
	// TODO: Hier bei Bedarf weitere Hilfsvariablen definieren
	// ****************************************************************************
	int befehl = 0;
	int Motor[2] = { 0,0 };
	int Motor_dez = 0;
	// Automat läuft in einer Endlosschleife.
	while (true) {
		// Beschreibung des Zustandsautomaten
		stock = aktueller_zustand;
		switch (aktueller_zustand) {
			// ************************************************************************
			// TODO: Jeden Zustand in einem eigenen case implementieren
			/* Zustand  */
		case EG:case S1:case S2:case S3: {
			Motor_dez = ausgabe::b_stop;
			umwandlung_dez_bin(Motor, Motor_dez);
			cout << "\n----------------------------------------------------" << endl;
			cout << "Aktueller Zustand: " << "\tStock " << stock << endl;
			cout << "Aktuelle Ausgabe: " << "\tMotor " << Motor[0] << Motor[1] << endl;
			cout << "----------------------------------------------------" << endl;

			befehl = befehl_einlesen();

			if (befehl == stock) {
				cout << "Aufzug ist bereits im Stock " << stock << endl;
				break;
			}
			if (befehl > stock) {
				aktueller_zustand = Fahrt_nach_oben;
			}
			else {
				aktueller_zustand = Fahrt_nach_unten;
			}
			break;
		}

			/* Zustand  */
		case Fahrt_nach_oben: {
			Motor_dez = ausgabe::b_up;
			umwandlung_dez_bin(Motor, Motor_dez);
			cout << "\n----------------------------------------------------" << endl;
			cout << "Aktueller Zustand: " << "\tFahrt nach oben" << endl;
			cout << "Aktuelle Ausgabe: " << "\tMotor " << Motor[0] << Motor[1] << endl;
			cout << "----------------------------------------------------" << endl;
			fahre(stock, befehl);
			aktueller_zustand = zustand(befehl);
			stock = aktueller_zustand;
			break;
		}

			/* Zustand  */
		case Fahrt_nach_unten: {
			Motor_dez = ausgabe::b_down;
			umwandlung_dez_bin(Motor, Motor_dez);
			cout << "\n----------------------------------------------------" << endl;
			cout << "Aktueller Zustand: " << "\tFahrt nach unten" << endl;
			cout << "Aktuelle Ausgabe: " << "\tMotor " << Motor[0] << Motor[1] << endl;
			cout << "----------------------------------------------------" << endl;
			fahre(stock, befehl);
			aktueller_zustand = zustand(befehl);
			stock = aktueller_zustand;
		
			break;
		}
			// ************************************************************************
		}
	}
}

int main() {
	zustandsautomat();
	return 0;
}
