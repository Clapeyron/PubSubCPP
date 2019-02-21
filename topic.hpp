#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <memory>
#include <vector>
#include <cerrno>

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )

#ifndef PUBSUBCPP_TOPIC_H
#define PUBSUBCPP_TOPIC_H


#define _enable_std_make_unique

namespace topic {
    volatile bool interrupted = false;
    void signal_handler(int i){
        interrupted = true;
    }
    void init_system(){
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, signal_handler);
        signal(SIGTERM, signal_handler);
        signal(SIGKILL, signal_handler);
        signal(SIGSTOP, signal_handler);
    }
    using ui = unsigned long int;

    bool Err(const std::string &str) {
        std::cout << str << std::endl;
        return false;
    }

    class SharedMemory {
    public:
        SharedMemory(const std::string &name, ui size) {
            this->name = name;
            this->fd = -1;
            this->size = size;
            this->data = MAP_FAILED;
        }

        bool exists() {
            if (fd >= 0) return true;
            fd = shm_open(name.c_str(), O_RDWR, 0777);
            if (fd < 0) return false;
            ::close(fd);
            return true;
        }

        bool create() {
            fd = shm_open(name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0777);
            if (fd < 0) return false;
            DEBUG_MSG("Truncate " << size);
            ftruncate(fd, size);
            ::close(fd);
            return true;
        }

        bool open(bool ign_size) {
            if (MAP_FAILED != data) return true;
            if (!exists()) return Err("Shared memory doesn't exist");
            fd = shm_open(name.c_str(), O_RDWR, 0777);
            if (fd < 0) return false;
            {
                struct stat info;
                fstat(fd, &info);
                if (info.st_size != size) {
                    if (!ign_size) {
                        ::close(fd);
                        return Err("Shared memory size doesn't match");
                    } else size = info.st_size;
                }
            }
            data = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            return MAP_FAILED != data;
        }

        bool is_open() {
            return MAP_FAILED != data;
        }

        bool close() {
            if (!is_open()) return true;
            munmap(data, size);
            ::close(fd);
            data = MAP_FAILED;
            fd = -1;
            return true;
        }

        bool remove() {
            shm_unlink(name.c_str());
            return true;
        }

        void *data;
        std::string name;
        ui size;
        int fd = -1;

        friend class Topic;
    };

    using Shm = std::unique_ptr<SharedMemory>;

    Shm ShmMake(const std::string &name, ui size) {
        return std::make_unique<SharedMemory>(name, size);
    }

    class Semaphore {
    public:
        explicit Semaphore(const std::string &name) {
            this->name = name;
            this->sem = SEM_FAILED;
        }

        bool exists() {
            if (sem != SEM_FAILED) return true;
            sem = sem_open(name.c_str(), O_RDWR);
            if (SEM_FAILED == sem) return false;
            sem_close(sem);
            sem = SEM_FAILED;
            return true;
        }

        bool create(int val) {
            sem = sem_open(name.c_str(), O_RDWR | O_CREAT | O_EXCL, 0777, val);
            if (SEM_FAILED == sem) return Err("Cann't create semaphore: error in sem_open");
            sem_close(sem);
            sem = SEM_FAILED;
            return true;
        }

        bool open() {
            if (SEM_FAILED != sem) return true;
            if (!exists()) return Err("Semaphore doesn't exist");
            sem = sem_open(name.c_str(), O_RDWR);
            return SEM_FAILED != sem;
        }

        bool is_open() {
            return SEM_FAILED != sem;
        }

        bool close() {
            if (!is_open()) return true;
            sem_close(sem);
            sem = SEM_FAILED;
            return true;
        }

        bool remove() {
            sem_unlink(name.c_str());
            return true;
        }

        sem_t *sem;
        std::string name;
    };

    using Sem = std::unique_ptr<Semaphore>;

    Sem SemMake(const std::string &name) {
        return std::make_unique<Semaphore>(name);
    }

    class Lock {
    public:
        explicit Lock(sem_t *sem) {
            this->sem = sem;
            sem_wait(sem);
        }

        ~Lock() {
            sem_post(sem);
        }

        sem_t *sem;
    };

    class ReadersLock {
    public:
        ReadersLock(sem_t *sem, ui *counter, sem_t *cond) {
            this->counter = counter;
            this->cond = cond;
            this->sem = sem;
            auto l = Lock(sem);
            DEBUG_MSG(" Rcounter(c0): " << *counter);
            if (1 == ++ *counter) {
                DEBUG_MSG("1reader");
                sem_wait(cond);
            }
            DEBUG_MSG("Rcounter(c1): " << *counter);
        }

        ~ReadersLock() {
            auto l = Lock(sem);
            DEBUG_MSG("Rcounter(d0): " << *counter);
            if (0 == -- *counter) {
                DEBUG_MSG("0reader");
                sem_post(cond);
            }
           DEBUG_MSG("Rcounter(d1): " << *counter);
        }

        sem_t *sem, *cond;
        ui *counter;
    };

    class WriterLock {
    public:
        WriterLock(sem_t *sem, ui *counter, sem_t **lim, ui lim_count) {
            this->lim = lim;
            auto l = Lock(sem);
            pos = (*counter)++;
            DEBUG_MSG("Writer pos: " << pos);
            *counter %= lim_count;
            DEBUG_MSG("Next: " << *counter);
            sem_wait(lim[*counter]);
        }

        ~WriterLock() {
            DEBUG_MSG("Writer sem_post:" << pos);
            sem_post(lim[pos]);
        }

        sem_t **lim;
        ui pos;
    };

    class SemaphoreRange {
    public:
        explicit SemaphoreRange(ui count) {
            this->count = count;
            sem = (sem_t **) malloc(count * sizeof(sem_t *));
        }

        ~SemaphoreRange() {
            free(sem);
        }

        ui count;
        sem_t **sem;
    };

    using SemRange = std::unique_ptr<SemaphoreRange>;

    SemRange SemRangeMake(ui count) {
        return std::make_unique<SemaphoreRange>(count);
    }


    class Topic {
    public:
        using Top = std::unique_ptr<Topic>;

        static bool remove(const std::string &name) {
            auto t = std::make_unique<Topic>(name, 0, 0);
            return t->remove();
        }

        static Top spawn(const std::string &name, ui msg_size, ui msg_count) {
            auto t = std::make_unique<Topic>(name, msg_size, msg_count);
            if (t->start(false, false, false)) return t;
            else return nullptr;
        }

        static Top spawn(const std::string &name, ui msg_size) {
            auto t = std::make_unique<Topic>(name, msg_size, 0);
            if (t->start(false, false, true)) return t;
            else return nullptr;
        }

        static Top spawn_create(const std::string &name, ui msg_size, ui msg_count) {
            auto t = std::make_unique<Topic>(name, msg_size, msg_count);
            if (t->start(true, false, false)) return t;
            else return nullptr;
        }

        static Top spawn(const std::string &name) {
            auto t = std::make_unique<Topic>(name, 0, 0);
            if (t == nullptr) return nullptr;
            if (t->start(false, true, true)) return t;
            else return nullptr;
        }

        void pub(void *msg) {
            auto l = WriterLock(nlock, WposSRC, wlocks->sem, msg_count);
            Wpos = l.pos;
            memcpy(data[Wpos], msg, msg_size);
        }

        void sub(void *msg) {
            auto l = ReadersLock(rlocks->sem[Rpos], Rcounters[Rpos], wlocks->sem[Rpos]);
            memcpy(msg, data[Rpos], msg_size);
            Rpos = (Rpos + 1) % msg_count;
        }

        ui get_msg_size() {
            return msg_size;
        }

        ui get_msg_count() {
            return msg_count;
        }

        ui get_shmem_size() {
            return full_size;
        }

        bool is_ready() {
            return steady;
        }

        const std::string &get_name() {
            return name;
        }

        Topic(const std::string &name, ui msg_size, ui msg_count) {
            init_system();
            this->name = name;
            this->msg_size = msg_size;
            this->msg_count = msg_count;
            full_size = DATA_START + (msg_size + UI_SZ) * msg_count;
            DEBUG_MSG("Full size " << full_size);
            memory = ShmMake(name, full_size);
        }

        struct Header {
            ui msg_size;
            ui msg_count;
            ui writer_pos;
        };

        static const ui DATA_START = 32;
        static const ui UI_SZ = sizeof(ui);
        static const ui HDR_SZ = sizeof(Header);
    private:
        bool remove() {
            if (semN != nullptr) semN->remove();
            for (auto i = semW.begin(); i != semW.end(); i++) i->get()->remove();
            for (auto i = semR.begin(); i != semR.end(); i++) i->get()->remove();
            if (memory != nullptr) memory->remove();
            return true;
        }

        bool start(bool create, bool ign_size, bool ign_count) {
            if (steady) return true;
            char *mp;
            semN = SemMake(name + "--n");
            semR.clear();
            semW.clear();
            for (ui i = 0; i < msg_count; i++) semR.push_back(SemMake(name + "--r" + std::to_string(i)));
            for (ui i = 0; i < msg_count; i++) semW.push_back(SemMake(name + "--w" + std::to_string(i)));
            bool existed = false;
            if (!memory->exists()) {
                if (!create) return Err("Topic doesn't exist; do nothing.");
                if (!memory->create()) return Err("Cann't create topic.");
                if (!memory->open(false)) return Err("Topic created, but errors occured while opening");
                mp = (char *) memory->data;
                auto hdr = (Header *) mp;
                hdr->msg_count = msg_count;
                hdr->msg_size = msg_size;
                hdr->writer_pos = 0;
                WposSRC = &(hdr->writer_pos);
                Rpos = 0;
                create_sems();
            } else {
                existed = true;
                if (!memory->open(true)) return Err("Topic existed, but errors occured while opening");
                mp = (char *) memory->data;
                auto hdr = (Header *) mp;
                if (msg_size != hdr->msg_size) {
                    if (!ign_size) return Err("Proposed message size doesn't match existing topic message size");
                    msg_size = hdr->msg_size;
                }
                if (msg_count != hdr->msg_count) {
                    if (!ign_count) return Err("Proposed message count doesn't match existing topic message count");
                    msg_count = hdr->msg_count;
                }
                WposSRC = &(hdr->writer_pos);
                Rpos = 0;
            }
            if (msg_size <= 0) return Err("Message size should be > 0");
            if (msg_count <= 0) return Err("Message count should be > 0");
            full_size = memory->size;
            open_sems();
            char *mpd = mp + DATA_START;
            data.clear();
            Rcounters.clear();
            for (int i = 0; i < msg_count; i++) data.push_back(mpd + i*(msg_size + UI_SZ) + UI_SZ);
            for (int i = 0; i < msg_count; i++) Rcounters.push_back((ui *) (mpd + i*(msg_size + UI_SZ)));
            if (!existed) for (int i = 0; i < msg_count; i++) (*Rcounters[i]) = 0;
            return true;
        }

        bool create_sems() {
            semN->remove();
            if (!semN->create(1)) return Err("Cann't create W_POS semaphore");
            for (auto i = semR.begin(); i != semR.end(); i++) i->get()->remove();
            for (auto i = semW.begin(); i != semW.end(); i++) i->get()->remove();
            if ((!semR[0]->create(1)) || (!semW[0]->create(0))) return Err("Cann't create W/R semaphore(0)");
            for (int i = 1; i < msg_count; i++)
                if (!semR[i]->create(1) || !semW[i]->create(1)) return Err("Cann't create W/R semaphore(all)");
            return true;
        }

        bool open_sems() {
            if (!semN->open()) return Err("Cann't open W_POS semaphore");
            for (int i = 0; i < msg_count; i++)
                if ((!semR[i]->open()) || (!semW[i]->open())) return Err("Cann't open W/R semaphore");
            rlocks = SemRangeMake(msg_count);
            wlocks = SemRangeMake(msg_count);
            for (int i = 0; i < msg_count; i++) {
                rlocks->sem[i] = semR[i]->sem;
                wlocks->sem[i] = semW[i]->sem;
            }
            nlock = semN->sem;
            return true;
        }

        bool steady;
        Shm memory;
        Sem semN;
        std::vector<Sem> semW, semR;
        SemRange wlocks, rlocks;
        sem_t *nlock;
        std::vector<char *> data;
        std::vector<ui*> Rcounters;
        ui Wpos, *WposSRC, Rpos;
        std::string name;
        ui msg_size, msg_count, full_size;
    };
}

#endif //PUBSUBCPP2_TOPIC_H

#endif // DEBUG MSG