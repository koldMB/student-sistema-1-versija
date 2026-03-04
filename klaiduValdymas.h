#ifndef STUDENTU_SISTEMA_KLAIDUVALDYMAS_H
#define STUDENTU_SISTEMA_KLAIDUVALDYMAS_H

#include <iostream>
#include <stdexcept>
#include <future>
#include <string>
#include <optional>

using std::cerr;

class AllExceptionsHandler {
public:
    // Run a function and catch all standard exceptions with default messages
    template<typename Func>
    static void CatchAll(Func&& func) {
        try {
            func();
        }
        catch (const std::bad_alloc&) {
            cerr << "bad_alloc: atminties paskirstymas nepavyko" << std::endl;
            cerr.flush();
            exit(-1);
        }
        catch (const std::ios_base::failure&) {
            cerr << "ios_base::failure: įvesties/išvesties operacija nepavyko" << std::endl;
            cerr.flush();
            exit(-2);
        }
        catch (const std::system_error&) {
            cerr << "system_error: sistemos kvietimas nepavyko" << std::endl;
            cerr.flush();
            exit(-3);
        }
        catch (const std::future_error&) {
            cerr << "future_error: klaida su future/promise" << std::endl;
            cerr.flush();
            exit(-4);
        }
        catch (const std::logic_error&) {
            cerr << "logic_error: logikos pažeidimas" << std::endl;
            cerr.flush();
            exit(-5);
        }
        catch (const std::runtime_error& e) {
            cerr << "runtime_error: " << e.what() << std::endl;
            cerr.flush();
            exit(-6);
        }
        catch (const std::exception& e) {
            cerr << "std::exception: " << e.what() << std::endl;
            cerr.flush();
            exit(-7);
        }
        catch (...) {
            cerr << "Nežinoma klaida" << std::endl;
            cerr.flush();
            exit(-8);
        }
    }

    // Try to convert string to int, returns std::optional
    template<typename T = int>
    static std::optional<T> TryStoI(const std::string& s) {
        try {
            return std::stoi(s);
        }
        catch (const std::invalid_argument&) {
            return std::nullopt;
        }
        catch (const std::out_of_range&) {
            return std::nullopt;
        }
    }

    // Throw a runtime_error with default message
    static void ThrowRuntimeError() {
        throw std::runtime_error("runtime_error: vykdymo klaida");
        exit(-6);
    }
};

#endif //STUDENTU_SISTEMA_KLAIDUVALDYMAS_H