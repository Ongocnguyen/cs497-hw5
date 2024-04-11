#include <cassert>

#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Apply.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {
    
    Apply::Apply(Object* abstractionObj, List* arguments) 
    : _abstractionObj {abstractionObj}
    , _arguments {arguments}
    {}

Object* Apply::eval(Evaluator* etor) {
    Triple* savedEnv = etor->environment();

    // Evaluate the abstraction object
    Object* abstractionResult = _abstractionObj->eval(etor);
    List* argumentsList = _arguments;
    while (!argumentsList->isEmpty()) {
        argumentsList->first()->eval(etor);
        argumentsList = argumentsList->restAsList();
    }

    // Apply the abstraction to the evaluated arguments
    Object* result = abstractionResult->apply(etor, _arguments);
    // Restore the environment
    etor->setEnvironment(savedEnv);
    return result;
}

    void Apply::showOn(std::ostream& ostream) const {
    switch (_abstractionObj->typeId()) {
        case TypeId::D_CLOSURE:
        case TypeId::E_FUNCTION:
        case TypeId::E_NAMEDFUNCTION:
            ostream << '(';
            _abstractionObj->showOn(ostream);  // Output content of _abstractionObj
            ostream << ')';
            break;
        default:
            _abstractionObj->showOn(ostream);  // Output content of _abstractionObj
            break;
    }
    _arguments->showOnWith(ostream, "(", ", ", ")");
}

    TypeId Apply::typeId() const {
        return TypeId::E_APPLY;
    }

}

