#include <cassert>

#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Throw.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Throw::Throw(Object* expr)
        : _expr {expr}
    {}

    Object* Throw::eval(Evaluator* etor) {
        (void)etor;
        throw _expr;
    }

    void Throw::showOn(std::ostream& ostream) const {
        ostream << "throw " << _expr;
    }

    TypeId Throw::typeId() const {
        return TypeId::E_THROW;
    }

}
