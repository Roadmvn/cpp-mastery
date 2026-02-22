// ============================================================
// Challenge Offensif : Gestion de handles avec smart pointers
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
// ============================================================
// Contexte : Tu developpes un gestionnaire de handles bas-niveau
// (descripteurs de fichiers, sockets, handles OS). Ces ressources
// doivent etre liberees meme en cas d'exception. C'est le pattern
// RAII applique aux handles systeme avec smart pointers.
//
// Scenarios :
//   - unique_ptr<Handle> : connexion exclusive (1 owner)
//   - shared_ptr<Handle> : handle partage entre plusieurs workers
//   - weak_ptr<Handle>   : monitoring sans bloquer la liberation
//   - Custom deleter     : appel d'une fonction close() specifique
// ============================================================

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
using namespace std;

// ============================================================
// Simulation d'un handle systeme (file descriptor, socket, etc.)
// ============================================================

struct HandleStats {
    int total_opened  = 0;
    int total_closed  = 0;
    int currently_open = 0;

    void opened() { total_opened++;   currently_open++; }
    void closed() { total_closed++;   currently_open--; }
    void print() const {
        cout << "  Handles ouverts au total  : " << total_opened  << endl;
        cout << "  Handles fermes au total   : " << total_closed  << endl;
        cout << "  Handles encore ouverts    : " << currently_open << endl;
        if (currently_open == 0)
            cout << "  -> Aucune fuite de ressource. Propre." << endl;
        else
            cout << "  -> FUITE : " << currently_open << " handle(s) non libere(s) !" << endl;
    }
};

static HandleStats g_stats;

class Handle {
    int    fd;
    string name;
    bool   closed;

public:
    Handle(int fd_, const string& name_)
        : fd(fd_), name(name_), closed(false)
    {
        g_stats.opened();
        cout << "  [OPEN]  Handle fd=" << fd << " name=" << name << endl;
    }

    ~Handle() {
        if (!closed) close();
    }

    void close() {
        if (closed) return;
        closed = true;
        g_stats.closed();
        cout << "  [CLOSE] Handle fd=" << fd << " name=" << name << endl;
    }

    void write(const string& data) const {
        if (closed) throw runtime_error("Write sur handle ferme : " + name);
        cout << "  [WRITE] fd=" << fd << " -> \"" << data << "\"" << endl;
    }

    void read(const string& data) const {
        if (closed) throw runtime_error("Read sur handle ferme : " + name);
        cout << "  [READ]  fd=" << fd << " <- \"" << data << "\"" << endl;
    }

    int  getFd()   const { return fd;   }
    bool isClosed()const { return closed; }
    const string& getName() const { return name; }
};

// ============================================================
// 1. unique_ptr<Handle> : connexion exclusive
// ============================================================

void demo_unique() {
    cout << "\n--- Demo 1 : unique_ptr (connexion exclusive) ---" << endl;

    // Simule une connexion SSH exclusive
    auto ssh = make_unique<Handle>(3, "ssh://target:22");
    ssh->write("ls -la /etc/shadow");
    ssh->read("Permission denied");

    // Transfert vers un autre owner (ex: worker thread)
    auto worker = std::move(ssh);
    cout << "  ssh est null apres move : " << (ssh == nullptr ? "OUI" : "NON") << endl;
    worker->write("sudo cat /etc/passwd");
    worker->read("root:x:0:0:...");

    // worker sort de scope -> Handle ferme automatiquement
    cout << "  [worker sort de scope]" << endl;
}

// ============================================================
// 2. shared_ptr<Handle> : handle partage entre workers
// ============================================================

class Worker {
    string       id;
    shared_ptr<Handle> handle;
public:
    Worker(const string& id_, shared_ptr<Handle> h)
        : id(id_), handle(std::move(h)) {}

    void work(const string& cmd) {
        cout << "  Worker " << id << " utilise handle fd="
             << handle->getFd() << " : " << cmd << endl;
        handle->write(cmd);
    }

    long use_count() const { return handle.use_count(); }
};

void demo_shared() {
    cout << "\n--- Demo 2 : shared_ptr (handle partage entre workers) ---" << endl;

    auto socket = make_shared<Handle>(7, "tcp://192.168.1.100:4444");
    cout << "  use_count initial : " << socket.use_count() << endl;

    {
        Worker w1("Alpha", socket);
        Worker w2("Bravo", socket);
        cout << "  use_count avec 2 workers : " << socket.use_count() << endl;

        w1.work("RECON --stealth");
        w2.work("EXFIL --compress");

        cout << "  [workers sortent de scope]" << endl;
    }

    cout << "  use_count apres workers : " << socket.use_count() << endl;
    cout << "  [socket sort de scope]" << endl;
}

// ============================================================
// 3. weak_ptr<Handle> : monitoring sans bloquer la liberation
// ============================================================

class HandleMonitor {
    string        monitor_id;
    weak_ptr<Handle> target;

public:
    HandleMonitor(const string& id, weak_ptr<Handle> t)
        : monitor_id(id), target(std::move(t)) {}

    void check() {
        if (auto h = target.lock()) {
            cout << "  Monitor[" << monitor_id << "] : Handle fd="
                 << h->getFd() << " actif (use_count=" << h.use_count() << ")" << endl;
        } else {
            cout << "  Monitor[" << monitor_id << "] : Handle libere, plus accessible." << endl;
        }
    }
};

void demo_weak() {
    cout << "\n--- Demo 3 : weak_ptr (monitoring non-proprietaire) ---" << endl;

    HandleMonitor* mon = nullptr;

    {
        auto conn = make_shared<Handle>(9, "udp://10.0.0.1:53");
        mon = new HandleMonitor("IDS", conn);

        mon->check(); // Handle actif
        conn->write("DNS query: evil.domain");

        cout << "  [conn sort de scope -> liberation]" << endl;
    }

    mon->check(); // Handle libere
    delete mon;
}

// ============================================================
// 4. Custom deleter : nettoyage specifique a la ressource
// ============================================================

void demo_custom_deleter() {
    cout << "\n--- Demo 4 : Custom deleter ---" << endl;

    // Deleter qui appelle une fonction de cleanup avant delete
    auto custom_close = [](Handle* h) {
        cout << "  [CUSTOM DELETER] Flush buffer avant fermeture de fd=" << h->getFd() << endl;
        cout << "  [CUSTOM DELETER] Notification au serveur : closing fd=" << h->getFd() << endl;
        delete h;
    };

    {
        unique_ptr<Handle, decltype(custom_close)>
            raw_conn(new Handle(11, "raw://0.0.0.0:31337"), custom_close);

        raw_conn->write("PAYLOAD 0x41414141");
        cout << "  [raw_conn sort de scope -> custom deleter appele]" << endl;
    }
}

// ============================================================
// 5. Pool de handles avec unique_ptr
// ============================================================

void demo_pool() {
    cout << "\n--- Demo 5 : Pool de handles ---" << endl;

    vector<unique_ptr<Handle>> pool;
    pool.reserve(4);
    pool.push_back(make_unique<Handle>(20, "worker-0"));
    pool.push_back(make_unique<Handle>(21, "worker-1"));
    pool.push_back(make_unique<Handle>(22, "worker-2"));
    pool.push_back(make_unique<Handle>(23, "worker-3"));

    cout << "  Pool de " << pool.size() << " handles operationnels." << endl;

    for (const auto& h : pool) {
        h->write("PING");
    }

    // Libere le handle 21 (compromis)
    pool.erase(pool.begin() + 1);
    cout << "  Handle worker-1 ferme (compromis). Pool : " << pool.size() << " handles." << endl;

    cout << "  [pool sort de scope -> tous les handles fermes]" << endl;
}

int main() {
    cout << "=== Challenge : Gestion de Handles avec Smart Pointers ===" << endl;

    demo_unique();
    demo_shared();
    demo_weak();
    demo_custom_deleter();
    demo_pool();

    cout << "\n=== Bilan des ressources ===" << endl;
    g_stats.print();

    return 0;
}
