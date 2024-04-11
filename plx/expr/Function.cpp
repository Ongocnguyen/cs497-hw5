#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Function.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Function::Function(List* parameters, Object* body)
        : _parameters {parameters}
        , _body {body}
    {}

    Object* Function::eval(Evaluator* etor) {
    Triple* savedEnv = etor->environment();
    Triple* funcEnv = new Triple();
    //Bind parameters to their values in the new environment
    List* parameters = _parameters;
    Object* body = _body;
    while (parameters != nullptr) {
        Object* param = parameters->first();
        // Get the value for the parameter from the evaluator's environment
        Object* value = etor->evalExpr(param);
        // Bind the parameter to its value in the function's environment
        funcEnv = etor->bind(param, value);
        // Move to the next parameter
        parameters = parameters->restAsList();
    }
    //Evaluate the body of the function in the new environment
    Object* result = etor->evalExpr(body, funcEnv);
    etor->setEnvironment(savedEnv);
    return result;
}

    void Function::showOn(std::ostream& ostream) const {
        (void)ostream;
    }

    TypeId Function::typeId() const {
        return TypeId::E_FUNCTION;
    }

}