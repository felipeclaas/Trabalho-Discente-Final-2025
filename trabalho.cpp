#include <iostream>
#include <queue>
#include <string>
#include <iomanip>

using namespace std;

struct Paciente {
    string senha;
    char prior;
    int t;
};

int main(){
    queue<Paciente> filaV, filaA, filaD, filaB;
    char X;
    int total_atendidos = 0;
    int atV=0, atA=0, atD=0, atB=0;
    int pico = 0;
    int espera_maxima = 0;

    while (true) {
        cin >> X;
        switch (X) {
            case 'C': {
                string senha;
                char prior;
                int hh, mm;

                cin >> senha >> prior >> hh >> mm;
                int tempo = hh*60 + mm;

                Paciente paciente{senha, prior, tempo};
                switch (prior) {
                    case 'V': 
                        filaV.push(paciente); 
                        break;
                    case 'A':
                        filaA.push(paciente);
                        break;
                    case 'D':
                        filaD.push(paciente);
                        break;
                    case 'B':
                        filaB.push(paciente);
                        break;
                    default:
                        break;
                }
                
                int total = filaV.size() + filaA.size() + filaD.size() + filaB.size();
                if (total > pico) {
                    pico = total;
                }

                break;
            }
            case 'A': {
                int hh, mm;
                cin >> hh >> mm;
                int tempo_atual = hh*60 + mm;

                if (filaV.empty() && filaA.empty() && filaD.empty() && filaB.empty()) {
                    cout << hh << " " << mm << " Sem pacientes aguardando atendimento.\n";
                } else {
                    Paciente paciente;
                    if (!filaV.empty()) {
                        paciente = filaV.front(); filaV.pop(); atV++;
                    } else if (!filaA.empty()) {
                        paciente = filaA.front(); filaA.pop(); atA++;
                    } else if (!filaD.empty()) {
                        paciente = filaD.front(); filaD.pop(); atD++;
                    } else {
                        paciente = filaB.front(); filaB.pop(); atB++;
                    }

                    total_atendidos++;

                    int espera = tempo_atual - paciente.t;
                    if (espera > espera_maxima){
                        espera_maxima = espera;
                    }
                }

                break;
            }
            case 'D': {
                cout << "V:" << filaV.size() << " A:" << filaA.size() << " D:" << filaD.size() << " B:" << filaB.size() << " | Atendidos:" << total_atendidos << "\n";
                break;
            }
            case 'Q': {
                cout << "--- RELATORIO FINAL ---\n";
                cout << "Total atendidos: " << total_atendidos << "\n";
                cout << "Por prioridade: V=" << atV << " A=" << atA << " D=" << atD << " B=" << atB << "\n";
                cout << "Pico de lotacao: " << pico << "\n";
                cout << "Espera maxima: " << espera_maxima << " min\n";
                return 0;
            }
            default:
                break;
        }
    }
    return 0;
}