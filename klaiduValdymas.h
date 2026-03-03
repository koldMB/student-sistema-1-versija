#ifndef STUDENTU_SISTEMA_KLAIDUVALDYMAS_H
#define STUDENTU_SISTEMA_KLAIDUVALDYMAS_H

#include <functional>

class AllExceptionsHandler {
public:
    // Run a function and catch all standard exceptions with default messages
    static void CatchAll(const std::function<void()>& func);

    // Throw a runtime_error with default message
    static void ThrowRuntimeError();
};

#endif //STUDENTU_SISTEMA_KLAIDUVALDYMAS_H