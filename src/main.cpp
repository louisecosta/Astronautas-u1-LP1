#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Parte 1: escreva aqui as classes Astronauta, Voo e Agencia.
class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

public:
//contrutor: todo astronauta começa vivo e disponivel
    Astronauta(string cpf, string nome, int idade){
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        this->vivo = true; //começa vivo
        this->disponivel = true; //começa disponivel
    }

    string getCpf() {
        return cpf;
    }
    string getNome() {
        return nome;
    }
    int getIdade() {
        return idade;
    }
    bool estaVivo() {
        return vivo;
    }
    bool estaDisponivel() {
        return disponivel;
    }
    void embarcar (){
        disponivel = false; //fica indisponivel quando embarca
    }
    void desembarcar (){
    if (vivo){
        disponivel = true; //voltando vivo, fica disponivel
        }
    }
    void morrer (){
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
    Voo(int codigo){
        this->codigo = codigo;
        this->estado = "planejando"; //começa planejando
    }
    int getCodigo(){
        return codigo;
    }
    string getEstado(){
        return estado;
    }
    int getQuantidadeAstronautas(){
        return cpfs.size();
    }

    string getCpf(int posicao){
        return cpfs[posicao];
    }

    bool temAstronauta(string cpf){
        for(int i = 0; i < (int)cpfs.size(); i++){
            if(cpfs[i] == cpf){
                return true;
            }
        }
        return false;
    }

    void adicionarAstronauta(string cpf){
        cpfs.push_back(cpf);
    }

    bool removerAstronauta(string cpf){
        for(int i = 0; i < (int)cpfs.size(); i++){
            if(cpfs[i] == cpf){
                cpfs.erase(cpfs.begin() + i);
                return true;
            }
        }
        return false;
    }
    void lancar() { 
        estado = "em curso";
    }
    void explodir() { 
        estado = "finalizado com explosao";
    }
    void finalizar() { 
        estado = "finalizado com sucesso";
    }
};

class Agencia {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;
    
    int buscarAstronauta(string cpf){
        for(int i = 0; i < (int)astronautas.size(); i++){
            if(astronautas[i].getCpf() == cpf){
                return i;
            }
        }
        return -1; 
    }
    int buscarVoo(int codigo){
        for(int i = 0; i < (int)voos.size(); i++){
            if(voos[i].getCodigo() == codigo){
                return i;
            }
        }
        return -1; 
    }
public:
    void cadastrarAstronauta(string cpf, string nome, int idade){
        if(buscarAstronauta(cpf) != -1){
            cout << "ERRO: astronauta com CPF" << cpf << " ja cadastrado" << endl;
            return;
        }
        Astronauta novoAstronauta(cpf, nome, idade);
        astronautas.push_back(novoAstronauta);
        cout << "OK: astronauta " << cpf << "cadastrado" << endl;
    }
    int cadastrarVoo(int codigo){
        if(buscarVoo(codigo) != -1){
            cout << "ERRO: voo " << codigo << " ja cadastrado" << endl;
            return -1;
        }
        Voo novoVoo(codigo);
        voos.push_back(novoVoo);
        cout << "OK: voo " << codigo << " cadastrado" << endl;
        return 0;
    }
    void listarVoos() {
    cout << "LISTA DE VOOS\n";
    vector<string> estados = {
        "planejado", 
        "em curso", 
        "finalizado com sucesso", 
        "finalizado com explosao"
    };

    for (string est : estados) {
        cout << "== " << est << " == "<< endl;
        bool algumNesseEstado = false;

        for (int i = 0; i < (int)voos.size(); i++) {
            if (voos[i].getEstado() == est) {
                algumNesseEstado = true;
                cout << "Voo " << voos[i].getCodigo() << ": ";

                if (voos[i].getQuantidadeAstronautas() == 0) {
                    cout << "sem astronautas "<< endl;
                } else {
                    for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                        string cpf = voos[i].getCpf(j);
                        int idxAst = buscarAstronauta(cpf);
                        cout << cpf << " " << astronautas[idxAst].getNome();
                        if (j < voos[i].getQuantidadeAstronautas() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << " " << endl;
                }
            }
        }
        if (!algumNesseEstado) {
            cout << "(nenhum) " << endl;
        }
    }
}
void listarMortos(){
    cout << "ASTRONAUTAS MORTOS" << endl;
    bool algumMorto = false;

    for (int i = 0; i<(int)astronautas.size(); i++){
        if (!astronautas[i].estaVivo()){
            algumMorto = true;
            cout << astronautas[i].getCpf() << " " << astronautas[i].getNome() << "voos: ";
           
            bool vooEmAlgum = false;
            for(int j = 0; j<(int)voos.size(); j++){
                if (voos[j].getEstado() != "planejado" && voos[j].temAstronauta(astronautas[i].getCpf())){
                    cout << " " << voos[j].getCodigo();
                    vooEmAlgum = true;
                   }
            }
            if (!vooEmAlgum){
                cout << " nenhum";
            }
            cout << endl;
        }
    }
    if (!algumMorto){
        cout << "(nenhum)" << endl;
    }

}
void adicionarAstronauta(string cpf, int codigo) {
    
    int idxAst = buscarAstronauta(cpf);
    if (idxAst == -1) {
        cout << "ERRO: astronauta " << cpf << " nao cadastrado"<< endl;
        return;
    }

    int idxVoo = buscarVoo(codigo);
    if (idxVoo == -1) {
        cout << "ERRO: voo " << codigo << " nao cadastrado"<< endl;
        return;
    }

    if (voos[idxVoo].getEstado() != "planejado") {
        cout << "ERRO: voo " << codigo << " nao esta planejado "<< endl;
        return;
    }

    if (!astronautas[idxAst].estaVivo()) {
        cout << "ERRO: astronauta " << cpf << " esta morto "<< endl;
        return;
    }

    if (voos[idxVoo].temAstronauta(cpf)) {
        cout << "ERRO: astronauta " << cpf << " ja esta no voo " << codigo << endl;
        return;
    }

    voos[idxVoo].adicionarAstronauta(cpf);
    cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << endl;
}

void removerAstronauta(string cpf, int codigo) {
    // 1. Astronauta cadastrado?
    int idxAst = buscarAstronauta(cpf);
    if (idxAst == -1) {
        cout << "ERRO: astronauta " << cpf << " nao cadastrado "<< endl;
        return;
    }

    int idxVoo = buscarVoo(codigo);
    if (idxVoo == -1) {
        cout << "ERRO: voo " << codigo << " nao cadastrado "<< endl;
        return;
    }

    if (voos[idxVoo].getEstado() != "planejado") {
        cout << "ERRO: voo " << codigo << " nao esta planejado "<< endl;
        return;
    }

    if (!voos[idxVoo].temAstronauta(cpf)) {
        cout << "ERRO: astronauta " << cpf << " nao esta no voo " << codigo << endl;
        return;
    }

    voos[idxVoo].removerAstronauta(cpf);
    cout << "OK: astronauta " << cpf << " removido do voo " << codigo << endl;
}

void lancarVoo(int codigo) {
    int idxVoo = buscarVoo(codigo);
    if (idxVoo == -1) {
        cout << "ERRO: voo " << codigo << " nao cadastrado " << endl;
        return;
    }

    if (voos[idxVoo].getEstado() != "planejado") {
        cout << "ERRO: voo " << codigo << " nao esta planejado " << endl;
        return;
    }

    if (voos[idxVoo].getQuantidadeAstronautas() == 0) {
        cout << "ERRO: voo " << codigo << " nao possui astronautas " << endl;
        return;
    }

    // Checa os astronautas antes de alterar qualquer estado
    for (int i = 0; i < voos[idxVoo].getQuantidadeAstronautas(); i++) {
        string cpf = voos[idxVoo].getCpf(i);
        int idxAst = buscarAstronauta(cpf);

        if (!astronautas[idxAst].estaVivo()) {
            cout << "ERRO: astronauta " << cpf << " esta morto "<< endl;
            return;
        }
        if (!astronautas[idxAst].estaDisponivel()) {
            cout << "ERRO: astronauta " << cpf << " esta indisponivel "<< endl;
            return;
        }
    }

    // Se passaram nas checagens, lança o voo e altera o estado dos astronautas
    voos[idxVoo].lancar();
    for (int i = 0; i < voos[idxVoo].getQuantidadeAstronautas(); i++) {
        string cpf = voos[idxVoo].getCpf(i);
        int idxAst = buscarAstronauta(cpf);
        astronautas[idxAst].embarcar();
    }

    cout << "OK: voo " << codigo << " lancado " << endl;
}

void finalizarVoo(int codigo) {
    int idxVoo = buscarVoo(codigo);
    if (idxVoo == -1) {
        cout << "ERRO: voo " << codigo << " nao cadastrado " << endl;
        return;
    }

    if (voos[idxVoo].getEstado() != "em curso") {
        cout << "ERRO: voo " << codigo << " nao esta em curso " << endl;
        return;
    }

    voos[idxVoo].finalizar();
    for (int i = 0; i < voos[idxVoo].getQuantidadeAstronautas(); i++) {
        string cpf = voos[idxVoo].getCpf(i);
        int idxAst = buscarAstronauta(cpf);
        astronautas[idxAst].desembarcar();
    }

    cout << "OK: voo " << codigo << " finalizado com sucesso " << endl;
}

void explodirVoo(int codigo) {
    int idxVoo = buscarVoo(codigo);
    if (idxVoo == -1) {
        cout << "ERRO: voo " << codigo << " nao cadastrado " << endl;
        return;
    }

    if (voos[idxVoo].getEstado() != "em curso") {
        cout << "ERRO: voo " << codigo << " nao esta em curso " << endl;
        return;
    }

    voos[idxVoo].explodir();
    for (int i = 0; i < voos[idxVoo].getQuantidadeAstronautas(); i++) {
        string cpf = voos[idxVoo].getCpf(i);
        int idxAst = buscarAstronauta(cpf);
        astronautas[idxAst].morrer();
    }

    cout << "OK: voo " << codigo << " explodiu " << endl;
}

};

int main() {
    
    Agencia agencia; //instância da agência que vai gerenciar tudo
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
