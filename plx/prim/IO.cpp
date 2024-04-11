#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {
    namespace Prim_IO {

        Object* display(Evaluator* etor, List* args) {
            List* argVals = evalArgs(etor, args);
            while (!argVals->isEmpty()) {
                Object* arg = argVals->first();
                arg->displayOn(std::cout);
                argVals = argVals->restAsList();
            }
            return GLOBALS->NilObject();
        }

        Object* nl(Evaluator* etor, List* args) {
           const std::string NL_PRIM_NAME = "nl";
           evalNArgs(NL_PRIM_NAME, etor, args, {});
            std::cout << std::endl;
            return GLOBALS->NilObject();
        }


        Object* readLine(Evaluator* etor, List* args) {
            const std::string READLINE_PRIM_NAME = "readLine";
            evalNArgs(READLINE_PRIM_NAME, etor, args, {});
            std::string input;
            std::getline(std::cin, input);
            return new String(input);
        }

        Object* show(Evaluator* etor, List* args) {
            const std::string SHOW_PRIM_NAME = "show";
            evalNArgs(SHOW_PRIM_NAME, etor, args, {});
            while (!args->isEmpty()) {
                Object* arg = etor->evalExpr(args->first());
               arg->showOn(std::cout);
                args = args->restAsList();
            }
            return GLOBALS->NilObject();
        }
    }
}

