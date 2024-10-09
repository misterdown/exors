#ifndef EXORS_HPP_
#define EXORS_HPP_

#if (!defined EXORS_DEFAULT_CONTAINER)
#   include <vector>
#   define EXORS_DEFAULT_CONTAINER std::vector
#endif //!defined EXORS_DEFAULT_CONTAINER

#if (!defined EXORS_DEFAULT_STRING)
#   include <string>
#   define EXORS_DEFAULT_STRING std::string
#endif //!defined EXORS_DEFAULT_STRING

#if (!defined EXORS_MOVE)
#   include <utility>
#   define EXORS_MOVE std::move
#endif //!defined EXORS_MOVE

#if (!defined EXORS_SIZE_TTPE)
#   include <cstdint>
#   define EXORS_SIZE_TTPE std::size_t
#endif //!defined EXORS_SIZE_TTPE

#if (!defined EXORS_STRING_TO_DOUBLE)
#   include <string>
#   define EXORS_STRING_TO_DOUBLE std::stod
#endif //!defined EXORS_STRING_TO_DOUBLE

#if (!defined EXORS_TO_STRING)
#   include <string>
#   define EXORS_TO_STRING std::to_string
#endif //!defined EXORS_TO_STRING

#if (!defined EXORS_ASSERT)
#   include <cassert>
#   define EXORS_ASSERT assert
#endif //!defined EXORS_ASSERT

namespace exors {
    /*
        solver interface:
            expression operator(const expression&) const;
    */
    template<template<class...> class ContainerT_ = EXORS_DEFAULT_CONTAINER, class StringT_ = EXORS_DEFAULT_STRING>
    struct expression_t {
        public:
        StringT_ name; // or a value for primary expressions
        ContainerT_<expression_t> expressions;

        public:
        expression_t() {

        }
        expression_t(const StringT_& name) : name(name) {

        }
        expression_t(const StringT_& name, const EXORS_DEFAULT_CONTAINER<expression_t>& subs) : name(name), expressions(subs) {

        }

        public:
        bool is_primary() const {
            return expressions.empty();
        }

        public:
        void add_subexpression(const expression_t& subexpr) {
            expressions.emplace_back(subexpr);
        }
        void add_subexpression(expression_t&& subexpr) {
            expressions.emplace_back(EXORS_MOVE(subexpr));
        }
    };

    typedef expression_t<> expression;

    template<template<class...> class ContainerT_ = EXORS_DEFAULT_CONTAINER, class StringT_ = EXORS_DEFAULT_STRING>
    expression_t<ContainerT_, StringT_> calculator(const expression_t<ContainerT_, StringT_>& expr) {
        typedef expression_t<ContainerT_, StringT_> expression_type;
        const auto plusSolver = [](const expression_type& expr1, const expression_type& expr2) {
            EXORS_ASSERT(expr1.is_primary());
            EXORS_ASSERT(expr2.is_primary());
            
            const double result = EXORS_STRING_TO_DOUBLE(expr1.name) + EXORS_STRING_TO_DOUBLE(expr2.name);
            return expression_type(EXORS_TO_STRING(result));
        };
        const auto minusSolver = [](const expression_type& expr1, const expression_type& expr2) {
            EXORS_ASSERT(expr1.is_primary());
            EXORS_ASSERT(expr2.is_primary());

            const double result = EXORS_STRING_TO_DOUBLE(expr1.name) - EXORS_STRING_TO_DOUBLE(expr2.name);
            return expression_type(EXORS_TO_STRING(result));
        };
        const auto mutiplicationSolver = [](const expression_type& expr1, const expression_type& expr2) {
            EXORS_ASSERT(expr1.is_primary());
            EXORS_ASSERT(expr2.is_primary());

            const double result = EXORS_STRING_TO_DOUBLE(expr1.name) * EXORS_STRING_TO_DOUBLE(expr2.name);
            return expression_type(EXORS_TO_STRING(result));
        };
        const auto divisionSolver = [](const expression_type& expr1, const expression_type& expr2) {
            EXORS_ASSERT(expr1.is_primary());
            EXORS_ASSERT(expr2.is_primary());

            const double result = EXORS_STRING_TO_DOUBLE(expr1.name) / EXORS_STRING_TO_DOUBLE(expr2.name);
            return expression_type(EXORS_TO_STRING(result));
        };
        /*const auto isNumber = [](const expression& expr) {
            for (auto i : expr.name) {
                if (!std::isdigit(i) && i != (EXORS_DEFAULT_STRING::value_type)'.')
                    return false;
            }
            return true;
        };*/

        // recursion :(

        if (expr.is_primary()) {
            return expr;
        }
        const auto& first =  expr.expressions[0];
        const auto& second = expr.expressions[1];

        if (expr.name == "+") {
            return plusSolver(
                first.is_primary() ? first : calculator(first),
                second.is_primary() ? second : calculator(second));

        } else if (expr.name == "-") {
            return minusSolver(
                first.is_primary() ? first : calculator(first),
                second.is_primary() ? second : calculator(second));

        } else if (expr.name == "*") {
            return mutiplicationSolver(
                first.is_primary() ? first : calculator(first),
                second.is_primary() ? second : calculator(second));

        } else if (expr.name == "/") {
            return divisionSolver(
                first.is_primary() ? first : calculator(first),
                second.is_primary() ? second : calculator(second));

        } else {
            EXORS_ASSERT(false);
        }

        return expr;
    }
};

#endif // ifndef EXORS_HPP_