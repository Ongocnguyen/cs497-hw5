#include <cassert>
#include <plx/expr/Identifier.hpp>
#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Function.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {
    Closure::Closure(List* parameters, Object* body, Triple* lexicalEnvironment)
        : _parameters {parameters}
        , _body {body}
        , _lexicalEnvironment {lexicalEnvironment}
    {}

    Object* Closure::apply(Evaluator* etor, List* arguments) {
        Triple* savedEnv = etor->environment();
        List* parameters = _parameters;
        List* Argument = arguments;
        Triple* newEnv = _lexicalEnvironment;
     while (parameters && Argument) {
        Object* param = parameters->first();
        Object* arg = Argument->first();
        newEnv = new Triple(param, arg, newEnv);
        parameters = parameters->restAsList();
        Argument = Argument->restAsList();
    }
    etor->setEnvironment(newEnv);
    Object* result = _body->eval(etor);
    etor->setEnvironment(savedEnv);

    return result;
}

    void Closure::showOn(std::ostream& ostream) const {
        ostream << "Closure with parameters: ";
    _parameters->showOn(ostream);
    ostream << ", body: " << _body;
    ostream << ", lexical environment: " << _lexicalEnvironment;
    }

    TypeId Closure::typeId() const {
        return TypeId::D_CLOSURE;
    }

}