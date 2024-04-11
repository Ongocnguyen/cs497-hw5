#include <cassert>

#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Do.hpp>
#include <plx/expr/Let.hpp>
#include <plx/expr/LetIn.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    LetIn::LetIn(Triple* bindings, Object* body)
        : _let {new Let(bindings)}
        , _body {body}
    {}

    Object* LetIn::eval(Evaluator* etor) {
        Triple* savedEnv = etor->environment();
        etor->evalExpr(_let);
        Object* value = etor->evalExpr(_body);
        etor->setEnvironment(savedEnv);
        return value;
    }

    void LetIn::showOn(std::ostream& ostream) const {
        ostream << _let
                << " in "
                << _body;
    }

    TypeId LetIn::typeId() const {
        return TypeId::E_LETIN;
    }

}