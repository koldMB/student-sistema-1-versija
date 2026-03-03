#include <iostream>
#include <stdexcept>
#include <future>
#include "klaiduValdymas.h"

void AllExceptionsHandler::CatchAll(const std::function<void()>& func) {
    try {
        func();
    }
    catch (const std::bad_alloc&) {
        std::cerr << "bad_alloc: atminties paskirstymas nepavyko" << std::endl;
    }
    catch (const std::ios_base::failure&) {
        std::cerr << "ios_base::failure: įvesties/išvesties operacija nepavyko" << std::endl;
    }
    catch (const std::system_error&) {
        std::cerr << "system_error: sistemos kvietimas nepavyko" << std::endl;
    }
    catch (const std::future_error&) {
        std::cerr << "future_error: klaida su future/promise" << std::endl;
    }
    catch (const std::logic_error&) {
        std::cerr << "logic_error: logikos pažeidimas" << std::endl;
    }
    catch (const std::runtime_error&) {
        std::cerr << "runtime_error: vykdymo klaida" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "std::exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Nežinoma klaida" << std::endl;
    }
}

void AllExceptionsHandler::ThrowRuntimeError() {
    throw std::runtime_error("runtime_error: vykdymo klaida");
}