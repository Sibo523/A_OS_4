#include <iostream>
#include <mutex>

// Singleton Abstract Base Class
class Singleton {
protected:
    Singleton() = default;
    virtual ~Singleton() = default;

public:
    static Singleton& getInstance() {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        return getInstanceImpl();
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    virtual Singleton& getInstanceImpl() = 0;
};

// Concrete Singleton class
class ConcreteSingleton : public Singleton {
protected:
    ConcreteSingleton() = default;

    Singleton& getInstanceImpl() override {
        static ConcreteSingleton instance;
        return instance;
    }

public:
    void doSomething() {
        std::cout << "ConcreteSingleton is doing something." << std::endl;
    }
};

// Guard (Scope Mutex) Class
class Guard {
public:
    explicit Guard(std::mutex& mtx)
        : m_mutex(mtx) {
        m_mutex.lock();
    }

    ~Guard() {
        m_mutex.unlock();
    }

    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;

private:
    std::mutex& m_mutex;
};

// Main function to demonstrate usage
int main() {
    // Using the Singleton
    ConcreteSingleton& instance = static_cast<ConcreteSingleton&>(ConcreteSingleton::getInstance());
    instance.doSomething();

    // Using the Guard
    std::mutex exampleMutex;
    {
        Guard lock(exampleMutex);
        std::cout << "This section is protected by the Guard." << std::endl;
    }
    std::cout << "The Guard has released the mutex." << std::endl;

    return 0;
}