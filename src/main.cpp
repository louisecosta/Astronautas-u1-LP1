#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

public:
    Astronauta(string cpf, string nome, int idade) {
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        vivo = true;
        disponivel = true;
    }

    string getCpf() { return cpf; }
    string getNome() { return nome; }
    int getIdade() { return idade; }
    bool estaVivo() { return vivo; }
    bool estaDisponivel() { return disponivel; }

    void embarcar() { disponivel = false; }
    void desembarcar() { disponivel = true; }
    void morrer() {
        vivo = false;
        disponivel = false;
    }
};

class Voo {
private:
    int codigo;
    string estado;
    vector<string> cpfs;

public:
    Voo(int codigo) {
        this->codigo = codigo;
        estado = "planejado";
    }

    int getCodigo() { return codigo; }
    string getEstado() { return estado; }
    bool estaPlanejado() { return estado == "planejado"; }
    int getQuantidadeAstronautas() { return cpfs.size(); }
    string getCpf(int posicao) { return cpfs[posicao]; }

    bool temAstronauta(string cpf) {
        for (size_t i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) return true;
        }
        return false;
    }

    void adicionarAstronauta(string cpf) {
        cpfs.push_back(cpf);
    }

    bool removerAstronauta(string cpf) {
        for (size_t i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) {
                cpfs.erase(cpfs.begin() + i);
                return true;
            }
        }
        return false;
    }

    void lancar() { estado = "em curso"; }
    void explodir() { estado = "finalizado com explosao"; }
    void finalizar() { estado = "finalizado com sucesso"; }
};

class Agencia {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    int buscarAstronauta(string cpf) {
        for (size_t i = 0; i < astronautas.size(); i++) {
            if (astronautas[i].getCpf() == cpf) return i;
        }
        return -1;
    }

    int buscarVoo(int codigo) {
        for (size_t i = 0; i < voos.size(); i++) {
            if (voos[i].getCodigo() == codigo) return i;
        }
        return -1;
    }

public:
    void cadastrarAstronauta(string cpf, string nome, int idade) {
        if (buscarAstronauta(cpf) != -1) {
            cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado" << endl;
            return;
        }
        Astronauta astronauta(cpf, nome, idade);
        astronautas.push_back(astronauta);
        cout << "OK: astronauta " << cpf << " cadastrado" << endl;
    }

    void cadastrarVoo(int codigo) {
        if (buscarVoo(codigo) != -1) {
            cout << "ERRO: voo " << codigo << " ja cadastrado" << endl;
            return;
        }
        Voo voo(codigo);
        voos.push_back(voo);
        cout << "OK: voo " << codigo << " cadastrado" << endl;
    }

    void adicionarAstronauta(string cpf, int codigo) {
        int posA = buscarAstronauta(cpf);
        int posV = buscarVoo(codigo);

        if (posA == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        if (posV == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (!voos[posV].estaPlanejado()) {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (!astronautas[posA].estaVivo()) {
            cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
            return;
        }
        if (voos[posV].temAstronauta(cpf)) {
            cout << "ERRO: astronauta " << cpf << " ja esta no voo " << codigo << endl;
            return;
        }

        voos[posV].adicionarAstronauta(cpf);
        cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << endl;
    }

    void removerAstronauta(string cpf, int codigo) {
        int posA = buscarAstronauta(cpf);
        int posV = buscarVoo(codigo);

        if (posA == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        if (posV == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (!voos[posV].estaPlanejado()) {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (!voos[posV].temAstronauta(cpf)) {
            cout << "ERRO: astronauta " << cpf << " nao esta no voo " << codigo << endl;
            return;
        }

        voos[posV].removerAstronauta(cpf);
        cout << "OK: astronauta " << cpf << " removido do voo " << codigo << endl;
    }

    void lancarVoo(int codigo) {
        int posV = buscarVoo(codigo);

        if (posV == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (!voos[posV].estaPlanejado()) {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (voos[posV].getQuantidadeAstronautas() == 0) {
            cout << "ERRO: voo " << codigo << " nao possui astronautas" << endl;
            return;
        }

        for (int i = 0; i < voos[posV].getQuantidadeAstronautas(); i++) {
            string cpf = voos[posV].getCpf(i);
            int posA = buscarAstronauta(cpf);

            if (!astronautas[posA].estaVivo()) {
                cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
                return;
            }
            if (!astronautas[posA].estaDisponivel()) {
                cout << "ERRO: astronauta " << cpf << " esta indisponivel" << endl;
                return;
            }
        }

        for (int i = 0; i < voos[posV].getQuantidadeAstronautas(); i++) {
            string cpf = voos[posV].getCpf(i);
            int posA = buscarAstronauta(cpf);
            astronautas[posA].embarcar();
        }

        voos[posV].lancar();
        cout << "OK: voo " << codigo << " lancado" << endl;
    }

    void finalizarVoo(int codigo) {
        int posV = buscarVoo(codigo);

        if (posV == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[posV].getEstado() != "em curso") {
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }

        for (int i = 0; i < voos[posV].getQuantidadeAstronautas(); i++) {
            string cpf = voos[posV].getCpf(i);
            int posA = buscarAstronauta(cpf);
            astronautas[posA].desembarcar();
        }

        voos[posV].finalizar();
        cout << "OK: voo " << codigo << " finalizado com sucesso" << endl;
    }

    void explodirVoo(int codigo) {
        int posV = buscarVoo(codigo);

        if (posV == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[posV].getEstado() != "em curso") {
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }

        for (int i = 0; i < voos[posV].getQuantidadeAstronautas(); i++) {
            string cpf = voos[posV].getCpf(i);
            int posA = buscarAstronauta(cpf);
            astronautas[posA].morrer();
        }

        voos[posV].explodir();
        cout << "OK: voo " << codigo << " explodiu" << endl;
    }

    void listarMortos() {
        cout << "ASTRONAUTAS MORTOS" << endl;
        bool encontrou = false;

        for (size_t i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) {
                encontrou = true;
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome() << " - voos:";

                bool encontrouVoo = false;
                for (size_t j = 0; j < voos.size(); j++) {
                    if (voos[j].temAstronauta(astronautas[i].getCpf()) && !voos[j].estaPlanejado()) {
                        cout << " " << voos[j].getCodigo();
                        encontrouVoo = true;
                    }
                }

                if (!encontrouVoo) {
                    cout << " nenhum";
                }
                cout << endl;
            }
        }

        if (!encontrou) {
            cout << "(nenhum)" << endl;
        }
    }

    void listarVoos() {
        cout << "LISTA DE VOOS" << endl;
        string estados[4] = {
            "planejado",
            "em curso",
            "finalizado com sucesso",
            "finalizado com explosao"
        };

        for (int e = 0; e < 4; e++) {
            cout << "== " << estados[e] << " ==" << endl;
            bool encontrou = false;

            for (size_t i = 0; i < voos.size(); i++) {
                if (voos[i].getEstado() == estados[e]) {
                    encontrou = true;
                    cout << "Voo " << voos[i].getCodigo() << ": ";

                    if (voos[i].getQuantidadeAstronautas() == 0) {
                        cout << "sem astronautas";
                    } else {
                        for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                            string cpf = voos[i].getCpf(j);
                            int posA = buscarAstronauta(cpf);

                            if (j > 0) cout << ", ";
                            cout << cpf << " " << astronautas[posA].getNome();
                        }
                    }
                    cout << endl;
                }
            }

            if (!encontrou) cout << "(nenhum)" << endl;
        }
    }
};

int main() {
    Agencia agencia;
    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);
            agencia.cadastrarAstronauta(cpf, nome, idade);
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.cadastrarVoo(codigo);
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.adicionarAstronauta(cpf, codigo);
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.removerAstronauta(cpf, codigo);
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.lancarVoo(codigo);
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.explodirVoo(codigo);
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.finalizarVoo(codigo);
        } else if (comando == "LISTAR_VOOS") {
            agencia.listarVoos();
        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}