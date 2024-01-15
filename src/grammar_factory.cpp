#include "headers/grammar_factory.hpp"
#include "headers/grammar_1.hpp"
#include "headers/grammar_2.hpp"
#include "headers/grammar_3.hpp"
#include "headers/grammar_4.hpp"
#include "headers/grammar_5.hpp"
#include "headers/grammar_6.hpp"


Grammar* GrammarFactory::CreateGrammar(unsigned grammarNumber) const
{
    switch (grammarNumber) {
        case 1: {
            return new Grammar1();
        }
        case 2: {
            return new Grammar2();
        }
        case 3: {
            return new Grammar3();
        }
        case 4: {
            return new Grammar4();
        }
        case 5: {
            return new Grammar5();
        }
        case 6: {
            return new Grammar6();
        }
        default:
            // throw new InvalidGrammarException();
            return nullptr;
    }
}