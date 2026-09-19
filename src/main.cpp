#include <iostream>
#include <fstream>
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
    Astronauta(const string& cpf, const string& nome, int idade) {
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        vivo = true;
        disponivel = true;
    }

    const string& getCpf() const { return cpf; }
    const string& getNome() const { return nome; }
    int getIdade() const { return idade; }
    bool estaVivo() const { return vivo; }
    bool estaDisponivel() const { return disponivel; }

    void embarcar() { disponivel = false; }
    void desembarcar() { disponivel = true; }
    void morrer() {
        vivo = false;
        disponivel = false;
    }

    void setVivo(bool vivo) { this->vivo = vivo; }
    void setDisponivel(bool disponivel) { this->disponivel = disponivel; }
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

    int getCodigo() const { return codigo; }
    const string& getEstado() const { return estado; }
    bool estaPlanejado() const { return estado == "planejado"; }
    int getQuantidadeAstronautas() const { return cpfs.size(); }
    const string& getCpf(int posicao) const { return cpfs[posicao]; }

    bool temAstronauta(const string& cpf) const {
        for (size_t i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) return true;
        }
        return false;
    }

    void adicionarAstronauta(const string& cpf) {
        cpfs.push_back(cpf);
    }

    bool removerAstronauta(const string& cpf) {
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

    void setEstado(const string& estado) { this->estado = estado; }
};

class Agencia {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    int buscarAstronauta(const string& cpf) const {
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
    void cadastrarAstronauta(const string& cpf, const string& nome, int idade) {
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

    void adicionarAstronauta(const string& cpf, int codigo) {
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

    void removerAstronauta(const string& cpf, int codigo) {
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

    void listarMortos() const {
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

    void listarVoos() const {
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

    void listarAstronautas() const {
        cout << "LISTA DE ASTRONAUTAS" << endl;

        cout << "== disponiveis ==" << endl;
        bool encontrou = false;
        for (size_t i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) continue;

            bool emVoo = false;
            for (size_t j = 0; j < voos.size(); j++) {
                if (voos[j].getEstado() == "em curso" && voos[j].temAstronauta(astronautas[i].getCpf())) {
                    emVoo = true;
                    break;
                }
            }

            if (!emVoo) {
                encontrou = true;
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                     << " (" << astronautas[i].getIdade() << " anos)" << endl;
            }
        }
        if (!encontrou) cout << "(nenhum)" << endl;

        cout << "== em voo ==" << endl;
        encontrou = false;
        for (size_t i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) continue;

            for (size_t j = 0; j < voos.size(); j++) {
                if (voos[j].getEstado() == "em curso" && voos[j].temAstronauta(astronautas[i].getCpf())) {
                    encontrou = true;
                    cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                         << " (" << astronautas[i].getIdade() << " anos) - voo "
                         << voos[j].getCodigo() << endl;
                    break;
                }
            }
        }
        if (!encontrou) cout << "(nenhum)" << endl;

        cout << "== mortos ==" << endl;
        encontrou = false;
        for (size_t i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) {
                encontrou = true;
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                     << " (" << astronautas[i].getIdade() << " anos)" << endl;
            }
        }
        if (!encontrou) cout << "(nenhum)" << endl;
    }

    void historico(const string& cpf) const {
        int posA = buscarAstronauta(cpf);
        if (posA == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }

        cout << "HISTORICO DE " << astronautas[posA].getCpf() << " " << astronautas[posA].getNome() << endl;

        bool encontrou = false;
        for (size_t i = 0; i < voos.size(); i++) {
            if (voos[i].temAstronauta(cpf) && !voos[i].estaPlanejado()) {
                encontrou = true;
                cout << "voo " << voos[i].getCodigo() << ": " << voos[i].getEstado() << endl;
            }
        }

        if (!encontrou) cout << "(nenhum voo)" << endl;
    }

    void salvar(const string& arquivo) const {
        ofstream saida(arquivo.c_str());
        if (!saida) {
            cout << "ERRO: nao foi possivel salvar em " << arquivo << endl;
            return;
        }

        saida << "ASTRONAUTAS " << astronautas.size() << endl;
        for (size_t i = 0; i < astronautas.size(); i++) {
            saida << astronautas[i].getCpf() << " "
                  << astronautas[i].getIdade() << " "
                  << (astronautas[i].estaVivo() ? 1 : 0) << " "
                  << (astronautas[i].estaDisponivel() ? 1 : 0) << " "
                  << astronautas[i].getNome() << endl;
        }

        saida << "VOOS " << voos.size() << endl;
        for (size_t i = 0; i < voos.size(); i++) {
            saida << voos[i].getCodigo() << " "
                  << voos[i].getQuantidadeAstronautas();
            for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                saida << " " << voos[i].getCpf(j);
            }
            saida << " " << voos[i].getEstado() << endl;
        }

        cout << "OK: dados salvos em " << arquivo << endl;
    }

    void carregar(const string& arquivo) {
        ifstream entrada(arquivo.c_str());
        if (!entrada) {
            cout << "ERRO: nao foi possivel carregar de " << arquivo << endl;
            return;
        }

        vector<Astronauta> novosAstronautas;
        vector<Voo> novosVoos;

        string rotulo;
        int qtd;

        entrada >> ws >> rotulo >> qtd;
        for (int i = 0; i < qtd; i++) {
            string cpf, nome;
            int idade, vivoInt, disponivelInt;
            entrada >> cpf >> idade >> vivoInt >> disponivelInt;
            getline(entrada >> ws, nome);

            Astronauta astronauta(cpf, nome, idade);
            astronauta.setVivo(vivoInt == 1);
            astronauta.setDisponivel(disponivelInt == 1);
            novosAstronautas.push_back(astronauta);
        }

        entrada >> ws >> rotulo >> qtd;
        for (int i = 0; i < qtd; i++) {
            int codigo, quantidade;
            entrada >> codigo >> quantidade;

            Voo voo(codigo);
            for (int j = 0; j < quantidade; j++) {
                string cpf;
                entrada >> cpf;
                voo.adicionarAstronauta(cpf);
            }

            string estado;
            getline(entrada >> ws, estado);
            voo.setEstado(estado);
            novosVoos.push_back(voo);
        }

        astronautas = novosAstronautas;
        voos = novosVoos;
        cout << "OK: dados carregados de " << arquivo << endl;
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
        } else if (comando == "LISTAR_ASTRONAUTAS") {
            agencia.listarAstronautas();
        } else if (comando == "HISTORICO") {
            string cpf;
            cin >> cpf;
            agencia.historico(cpf);
        } else if (comando == "SALVAR") {
            string arquivo;
            cin >> arquivo;
            agencia.salvar(arquivo);
        } else if (comando == "CARREGAR") {
            string arquivo;
            cin >> arquivo;
            agencia.carregar(arquivo);
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}