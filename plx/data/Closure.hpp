#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;
    class Triple;
    class Function;

    class Closure : public Object {
    public:
    Closure(List* parameters, Object* body, Triple* lexicalEnvironment);

        // Overridden functions --------------------------------------------

        Object* apply(Evaluator* etor, List* arguments) override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
    List* _parameters;
    Object* _body;
    Triple* _lexicalEnvironment;
    };

}
