#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Match.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Match::Match(Object* expression, Triple* rules)
        : _expression {expression}
        , _rules {rules}
    {}

    Object* Match::eval(Evaluator* etor) {
        Object* exprValue = etor->evalExpr(_expression);
        Triple* rules = _rules;
        Triple* env = etor->environment();
        Object* value;
        if (!rules->matchLocate(exprValue, value, env)) {
            throwException("Match::eval", "Argument mismatch", new Array({exprValue, this}));
        }
        return value;
    }

    void Match::showOn(std::ostream& ostream) const {
        ostream << "match " << _expression << " in ";
        _rules->showOnWith(ostream, " | ");
        ostream << " end";
    }

    TypeId Match::typeId() const {
        return TypeId::E_MATCH;
    }

}